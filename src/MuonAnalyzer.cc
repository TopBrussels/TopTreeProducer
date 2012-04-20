#include "../interface/MuonAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

MuonAnalyzer::MuonAnalyzer (const edm::ParameterSet & producersNames):
verbosity_(0),
useMC_(false)
{
	muonProducer_ = producersNames.getParameter < edm::InputTag > ("muonProducer");
}

MuonAnalyzer::MuonAnalyzer (const edm::ParameterSet & producersNames, const edm::ParameterSet & myConfig, int verbosity):
verbosity_ (verbosity)
{
	muonProducer_ = producersNames.getParameter < edm::InputTag > ("muonProducer");
	useMC_ = myConfig.getUntrackedParameter < bool > ("doMuonMC");
}
MuonAnalyzer::MuonAnalyzer (const edm::ParameterSet & producersNames, int iter, const edm::ParameterSet & myConfig, int verbosity):
verbosity_ (verbosity)
{
	vMuonProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vmuonProducer");
	muonProducer_ =	edm::InputTag(vMuonProducer[iter]);
	useMC_ = myConfig.getUntrackedParameter < bool > ("doMuonMC");
}

MuonAnalyzer::~MuonAnalyzer ()
{
}

void
MuonAnalyzer::Process (const edm::Event & iEvent, TClonesArray * rootMuons)
{
	unsigned int nMuons = 0;

	edm::Handle < std::vector < pat::Muon > >patMuons;
	iEvent.getByLabel (muonProducer_, patMuons);
	nMuons = patMuons->size ();
	
	edm::Handle<reco::BeamSpot> beamSpotHandle;
	iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);
	const reco::TrackBase::Point & beamSpot = reco::TrackBase::Point(beamSpotHandle->x0(), beamSpotHandle->y0(), beamSpotHandle->z0());

	if (verbosity_ > 1)
		std::cout << "   Number of muons = " << nMuons << "   Label: " << muonProducer_.label () << "   Instance: " << muonProducer_.instance () << std::endl;

	for (unsigned int j = 0; j < nMuons; j++)
	{
		const reco::Muon * muon = 0;
		muon = (const reco::Muon *) (&((*patMuons)[j]));

		TRootMuon localMuon (muon->px (), muon->py (), muon->pz (), muon->energy (), muon->vx (), muon->vy (), muon->vz (), muon->pdgId (), muon->charge ());
		localMuon.setIsoR03 (muon->isolationR03 ().emEt, muon->isolationR03 ().hadEt, muon->isolationR03 ().sumPt);
		localMuon.setAlgo (muon->type ());
		localMuon.setID (int ( muon::isGoodMuon ( *muon, muon::AllGlobalMuons)), int ( muon::isGoodMuon ( *muon, muon::AllTrackerMuons)), int ( muon::isGoodMuon ( *muon, muon::AllStandAloneMuons)), int ( muon::isGoodMuon ( *muon, muon::TrackerMuonArbitrated)), int ( muon::isGoodMuon ( *muon, muon::AllArbitrated)), int ( muon::isGoodMuon ( *muon, muon::GlobalMuonPromptTight)), int ( muon::isGoodMuon (*muon, muon::TMLastStationLoose)), int ( muon::isGoodMuon ( *muon, muon::TMLastStationTight)),int ( muon::isGoodMuon ( *muon, muon::TMLastStationAngTight)) , int ( muon::isGoodMuon ( *muon, muon::TMOneStationLoose)), int ( muon::isGoodMuon ( *muon, muon::TMOneStationTight)), int ( muon::isGoodMuon ( *muon, muon::TMLastStationOptimizedLowPtLoose)), int ( muon::isGoodMuon ( *muon, muon::TMLastStationOptimizedLowPtTight)), int ( muon::isGoodMuon ( *muon, muon::TM2DCompatibilityLoose)), int ( muon::isGoodMuon ( *muon, muon::TM2DCompatibilityTight)));

		if(muon->innerTrack().isNonnull() && muon->innerTrack().isAvailable())
		{
			localMuon.SetD0 ( - (muon->innerTrack()->dxy(beamSpot)) );
			localMuon.SetD0Error (sqrt(pow(muon->innerTrack()->dxyError(),2)+pow(beamSpotHandle->BeamWidthX(),2)+ pow(beamSpotHandle->BeamWidthY(),2)));
			localMuon.SetDZ (muon->innerTrack()->dz(beamSpot));
			localMuon.SetDZError (muon->innerTrack()->dzError());
			localMuon.SetNofValidHits (muon->innerTrack()->numberOfValidHits ());
			localMuon.SetNofValidPixelHits(muon->innerTrack()->hitPattern().numberOfValidPixelHits());
			localMuon.SetNofTrackerLayersWithMeasurement(muon->innerTrack()->hitPattern().trackerLayersWithMeasurement());
		}

		if(muon->isGlobalMuon ())
		{
		  localMuon.SetNofValidMuHits(muon->globalTrack()->hitPattern().numberOfValidMuonHits());
		  localMuon.SetNofMatchedStations(muon->numberOfMatchedStations());
		}

		// Some specific methods to pat::Muon
		const pat::Muon * patMuon = dynamic_cast < const pat::Muon * >(&*muon);
		if(patMuon->innerTrack().isNonnull() && patMuon->innerTrack().isAvailable())
		{
			localMuon.SetdB(patMuon->dB());
			localMuon.SetdBError(patMuon->edB());
		}
		
    localMuon.SetChi2 (patMuon->normChi2 ());
		if (patMuon->ecalIsoDeposit ()) localMuon.SetVetoEm  (patMuon->ecalIsoDeposit ()->candEnergy ());
		if (patMuon->hcalIsoDeposit ()) localMuon.SetVetoHad (patMuon->hcalIsoDeposit ()->candEnergy ());
		
		if (useMC_)
		{
			// MC truth associator index
			if ((patMuon->genParticleRef ()).isNonnull ())
			{
				localMuon.setGenParticleIndex ((patMuon->genParticleRef ()).index ());
			}
			else
			{
				localMuon.setGenParticleIndex (-1);
			}
		}
			
		if(patMuon->chargedHadronIso() != -1) localMuon.SetChargedHadronIso(patMuon->chargedHadronIso());
  	if(patMuon->photonIso() != -1) localMuon.SetPhotonIso(patMuon->photonIso());
		if(patMuon->neutralHadronIso() != -1) localMuon.SetNeutralHadronIso(patMuon->neutralHadronIso());

		new ((*rootMuons)[j]) TRootMuon (localMuon);
		if (verbosity_ > 2)
			cout << "   [" << setw (3) << j << "] " << localMuon << endl;
	}
}
