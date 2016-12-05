from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'TOPTREE_740_TTJets_RelVal_Debug1'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.sendExternalFolder = True
#config.JobType.psetName = 'Hadronizer_Tune4C_13TeV_aMCatNLO_LHE_pythia8_cff_py_GEN_SIM_RECO_HLT_PU.py'
config.JobType.psetName = 'TOPTREE_fromminiAOD.py'
#config.JobType.inputFiles = ['root://cms-xrd-global.cern.ch//store/user/heilman/LHEstore/FOURTOP_NLO_100k_v2.lhe']
config.JobType.outputFiles = ['TOPTREE.root']

config.section_("Data")
config.Data.inputDataset = '/RelValTTbar_13/CMSSW_7_4_0-PU25ns_MCRUN2_74_V7_gs7115_puProd-v1/MINIAODSIM'


#config.Data.dbsUrl = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
#config.Data.totalUnits = 90
config.Data.publication = False
config.Data.ignoreLocality = True
#config.Data.publishDBS = 'phys03'
#config.Data.publishDataName = 'FOURTOP_NLO_13TeV_aMCatNLO_LHE_pythia8_AODSIM_CRAB3'


config.section_("Site")
config.Site.storageSite = 'T2_BE_IIHE'
