import FWCore.ParameterSet.Config as cms


from RecoJets.Configuration.GenJetParticles_cff import genParticlesForJets
genParticlesForJets=genParticlesForJets.clone()
genParticlesForJets.excludeFromResonancePids=(11, 12, 13, 14, 16)

from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
ak5GenJets=ak5GenJets.clone()
ak5GenJets.src ="genParticlesForJets"

