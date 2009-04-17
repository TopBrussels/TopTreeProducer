import FWCore.ParameterSet.Config as cms

process = cms.Process("NewProcess")

#keep the logging output to a nice level
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

# Global geometry
process.load("Configuration.StandardSequences.Geometry_cff")

# geometry needed for clustering and calo shapes variables
process.load("RecoEcal.EgammaClusterProducers.geometryForClustering_cff")
# 3 folllowing config files included in RecoEcal.EgammaClusterProducers.geometryForClustering_cff
#process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi")
#process.load("Geometry.CaloEventSetup.CaloGeometry_cfi")
#process.load("Geometry.CaloEventSetup.CaloTopology_cfi")

# ES cluster for pi0 discrimination variables
#process.load("RecoEcal.EgammaClusterProducers.preshowerClusterShape_cfi")

# pi0 discrimination variables
#process.load("RecoEcal.EgammaClusterProducers.piZeroDiscriminators_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)


process.source = cms.Source("PoolSource",
        duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
# RECO
# AOD
# PATAOD
# PAT
	#fileNames = cms.untracked.vstring('file:/user/jmmaes/CMSSW/CMSSW_2_2_3/src/Crab/PATSkim1/PATLayer1_Skim1_semilep.root')
	#fileNames = cms.untracked.vstring('file:/user/echabert/CMSSW/CMSSW_2_2_3/src/TopQuarkAnalysis/TopEventProducers/test/toto2.root')
	#fileNames = cms.untracked.vstring('file:/user/echabert/CMSSW/CMSSW_2_2_3/src/CRAB/PATLayer1.root')
	fileNames = cms.untracked.vstring('dcap:///pnfs/iihe/cms/store/user/ghammad/CMSSW223/Common/PATLayer1/TauolaTTbar/PATLayer1_1.root')
)


process.analysis = cms.EDAnalyzer("TopTreeProducer",
	myConfig = cms.PSet(

		# Data type of the PoolSource ( RECO / AOD / PAT  /  PATAOD )
		#dataType = cms.untracked.string("RECO"),   # only RECO collections are present
		#dataType = cms.untracked.string("AOD"),     # only AOD collections are present 
		#dataType = cms.untracked.string("PATAOD"), # mixture of PAT and AOD collections
		dataType = cms.untracked.string("PAT"),    # only PAT collections are present

		# Verbosite
		# 		0 = muet
 		# 		1 = Number of evt every 100 evts
 		# 		2 = Give the functions executed & nof objects build per event
 		# 		3 = Liste of high level objects (jetss, muons, ...)
 		# 		4 = List of all  objects 
		# 		5 = Debug
 		verbosity = cms.untracked.int32(1),

		# name of output root file
		RootFileName = cms.untracked.string('TopTree.root'),

		# Is PoolSource coming from CSA07 Soup Production ? (needed to get CSA07 Process Id and weights)
		isCSA07Soup = cms.untracked.bool(False),

		# What is written to rootuple		    
		doHLT = cms.untracked.bool(False),
		doMC = cms.untracked.bool(False),
		doPDFInfo = cms.untracked.bool(True),
#		signalGenerator = cms.untracked.string('PYTHIA'),
#		signalGenerator = cms.untracked.string('ALPGEN'),
		signalGenerator = cms.untracked.string('MADGRAPH'),

		doElectronMC = cms.untracked.bool(False),
		doMuonMC = cms.untracked.bool(False),
		doJetMC = cms.untracked.bool(True),
		doMETMC = cms.untracked.bool(False),
		doUnstablePartsMC = cms.untracked.bool(False),
		doPrimaryVertex = cms.untracked.bool(True),
		doJet = cms.untracked.bool(True),
		doMuon = cms.untracked.bool(True),
		doElectron = cms.untracked.bool(False),
		doMET = cms.untracked.bool(True),
		doGenEvent = cms.untracked.bool(False),

		conversionLikelihoodWeightsFile = cms.untracked.string('RecoEgamma/EgammaTools/data/TMVAnalysis_Likelihood.weights.txt'),

		# Draw MC particle tree
		drawMCTree = cms.untracked.bool(False),
		mcTreePrintP4 = cms.untracked.bool(True),
		mcTreePrintPtEtaPhi = cms.untracked.bool(False),
		mcTreePrintVertex = cms.untracked.bool(False),
		mcTreePrintStatus = cms.untracked.bool(True),
		mcTreePrintIndex = cms.untracked.bool(True),
		mcTreeStatus = cms.untracked.vint32( 3 ),	# accepted status codes

	
		# MC particles acceptance cuts
		electronMC_etaMax = cms.double(3.0),
		electronMC_ptMin = cms.double(2.0),
		muonMC_etaMax = cms.double(3.0),
		muonMC_ptMin = cms.double(0.0),
		jetMC_etaMax = cms.double(6.0),
		jetMC_ptMin = cms.double(5.0),

	),

	producersNamesRECO = cms.PSet(
		dataType = cms.untracked.string("RECO"), 
		hltProducer = cms.InputTag("TriggerResults","","HLT"),
		genParticlesProducer = cms.InputTag("genParticles"),
		primaryVertexProducer = cms.InputTag("offlinePrimaryVertices"),
		jetProducer = cms.InputTag("iterativeCone5CaloJets"),
		#jetProducer = cms.InputTag("iterativeCone5PFJets"),
		muonProducer = cms.InputTag("muons"),
		electronProducer = cms.InputTag("pixelMatchGsfElectrons"),
		metProducer = cms.InputTag("met"),
	        genEventProducer = cms.InputTag("genEvt")
	),

	producersNamesAOD = cms.PSet(
		dataType = cms.untracked.string("AOD"), 
		hltProducer = cms.InputTag("TriggerResults","","HLT"),
		genParticlesProducer = cms.InputTag("genParticles"),
		primaryVertexProducer = cms.InputTag("offlinePrimaryVertices"),
		jetProducer = cms.InputTag("iterativeCone5CaloJets"),
		muonProducer = cms.InputTag("muons"),
		electronProducer = cms.InputTag("pixelMatchGsfElectrons"),
		metProducer = cms.InputTag("met"),
	        genEventProducer = cms.InputTag("genEvt")
	),

	producersNamesPATAOD = cms.PSet(
		dataType = cms.untracked.string("PATAOD"), 
		hltProducer = cms.InputTag("TriggerResults","","HLT"),
		genParticlesProducer = cms.InputTag("genParticles"),
		primaryVertexProducer = cms.InputTag("offlinePrimaryVertices"),
		jetProducer = cms.InputTag("selectedLayer1Jets"),
		muonProducer = cms.InputTag("selectedLayer1Muons"),
		electronProducer = cms.InputTag("selectedLayer1Electrons"),
		metProducer = cms.InputTag("selectedLayer1METs"),
	        genEventProducer = cms.InputTag("genEvt")
	),

	producersNamesPAT = cms.PSet(
		dataType = cms.untracked.string("PAT"), 
		hltProducer = cms.InputTag("PATALACON"),
		genParticlesProducer = cms.InputTag("genParticles"),
		primaryVertexProducer = cms.InputTag("offlinePrimaryVertices"),
		jetProducer = cms.InputTag("selectedLayer1Jets"),
		muonProducer = cms.InputTag("selectedLayer1Muons"),
		electronProducer = cms.InputTag("selectedLayer1Electrons"),
		metProducer = cms.InputTag("selectedLayer1METs"),
	        genEventProducer = cms.InputTag("genEvt")
	)
 )

process.p = cms.Path(process.analysis)

