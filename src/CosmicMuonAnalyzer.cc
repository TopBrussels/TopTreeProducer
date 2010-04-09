#include "../interface/CosmicMuonAnalyzer.h"

#define PI 3.14159265

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

CosmicMuonAnalyzer::CosmicMuonAnalyzer (const edm::ParameterSet & producersNames):
  verbosity_ (0)
{
  dataType_ = producersNames.getUntrackedParameter < string > ("dataType", "unknown");
  vCosmicMuonProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vcosmicMuonProducer");
  CosmicMuonProducer_ = edm::InputTag(vCosmicMuonProducer[0]);
}

CosmicMuonAnalyzer::CosmicMuonAnalyzer (const edm::ParameterSet & producersNames, int iter ,  const edm::ParameterSet & myConfig, int verbosity):
verbosity_ (verbosity)
{
  dataType_ = producersNames.getUntrackedParameter < string > ("dataType", "unknown");
  vCosmicMuonProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vcosmicMuonProducer");
  CosmicMuonProducer_ = edm::InputTag(vCosmicMuonProducer[iter]);
}

CosmicMuonAnalyzer::~CosmicMuonAnalyzer ()
{
}

void
CosmicMuonAnalyzer::Process (const edm::Event & iEvent, TClonesArray * rootCosmicMuons, vector<TClonesArray*> rootCosmicMuonTracks)
{

  Float_t sintheta = 0.;

  unsigned int nmuons = 0;

  vector<reco::TrackRef> globalTracks, trackerTracks, standaloneTracks;

  edm::Handle < std::vector < reco::Muon > >recoMuons;
  edm::Handle<reco::TrackCollection> glTrackHandle, trTrackHandle, staTrackHandle;

  if (dataType_ == "RECO" || dataType_ == "AOD")
    {
      iEvent.getByLabel (CosmicMuonProducer_, recoMuons);
      nmuons = recoMuons->size ();

      //** STORE TRACK REFERENCES **//

      if (CosmicMuonProducer_.label() == "muons") {
	
	iEvent.getByLabel("globalCosmicMuons",glTrackHandle);
	iEvent.getByLabel("ctfWithMaterialTracksP5LHCNavigation",trTrackHandle);
	iEvent.getByLabel("cosmicMuons",staTrackHandle);

      }

      if (CosmicMuonProducer_.label() == "muons1Leg") {
	
	iEvent.getByLabel("globalCosmicMuons1Leg",glTrackHandle);
	iEvent.getByLabel("ctfWithMaterialTracksP5",trTrackHandle);
	iEvent.getByLabel("cosmicMuons1Leg",staTrackHandle);

      }

      if (CosmicMuonProducer_.label() == "muonsBarrelOnly") {
	
	iEvent.getByLabel("globalCosmicMuonsBarrelOnly",glTrackHandle);
	iEvent.getByLabel("ctfWithMaterialTracksP5LHCNavigation",trTrackHandle);
	iEvent.getByLabel("cosmicMuonsBarrelOnly",staTrackHandle);

      }

      if (CosmicMuonProducer_.label() == "muons1LegBarrelOnly") {
	
	iEvent.getByLabel("globalCosmicMuons1LegBarrelOnly",glTrackHandle);
	iEvent.getByLabel("ctfWithMaterialTracksP5",trTrackHandle);
	iEvent.getByLabel("cosmicMuons1LegBarrelOnly",staTrackHandle);

      }

    }

  edm::Handle < std::vector < pat::Muon > >patMuons;
  if (dataType_ == "PAT" || dataType_ == "PATAOD")
    {
      // not yet
    }

  //** STORE TRACKS IN THE EVENT (e.g.: those that are not mathed to a muon)

  for (unsigned int i=0; i<glTrackHandle->size(); i++) 
    globalTracks.push_back(reco::TrackRef(glTrackHandle,i));

  for (unsigned int i=0; i<trTrackHandle->size(); i++) 
    trackerTracks.push_back(reco::TrackRef(trTrackHandle,i));

  for (unsigned int i=0; i<staTrackHandle->size(); i++) 
    standaloneTracks.push_back(reco::TrackRef(staTrackHandle,i));

  if (verbosity_ > 1) {
   
    std::cout << "   Number of cosmic muon global tracks = " << glTrackHandle->size() << "   Label: " << CosmicMuonProducer_.label () << "   Instance: " << CosmicMuonProducer_.instance () << std::endl;

    std::cout << "   Number of cosmic muon tracker tracks = " << trTrackHandle->size() << "   Label: " << CosmicMuonProducer_.label () << "   Instance: " << CosmicMuonProducer_.instance () << std::endl;

    std::cout << "   Number cosmic muon standalone tracks = " << staTrackHandle->size() << "   Label: " << CosmicMuonProducer_.label () << "   Instance: " << CosmicMuonProducer_.instance () << std::endl;
    
  }

  //cout << "Remaining number of global tracks " << globalTracks.size() << endl;

  for (unsigned int i=0; i<3; i++) {

    vector<reco::TrackRef> refs;

    if (i==0) refs = globalTracks;
    else if (i==1) refs = trackerTracks;
    else if (i==2) refs = standaloneTracks;

    for (unsigned int j=0; j<refs.size(); j++) {
      
      reco::TrackRef Track = refs.at(j);

      TRootTrack track (TLorentzVector(Track->px(),Track->py(),Track->pz()),TVector3(Track->vx(),Track->vy(),Track->vz()),0,Track->charge());

      // Set the track properties
	  
      track.SetNofValidHits(Track->numberOfValidHits());
      track.SetChi2(Track->normalizedChi2());  
      track.SetD0(Track->d0());
      track.SetD0Error(Track->d0Error());
      track.SetDZ(Track->dz());
      track.SetDZError(Track->dzError());
      track.SetInnerPosition(Track->innerPosition().x(),Track->innerPosition().y(),Track->innerPosition().z());
      track.SetOuterPosition(Track->outerPosition().x(),Track->outerPosition().y(),Track->outerPosition().z());
   
      // put the tracks in their TClonesArray

      new ((*rootCosmicMuonTracks[i])[j]) TRootTrack (track);
      if (verbosity_ > 2 && i == 0)
	cout << "   [" << setw (3) << j << "] " << "Cosmic Muon Global Track"  << " <-> " <<  TRootTrack(track) << endl;

      if (verbosity_ > 2 && i == 1)
	cout << "   [" << setw (3) << j << "] " << "Cosmic Muon Tracker Track"  << " <-> " <<  TRootTrack(track) << endl;

      if (verbosity_ > 2 && i == 2)
	cout << "   [" << setw (3) << j << "] " << "Cosmic Muon StandAlone Track"  << " <-> " <<  TRootTrack(track) << endl;


    }
  }

  // start processing muons

  if (verbosity_ > 1) {
    std::cout << "   Number cosmic muons = " << nmuons << "   Label: " << CosmicMuonProducer_.label () << "   Instance: " << CosmicMuonProducer_.instance () << std::endl;

  }

    for (unsigned int j = 0; j < nmuons; j++) {

      const reco::Muon * muon = 0;
      if (dataType_ == "RECO" || dataType_ == "AOD")

	muon = &((*recoMuons)[j]);

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
      //localCosmicMuon.setID (int (muon::isGoodMuon (muon::TrackerMuonArbitrated)), int (muon::isGoodMuon (muon::AllArbitrated)), int (muon::isGoodMuon (muon::GlobalMuonPromptTight)), int (muon::isGoodMuon (muon::TMLastStationLoose)),int (muon::isGoodMuon (muon::TMLastStationTight)), int (muon::isGoodMuon (muon::TM2DCompatibilityLoose)), int (muon::isGoodMuon (muon::TM2DCompatibilityTight)));
      localCosmicMuon.setID (int ( muon::isGoodMuon ( *muon, muon::AllGlobalMuons)), int ( muon::isGoodMuon ( *muon, muon::AllTrackerMuons)), int ( muon::isGoodMuon ( *muon, muon::AllStandAloneMuons)), int ( muon::isGoodMuon ( *muon, muon::TrackerMuonArbitrated)), int ( muon::isGoodMuon ( *muon, muon::AllArbitrated)), int ( muon::isGoodMuon ( *muon, muon::GlobalMuonPromptTight)), int ( muon::isGoodMuon (*muon, muon::TMLastStationLoose)), int ( muon::isGoodMuon ( *muon, muon::TMLastStationTight)), int ( muon::isGoodMuon ( *muon, muon::TMOneStationLoose)), int ( muon::isGoodMuon ( *muon, muon::TMOneStationTight)), int ( muon::isGoodMuon ( *muon, muon::TMLastStationOptimizedLowPtLoose)), int ( muon::isGoodMuon ( *muon, muon::TMLastStationOptimizedLowPtTight)), int ( muon::isGoodMuon ( *muon, muon::TM2DCompatibilityLoose)), int ( muon::isGoodMuon ( *muon, muon::TM2DCompatibilityTight)));
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
      

      if (dataType_ == "RECO" || dataType_ == "AOD") {
	  // Some specific methods requiring  RECO / AOD format
	  // Do association to genParticle ?
	  // Add InnerTrack, OuterTrack, GlobalTrack infos ?

	// do the track match

	// global

	if (muon->globalTrack().isNonnull()) {

	  reco::TrackRef muontrack = muon->globalTrack();

	  for (unsigned int p=0; p<globalTracks.size(); p++) {

	    if (muontrack == globalTracks.at(p)) {

	      //TRef ref = TRef((*rootCosmicMuonTracks[0])[p]);

	      localCosmicMuon.SetGlobalTrack((TObject*)rootCosmicMuonTracks[0]->At(p));

	    }

	  }

	}

	// tracker

	if (muon->innerTrack().isNonnull()) {

	  reco::TrackRef muontrack = muon->innerTrack();

	  for (unsigned int p=0; p<trackerTracks.size(); p++) {

	    if (muontrack == trackerTracks.at(p)) {

	      localCosmicMuon.SetTrackerTrack((TObject*)rootCosmicMuonTracks[1]->At(p));

	    }

	  }

	}

	// StandAlone 
	  
	if (muon->outerTrack().isNonnull()) {

	  reco::TrackRef muontrack = muon->outerTrack();

	  for (unsigned int p=0; p<standaloneTracks.size(); p++) {

	    if (muontrack == standaloneTracks.at(p)) {

	      localCosmicMuon.SetStandAloneTrack((TObject*)rootCosmicMuonTracks[2]->At(p));

	    }

	  }

	}

      }

      if (dataType_ == "PATAOD" || dataType_ == "PAT") {
	  // not yet implemented Cosmics under PAT
      }

      new ((*rootCosmicMuons)[j]) TRootCosmicMuon (localCosmicMuon);
      if (verbosity_ > 2)
	cout << "   [" << setw (3) << j << "] " << localCosmicMuon << endl;


    }

}

