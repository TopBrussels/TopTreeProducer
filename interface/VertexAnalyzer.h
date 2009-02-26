#ifndef VertexAnalyzer_h
#define VertexAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "../interface/TRootEvent.h"

#include "TClonesArray.h"


class VertexAnalyzer{
	
public:
	VertexAnalyzer(const edm::ParameterSet& producersNames);
	VertexAnalyzer(const edm::ParameterSet& producersNames, int verbosity);
	~VertexAnalyzer();
	void SetVerbosity(int verbosity) {verbosity_ = verbosity; };
	void Process(const edm::Event& iEvent, TRootEvent* rootEvent);

private:
	int verbosity_;
	edm::InputTag primaryVertexProducer_;

};

#endif
