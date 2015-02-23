#ifndef FatJetAnalyzer_h
#define FatJetAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"

#include "../interface/TRootSubstructureJet.h"
#include "../interface/JetAnalyzer.h"

#include "TClonesArray.h"



class FatJetAnalyzer : JetAnalyzer {

public:
	FatJetAnalyzer(const edm::ParameterSet& producersNames);
	FatJetAnalyzer(const edm::ParameterSet& producersNames, int verbosity);
	FatJetAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
	FatJetAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity);
	~FatJetAnalyzer();
	void SetVerbosity(int verbosity) {verbosity_ = verbosity; };
	void Process(const edm::Event& iEvent, TClonesArray* rootPFJets, const edm::EventSetup& iSetup);

private:
	int verbosity_;
	edm::InputTag fatJetProducer_;
	edm::InputTag mcProducer_;
	std::vector<std::string> vFatJetProducer;
	JetAnalyzer* myJetAnalyzer; // FIXME: Handle the deletion of the JetAnalyzer

};

#endif
