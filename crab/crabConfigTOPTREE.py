from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = '80X_v6_MCTest'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.sendExternalFolder = True
config.JobType.psetName = 'TOPTREE_fromminiAOD.py'
config.JobType.outputFiles = ['TOPTREE.root']

config.section_("Data")
config.Data.inputDataset = '/ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'



#config.Data.dbsUrl = 'phys03'
config.Data.splitting = 'FileBased'
# default: 100, was asked by crab team to use default
#config.Data.unitsPerJob = 2
#config.Data.totalUnits = 90
config.Data.publication = False
config.Data.ignoreLocality = True

config.section_("Site")
config.Site.storageSite = 'T2_BE_IIHE'
