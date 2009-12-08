#ifndef JetAnalyzer_h
#define JetAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"

#include "../interface/TRootJet.h"

#include "TClonesArray.h"


class JetAnalyzer{
	
public:
	JetAnalyzer(const edm::ParameterSet& producersNames);
	JetAnalyzer(const edm::ParameterSet& producersNames, int verbosity);
	JetAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
	JetAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity);
	~JetAnalyzer();
	void SetVerbosity(int verbosity) {verbosity_ = verbosity; };
	void Process(const edm::Event& iEvent, TClonesArray* rootJets);

private:
	int verbosity_;
	std::string dataType_ ;
	edm::InputTag jetProducer_;
	edm::InputTag mcProducer_;
	bool useMC_;
	bool doJetId_;
	std::vector<std::string> vJetProducer;

};

#endif
