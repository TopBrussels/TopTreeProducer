#ifndef CosmicMuonAnalyzer_h
#define CosmicMuonAnalyzer_h

// system include files
#include <iostream>
#include <Math/VectorUtil.h>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "../interface/TRootCosmicMuon.h"
#include "../interface/TRootTrack.h"
#include "../interface/TRootXYZPoint.h"

#include "TClonesArray.h"


class CosmicMuonAnalyzer{
	
public:
	CosmicMuonAnalyzer(const edm::ParameterSet& producersNames);
	CosmicMuonAnalyzer(const edm::ParameterSet& producersNames, int iter,  const edm::ParameterSet& myConfig, int verbosity);

	~CosmicMuonAnalyzer();
	void SetVerbosity(int verbosity) {verbosity_ = verbosity; };
	void Process(const edm::Event& iEvent, TClonesArray* rootCosmicMuons, vector<TClonesArray*> rootCosmicMuonTracks);

private:
	int verbosity_;
	std::string dataType_ ;
	std::vector<std::string> vCosmicMuonProducer;
	edm::InputTag CosmicMuonProducer_;
	edm::InputTag jetProducer_;
};

#endif
