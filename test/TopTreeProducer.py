import FWCore.ParameterSet.Config as cms

process = cms.Process("NewProcess")

#keep the logging output to a nice level
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

# Global geometry
process.load("Configuration.StandardSequences.Geometry_cff")

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
    input = cms.untracked.int32(100)
)


process.source = cms.Source("PoolSource",
#        duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
# RECO
# AOD
# PATAOD
# PAT
	fileNames = cms.untracked.vstring('file:/tmp/ajafari/GenSimReco_355.root')
	#fileNames = cms.untracked.vstring('/store/data/CRAFT09/Cosmics/RAW-RECO/SuperPointing-CRAFT09_R_V4_CosmicsSeq_v1/0009/763782DB-DCB9-DE11-A238-003048678B30.root')
	#fileNames = cms.untracked.vstring('file:/user/echabert/CMSSW/CMSSW_2_2_3/src/TopQuarkAnalysis/TopEventProducers/test/toto2.root')
	#fileNames = cms.untracked.vstring('file:/user/echabert/CMSSW/CMSSW_2_2_6/src/NewPhysicsAnalysis/SUSYAnalysis/TopSUSYEvents.root')
#	fileNames = cms.untracked.vstring('dcap:///pnfs/iihe/cms/store/user/blyweert/temp/CRAFT09_RERECO/CRAFT09_SuperPointing_RERECO_CMSSW330_1.root')
	#fileNames = cms.untracked.vstring('dcap:///pnfs/iihe/cms/store/user/ghammad/CMSSW223/Common/PATLayer1/TauolaTTbar/PATLayer1_1.root')
#	fileNames = cms.untracked.vstring('dcap:///pnfs/iihe/cms/store/user/jmmaes/TTJets-madgraph/CMSSW227_R3_TTJets-madgraph_redigi_ns_3_PATLayer1WithTtGenEvt/5806ec35aac362025b4eea830982d55c/PATLayer1Ext_1.root')
#fileNames = cms.untracked.vstring('/store/data/Commissioning08/Cosmics/RAW-RECO/CRAFT-ALL-V13-2213-Tosca090322_2pi-scaled-ReReco-FromSuperPointing-v1/0001/02AFE1E4-775D-DE11-BC49-001731AF67E1.root')
)
#process.load("TopBrussels.SanityChecker.PATLayer1_R3_TauolaTTbar_redigi_NoEvtSel_input_cfi")
#process.load("TopBrussels.SanityChecker.PATLayer1_R3_InclusiveMuPt15_redigi_input_cfi")

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
 		verbosity = cms.untracked.int32(5),

		# name of output root file
		RootFileName = cms.untracked.string('TopTree_pythia.root'),

		# Is PoolSource coming from CSA07 Soup Production ? (needed to get CSA07 Process Id and weights)
		isCSA07Soup = cms.untracked.bool(False),

		# What is written to rootuple		    
		doHLT = cms.untracked.bool(False),
		doHLTStudy = cms.untracked.bool(False),
		doMC = cms.untracked.bool(False),
		doPDFInfo = cms.untracked.bool(False),
		signalGenerator = cms.untracked.string('PYTHIA'),
