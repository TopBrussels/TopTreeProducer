import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
import copy

##############################
###### Parameters ############
##############################

options = VarParsing ('python')

options.register('runOnData', False,
    VarParsing.multiplicity.singleton,
    VarParsing.varType.bool,
    "Run this on real data"
)

options.parseArguments()

import sys


process = cms.Process("NewProcess")

#keep the logging output to a nice level
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")

# Global geometry
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")

process.options   = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False),
    allowUnscheduled = cms.untracked.bool(True)	 # needed for ak10 computation (JMEAnalysis/JetToolbox)
)
process.MessageLogger.suppressWarning = cms.untracked.vstring(["JetPtMismatchAtLowPt","NullTransverseMomentum","MissingJetConstituent","MissingJetConstituent","JetMatchingFailed","JetPtMismatch"])
genParticleCollection = 'prunedGenParticles'
genJetCollection = 'slimmedGenJets'

# Supplies PDG ID to real name resolution of MC particles
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

# Ghost particle collection used for Hadron-Jet association 
# MUST use proper input particle collection
from PhysicsTools.JetMCAlgos.HadronAndPartonSelector_cfi import selectedHadronsAndPartons
process.selectedHadronsAndPartons = selectedHadronsAndPartons.clone(
    particles = genParticleCollection
)

# Input particle collection for matching to gen jets (partons + leptons) 
# MUST use use proper input jet collection: the jets to which hadrons should be associated
# rParam and jetAlgorithm MUST match those used for jets to be associated with hadrons
# More details on the tool: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideBTagMCTools#New_jet_flavour_definition
from PhysicsTools.JetMCAlgos.AK4PFJetsMCFlavourInfos_cfi import ak4JetFlavourInfos
process.genJetFlavourInfos = ak4JetFlavourInfos.clone(
    jets = genJetCollection,
)

# Plugin for analysing B hadrons
# MUST use the same particle collection as in selectedHadronsAndPartons
from PhysicsTools.JetMCAlgos.GenHFHadronMatcher_cff import matchGenBHadron
process.matchGenBHadron = matchGenBHadron.clone(
    genParticles = genParticleCollection,
    jetFlavourInfos = "genJetFlavourInfos"
)

# Plugin for analysing C hadrons
# MUST use the same particle collection as in selectedHadronsAndPartons
from PhysicsTools.JetMCAlgos.GenHFHadronMatcher_cff import matchGenCHadron
process.matchGenCHadron = matchGenCHadron.clone(
    genParticles = genParticleCollection,
    jetFlavourInfos = "genJetFlavourInfos"
)


# good global tags can be found here. Beware that the default is MC which has to be updated for data!
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions
process.GlobalTag.globaltag = cms.string('80X_mcRun2_asymptotic_2016_TrancheIV_v8')

process.load('RecoMET.METFilters.BadPFMuonFilter_cfi')
process.BadPFMuonFilter.muons = cms.InputTag("slimmedMuons")
process.BadPFMuonFilter.PFCandidates = cms.InputTag("packedPFCandidates")

process.load('RecoMET.METFilters.BadChargedCandidateFilter_cfi')
process.BadChargedCandidateFilter.muons = cms.InputTag("slimmedMuons")
process.BadChargedCandidateFilter.PFCandidates = cms.InputTag("packedPFCandidates")

#################################################
# Duplicate muon filter
#################################################
#see https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/2786.html
process.load('RecoMET.METFilters.badGlobalMuonTaggersMiniAOD_cff')

#################################################
# MET recalcualtion
#################################################
# see https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETUncertaintyPrescription#Instructions_for_8_0_X_X_26_patc
from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
#runMetCorAndUncFromMiniAOD(process,
#                           isData=options.runOnData,
#                           )
# If you would like to re-cluster and get the proper uncertainties
runMetCorAndUncFromMiniAOD(process,
                           isData=options.runOnData,
                           pfCandColl=cms.InputTag("packedPFCandidates"),
                           recoMetFromPFCs=True,
                           )
