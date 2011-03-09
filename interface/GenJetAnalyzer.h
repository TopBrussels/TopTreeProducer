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
	GenJetAnalyzer(const edm::ParameterSet& producersNames);
	GenJetAnalyzer(const edm::ParameterSet& producersNames, int verbosity);
	GenJetAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
	GenJetAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity);
	~GenJetAnalyzer();
	void SetVerbosity(int verbosity) { verbosity_ = verbosity; };
	void Process(const edm::Event& iEvent, TClonesArray* rootGenJets);

private:
	int verbosity_;
	edm::InputTag genJetProducer_;
	edm::InputTag mcProducer_;
	std::vector<std::string> vGenJetProducer;

};

#endif
