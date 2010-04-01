import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.mcMatchLayer0.electronMatch_cfi import *
from PhysicsTools.PatAlgos.producersLayer1.electronProducer_cfi import *
from PhysicsTools.PatAlgos.selectionLayer1.electronSelector_cfi import *

from TopBrussels.TopTreeProducer.TowerRemover_cfi import * 

from RecoJets.JetProducers.ak5CaloJets_cfi import ak5CaloJets
newAntikt5CaloJets=ak5CaloJets.clone()
newAntikt5CaloJets.src ="cleanTowers"


TowerCleaningSeq = cms.Sequence(electronMatch * patElectrons * selectedPatElectrons * cleanTowers * newAntikt5CaloJets)