# If you would like to re-cluster both jets and met and get the proper uncertainties
#runMetCorAndUncFromMiniAOD(process,
#                           isData=options.runOnData,
#                           pfCandColl=cms.InputTag("packedPFCandidates"),
#                           recoMetFromPFCs=True,
#                           CHS = True, #This is an important step and determines what type of jets to be reclustered
#                           reclusterJets = True
#                           )

#################################################
# Apply the regression from a remote database: https://twiki.cern.ch/twiki/bin/viewauth/CMS/EGMRegression
# -> Later this regression will be directly introduced in the global tag -> KEEP POSTED ABOUT THIS CHANGE!!!!
#################################################
from EgammaAnalysis.ElectronTools.regressionWeights_cfi import regressionWeights
process = regressionWeights(process)

#################################################
# Applying EGM smearing for ICHEP dataset: https://twiki.cern.ch/twiki/bin/viewauth/CMS/EGMSmearer#How_to_apply_corrections_directl
#################################################
process.load('EgammaAnalysis.ElectronTools.calibratedElectronsRun2_cfi')

process.load('Configuration.StandardSequences.Services_cff')
process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
                  calibratedPatElectrons  = cms.PSet( initialSeed = cms.untracked.uint32(8675389),
                                                      engineName = cms.untracked.string('TRandom3'),
                                                      ),
                  calibratedPatPhotons    = cms.PSet( initialSeed = cms.untracked.uint32(8675389),
                                                      engineName = cms.untracked.string('TRandom3'),
                                                      ),
)



process.load('EgammaAnalysis.ElectronTools.regressionApplication_cff')
process.load('EgammaAnalysis.ElectronTools.calibratedPatElectronsRun2_cfi')

# Set the lines below to True or False depending if you are correcting the scale (data) or smearing the resolution (MC) 
process.calibratedPatElectrons.isMC = cms.bool(not options.runOnData)




#
# Set up electron ID (VID framework)
#

# egamma
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
switchOnVIDElectronIdProducer(process,DataFormat.MiniAOD)

# https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2
# https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2

my_id_modules = [
'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Summer16_80X_V1_cff',
'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff',
'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Spring16_GeneralPurpose_V1_cff'
]

for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

process.load("RecoEgamma.ElectronIdentification.ElectronMVAValueMapProducer_cfi")
process.load("RecoEgamma.ElectronIdentification.ElectronIDValueMapProducer_cfi")

process.selectedElectrons = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("calibratedPatElectrons"),
    cut = cms.string("pt>5 && abs(eta)")
)
process.egmGsfElectronIDs.physicsObjectSrc = cms.InputTag('selectedElectrons')
process.electronIDValueMapProducer.srcMiniAOD = cms.InputTag('selectedElectrons')
process.electronRegressionValueMapProducer.srcMiniAOD = cms.InputTag('selectedElectrons')
process.electronMVAValueMapProducer.srcMiniAOD = cms.InputTag('selectedElectrons')


#####################
# MET Significance  #
#####################
process.load("RecoMET/METProducers.METSignificance_cfi")
process.load("RecoMET/METProducers.METSignificanceParams_cfi")
from RecoMET.METProducers.testInputFiles_cff import recoMETtestInputFiles


#####################
# TOP Producer      #
#####################
process.mergedGenParticles = cms.EDProducer("MergedGenParticleProducer",
                    inputPruned = cms.InputTag("prunedGenParticles"),
                        inputPacked = cms.InputTag("packedGenParticles"),
)
from GeneratorInterface.RivetInterface.genParticles2HepMC_cfi import genParticles2HepMC
process.genParticles2HepMC = genParticles2HepMC.clone( genParticles = cms.InputTag("mergedGenParticles") )
process.load("TopQuarkAnalysis.TopEventProducers.producers.pseudoTop_cfi")
process.load('TopQuarkAnalysis.BFragmentationAnalyzer.bfragWgtProducer_cfi')

process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(1000)
)

