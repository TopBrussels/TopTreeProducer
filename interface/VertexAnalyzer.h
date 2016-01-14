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

#include "../interface/TRootVertex.h"

#include "TClonesArray.h"

using namespace TopTree;

class VertexAnalyzer {
	
public:
	VertexAnalyzer(int verbosity);
	~VertexAnalyzer();
	void Process(const edm::Event& iEvent, TClonesArray* rootVertex, edm::EDGetTokenT<reco::VertexCollection> vtxToken);

private:
	int verbosity_;
	edm::InputTag primaryVertexProducer_;

};

#endif
