#ifndef ElectronAnalyzer_h
#define ElectronAnalyzer_h

// system include files
#include <iostream>
#include <TLorentzVector.h>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "DataFormats/TrackReco/interface/HitPattern.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Scalers/interface/DcsStatus.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "RecoEgamma/EgammaTools/interface/ConversionFinder.h"
#include "../interface/TRootElectron.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"

#include "TClonesArray.h"

using namespace edm;
using namespace reco;
class ElectronAnalyzer{
	
public:
	ElectronAnalyzer(const edm::ParameterSet& myConfig, int verbosity);
	~ElectronAnalyzer();
	void Process(
	  const edm::Event& iEvent, TClonesArray* rootElectrons, 
	  const edm::EventSetup& iSetup, 
	  edm::EDGetTokenT<reco::BeamSpot> offlineBSToken, 
	  edm::EDGetTokenT<pat::ElectronCollection> electronToken_calibrated, 
	  edm::EDGetTokenT<pat::ElectronCollection> electronToken_uncalibrated, 
	  edm::EDGetTokenT<edm::View<reco::GsfElectron>> GsfelectronToken, 
	  edm::EDGetTokenT<reco::VertexCollection> vtxToken, 
    edm::EDGetTokenT<edm::ValueMap<bool>> eleMediumMVAIdMapToken,
    edm::EDGetTokenT<edm::ValueMap<bool>> eleTightMVAIdMapToken,
    edm::EDGetTokenT<edm::ValueMap<float>> mvaValuesMapToken,
    edm::EDGetTokenT<edm::ValueMap<int>> mvaCategoriesMapToken,
    edm::EDGetTokenT<edm::ValueMap<bool>> eleVetoCBIdMapToken,
    edm::EDGetTokenT<edm::ValueMap<bool>> eleLooseCBIdMapToken,
    edm::EDGetTokenT<edm::ValueMap<bool>> eleMediumCBIdMapToken,
    edm::EDGetTokenT<edm::ValueMap<bool>> eleTightCBIdMapToken,
    edm::EDGetTokenT<edm::ValueMap<bool>> eleHEEPCBIdMapToken
	);
  typedef std::vector< edm::Handle< edm::ValueMap<double> > > IsoDepositVals;

private:
	int verbosity_;
	bool useMC_;
	bool runSuperCluster_;
	bool doPrimaryVertex_;
	bool isData_;
  double electron_ptMin_;

};

#endif
