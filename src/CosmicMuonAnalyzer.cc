#include "../interface/CosmicMuonAnalyzer.h"

#define PI 3.14159265

using namespace std;
using namespace reco;
using namespace edm;

CosmicMuonAnalyzer::CosmicMuonAnalyzer (const edm::ParameterSet & producersNames):
  verbosity_ (0)
{
  dataType_ = producersNames.getUntrackedParameter < string > ("dataType", "unknown");
  CosmicMuonProducer1Leg_ = producersNames.getParameter < edm::InputTag > ("CosmicMuonProducer1Leg");
  CosmicMuonProducer2Leg_ = producersNames.getParameter < edm::InputTag > ("CosmicMuonProducer2Leg");
  jetProducer_ = producersNames.getParameter < edm::InputTag > ("jetProducer");
}

CosmicMuonAnalyzer::CosmicMuonAnalyzer (const edm::ParameterSet & producersNames, const edm::ParameterSet & myConfig, int verbosity):
verbosity_ (verbosity)
{
  dataType_ = producersNames.getUntrackedParameter < string > ("dataType", "unknown");
  CosmicMuonProducer1Leg_ = producersNames.getParameter < edm::InputTag > ("CosmicMuonProducer1Leg");
  CosmicMuonProducer2Leg_ = producersNames.getParameter < edm::InputTag > ("CosmicMuonProducer2Leg");
  jetProducer_ = producersNames.getParameter < edm::InputTag > ("jetProducer");
}

CosmicMuonAnalyzer::~CosmicMuonAnalyzer ()
{
}

