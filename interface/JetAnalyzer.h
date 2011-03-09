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

using namespace TopTree;

class JetAnalyzer {
	
public:
	JetAnalyzer();
	JetAnalyzer(int verbosity);
	JetAnalyzer(const edm::ParameterSet& myConfig, int verbosity);
	~JetAnalyzer();
	void SetVerbosity(int verbosity) {verbosity_ = verbosity; };
	TRootJet Process(const reco::Jet* jet);

private:
	int verbosity_;
	bool useMC_;
	bool isData_;

};

#endif
