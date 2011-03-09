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
#include "FWCore/Common/interface/TriggerNames.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"
#include "DataFormats/Scalers/interface/DcsStatus.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "RecoEgamma/EgammaTools/interface/ConversionFinder.h"
#include "../interface/TRootElectron.h"
//#include "../interface/Conversion.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
//#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "Math/VectorUtil.h"

#include "TClonesArray.h"

using namespace edm;
using namespace reco;
class ElectronAnalyzer{
	
public:
	ElectronAnalyzer(const edm::ParameterSet& producersNames);
	ElectronAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
	ElectronAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity);
	~ElectronAnalyzer();
	void SetVerbosity(int verbosity) {verbosity_ = verbosity; };
	void Process(const edm::Event& iEvent, TClonesArray* rootElectrons, EcalClusterLazyTools& lazyTools, const edm::EventSetup& iSetup);

	const reco::Track* getElectronTrack(const reco::GsfElectron& gsfElectron, const float minFracSharedHits);
	std::pair<double, double> getConversionInfo(TLorentzVector trk1_p4,int trk1_q, float trk1_d0,TLorentzVector trk2_p4,int trk2_q, float trk2_d0,float bFieldAtOrigin);
	reco::TrackRef getConversionPartnerTrack(const reco::GsfElectron& gsfElectron,
	const edm::Handle<reco::TrackCollection>& track_h,
	const float bFieldAtOrigin,
	double& Dist,
	double& DCot,
	const float maxAbsDist = 0.02,
	const float maxAbsDCot = 0.02,
	const float minFracSharedHits = 0.45);

private:
	int verbosity_;
	edm::InputTag electronProducer_;
	std::vector<std::string> vElectronProducer;	
	edm::InputTag primaryVertexProducer_;
	edm::InputTag TrackLabel_;
	bool useMC_;
	bool runSuperCluster_;
	bool newId_;
	bool doPrimaryVertex_;
	bool isData_;
	std::vector<std::string> pathNames;

};

#endif
