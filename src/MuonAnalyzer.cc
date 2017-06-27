#include "../interface/MuonAnalyzer.h"
#include "DataFormats/Candidate/interface/OverlapChecker.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;
using namespace isodeposit;

MuonAnalyzer::MuonAnalyzer (const edm::ParameterSet & myConfig, int verbosity):
verbosity_ (verbosity)
{
	useMC_       = myConfig.getUntrackedParameter < bool > ("doMuonMC");
   muon_ptMin_       = myConfig.getParameter<double>("muon_ptMin");
 applyBadMuonTagger_ = myConfig.getUntrackedParameter < bool > ("doBadMuonTagging");
 applyCloneMuonTagger_ = myConfig.getUntrackedParameter < bool > ("doCloneMuonTagging");
}


MuonAnalyzer::~MuonAnalyzer ()
{
}

void MuonAnalyzer::TagBadMuons(edm::EDGetTokenT<edm::PtrVector<reco::Muon>> token) {
	badMuonsToken_	= token;
}

void MuonAnalyzer::TagCloneMuons(edm::EDGetTokenT<edm::PtrVector<reco::Muon>> token) {
	cloneMuonsToken_	= token;
}

void
MuonAnalyzer::Process (const edm::Event & iEvent, TClonesArray * rootMuons,edm::EDGetTokenT<reco::BeamSpot> offlineBSToken, edm::EDGetTokenT<pat::MuonCollection> muonToken, edm::EDGetTokenT<reco::VertexCollection> vtxToken)
{
unsigned int nMuons = 0;
unsigned int nMuons_passedSkimming = 0;

	edm::Handle < std::vector < pat::Muon > >patMuons;
	iEvent.getByToken (muonToken, patMuons);
	nMuons = patMuons->size ();

  	edm::Handle< reco::VertexCollection > pvHandle;
  	iEvent.getByToken(vtxToken, pvHandle);

  	edm::Handle<reco::BeamSpot> beamSpotHandle;
  	iEvent.getByToken(offlineBSToken, beamSpotHandle);

	if (verbosity_ > 1)
		std::cout << "   Number of muons = " << nMuons << std::endl;

	// 80X bad and clone muons https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/2786.html
	edm::Handle<edm::PtrVector<reco::Muon>> badMuons;
	if (applyBadMuonTagger_) {
		try{
			iEvent.getByToken(badMuonsToken_, badMuons);
		} catch (...) {
			std::cerr << "tried to retrieve BadGlobalmuon  filter information and failed! " << std::endl;
		}
	}

	edm::Handle<edm::PtrVector<reco::Muon>> cloneMuons;
	if (applyCloneMuonTagger_) {
		try{
                        iEvent.getByToken(cloneMuonsToken_, cloneMuons);
                } catch (...) {
                        std::cerr << "tried to retrieve CloneGlobalmuon  filter information and failed! " << std::endl;
                }
	}
	
    for (unsigned int j = 0; j < nMuons; j++)
    {
      const pat::Muon*  patMuon = &((*patMuons)[j]);
      const reco::Muon* muon = (const reco::Muon *) patMuon;
      
      if (muon->pt() < muon_ptMin_) continue;

      TRootMuon localMuon (muon->px (), muon->py (), muon->pz (), muon->energy (), muon->vx (), muon->vy (), muon->vz (), muon->pdgId (), muon->charge ());

      localMuon.setAlgo (muon->type ());
      localMuon.setID (int ( muon::isGoodMuon ( *muon, muon::AllGlobalMuons)), int ( muon::isGoodMuon ( *muon, muon::AllTrackerMuons)), int ( muon::isGoodMuon ( *muon, muon::AllStandAloneMuons)), int ( muon::isGoodMuon ( *muon, muon::TrackerMuonArbitrated)), int ( muon::isGoodMuon ( *muon, muon::AllArbitrated)), int ( muon::isGoodMuon ( *muon, muon::GlobalMuonPromptTight)), int ( muon::isGoodMuon (*muon, muon::TMLastStationLoose)), int ( muon::isGoodMuon ( *muon, muon::TMLastStationTight)),int ( muon::isGoodMuon ( *muon, muon::TMLastStationAngTight)) , int ( muon::isGoodMuon ( *muon, muon::TMOneStationLoose)), int ( muon::isGoodMuon ( *muon, muon::TMOneStationTight)), int ( muon::isGoodMuon ( *muon, muon::TMLastStationOptimizedLowPtLoose)), int ( muon::isGoodMuon ( *muon, muon::TMLastStationOptimizedLowPtTight)), int ( muon::isGoodMuon ( *muon, muon::TM2DCompatibilityLoose)), int ( muon::isGoodMuon ( *muon, muon::TM2DCompatibilityTight)));


      const reco::BeamSpot &mybeamspot = *beamSpotHandle.product();

      localMuon.setD0BeamSpot ( muon->muonBestTrack()->dxy(mybeamspot.position()) );
      localMuon.setD0BeamSpotError ( sqrt(pow(muon->muonBestTrack()->dxyError(),2)+pow(mybeamspot.x0Error(),2)+ pow(mybeamspot.y0Error(),2)) );

      localMuon.setDzBeamSpot ( muon->muonBestTrack()->dz(mybeamspot.position()) );
      localMuon.setDzBeamSpotError ( sqrt(pow(muon->muonBestTrack()->dzError(),2)+pow(mybeamspot.x0Error(),2)+ pow(mybeamspot.y0Error(),2)) );


      if(muon->innerTrack().isNonnull() && muon->innerTrack().isAvailable())
      {


        if(pvHandle.isValid() && pvHandle->size() != 0)
        {
          reco::VertexRef vtx(pvHandle,0);
          localMuon.setD0 ( muon->muonBestTrack()->dxy(vtx->position()) );
          localMuon.setD0Error ( sqrt(pow(muon->muonBestTrack()->dxyError(),2)+pow(vtx->xError(),2)+ pow(vtx->yError(),2)) );


          localMuon.setDz ( muon->muonBestTrack()->dz(vtx->position()) );
          localMuon.setDzError ( sqrt(pow(muon->muonBestTrack()->dzError(),2)+pow(vtx->zError(),2)) );
        }
        else{
          localMuon.setD0 ( muon->innerTrack()->dxy() );
          localMuon.setD0Error ( muon->innerTrack()->dxyError() );
          localMuon.setDz ( muon->innerTrack()->dz() );
          localMuon.setDzError ( muon->innerTrack()->dzError() );

        }
        localMuon.setNofValidHits ( muon->innerTrack()->numberOfValidHits() );
        localMuon.setNofValidPixelHits( muon->innerTrack()->hitPattern().numberOfValidPixelHits() );
        localMuon.setNofTrackerLayersWithMeasurement( muon->innerTrack()->hitPattern().trackerLayersWithMeasurement() );
        localMuon.setValidFraction( muon->innerTrack()->validFraction());
      }

      if(muon->isGlobalMuon ())
      {
        localMuon.setNofValidMuHits(muon->globalTrack()->hitPattern().numberOfValidMuonHits());
        localMuon.setNofMatchedStations(muon->numberOfMatchedStations());
        localMuon.setChi2LocalPosition(muon->combinedQuality().chi2LocalPosition);
        localMuon.setTrkKink(muon->combinedQuality().trkKink);
        localMuon.setSegmentCompatibility( muon::segmentCompatibility(*patMuon) );
      }

      // Some specific methods to pat::Muon
      localMuon.setIsPFMuon(patMuon->isPFMuon());

      try {
        localMuon.setChi2 (patMuon->globalTrack()->normalizedChi2());
      }
      catch (cms::Exception &lce) {
        if (verbosity_ > 2)cout  << "MuonAnalyzer:: WARNING, unable to access muon normChi2 value!!!!" << endl;
        localMuon.setChi2 (+99999.);
      }

      if (useMC_)
      {
        // MC truth associator index
        if ((patMuon->genParticleRef ()).isNonnull ())
        {
          localMuon.setGenParticleIndex ((patMuon->genParticleRef ()).index ());
	  localMuon.setPID((patMuon->genParticle())->pdgId());
        }
        else
        {
          localMuon.setGenParticleIndex (-1);
        }
      }

      //set pf-isolation, old wrong(?) Iso
      //default cone size from PAT setup : currently r=0.4
/*      if(patMuon->chargedHadronIso() != -1)   localMuon.setIsoR04_ChargedHadronIso(patMuon->chargedHadronIso());
      if(patMuon->puChargedHadronIso() != -1) localMuon.setIsoR04_PuChargedHadronIso( patMuon->puChargedHadronIso() );
      if(patMuon->photonIso() != -1)          localMuon.setIsoR04_PhotonIso(patMuon->photonIso());
      if(patMuon->neutralHadronIso() != -1)   localMuon.setIsoR04_NeutralHadronIso(patMuon->neutralHadronIso());
*/
      // 19 May 2016, taken from
      // https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2#Muon_Isolation
      localMuon.setIsoR04_ChargedHadronIso(patMuon->pfIsolationR04().sumChargedHadronPt); 
      localMuon.setIsoR04_PuChargedHadronIso(patMuon->pfIsolationR04().sumPUPt);
      localMuon.setIsoR04_PhotonIso(patMuon->pfIsolationR04().sumPhotonEt);
      localMuon.setIsoR04_NeutralHadronIso(patMuon->pfIsolationR04().sumNeutralHadronEt);


       //this is for cone size r=0.3
      localMuon.setIsoR03_ChargedHadronIso(patMuon->pfIsolationR03().sumChargedHadronPt);
      localMuon.setIsoR03_PuChargedHadronIso(patMuon->pfIsolationR03().sumPUPt);
      localMuon.setIsoR03_PhotonIso(patMuon->pfIsolationR03().sumPhotonEt);
      localMuon.setIsoR03_NeutralHadronIso(patMuon->pfIsolationR03().sumNeutralHadronEt);
       

       //following Muon POG isolation definition
       AbsVetos veto_ch;
       AbsVetos veto_nh;
       AbsVetos veto_ph;
       Direction Dir = Direction(patMuon->eta(), patMuon->phi());
       veto_ch.push_back(new reco::isodeposit::ConeVeto( Dir, 0.0001 ));
       veto_nh.push_back(new reco::isodeposit::ConeVeto( Dir, 0.01 ));
       veto_nh.push_back(new reco::isodeposit::ThresholdVeto( 0.5 ));
       veto_ph.push_back(new reco::isodeposit::ConeVeto( Dir, 0.01 ));
       veto_ph.push_back(new reco::isodeposit::ThresholdVeto( 0.5 ));

       //80X https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/2786.html
       //80X ReReco data (see https://twiki.cern.ch/twiki/bin/view/CMSPublic/ReMiniAOD03Feb2017Notes#Muons)
       //In ReReco data bad muons have isPFMuon() flag removed, therefore TRootMuon is marked both 'bad' and 'clone' if isPFMuon() is not set
       OverlapChecker overlap;
       if (badMuons.isValid()) {
	       for ( auto badMuon : (*badMuons) ) {
			if ( overlap( *badMuon, *muon )) {
				localMuon.setBad80X();
			}
	       }
       }
       if (cloneMuons.isValid()) {
	       for ( auto cloneMuon : (*cloneMuons) ) {
			if ( overlap( *cloneMuon, *muon )) {
				localMuon.setClone80X();
			}
	       }
       }

      new ((*rootMuons)[nMuons_passedSkimming]) TRootMuon (localMuon);
      nMuons_passedSkimming++;
      if (verbosity_ > 2){
        cout << "   [" << setw (3) << j << "] " << localMuon << endl;
      }
      if (verbosity_ > 4){
        cout << "   [" << setw (3) << j << "] " << "CH: " << patMuon->pfIsolationR04().sumChargedHadronPt << endl;
        cout << "   [" << setw (3) << j << "] " << "NH: " << patMuon->pfIsolationR04().sumNeutralHadronEt << endl;
        cout << "   [" << setw (3) << j << "] " << "PU: " << patMuon->pfIsolationR04().sumPUPt << endl;
        cout << "   [" << setw (3) << j << "] " << "PH: " << patMuon->pfIsolationR04().sumPhotonEt << endl;
     }
   }
}
