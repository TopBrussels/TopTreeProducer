#ifndef PhotonAnalyzer_h
#define PhotonAnalyzer_h

// system include files
#include <iostream>
#include <Math/VectorUtil.h>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include "../interface/TRootPhoton.h"

#include "TClonesArray.h"


class PhotonAnalyzer
{
	
public:
	PhotonAnalyzer(const edm::ParameterSet& myConfig, int verbosity);
	~PhotonAnalyzer();
	void Process(const edm::Event& iEvent, TClonesArray* rootPhotons, const edm::EventSetup& iSetup, edm::EDGetTokenT<pat::PhotonCollection> photonToken);

    typedef std::vector< edm::Handle< edm::ValueMap<reco::IsoDeposit> > > IsoDepositMaps;
    typedef std::vector< edm::Handle< edm::ValueMap<double> > > IsoDepositVals;

private:
	int verbosity_;
	edm::InputTag photonProducer_;
	std::vector<std::string> vPhotonProducer;
	bool useMC_;
 
    //photon isolation
    std::vector<edm::InputTag> inputTagIsoDepPhotons_;
    std::vector<edm::InputTag> inputTagIsoValPhotons_; 
};

#endif
