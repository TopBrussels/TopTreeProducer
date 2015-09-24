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

#Data measurements from Summer11
process.load("RecoBTag.PerformanceDB.BTagPerformanceDB1107")
process.load("RecoBTag.PerformanceDB.PoolBTagPerformanceDB1107")

# good global tags can be found here. Beware that the default is MC which has to be updated for data!
# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFrontierConditions
process.GlobalTag.globaltag = cms.string('MCRUN2_74_V9')
# geometry needed for clustering and calo shapes variables
# process.load("RecoEcal.EgammaClusterProducers.geometryForClustering_cff")
# 3 folllowing config files included in RecoEcal.EgammaClusterProducers.geometryForClustering_cff
#process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")
#process.load("Geometry.CaloEventSetup.CaloGeometry_cfi")
#process.load("Geometry.CaloEventSetup.CaloTopology_cfi")

# ES cluster for pi0 discrimination variables
#process.load("RecoEcal.EgammaClusterProducers.preshowerClusterShape_cfi")

# pi0 discrimination variables
#process.load("RecoEcal.EgammaClusterProducers.piZeroDiscriminators_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
)

process.options = cms.untracked.PSet(
     SkipEvent = cms.untracked.vstring('ProductNotFound')
)


process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/mc/RunIISpring15DR74/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/00000/18E6854B-1809-E511-A405-0025905B8590.root'))

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
#		signalGenerator = cms.untracked.string('ALPGEN'),
#		signalGenerator = cms.untracked.string('MADGRAPH'),

		doElectronMC = cms.untracked.bool(True),
		doMuonMC = cms.untracked.bool(True),
		doJetMC = cms.untracked.bool(True),
		doMETMC = cms.untracked.bool(False),
		doPhotonMC = cms.untracked.bool(False),
		doUnstablePartsMC = cms.untracked.bool(True),
		doPrimaryVertex = cms.untracked.bool(True),
		runGeneralTracks = cms.untracked.bool(True),#true only if generalTracks are stored.
		doCaloJet = cms.untracked.bool(False),
		doGenJet = cms.untracked.bool(True),
		doCaloJetId = cms.untracked.bool(False),
		doPFJet = cms.untracked.bool(True),
         	doFatJet = cms.untracked.bool(True),
		doJPTJet = cms.untracked.bool(False),
		doJPTJetId = cms.untracked.bool(False),
		doMuon = cms.untracked.bool(True),
		doElectron = cms.untracked.bool(True),
         	doPhoton = cms.untracked.bool(False),
		runSuperCluster = cms.untracked.bool(True),#true only if SuperCluster are stored
		doCaloMET = cms.untracked.bool(False),
		doPFMET = cms.untracked.bool(True),
		doTCMET = cms.untracked.bool(False),
		doGenEvent = cms.untracked.bool(False),#put on False when running non-ttbar or when running toptree from reco
		doNPGenEvent = cms.untracked.bool(False),#put on True when running New Physics sample
		doSpinCorrGen = cms.untracked.bool(False),#put on True only if you need SpinCorrelation Variables
        	doLHEEventProd = cms.untracked.bool(True),#put on True only if you need SpinCorrelation Variables
		doSemiLepEvent = cms.untracked.bool(False),#put on True only if you need TtSemiLeptonicEvent Collection exist in PAT-uples (L2)

		conversionLikelihoodWeightsFile = cms.untracked.string('RecoEgamma/EgammaTools/data/TMVAnalysis_Likelihood.weights.txt'),



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
	),

	producersNames = cms.PSet(
		hltProducer1st = cms.InputTag("TriggerResults","","HLT"),
		hltProducer2nd = cms.InputTag("TriggerResults","","RECO"),
		hltProducer3rd = cms.InputTag("TriggerResults","","REDIGI"),
		hltProducer4th = cms.InputTag("TriggerResults","","REDIGI311X"),
		pileUpProducer = cms.InputTag("addPileupInfo"),
		genParticlesProducer = cms.InputTag("prunedGenParticles"),
                lheEventProductProducer = cms.InputTag("source"),
		primaryVertexProducer = cms.InputTag("offlineSlimmedPrimaryVertices"),
		vcaloJetProducer = cms.untracked.vstring("selectedPatJetsAK5Calo"),
		vgenJetProducer = cms.untracked.vstring("slimmedGenJets"),
		vpfJetProducer = cms.untracked.vstring("slimmedJets"),#,"selectedPatJetsPF2PATNoPFnoPU"),
		vfatJetProducer = cms.untracked.vstring("slimmedJetsAK8"),#,"selectedPatJetsPF2PATNoPFnoPU"),
		vJPTJetProducer = cms.untracked.vstring(""),
		vmuonProducer = cms.untracked.vstring("slimmedMuons"),#,"selectedPatMuonsPF2PATNoPFnoPU"),
		velectronProducer = cms.untracked.vstring("slimmedElectrons"),#,"selectedPatElectronsPF2PATNoPFnoPU"),
         	vphotonProducer = cms.untracked.vstring("slimmedPhotons"),
		CalometProducer = cms.InputTag("patMETs"),
		vpfmetProducer = cms.untracked.vstring("slimmedMETs"),#,"patType1CorrectedPFMetPF2PATNoPFnoPU"),
		TCmetProducer = cms.InputTag("patMETsTC"),
		genEventProducer = cms.InputTag("genEvt"),
		generalTrackLabel = cms.InputTag("generalTracks")
	)
)

#process.TFileService = cms.Service("TFileService", fileName = cms.string('TFileTOPTREE.root') )

process.p = cms.Path(process.analysis)
temp = process.dumpPython()
outputfile = file("expanded.py",'w')
outputfile.write(temp)
outputfile.close()