void
CosmicMuonAnalyzer::Process (const edm::Event & iEvent, TClonesArray * rootCosmicMuons)
{

  Float_t sintheta = 0.;

  unsigned int nMuons1Leg = 0, nMuons2Leg = 0;

  edm::Handle < std::vector < reco::Muon > >recoMuons1Leg, recoMuons2Leg;
  if (dataType_ == "RECO" || dataType_ == "AOD")
    {
      iEvent.getByLabel (CosmicMuonProducer1Leg_, recoMuons1Leg);
      iEvent.getByLabel (CosmicMuonProducer2Leg_, recoMuons2Leg);
      nMuons1Leg = recoMuons1Leg->size ();
      nMuons2Leg = recoMuons2Leg->size ();
    }

  edm::Handle < std::vector < pat::Muon > >patMuons;
  if (dataType_ == "PAT" || dataType_ == "PATAOD")
    {
      // not yet
    }

   unsigned int nJets = 0;
  // reco::CaloJet or reco::PFJet ?
  std::string jetType = "CALO";
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




  if (verbosity_ > 1) {
    std::cout << "   Number of 1Leg muons = " << nMuons1Leg << "   Label: " << CosmicMuonProducer1Leg_.label () << "   Instance: " << CosmicMuonProducer1Leg_.instance () << std::endl;
    
    std::cout << "   Number of 2Leg muons = " << nMuons2Leg << "   Label: " << CosmicMuonProducer2Leg_.label () << "   Instance: " << CosmicMuonProducer2Leg_.instance () << std::endl;

  }

  for (int k=0; k<2; k++) {

    int size=0;

    if (k == 0)
      size=nMuons1Leg;
    else
      size=nMuons2Leg;

    for (int j = 0; j < size; j++) {

      const reco::Muon * muon = 0;
      if (dataType_ == "RECO" || dataType_ == "AOD")
	if (k==0)
	  muon = &((*recoMuons1Leg)[j]);
	else 
	  muon = &((*recoMuons2Leg)[j]);

      /*if (dataType_ == "PAT" || dataType_ == "PATAOD")
	muon = (const reco::Muon *) (&((*patMuons)[j]));*/

      TRootCosmicMuon localCosmicMuon (muon->px (), muon->py (), muon->pz (), muon->energy (), muon->vx (), muon->vy (), muon->vz (), muon->pdgId (), muon->charge ());

      // Variables from reco::Muon
      sintheta = sin (localCosmicMuon.Theta ());

      localCosmicMuon.setCaloEnergy (muon->calEnergy ().em * sintheta, muon->calEnergy ().had * sintheta, muon->calEnergy ().ho * sintheta, muon->caloCompatibility ());

      localCosmicMuon.setIsoR03 (muon->isolationR03 ().emEt, muon->isolationR03 ().hadEt, muon->isolationR03 ().hoEt, muon->isolationR03 ().sumPt, muon->isolationR03 ().nTracks, muon->isolationR03 ().nJets);

      localCosmicMuon.setIsoR05 (muon->isolationR05 ().emEt, muon->isolationR05 ().hadEt, muon->isolationR05 ().hoEt, muon->isolationR05 ().sumPt, muon->isolationR05 ().nTracks, muon->isolationR05 ().nJets);

      localCosmicMuon.setValidity (muon->isEnergyValid (), muon->isMatchesValid (), muon->isIsolationValid ());

      localCosmicMuon.setDirection (muon->time ().direction ());
      localCosmicMuon.setAlgo (muon->type ());
      localCosmicMuon.setID (int (muon->isGood (reco::Muon::TrackerMuonArbitrated)), int (muon->isGood (reco::Muon::AllArbitrated)), int (muon->isGood (reco::Muon::GlobalMuonPromptTight)), int (muon->isGood (reco::Muon::TMLastStationLoose)),
		       int (muon->isGood (reco::Muon::TMLastStationTight)), int (muon->isGood (reco::Muon::TM2DCompatibilityLoose)), int (muon->isGood (reco::Muon::TM2DCompatibilityTight)));
      if (muon->isGlobalMuon ()) {
	localCosmicMuon.SetD0 ((muon->globalTrack())->d0());
	localCosmicMuon.SetD0Error ((muon->globalTrack())->d0Error());
	localCosmicMuon.SetDZ ((muon->globalTrack())->dz());
	localCosmicMuon.SetDZError ((muon->globalTrack())->dzError());
	localCosmicMuon.SetChi2 ((muon->globalTrack())->normalizedChi2 ());
	localCosmicMuon.SetNofValidHits ((muon->innerTrack())->numberOfValidHits ());
	localCosmicMuon.SetNofValidHitsMuonDetector ((muon->outerTrack())->numberOfValidHits ());
	localCosmicMuon.SetInnerTrack (TLorentzVector (muon->innerTrack()->px (), muon->innerTrack ()->py(), muon->innerTrack()->pz (), muon->innerTrack()->p ()));
      }
      

      const reco::Jet * jet = 0;
      float DeltaRMin = 999.;
      for (unsigned int l = 0; l < nJets; l++)
	{

	  if ((dataType_ == "RECO" || dataType_ == "AOD") && jetType == "CALO")
	    jet = (const reco::Jet *) (&((*recoCaloJets)[k]));
	  if ((dataType_ == "RECO" || dataType_ == "AOD") && jetType == "PF")
	    jet = (const reco::Jet *) (&((*recoPFJets)[k]));
	  

	  if(jet && muon){
	    //float val = ROOT::Math::VectorUtil::DeltaR (jet->p4 (), muon->p4 ()); // produces a glibc error after a few events

	    double phi1 = muon->phi();
	    double phi2 = jet->phi();

	    double phia=phi1;
	    if(phi1>PI) phia=phi1-(2*PI);
	    double phib=phi2;
	    if(phi2>PI) phib=phi2-(2*PI);
	    double dphi=phia-phib;
	    if(dphi>PI) dphi-=(2*PI);
	    if(dphi<-PI) dphi+=(2*PI);
	    
	    double deta = muon->eta()-jet->eta();

	    float val=sqrt(pow(deta,2)+pow(dphi,2));
	    if (val < DeltaRMin)
	      DeltaRMin = val;
	  }
      }

      localCosmicMuon.SetDeltaRClosestJet (DeltaRMin);

      if (k == 0) 
	localCosmicMuon.SetOneLeg (true);
      else
	localCosmicMuon.SetOneLeg (false);


      if (dataType_ == "RECO" || dataType_ == "AOD") {
	  // Some specific methods requiring  RECO / AOD format
	  // Do association to genParticle ?
	  // Add InnerTrack, OuterTrack, GlobalTrack infos ?
      }

      if (dataType_ == "PATAOD" || dataType_ == "PAT") {
	  // not yet implemented Cosmics under PAT
      }

      int l=0;

      if (k == 0)
	l = j;
      else
	l = nMuons1Leg+j;

      new ((*rootCosmicMuons)[l]) TRootCosmicMuon (localCosmicMuon);
      if (verbosity_ > 2)
	cout << "   [" << setw (3) << l << "] " << localCosmicMuon << endl;
    }

  }
}

