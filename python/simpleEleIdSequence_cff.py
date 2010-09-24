import FWCore.ParameterSet.Config as cms

from TopBrussels.TopTreeProducer.simpleCutBasedElectronIDSpring10_cfi import *
from RecoEgamma.ElectronIdentification.electronIdCutBasedExt_cfi import *

simpleEleId70cIso = simpleCutBasedElectronID.clone()
simpleEleId70cIso.electronQuality = '70cIso'

simpleEleId95cIso = simpleCutBasedElectronID.clone()
simpleEleId95cIso.electronQuality = '95cIso'

simpleEleIdSequence = cms.Sequence(simpleEleId70cIso+simpleEleId95cIso)
