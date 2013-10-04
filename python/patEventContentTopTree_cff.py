import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.patEventContent_cff import patEventContentNoCleaning, patTriggerEventContent, patTriggerStandAloneEventContent

patEventContentTopTree = cms.untracked.vstring()

patEventContentTopTree.extend([
    'keep patJets_selectedPatJetsPF2PAT__PAT',
    'keep patMuons_selectedPatMuonsPF2PAT__PAT',
    'keep patElectrons_selectedPatElectronsPF2PAT__PAT',
    'keep patMETs_patType1CorrectedPFMetPF2PAT__PAT',
    'keep double_kt6PFJets_rho_RECO',
    'keep *_goodOfflinePrimaryVertices*_*_*',
    'keep *_TriggerResults_*_*',
    'keep *_hltTriggerSummaryAOD_*_*',
    'keep recoGenJets_ak5GenJetsNoNu_*_*',
    'keep *_bFlavorHistoryProducer_*_*',
    'keep *_cFlavorHistoryProducer_*_*',
    'keep *_flavorHistoryFilter_*_*',
    'keep PileupSummaryInfos_*_*_*',
    'keep recoTracks_generalTracks_*_*',
    'keep recoPFCandidates_selectedPatJetsPF2PAT_pfCandidates_PAT',
    'keep recoGenParticles_genParticles_*_*',
    'keep triggerTriggerEvent_*_*_*',
    'keep GenEventInfoProduct_*_*_*',
    'keep edmMergeableCounter_*_*_*',
    ])

