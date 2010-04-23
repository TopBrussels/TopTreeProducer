import FWCore.ParameterSet.Config as cms

# we rebuild genjets with and without electrons

# make a genparticle collection stripped from electrons
from RecoJets.Configuration.GenJetParticles_cff import genParticlesForJets

# remove leptons&neutrino's from the genparticles used for clustering
genParticlesForJetsNoE=genParticlesForJets.clone()
genParticlesForJetsNoE.excludeFromResonancePids=(11, 12, 13, 14, 16)

from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets

# make a genjet collection without electrons
ak5GenJetsNoE=ak5GenJets.clone()
ak5GenJetsNoE.src ="genParticlesForJetsNoE"

genJet = cms.Sequence(genParticlesForJetsNoE*ak5GenJetsNoE)
# sequence for noE genjets
