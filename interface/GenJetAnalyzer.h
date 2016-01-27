#ifndef GenJetAnalyzer_h
#define GenJetAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"

#include "../interface/TRootGenJet.h"

#include "TClonesArray.h"


class GenJetAnalyzer {

public:
	GenJetAnalyzer(std::string genJetProducerStr, const edm::ParameterSet& myConfig, int verbosity);
	~GenJetAnalyzer();
	void Process(const edm::Event& iEvent, TClonesArray * rootGenJets, edm::EDGetTokenT<std::vector<reco::GenJet> > genJetToken);

private:
	int verbosity_;
	edm::InputTag genJetProducer_;

    std::vector<const reco::Candidate *> getAncestors(const reco::Candidate &c);
    bool hasBottom(const reco::Candidate &c);
    bool hasCharm(const reco::Candidate &c);
    bool decayFromBHadron(const reco::Candidate &c);
    bool decayFromCHadron(const reco::Candidate &c);
    const reco::Candidate* lastBHadron(const reco::Candidate &c);
    const reco::Candidate* lastCHadron(const reco::Candidate &c);

};

#endif
