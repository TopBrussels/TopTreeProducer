import FWCore.ParameterSet.Config as cms


process = cms.Process("NewProcess")

#keep the logging output to a nice level
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

# Global geometry
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

#Data measurements from Summer11
process.load("RecoBTag.PerformanceDB.BTagPerformanceDB1107")
process.load("RecoBTag.PerformanceDB.PoolBTagPerformanceDB1107")

process.GlobalTag.globaltag = cms.string('MCRUN2_74_V9A')
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
    input = cms.untracked.int32(10)
)

#process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('file:miniAOD_PAT.root'))

process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/mc/RunIISpring15DR74/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v1/50000/94B04F22-1EFE-E411-96AB-90B11C2CA412.root'))

#process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring('file:miniAOD-prod_PAT_1.root'))
#process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring('file:miniAOD-prod_PAT_387.root','file:miniAOD-prod_PAT_104.root','file:miniAOD-prod_PAT_105.root'))


#process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/mc/Fall14DR73/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/AODSIM/PFr1_Flat_20_50_50ns_GSFromFall14_MCRUN2_73_V11-v1/00000/000B17A2-E6E6-E411-B185-003048FFD740.root'))




# reduce verbosity
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.options = cms.untracked.PSet(SkipEvent = cms.untracked.vstring('ProductNotFound'))

process.analysis = cms.EDAnalyzer("TopTreeProducer",
	myConfig = cms.PSet(
		# Verbosite
		# 		0 = muet
 		# 		1 = Number of evt every 100 evts
 		# 		2 = Give the functions executed & nof objects build per event
 		# 		3 = Liste of high level objects (jetss, muons, ...)
 		# 		4 = List of all  objects
		# 		5 = Debug
 		verbosity = cms.untracked.int32(2),

		# used in the electron to see if the magneticfield is taken from DCS or from IDEALMAGFIELDRECORD
		isData = cms.untracked.bool(False),

		# name of output root file
		RootFileName = cms.untracked.string("TOPTREE.root"),

		# What is written to rootuple
		doHLT = cms.untracked.bool(False),
		doMC = cms.untracked.bool(True),
		doPDFInfo = cms.untracked.bool(True),
		signalGenerator = cms.untracked.string('PYTHIA'),
#		signalGenerator = cms.untracked.string('ALPGEN'),
#		signalGenerator = cms.untracked.string('MADGRAPH'),

		doElectronMC = cms.untracked.bool(True),
		doMuonMC = cms.untracked.bool(True),
		doJetMC = cms.untracked.bool(True),
		doMETMC = cms.untracked.bool(False),
		doPhotonMC = cms.untracked.bool(True),
		doUnstablePartsMC = cms.untracked.bool(True),
		doPrimaryVertex = cms.untracked.bool(True),
		runGeneralTracks = cms.untracked.bool(True),#true only if generalTracks are stored.
		doCaloJet = cms.untracked.bool(False),
		doGenJet = cms.untracked.bool(False),
		doCaloJetId = cms.untracked.bool(False),
		doPFJet = cms.untracked.bool(True),
                doFatJet = cms.untracked.bool(True),
		doJPTJet = cms.untracked.bool(False),
		doJPTJetId = cms.untracked.bool(False),
		doMuon = cms.untracked.bool(True),
		doElectron = cms.untracked.bool(True),
         	doPhoton = cms.untracked.bool(True),
		runSuperCluster = cms.untracked.bool(True),#true only if SuperCluster are stored
		doCaloMET = cms.untracked.bool(False),
		doPFMET = cms.untracked.bool(True),
		doTCMET = cms.untracked.bool(False),
		doGenEvent = cms.untracked.bool(False),#put on False when running non-ttbar or when running toptree from reco
		doNPGenEvent = cms.untracked.bool(False),#put on True when running New Physics sample
		doSpinCorrGen = cms.untracked.bool(False),#put on True only if you need SpinCorrelation Variables
        	doLHEEventProd = cms.untracked.bool(False),#put on True only if you need SpinCorrelation Variables
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
		electronMC_ptMin = cms.double(2.0),
		muonMC_etaMax = cms.double(3.0),
		muonMC_ptMin = cms.double(0.0),
		jetMC_etaMax = cms.double(6.0),
		jetMC_ptMin = cms.double(5.0),
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
