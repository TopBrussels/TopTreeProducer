#include "../interface/CosmicMuonTrackAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

CosmicMuonTrackAnalyzer::CosmicMuonTrackAnalyzer (const edm::ParameterSet & producersNames):
  verbosity_ (0)
{
  dataType_ = producersNames.getUntrackedParameter < string > ("dataType", "unknown");
  CosmicMuonProducer1Leg_ = producersNames.getParameter < edm::InputTag > ("CosmicMuonProducer1Leg");
  CosmicMuonProducer2Leg_ = producersNames.getParameter < edm::InputTag > ("CosmicMuonProducer2Leg");
}

CosmicMuonTrackAnalyzer::CosmicMuonTrackAnalyzer (const edm::ParameterSet & producersNames, const edm::ParameterSet & myConfig, int verbosity):
verbosity_ (verbosity)
{
  dataType_ = producersNames.getUntrackedParameter < string > ("dataType", "unknown");
  CosmicMuonProducer1Leg_ = producersNames.getParameter < edm::InputTag > ("CosmicMuonProducer1Leg");
  CosmicMuonProducer2Leg_ = producersNames.getParameter < edm::InputTag > ("CosmicMuonProducer2Leg");
}

CosmicMuonTrackAnalyzer::~CosmicMuonTrackAnalyzer ()
{
}

void
CosmicMuonTrackAnalyzer::Process(const edm::Event& iEvent, std::string trackType, TClonesArray* rootCosmicMuonTracks)
{

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

  if (verbosity_ > 1) {
    std::cout << "CosmicsMuonTrackAnalyzer:  Number of 1Leg muons = " << nMuons1Leg << "   Label: " << CosmicMuonProducer1Leg_.label () << "   Instance: " << CosmicMuonProducer1Leg_.instance () << std::endl;
    
    std::cout << "CosmicsMuonTrackAnalyzer:  Number of 2Leg muons = " << nMuons2Leg << "   Label: " << CosmicMuonProducer2Leg_.label () << "   Instance: " << CosmicMuonProducer2Leg_.instance () << std::endl;

  }

  for (int k=0; k<2; k++) {
    //int k=0;
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


	reco::TrackRef Track;

	bool validTrack=false;

	// decide which kind of track

	if (trackType == "TrackerTrack") {
	  
	  Track = muon->innerTrack();
	  
	  if (Track.isNonnull())
	    validTrack = true;
	}

	else if (trackType == "StandAloneTrack") {

	  Track = muon->outerTrack();

	  if (Track.isNonnull())
	    validTrack = true;
	}
	
	else if (trackType == "GlobalTrack") {
	  
	  Track = muon->globalTrack();
	  
	  if (Track.isNonnull())
	    validTrack = true;
	}

	else 
	  continue; // if undecided -> skip event

	// create index to store track

	int l=0;

	if (k == 0)
	  l = j;
	else
	  l = nMuons1Leg+j;

	// fill in track properties and write it to branch

	if (validTrack) {
	
	  TRootTrack track (TLorentzVector(Track->px(),Track->py(),Track->pz()),TVector3(Track->vx(),Track->vy(),Track->vz()),muon->type(),Track->charge());

	  // Set the track properties

	  track.SetValid(true);
	  
	  track.SetNofValidHits(Track->numberOfValidHits());
	  
	  track.SetChi2(Track->normalizedChi2());

	  track.SetD0(Track->d0());
	  track.SetD0Error(Track->d0Error());
	  track.SetDZ(Track->dz());
	  track.SetDZError(Track->dzError());
	  
	  track.SetInnerPosition(Track->innerPosition().x(),Track->innerPosition().y(),Track->innerPosition().z());
	  track.SetOuterPosition(Track->outerPosition().x(),Track->outerPosition().y(),Track->outerPosition().z());

	  // put the tracks in their TClonesArray

	
	  new ((*rootCosmicMuonTracks)[l]) TRootTrack (track);
	  if (verbosity_ > 2)
	    cout << "   [" << setw (3) << l << "] " << trackType << " <-> " <<  TRootTrack(track) << endl;

	} else {

	  TRootTrack fakeTrack (TLorentzVector(-9999,-9999,-9999),TVector3(-9999,-9999,-9999),-9999,-9999);

	  fakeTrack.SetValid(false);

	  new ((*rootCosmicMuonTracks)[l]) TRootTrack (fakeTrack);
	  if (verbosity_ > 2)
	    cout << "   [" << setw (3) << l << "] " << "fake track" << endl;

	}
    }  

  }
 
}

