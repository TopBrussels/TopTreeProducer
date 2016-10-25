import FWCore.ParameterSet.Config as cms


process = cms.Process("NewProcess")

#keep the logging output to a nice level
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

# Global geometry
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")

# good global tags can be found here. Beware that the default is MC which has to be updated for data!
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions
process.GlobalTag.globaltag = cms.string('80X_mcRun2_asymptotic_2016_miniAODv2_v1')


#
# Set up electron ID (VID framework)
#

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
# turn on VID producer, indicate data format  to be
# DataFormat.AOD or DataFormat.MiniAOD, as appropriate 
dataFormat = DataFormat.MiniAOD

switchOnVIDElectronIdProducer(process, dataFormat)

# define which IDs we want to produce
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring15_25ns_nonTrig_V1_cff']

#add them to the VID producer
for idmod in my_id_modules:
  setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)


process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(1000)
)

process.options = cms.untracked.PSet(
  SkipEvent = cms.untracked.vstring('ProductNotFound')
)

#Default Test sample
#process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('root://xrootd-cms.infn.it///store/data/Run2016B/SingleElectron/MINIAOD/PromptReco-v2/000/273/150/00000/0A6284C7-D719-E611-93E6-02163E01421D.root'))
#process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('root://xrootd-cms.infn.it///store/mc/RunIISpring16MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PUSpring16RAWAODSIM_reHLT_80X_mcRun2_asymptotic_v14_ext3-v1/00000/0064B539-803A-E611-BDEA-002590D0B060.root'))
#process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('root://xrootd-cms.infn.it///store/mc/RunIISpring16MiniAODv2/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/00000/04FB4BAA-3A33-E611-BC64-008CFA197A90.root'))
#process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('root://xrootd-cms.infn.it///store/mc/RunIIFall15MiniAODv2/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12_ext4-v1/00000/0007DBD0-2ED2-E511-AD0D-20CF3019DEF5.root'))
process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('root://xrootd-cms.infn.it///store/mc/RunIISpring16MiniAODv2/ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/MINIAODSIM/premix_withHLT_80X_mcRun2_asymptotic_v14_ext1-v1/80000/02236588-E871-E611-BDA6-D8D385AE85C0.root'))

#TTTT Test file for testing LHE weights
#process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/mc/RunIISpring15DR74/TTTT_TuneCUETP8M1_13TeV-amcatnlo-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9_ext1-v1/00000/0C216A04-5C5D-E511-AD98-D4AE529D9537.root'))

# data test file from 2015D:
#process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Run2015D/SingleMuon/MINIAOD/PromptReco-v3/000/256/629/00000/8EA4C10E-F35E-E511-ABF9-02163E014108.root'))


# skipEvents=cms.untracked.uint32(1000))

#Python Fragment containing all PU20bx25 filenames through xrootd
#process.load("TopBrussels.TopTreeProducer.miniAODTTbar_PU20bx25_files_cfi")

#Python Fragment containing all PU40bx50 filenames through xrootd
#process.load("TopBrussels.TopTreeProducer.miniAODTTbar_PU40bx50_files_cfi")


#Python Fragment containing TTTT NLO 13TeV miniAOD files (Produced by Jesse)
#process.load("TopBrussels.TopTreeProducer.FOURTOP_NLO_13TeV_miniAOD_Files_cfi")

#Python Fragment containing TTTT LO 13TeV miniAOD files (Produced by Jesse)
#process.load("TopBrussels.TopTreeProducer.FOURTOP_LO_13TeV_miniAOD_Files_cfi")

#Python Fragment containing TTJets NLO 13TeV miniAOD files (Produced by Jesse)
#process.load("TopBrussels.TopTreeProducer.TTJets_NLO_aMCNLO_PYTHIA8_13TeV_miniAOD_Files_cfi")



