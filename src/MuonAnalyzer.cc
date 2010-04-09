#include "../interface/MuonAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

MuonAnalyzer::MuonAnalyzer (const edm::ParameterSet & producersNames):
verbosity_ (0),
useMC_ (false)
{
  dataType_ = producersNames.getUntrackedParameter < string > ("dataType", "unknown");
  muonProducer_ = producersNames.getParameter < edm::InputTag > ("muonProducer");
}

MuonAnalyzer::MuonAnalyzer (const edm::ParameterSet & producersNames, const edm::ParameterSet & myConfig, int verbosity):
verbosity_ (verbosity)
{
  dataType_ = producersNames.getUntrackedParameter < string > ("dataType", "unknown");
  muonProducer_ = producersNames.getParameter < edm::InputTag > ("muonProducer");
  useMC_ = myConfig.getUntrackedParameter < bool > ("doMuonMC");
}

MuonAnalyzer::~MuonAnalyzer ()
{
}

void
MuonAnalyzer::Process (const edm::Event & iEvent, TClonesArray * rootMuons)
{

  Float_t sintheta = 0.;
  unsigned int nMuons = 0;

  edm::Handle < std::vector < reco::Muon > >recoMuons;
  if (dataType_ == "RECO" || dataType_ == "AOD")
    {
      iEvent.getByLabel (muonProducer_, recoMuons);
      nMuons = recoMuons->size ();
    }

  edm::Handle < std::vector < pat::Muon > >patMuons;
  if (dataType_ == "PAT" || dataType_ == "PATAOD")
    {
      iEvent.getByLabel (muonProducer_, patMuons);
      nMuons = patMuons->size ();
    }

  edm::Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);
  const TrackBase::Point & beamSpot = beamSpotHandle->position();


  if (verbosity_ > 1)
    std::cout << "   Number of muons = " << nMuons << "   Label: " << muonProducer_.label () << "   Instance: " << muonProducer_.instance () << std::endl;

  for (unsigned int j = 0; j < nMuons; j++)
    {

      const reco::Muon * muon = 0;
      if (dataType_ == "RECO" || dataType_ == "AOD")
	muon = &((*recoMuons)[j]);
      if (dataType_ == "PAT" || dataType_ == "PATAOD")
	muon = (const reco::Muon *) (&((*patMuons)[j]));

      TRootMuon localMuon (muon->px (), muon->py (), muon->pz (), muon->energy (), muon->vx (), muon->vy (), muon->vz (), muon->pdgId (), muon->charge ());

      // Variables from reco::Muon
      sintheta = sin (localMuon.Theta ());

      localMuon.setCaloEnergy (muon->calEnergy ().em * sintheta, muon->calEnergy ().had * sintheta, muon->calEnergy ().ho * sintheta, muon->caloCompatibility ());

      localMuon.setIsoR03 (muon->isolationR03 ().emEt, muon->isolationR03 ().hadEt, muon->isolationR03 ().hoEt, muon->isolationR03 ().sumPt, muon->isolationR03 ().nTracks, muon->isolationR03 ().nJets);


      localMuon.setValidity (muon->isEnergyValid (), muon->isMatchesValid (), muon->isIsolationValid ());

      localMuon.setDirection (muon->time ().direction ());
      localMuon.setAlgo (muon->type ());
      localMuon.setID (int ( muon::isGoodMuon ( *muon, muon::AllGlobalMuons)), int ( muon::isGoodMuon ( *muon, muon::AllTrackerMuons)), int ( muon::isGoodMuon ( *muon, muon::AllStandAloneMuons)), int ( muon::isGoodMuon ( *muon, muon::TrackerMuonArbitrated)), int ( muon::isGoodMuon ( *muon, muon::AllArbitrated)), int ( muon::isGoodMuon ( *muon, muon::GlobalMuonPromptTight)), int ( muon::isGoodMuon (*muon, muon::TMLastStationLoose)), int ( muon::isGoodMuon ( *muon, muon::TMLastStationTight)), int ( muon::isGoodMuon ( *muon, muon::TMOneStationLoose)), int ( muon::isGoodMuon ( *muon, muon::TMOneStationTight)), int ( muon::isGoodMuon ( *muon, muon::TMLastStationOptimizedLowPtLoose)), int ( muon::isGoodMuon ( *muon, muon::TMLastStationOptimizedLowPtTight)), int ( muon::isGoodMuon ( *muon, muon::TM2DCompatibilityLoose)), int ( muon::isGoodMuon ( *muon, muon::TM2DCompatibilityTight)));
      if (muon->isGlobalMuon ())
	{
	  localMuon.SetD0 (muon->innerTrack()->dxy(beamSpot));
	  localMuon.SetD0Error (sqrt(pow(muon->innerTrack()->dxyError(),2)+pow(beamSpotHandle->BeamWidthX(),2)+ pow(beamSpotHandle->BeamWidthY(),2)));
	  localMuon.SetDZ (muon->innerTrack()->dz(beamSpot));
	  localMuon.SetDZError (muon->innerTrack()->dzError());

	  localMuon.SetChi2 (muon->globalTrack()->normalizedChi2 ());
	  localMuon.SetNofValidHits (muon->innerTrack()->numberOfValidHits ());
	  localMuon.SetInnerTrack (TLorentzVector (muon->innerTrack()->px (), muon->innerTrack ()->py(), muon->innerTrack()->pz (), muon->innerTrack()->p ()));
	}
      
      if (dataType_ == "RECO" || dataType_ == "AOD")
	{
	  // Some specific methods requiring  RECO / AOD format
	  // Do association to genParticle ?
	  // Add InnerTrack, OuterTrack, GlobalTrack infos ?
	}

      if (dataType_ == "PATAOD" || dataType_ == "PAT")
	{
	  // Some specific methods to pat::Muon
	  const pat::Muon * patMuon = dynamic_cast < const pat::Muon * >(&*muon);
	  // Use existing reference to genParticle [ pat::PATObject::genParticleRef() ] ?
	  // Alternative methode for isolation (isoDeposit) ?
	  //
	  // leptonID apparently not initialised in PAT...
	  // cout << "Valeur pourrie du leptonID=" << patMuon->leptonID() << endl;

	  if (patMuon->ecalIsoDeposit ()) localMuon.SetVetoEm  (patMuon->ecalIsoDeposit ()->candEnergy ());
	  if (patMuon->hcalIsoDeposit ()) localMuon.SetVetoHad (patMuon->hcalIsoDeposit ()->candEnergy ());

	  if (patMuon->ecalIsoDeposit () && patMuon->hcalIsoDeposit ())
	    {
	      if (patMuon->ecalIsoDeposit ()->candEnergy () < 4 && patMuon->hcalIsoDeposit ()->candEnergy () < 6)
		localMuon.SetVetoIso (true);
	    }

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
	}

      new ((*rootMuons)[j]) TRootMuon (localMuon);
      if (verbosity_ > 2)
	cout << "   [" << setw (3) << j << "] " << localMuon << endl;
    }
}

