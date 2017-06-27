from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = '80X_v6_dataTest'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.sendExternalFolder = True
config.JobType.psetName = 'TOPTREE_fromminiAOD.py'
config.JobType.outputFiles = ['TOPTREE.root']
config.JobType.pyCfgParams  = ['runOnData=True']

config.section_("Data")
config.Data.inputDataset = '/SingleElectron/Run2016C-03Feb2017-v1/MINIAOD'



#config.Data.dbsUrl = 'phys03'
config.Data.splitting = 'FileBased'
# default=100, was asked by crab team to use default
#config.Data.unitsPerJob = 2
#config.Data.totalUnits = 90
config.Data.publication = False
config.Data.ignoreLocality = True
config.Data.lumiMask = 'Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'

config.section_("Site")
config.Site.storageSite = 'T2_BE_IIHE'
