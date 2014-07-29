from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'CSA14_miniAODtoTOPTREE_test4_Wminus_v1'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'TOPTREE_fromminiAOD.py'

config.section_("Data")
#config.Data.inputDataset = '/GenericTTbar/HC-CMSSW_5_3_1_START53_V5-v1/GEN-SIM-RECO'
#config.Data.inputDataset = '/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/Spring14dr-PU_S14_POSTLS170_V6-v1/AODSIM'
#config.Data.inputDataset = '/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/keaveney-CSA14_test2-814812ec83fce2f620905d2bb30e9100/USER'
#config.Data.inputDataset = '/WplusToMuNu_CT10_13TeV-powheg-pythia8/Spring14dr-PU_S14_POSTLS170_V6-v1/AODSIM'

#S14 TTBAR CENTRALLY PRODUCED
#config.Data.inputDataset = '/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/Spring14miniaod-PU_S14_POSTLS170_V6-v1/MINIAODSIM'


#Wplus (produced by James, not yet ready )
#config.Data.inputDataset = ''

#Wminus (produced by Jesse)
config.Data.inputDataset = '/WminusToMuNu_CT10_13TeV-powheg-pythia8/heilman-CSA14_user_miniAOD_production-6f9bb2ea5d0da5816d9e790390fd7d77/USER'


config.Data.dbsUrl = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.totalUnits = 200
config.Data.publication = False
config.Data.ignoreLocality = True
config.Data.publishDbsUrl = 'phys03'
config.Data.publishDataName = 'CSA14_miniAODtoTOPTREE_test4_Wminus_v1'


config.section_("Site")
config.Site.storageSite = 'T2_BE_IIHE'
