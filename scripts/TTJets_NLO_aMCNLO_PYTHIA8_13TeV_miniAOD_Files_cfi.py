import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_1.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_10.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_11.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_12.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_13.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_14.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_15.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_16.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_17.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_18.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_19.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_2.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_20.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_21.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_22.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_23.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_24.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_25.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_26.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_27.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_28.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_29.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_3.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_30.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_31.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_32.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_33.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_34.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_35.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_36.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_37.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_38.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_39.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_4.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_40.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_41.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_42.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_43.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_44.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_45.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_46.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_47.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_48.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_49.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_5.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_50.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_6.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_7.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_8.root',
       'root://cms-xrd-global.cern.ch//store/user/heilman/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_CMSSW720/TTJets_NLO_aMCNLO_PYTHIA8_13TEV_AODSIMtoMINIAODSIM/141031_090012/0000/miniAOD-prod_PAT_9.root' ] );


secFiles.extend( [
               ] )