# reduce verbosity
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.analysis = cms.EDAnalyzer("TopTreeProducer",
  myConfig = cms.PSet(
    # Verbosite
    # 		0 = muet
    # 		1 = Number of evt every 100 evts
    # 		2 = Give the functions executed & nof objects build per event
    # 		3 = Liste of high level objects (jetss, muons, ...)
    # 		4 = List of all  objects
    # 		5 = Debug
    verbosity = cms.untracked.int32(1),
    
    # used in the electron to see if the magneticfield is taken from DCS or from IDEALMAGFIELDRECORD
    isData = cms.untracked.bool(False),
    
    # name of output root file
    RootFileName = cms.untracked.string("TOPTREE.root"),
    
    # What is written to rootuple
    doHLT = cms.untracked.bool(True),
    doMC = cms.untracked.bool(True),
    doPDFInfo = cms.untracked.bool(True),
    signalGenerator = cms.untracked.string('PYTHIA'),
#    signalGenerator = cms.untracked.string('ALPGEN'),
#    signalGenerator = cms.untracked.string('MADGRAPH'),
    
    doElectronMC = cms.untracked.bool(True),
    doMuonMC = cms.untracked.bool(True),
    doJetMC = cms.untracked.bool(True),
    doMETMC = cms.untracked.bool(True),
    doPhotonMC = cms.untracked.bool(True),
    doUnstablePartsMC = cms.untracked.bool(True),
    doMCAssociation = cms.untracked.bool(False),
    
    doPrimaryVertex = cms.untracked.bool(True),
    doGenJet = cms.untracked.bool(True),
    doPFJet = cms.untracked.bool(True),
    doFatJet = cms.untracked.bool(True),
    doMuon = cms.untracked.bool(True),
    doElectron = cms.untracked.bool(True),
    doPhoton = cms.untracked.bool(True),
    doPFMET = cms.untracked.bool(True),
    runSuperCluster = cms.untracked.bool(True),#True only if SuperCluster are stored
    doNPGenEvent = cms.untracked.bool(False),#put on True when running New Physics sample
    doLHEEventProd = cms.untracked.bool(True),
    doEventCleaningInfo = cms.untracked.bool(True), # only useful for data but protected for MC. Stores HBHE, HCalIso etc filter outputs as bools in TRootEvent
    
    conversionLikelihoodWeightsFile = cms.untracked.string('RecoEgamma/EgammaTools/data/TMVAnalysis_Likelihood.weights.txt'),
    
    
    # The PaticleTreeDrawer is not yet adapted to 76X TTP. Not sure if we still need this (Kevin and Seth, 13th jan 2016)
    # Draw MC particle tree
    drawMCTree = cms.untracked.bool(False),
    mcTreePrintP4 = cms.untracked.bool(False),
    mcTreePrintPtEtaPhi = cms.untracked.bool(False),
    mcTreePrintVertex = cms.untracked.bool(False),
    mcTreePrintStatus = cms.untracked.bool(False),
    mcTreePrintIndex = cms.untracked.bool(False),
    mcTreeStatus = cms.untracked.vint32( 3 ),	# accepted status codes
    
    
    # MC particles acceptance cuts
    electronMC_etaMax = cms.double(3.0),
    electronMC_ptMin = cms.double(10.0), #checking effect on filesize by tightening cuts here 2.0 -> 10.0
    muonMC_etaMax = cms.double(3.0),
    muonMC_ptMin = cms.double(10.0),  #checking effect on filesize by tightening cuts here 0.0 -> 10.0
    jetMC_etaMax = cms.double(6.0),
    jetMC_ptMin = cms.double(15.0), #checking effect on filesize by tightening cuts here 5.0 -> 15.0

    #lepton acceptance cuts
    electron_ptMin = cms.double(5.0),
    muon_ptMin = cms.double(5.0),
  ),
  
  
  #new for CMSSW76X and higher: all classes that are read from the event need to be registered in the constructor!
  #supposedly this is necessary in the case that the code is run on machines that use multi-threading.
  #It also allows the CMSSW compiler to optimise/speed up the code (or so the documentation says), by accessing collections that are used a lot or rarely with the consumesOften() and mayConsume() fuctions but consumes() will always work.
  #in the TopTreeProducer .py file these are all stored in the producersNames parameter set, so please add new objects there if you need them.
  producerNamesBookkeepingThreads = cms.PSet(
    vpfJetProducer = cms.untracked.vstring("slimmedJets"),
    vpfmetProducer = cms.untracked.vstring("slimmedMETs"),
    vmuonProducer = cms.untracked.vstring("slimmedMuons"),
    velectronProducer = cms.untracked.vstring("slimmedElectrons"),
    vphotonProducer = cms.untracked.vstring("slimmedPhotons"),#PhotonAnalyzer still has some getByLabels... (Kevin 14/01/2015)
    vfatJetProducer = cms.untracked.vstring("slimmedJetsAK8"),
    vgenJetProducer = cms.untracked.vstring("slimmedGenJets"),
    metfilterProducer = cms.untracked.InputTag("TriggerResults","","PAT"), # can also be RECO, depends on MiniAOD version!
    summaryHBHENoise = cms.untracked.InputTag("hcalnoise"),
    pileUpProducer = cms.untracked.InputTag("slimmedAddPileupInfo"),
    fixedGridRhoAll = cms.untracked.InputTag("fixedGridRhoAll"),
    fixedGridRhoFastjetAll = cms.untracked.InputTag("fixedGridRhoFastjetAll"),
    fixedGridRhoFastjetAllCalo = cms.untracked.InputTag("fixedGridRhoFastjetAllCalo"),
    fixedGridRhoFastjetCentralCalo = cms.untracked.InputTag("fixedGridRhoFastjetCentralCalo"),
    fixedGridRhoFastjetCentralChargedPileUp = cms.untracked.InputTag("fixedGridRhoFastjetCentralChargedPileUp"),
    fixedGridRhoFastjetCentralNeutral = cms.untracked.InputTag("fixedGridRhoFastjetCentralNeutral"),
    genEventInfoProduct = cms.untracked.InputTag("generator"),
    prunedGenParticles = cms.untracked.InputTag("prunedGenParticles"),
    lheproduct = cms.untracked.InputTag("externalLHEProducer"),
    
    primaryVertexProducer = cms.untracked.InputTag("offlineSlimmedPrimaryVertices"),
    offlineBeamSpot = cms.InputTag("offlineBeamSpot"),
    hltProducer1st = cms.InputTag("TriggerResults","","HLT"),
    hltProducer2nd = cms.InputTag("TriggerResults","","HLT2"),
    hltProducer3rd = cms.InputTag("TriggerResults","","RECO"),
    hltProducer4th = cms.InputTag("TriggerResults","","MINIAOD"),
    hltProducer5th = cms.InputTag("TriggerResults","","PAT"),
    electronMVAvaluesMapNonTrig = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring15NonTrig25nsV1Values"), #https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
    electronMVACategoriesNonTrig = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring15NonTrig25nsV1Categories"),
    #eleLooseIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring15-25ns-nonTrig-V1-wpLoose"), #Will only be available from CMSSW_8_1_X
    eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring15-25ns-nonTrig-V1-wp90"),
    eleTightIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring15-25ns-nonTrig-V1-wp80")
    
  )
                                
)

#process.TFileService = cms.Service("TFileService", fileName = cms.string('TFileTOPTREE.root') )

process.p = cms.Path(
  process.egmGsfElectronIDSequence*
  process.analysis
)
temp = process.dumpPython()
outputfile = file("expanded.py",'w')
outputfile.write(temp)
outputfile.close()