#		signalGenerator = cms.untracked.string('ALPGEN'),
#		signalGenerator = cms.untracked.string('MADGRAPH'),

		doElectronMC = cms.untracked.bool(False),
		doMuonMC = cms.untracked.bool(False),
		doJetMC = cms.untracked.bool(False),
		doMETMC = cms.untracked.bool(False),
		doUnstablePartsMC = cms.untracked.bool(False),
		doPrimaryVertex = cms.untracked.bool(False),
		doCaloJet = cms.untracked.bool(False),
		doCaloJetStudy = cms.untracked.bool(True),
		doCaloJetId = cms.untracked.bool(True),
		doPFJet = cms.untracked.bool(False),
		doPFJetStudy = cms.untracked.bool(False),
		doMuon = cms.untracked.bool(False),
		doCosmicMuon = cms.untracked.bool(False),
		doElectron = cms.untracked.bool(False),
		runSuperCluster = cms.untracked.bool(False),#true only if SuperCluster are stored
		doMET = cms.untracked.bool(False),
		doGenEvent = cms.untracked.bool(False),#put on False when running non-ttbar
		doNPGenEvent = cms.untracked.bool(False),#put on True when running New Physics sample
		doSpinCorrGen = cms.untracked.bool(False),#put on True only if you need SpinCorrelation Variables
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

	producersNamesRECO = cms.PSet(
		dataType = cms.untracked.string("RECO"), 
		hltProducer = cms.InputTag("TriggerResults","","HLT"),
		vhltProducer = cms.untracked.VInputTag(cms.InputTag("TriggerResults","","HLT8E29"),),
		genParticlesProducer = cms.InputTag("genParticles"),
		primaryVertexProducer = cms.InputTag("offlinePrimaryVertices"),
		caloJetProducer = cms.InputTag("iterativeCone5CaloJets"),
		vcaloJetProducer = cms.untracked.vstring("iterativeCone5CaloJets","sisCone5CaloJets","ak5CaloJets"),
		pfJetProducer = cms.InputTag("iterativeCone5PFJets"),
		vpfJetProducer = cms.untracked.vstring("iterativeCone5PFJets","sisCone5PFJets","ak5PFJets"),
		muonProducer = cms.InputTag("muons"),
		vcosmicMuonProducer = cms.untracked.vstring("muons"),
		electronProducer = cms.InputTag("pixelMatchGsfElectrons"),
		metProducer = cms.InputTag("met"),
		genEventProducer = cms.InputTag("genEvt"),
		electronNewId = cms.bool(False)
	),

	producersNamesAOD = cms.PSet(
		dataType = cms.untracked.string("AOD"), 
		hltProducer = cms.InputTag("TriggerResults","","HLT"),
		vhltProducer = cms.untracked.VInputTag(cms.InputTag("TriggerResults","","HLT8E29"),),
		genParticlesProducer = cms.InputTag("genParticles"),
		primaryVertexProducer = cms.InputTag("offlinePrimaryVertices"),
		caloJetProducer = cms.InputTag("iterativeCone5CaloJets"),
		vcaloJetProducer = cms.untracked.vstring("iterativeCone5CaloJets"),
		pfJetProducer = cms.InputTag("iterativeCone5PFJets"),
		vpfJetProducer = cms.untracked.vstring("iterativeCone5PFJets","sisCone5PFJets","ak5PFJets"),
		muonProducer = cms.InputTag("muons"),
		vcosmicMuonProducer = cms.untracked.vstring("muons","muons1Leg"),
		electronProducer = cms.InputTag("pixelMatchGsfElectrons"),
		metProducer = cms.InputTag("met"),
	        genEventProducer = cms.InputTag("genEvt"),
		electronNewId = cms.bool(False)
	),

	producersNamesPATAOD = cms.PSet(
		dataType = cms.untracked.string("PATAOD"), 
		hltProducer = cms.InputTag("TriggerResults","","HLT"),
		vhltProducer = cms.untracked.VInputTag(cms.InputTag("TriggerResults","","HLT8E29"),),
		genParticlesProducer = cms.InputTag("genParticles"),
		primaryVertexProducer = cms.InputTag("offlinePrimaryVertices"),
		caloJetProducer = cms.InputTag("selectedPatJets"),
		vcaloJetProducer = cms.untracked.vstring("selectedPatJets"),
		pfJetProducer = cms.InputTag("selectedPatJets"),
		vpfJetProducer = cms.untracked.vstring("selectedPatJets"),
		muonProducer = cms.InputTag("selectedPatMuons"),
		electronProducer = cms.InputTag("selectedPatElectrons"),
		metProducer = cms.InputTag("selectedPatMETs"),
		genEventProducer = cms.InputTag("genEvt"),
		electronNewId = cms.bool(False)
	),

	producersNamesPAT = cms.PSet(
		dataType = cms.untracked.string("PAT"), 
		hltProducer = cms.InputTag("TriggerResults","","HLT"),
		vhltProducer = cms.untracked.VInputTag(cms.InputTag("TriggerResults","","HLT8E29"),),
		genParticlesProducer = cms.InputTag("genParticles"),
		primaryVertexProducer = cms.InputTag("offlinePrimaryVertices"),
		caloJetProducer = cms.InputTag("selectedPatJets"),
		vcaloJetProducer = cms.untracked.vstring("selectedPatJets"),
		pfJetProducer = cms.InputTag("selectedPatJets"),
		vpfJetProducer = cms.untracked.vstring("selectedPatJets"),
		muonProducer = cms.InputTag("selectedPatMuons"),
		electronProducer = cms.InputTag("selectedPatElectrons"),
		metProducer = cms.InputTag("selectedPatMETs"),
		genEventProducer = cms.InputTag("genEvt"),
		electronNewId = cms.bool(False)
	)
)
process.p = cms.Path(process.analysis)

