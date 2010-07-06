#ifndef MHTAnalyzer_h
#define MHTAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/PatCandidates/interface/MHT.h"

#include "../interface/TRootEvent.h"
#include "../interface/TRootMHT.h"

#include "TClonesArray.h"


class MHTAnalyzer{
	
public:
	MHTAnalyzer(const edm::ParameterSet& producersNames);
	MHTAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
	~MHTAnalyzer();
	void SetVerbosity(int verbosity) { verbosity_ = verbosity; };
	void Process(const edm::Event& iEvent, TClonesArray* rootMHT);

private:
	int verbosity_;
	std::string dataType_ ;
	edm::InputTag mhtProducer_;
};

#endif
