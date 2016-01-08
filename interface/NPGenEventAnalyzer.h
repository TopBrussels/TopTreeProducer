#ifndef NPGenEventAnalyzer_h
#define NPGenEventAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "../interface/TRootNPGenEvent.h"

#include "TClonesArray.h"
#include "TLorentzVector.h"

using namespace TopTree;

class NPGenEventAnalyzer{
	
public:
	NPGenEventAnalyzer(int verbosity);
	~NPGenEventAnalyzer();
	void Process(const edm::Event& iEvent, TClonesArray* rootGenEvent, edm::EDGetTokenT<std::vector<reco::GenParticle> > genParticlesToken);
    TLorentzVector P4toTLV (reco::Particle::LorentzVector a);
    TRootMCParticle ConvertMCPart(reco::GenParticleCollection::const_iterator t);
    TRootMCParticle ConvertMCPart(reco::GenParticle::const_iterator t);
  
private:
	int verbosity_;
 ///
};

#endif
