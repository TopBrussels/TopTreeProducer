#include "../interface/MuonAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

MuonAnalyzer::MuonAnalyzer (const edm::ParameterSet & producersNames):
verbosity_ (0),
useMC_ (false)
{
  dataType_ = producersNames.getUntrackedParameter < string > ("dataType", "unknown");
  muonProducer_ = producersNames.getParameter < edm::InputTag > ("muonProducer");
  jetProducer_ = producersNames.getParameter < edm::InputTag > ("jetProducer");
}

MuonAnalyzer::MuonAnalyzer (const edm::ParameterSet & producersNames, const edm::ParameterSet & myConfig, int verbosity):
verbosity_ (verbosity)
{
  dataType_ = producersNames.getUntrackedParameter < string > ("dataType", "unknown");
  muonProducer_ = producersNames.getParameter < edm::InputTag > ("muonProducer");
  useMC_ = myConfig.getUntrackedParameter < bool > ("doMuonMC");
  jetProducer_ = producersNames.getParameter < edm::InputTag > ("jetProducer");
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

  unsigned int nJets = 0;
  // reco::CaloJet or reco::PFJet ?
  std::string jetType = "BASIC";
  if (jetProducer_.label () == "kt4CaloJets" || jetProducer_.label () == "kt6CaloJets" || jetProducer_.label () == "iterativeCone5CaloJets" || jetProducer_.label () == "sisCone5CaloJets" || jetProducer_.label () == "sisCone7CaloJets")
    jetType = "CALO";

  if (jetProducer_.label () == "kt4PFJets" || jetProducer_.label () == "kt6PFJets" || jetProducer_.label () == "iterativeCone5PFJets" || jetProducer_.label () == "sisCone5PFJets" || jetProducer_.label () == "sisCone7PFJets")
    jetType = "PF";

  edm::Handle < std::vector < reco::CaloJet > >recoCaloJets;
  if ((dataType_ == "RECO" || dataType_ == "AOD") && jetType == "CALO")
    {
      iEvent.getByLabel (jetProducer_, recoCaloJets);
      nJets = recoCaloJets->size ();
    }

  edm::Handle < std::vector < reco::PFJet > >recoPFJets;
  if ((dataType_ == "RECO" || dataType_ == "AOD") && jetType == "PF")
    {
      iEvent.getByLabel (jetProducer_, recoPFJets);
      nJets = recoPFJets->size ();
    }

  edm::Handle < std::vector < pat::Jet > >patJets;
  if (dataType_ == "PAT" || dataType_ == "PATAOD")
    {
      iEvent.getByLabel (jetProducer_, patJets);
      nJets = patJets->size ();
    }


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
      localMuon.setID (int (muon->isGood (reco::Muon::TrackerMuonArbitrated)), int (muon->isGood (reco::Muon::AllArbitrated)), int (muon->isGood (reco::Muon::GlobalMuonPromptTight)), int (muon->isGood (reco::Muon::TMLastStationLoose)),
		       int (muon->isGood (reco::Muon::TMLastStationTight)), int (muon->isGood (reco::Muon::TM2DCompatibilityLoose)), int (muon->isGood (reco::Muon::TM2DCompatibilityTight)));
      if (muon->isGlobalMuon ())
	{
	  localMuon.SetD0 (muon->innerTrack()->dxy(beamSpot));
	  localMuon.SetChi2 (muon->globalTrack()->normalizedChi2 ());
	  localMuon.SetNofValidHits (muon->innerTrack()->numberOfValidHits ());
	  localMuon.SetInnerTrack (TLorentzVector (muon->innerTrack()->px (), muon->innerTrack ()->py(), muon->innerTrack()->pz (), muon->innerTrack()->p ()));
	}
      
      const reco::Jet * jet = 0;
      float DeltaRMin = 999.;
      for (unsigned int k = 0; k < nJets; k++)
	{

	  if ((dataType_ == "RECO" || dataType_ == "AOD") && jetType == "CALO")
	    jet = (const reco::Jet *) (&((*recoCaloJets)[k]));
	  if ((dataType_ == "RECO" || dataType_ == "AOD") && jetType == "PF")
	    jet = (const reco::Jet *) (&((*recoPFJets)[k]));
	  if (dataType_ == "PAT" || dataType_ == "PATAOD")
	    {
	      jet = (const reco::Jet *) (&((*patJets)[k]));
	      if ((*patJets)[k].isCaloJet ())
		jetType = "CALO";
	      if ((*patJets)[k].isPFJet ())
		jetType = "PF";
	    }

	  if(jet && muon){
	    float val = ROOT::Math::VectorUtil::DeltaR (jet->p4 (), muon->p4 ());
	    if (val < DeltaRMin)
	      DeltaRMin = val;
	  }
	}
      localMuon.SetDeltaRClosestJet (DeltaRMin);

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