process.options = cms.untracked.PSet(
  SkipEvent = cms.untracked.vstring('ProductNotFound')
)

if options.runOnData:
#  process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('root://xrootd-cms.infn.it///store/data/Run2016C/SingleElectron/MINIAOD/03Feb2017-v1/100000/02169BE7-81EB-E611-BB99-02163E0137CD.root'))
   process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch///store/data/Run2016C/SingleElectron/MINIAOD/03Feb2017-v1/100000/02169BE7-81EB-E611-BB99-02163E0137CD.root'))
else:
#Test sample MC (synch ex)
  process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring('root://xrootd-cms.infn.it///store/mc/RunIISummer16MiniAODv2/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/50000/0693E0E7-97BE-E611-B32F-0CC47A78A3D8.root'),
  )


# reduce verbosity
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.analysis = cms.EDAnalyzer("TopTreeProducer",
  myConfig = cms.PSet(
    # Verbosity
    # 		0 = muet
    # 		1 = Number of evt every 100 evts
    # 		2 = Give the functions executed & nof objects built per event
    # 		3 = List of high level objects (jets, muons, ...)
    # 		4 = List of all objects
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
    doGenTTXGenerator = cms.untracked.bool(True),
    
    doPrimaryVertex = cms.untracked.bool(True),
    doGenJet = cms.untracked.bool(True),
    doPFJet = cms.untracked.bool(True),
    doFatJet = cms.untracked.bool(True),
    doMuon = cms.untracked.bool(True),
    doElectron = cms.untracked.bool(True),
    doPhoton = cms.untracked.bool(False),
    doPFMET = cms.untracked.bool(True),
    runSuperCluster = cms.untracked.bool(True),#True only if SuperCluster are stored
    doNPGenEvent = cms.untracked.bool(False),#put on True when running New Physics sample
    doLHEEventProd = cms.untracked.bool(not options.runOnData),
    doEventCleaningInfo = cms.untracked.bool(True), # only useful for data but protected for MC. Stores HBHE, HCalIso etc filter outputs as bools in TRootEvent
    
   # conversionLikelihoodWeightsFile = cms.untracked.string('RecoEgamma/EgammaTools/data/TMVAnalysis_Likelihood.weights.txt'),
    
    
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
    
    # Lepton acceptance cuts
    electron_ptMin = cms.double(5.0),
    muon_ptMin = cms.double(5.0),


    genJets = cms.InputTag(genJetCollection),
    genBHadJetIndex = cms.InputTag("matchGenBHadron", "genBHadJetIndex"),
    genBHadFlavour = cms.InputTag("matchGenBHadron", "genBHadFlavour"),
    genBHadFromTopWeakDecay = cms.InputTag("matchGenBHadron", "genBHadFromTopWeakDecay"),
    genBHadPlusMothers = cms.InputTag("matchGenBHadron", "genBHadPlusMothers"),
    genBHadPlusMothersIndices = cms.InputTag("matchGenBHadron", "genBHadPlusMothersIndices"),
    genBHadIndex = cms.InputTag("matchGenBHadron", "genBHadIndex"),
    genBHadLeptonHadronIndex = cms.InputTag("matchGenBHadron", "genBHadLeptonHadronIndex"),
    genBHadLeptonViaTau = cms.InputTag("matchGenBHadron", "genBHadLeptonViaTau"),
    genCHadJetIndex = cms.InputTag("matchGenCHadron", "genCHadJetIndex"),
    genCHadFlavour = cms.InputTag("matchGenCHadron", "genCHadFlavour"),
    genCHadFromTopWeakDecay = cms.InputTag("matchGenCHadron", "genCHadFromTopWeakDecay"),
    genCHadBHadronId = cms.InputTag("matchGenCHadron", "genCHadBHadronId"),      

    # 80X bad (duplicate) global muon filter (see https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/2786.html)
    doBadMuonTagging = cms.untracked.bool(True),
    doCloneMuonTagging = cms.untracked.bool(True),


  ),
  
  
  #new for CMSSW76X and higher: all classes that are read from the event need to be registered in the constructor!
  #supposedly this is necessary in the case that the code is run on machines that use multi-threading.
  #It also allows the CMSSW compiler to optimise/speed up the code (or so the documentation says), by accessing collections that are used a lot or rarely with the consumesOften() and mayConsume() fuctions but consumes() will always work.
  #in the TopTreeProducer .py file these are all stored in the producersNames parameter set, so please add new objects there if you need them.
  producerNamesBookkeepingThreads = cms.PSet(
    vpfJetProducer = cms.untracked.vstring("slimmedJets"),
    vpfmetProducer = cms.untracked.vstring("slimmedMETs"),
    vpfmetProducerMuEGClean = cms.untracked.vstring("slimmedMETsMuEGClean"),
    vmuonProducer = cms.untracked.vstring("slimmedMuons"),
    velectronProducer_uncalibrated = cms.untracked.vstring("slimmedElectrons"),
    velectronProducer_calibrated = cms.untracked.vstring("selectedElectrons"),#This is implemented to apply 80X EGM calibration corrections to the electrons. Change to slimmedElectrons if those corrections are not necessary.
    vphotonProducer = cms.untracked.vstring("slimmedPhotons"),#PhotonAnalyzer still has some getByLabels... (Kevin 14/01/2016)
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

    eleMediumMVAIdMap        = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring16-GeneralPurpose-V1-wp90"),
    eleTightMVAIdMap         = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring16-GeneralPurpose-V1-wp80"),
    mvaValuesMap             = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Values"),
    mvaCategoriesMap         = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Categories"),

    eleVetoCBIdMap           = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-veto"),
    eleLooseCBIdMap          = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-loose"),
    eleMediumCBIdMap         = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-medium"),
    eleTightCBIdMap          = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Summer16-80X-V1-tight"),
    eleHEEPCBIdMap           = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV60"),

    BadMuonFilter              = cms.untracked.InputTag("BadPFMuonFilter"),
    BadChargedCandidateFilter  = cms.untracked.InputTag("BadChargedCandidateFilter"),

    BadGlobalMuonTagger        = cms.InputTag("badGlobalMuonTaggerMAOD","bad","NewProcess"),
    CloneGlobalMuonTagger        = cms.InputTag("cloneGlobalMuonTaggerMAOD","bad","NewProcess"),
  )
                                
)


