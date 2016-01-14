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
	FatJetAnalyzer(const edm::ParameterSet& myConfig, int verbosity);
	~FatJetAnalyzer();
	void Process(const edm::Event& iEvent, TClonesArray* rootPFJets, const edm::EventSetup& iSetup, edm::EDGetTokenT<pat::JetCollection> fatjetToken);

private:
	int verbosity_;
	JetAnalyzer* myJetAnalyzer;

};

#endif
