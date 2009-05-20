#ifndef SemiLepEventAnalyzer_h
#define SemiLepEventAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"

#include "../interface/TRootGenEvent.h"
#include "../interface/TRootSemiLepEvent.h"

#include "TClonesArray.h"
#include "TLorentzVector.h"

class SemiLepEventAnalyzer{
	
public:
	SemiLepEventAnalyzer(const edm::ParameterSet& producersNames);
	SemiLepEventAnalyzer(const edm::ParameterSet& producersNames, int verbosity);
	SemiLepEventAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
	~SemiLepEventAnalyzer();
	void SetVerbosity(int verbosity) {verbosity_ = verbosity; };
	void Process(const edm::Event& iEvent, TClonesArray* rootGenEvent, TClonesArray* rootJets, TClonesArray* rootMuons);

private:
	int verbosity_;
	std::string dataType_ ;
	edm::InputTag semiLepEventProducer_;
 ///
};

#endif
