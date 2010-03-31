import FWCore.ParameterSet.Config as cms
from PhysicsTools.PatAlgos.patSequences_cff import * 
from PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff import * 

#change to 8E29 menu
patTrigger.processName      = 'HLT8E29'
patTriggerEvent.processName = 'HLT8E29'

#Keep the matchingInfo for two paths: one physics and on backup

electronTriggerMatchHLTEle15LWL1R.filterIdsEnum = 'TriggerElectron',
electronTriggerMatchHLTEle15LWL1R.maxDeltaR = 0.3
electronTriggerMatchHLTEle15LWL1R.pathNames = 'HLT_Ele15_LW_L1R',#backup
electronTriggerMatchHLTEle10LWL1R = electronTriggerMatchHLTEle15LWL1R.clone()
electronTriggerMatchHLTEle10LWL1R.pathNames = 'HLT_Ele10_LW_L1R',#physics

# keep matching only for electron
patTriggerMatcher = cms.Sequence(electronTriggerMatchHLTEle10LWL1R+electronTriggerMatchHLTEle15LWL1R+electronTriggerMatchHLTDoubleEle5SWL1R)

#change the matching sources in embedder
cleanPatElectronsTriggerMatch.matches = 'electronTriggerMatchHLTEle10LWL1R','electronTriggerMatchHLTEle15LWL1R'
cleanPatElectronsTriggerMatch.src = 'selectedPatElectrons'

# keep Embedding only for electron
patTriggerMatchEmbedder = cms.Sequence(cleanPatElectronsTriggerMatch)

patDefaultWithTrigger = cms.Sequence(patDefaultSequence * patTrigger * patTriggerMatcher * patTriggerMatchEmbedder * patTriggerEvent)