if not options.runOnData:
  process.p = cms.Path(
    process.regressionApplication *
    process.calibratedPatElectrons *
    process.selectedElectrons *
    process.egmGsfElectronIDSequence *
    process.electronIDValueMapProducer *
    process.electronMVAValueMapProducer *
    process.METSignificance *
    process.BadPFMuonFilter *
    process.BadChargedCandidateFilter *
    process.selectedHadronsAndPartons *
    process.genJetFlavourInfos *
    process.matchGenBHadron *
    process.matchGenCHadron *
    process.fullPatMetSequence *
    cms.ignore(process.badGlobalMuonTaggerMAOD) * 
    cms.ignore(process.cloneGlobalMuonTaggerMAOD) *
    process.mergedGenParticles*process.genParticles2HepMC*process.pseudoTop*process.bfragWgtProducer*
    process.analysis
  )
else:
  process.p = cms.Path(
    process.regressionApplication *
    process.calibratedPatElectrons *
    process.selectedElectrons *
    process.egmGsfElectronIDSequence *
    process.electronIDValueMapProducer *
    process.electronMVAValueMapProducer *
    process.METSignificance *
    process.BadPFMuonFilter *
    process.BadChargedCandidateFilter *
    process.fullPatMetSequence *
    cms.ignore(process.badGlobalMuonTaggerMAOD) * 
    cms.ignore(process.cloneGlobalMuonTaggerMAOD) *
    process.analysis
  )

temp = process.dumpPython()
outputfile = file("expanded.py",'w')
outputfile.write(temp)
outputfile.close()

