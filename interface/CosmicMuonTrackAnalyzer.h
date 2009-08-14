#ifndef CosmicMuonTrackAnalyzer_h
#define CosmicMuonTrackAnalyzer_h

// system include files
#include <iostream>
#include <Math/VectorUtil.h>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "../interface/TRootTrack.h"

#include "TClonesArray.h"


class CosmicMuonTrackAnalyzer{
	
public:
	CosmicMuonTrackAnalyzer(const edm::ParameterSet& producersNames);
	CosmicMuonTrackAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
	~CosmicMuonTrackAnalyzer();
	void SetVerbosity(int verbosity) {verbosity_ = verbosity; };
	void Process(const edm::Event& iEvent, std::string trackType, TClonesArray* rootCosmicMuonTracks);

private:
	int verbosity_;
	std::string dataType_ ;
	edm::InputTag CosmicMuonProducer1Leg_;
	edm::InputTag CosmicMuonProducer2Leg_;
};

#endif
