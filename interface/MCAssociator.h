#ifndef MCAssociator_h
#define MCAssociator_h

#include <memory>
#include <string>
#include <iostream>
#include <map>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "../interface/TRootParticle.h"
#include "../interface/TRootMCParticle.h"
#include "../interface/TRootElectron.h"

#include "TClonesArray.h"


class MCAssociator{
	
public:
	MCAssociator();
	MCAssociator(int verbosity);
	~MCAssociator() {};
	void init(const edm::Event& iEvent, TClonesArray* mcParticles, edm::EDGetTokenT<std::vector<reco::GenParticle> > genParticlesToken);
	void process(TClonesArray* recoParticles);
	void printParticleAssociation(TClonesArray* recoParticles);

private:
	int verbosity_;
	int nMC_;
	TClonesArray* mcParticles_;
	edm::Handle <reco::GenParticleCollection> genParticles_;
	std::map<int,int> mcParticlesMap_; // map between index in genParticle collection and index in mcParticles TClonesArray

};

#endif
