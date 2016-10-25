#ifndef MuonAnalyzer_h
#define MuonAnalyzer_h

// system include files
#include <iostream>
#include <Math/VectorUtil.h>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include "../interface/TRootMuon.h"

#include "TClonesArray.h"


class MuonAnalyzer
{
	
public:
	MuonAnalyzer(const edm::ParameterSet& myConfig, int verbosity);
	~MuonAnalyzer();
	void Process(const edm::Event& iEvent, TClonesArray* rootMuons, edm::EDGetTokenT<reco::BeamSpot> offlineBSToken, edm::EDGetTokenT<pat::MuonCollection> muonToken, edm::EDGetTokenT<reco::VertexCollection> vtxToken);

private:
	int verbosity_;
	bool useMC_;
  double muon_ptMin_;
};

#endif
