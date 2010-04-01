import FWCore.ParameterSet.Config as cms


cleanTowers=cms.EDProducer("TowerRemover",
			DREleTwr=cms.double(0.20),
			electronCriteria=cms.string('pt > 20 & ((abs( eta ) < 1.4442) | (abs( eta ) > 1.560 & abs( eta ) < 2.4)) & electronID("eidRobustTight") & ((dr03TkSumPt+dr03EcalRecHitSumEt+dr03HcalTowerSumEt)/et)< 0.1'),
			src = cms.InputTag("selectedPatElectrons")
)
