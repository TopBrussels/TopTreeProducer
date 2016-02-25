#include "../interface/ElectronAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;
using namespace isodeposit;

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
  useMC_ = myConfig.getUntrackedParameter<bool>("doElectronMC");
  isData_ = myConfig.getUntrackedParameter<bool>("isData");
  runSuperCluster_ = myConfig.getUntrackedParameter<bool>("runSuperCluster",false);
  doPrimaryVertex_ = myConfig.getUntrackedParameter<bool>("doPrimaryVertex");
}

ElectronAnalyzer::~ElectronAnalyzer()
{
}

void ElectronAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootElectrons, const edm::EventSetup& iSetup, edm::EDGetTokenT<reco::BeamSpot> offlineBSToken, edm::EDGetTokenT<edm::View<pat::Electron>> electronToken, edm::EDGetTokenT<reco::VertexCollection> vtxToken, edm::EDGetTokenT<edm::ValueMap<bool> > eleLooseIdMapToken, edm::EDGetTokenT<edm::ValueMap<bool> > eleMediumIdMapToken, edm::EDGetTokenT<edm::ValueMap<bool> > eleTightIdMapToken, edm::EDGetTokenT<edm::ValueMap<float> > EleMVAValuesMapToken, edm::EDGetTokenT<edm::ValueMap<int> > EleMVACategoriesMapToken)
{
  unsigned int nElectrons=0;

  edm::Handle < edm::View<pat::Electron> > patElectrons;
  iEvent.getByToken(electronToken, patElectrons);
  nElectrons = patElectrons->size();

  edm::Handle< reco::VertexCollection > pvHandle;
  iEvent.getByToken(vtxToken, pvHandle);

  edm::Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByToken(offlineBSToken, beamSpotHandle);

  // Get the electron ID data from the event stream.
  // Note: this implies that the VID ID modules have been run upstream.
  // If you need more info, check with the EGM group.
  edm::Handle<edm::ValueMap<bool> > loose_id_decisions;
  edm::Handle<edm::ValueMap<bool> > medium_id_decisions;
  edm::Handle<edm::ValueMap<bool> > tight_id_decisions; 
  iEvent.getByToken(eleLooseIdMapToken,loose_id_decisions);
  iEvent.getByToken(eleMediumIdMapToken,medium_id_decisions);
  iEvent.getByToken(eleTightIdMapToken,tight_id_decisions);

  // Get MVA values and categories (optional)
  edm::Handle<edm::ValueMap<float> > mvaValues;
  edm::Handle<edm::ValueMap<int> > mvaCategories;
  iEvent.getByToken(EleMVAValuesMapToken,mvaValues);
  iEvent.getByToken(EleMVACategoriesMapToken,mvaCategories);

  if(verbosity_>1) std::cout << "   Number of electrons = " << nElectrons << std::endl;

  //std::vector <reco::GsfElectron> electrons = (std::vector <reco::GsfElectron>) patElectrons;
  for (unsigned int j=0; j<nElectrons; j++)
  {
    const pat::Electron*  patElectron = &((*patElectrons)[j]);//dynamic_cast<const pat::Electron*>(&*electron);
    const reco::GsfElectron* electron = (const reco::GsfElectron*) patElectron;//( & ((*patElectrons)[j]) );
    const auto el = patElectrons->ptrAt(j);
     
    TRootElectron localElectron(
                                electron->px()
                                ,electron->py()
                                ,electron->pz()
                                ,electron->energy()
                                ,electron->vx()
                                ,electron->vy()
                                ,electron->vz()
                                ,electron->pdgId()
                                ,electron->charge()
                                );

    //cout<<"in electronAnalyzer...1"<<endl;
    //=======================================
    localElectron.setEcalSeeding(electron->ecalDrivenSeed());
    localElectron.setTrackerSeeding(electron->trackerDrivenSeed());
    localElectron.setEnergySuperClusterOverP(electron->eSuperClusterOverP());
    localElectron.setEnergyEleClusterOverPout(electron->eEleClusterOverPout());
    localElectron.setEnergySeedClusterOverPout(electron->eSeedClusterOverPout());

    localElectron.setDeltaEtaIn(electron->deltaEtaSuperClusterTrackAtVtx());
    localElectron.setDeltaEtaOut(electron->deltaEtaSeedClusterTrackAtCalo());
    localElectron.setDeltaPhiIn(electron->deltaPhiSuperClusterTrackAtVtx());
    localElectron.setDeltaPhiOut(electron->deltaPhiSeedClusterTrackAtCalo());
    localElectron.setDeltaPhiSuperClusterTrackAtCalo(electron->deltaPhiEleClusterTrackAtCalo());
    localElectron.setDeltaEtaSuperClusterTrackAtCalo(electron->deltaEtaEleClusterTrackAtCalo());
    localElectron.setIsEBEEGap(electron->isEBEEGap());

    localElectron.setFbrem(electron->fbrem());
    localElectron.setNBrems(electron->numberOfBrems());

    //setShowerShape
    localElectron.setE1x5( electron->e1x5() );
    localElectron.setE5x5( electron->e5x5() );
    localElectron.setHoverEDepth1( electron->hcalDepth1OverEcal() );
    localElectron.setHoverEDepth2( electron->hcalDepth2OverEcal() );
    localElectron.setSigmaIetaIeta_full5x5( electron->full5x5_sigmaIetaIeta() );
    localElectron.setSigmaIetaIeta( electron->sigmaIetaIeta() );

    // switching to gsf track for miniAOD, seems this is the correct thing for
    //now
    reco::GsfTrackRef myTrackRef = electron->gsfTrack();

   if ( myTrackRef.isNonnull() )
    {
	    const reco::HitPattern& hit = myTrackRef->hitPattern();
	    localElectron.setPixelLayersWithMeasurement(hit.pixelLayersWithMeasurement());
	    localElectron.setStripLayersWithMeasurement(hit.stripLayersWithMeasurement());
        localElectron.setTrackNormalizedChi2(myTrackRef->normalizedChi2());
        localElectron.setNValidHits(myTrackRef->numberOfValidHits());
    }

    reco::GsfTrackRef gsfTrack = electron->gsfTrack();

    if ( gsfTrack.isNonnull() )
    {
      localElectron.setGsfTrackNormalizedChi2(gsfTrack->normalizedChi2());
      localElectron.setTrackMissingHits(gsfTrack->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS));
      localElectron.setGsfTrackChi2(gsfTrack->chi2());
      localElectron.setGsfTrackNdof(gsfTrack->ndof());

      if(doPrimaryVertex_ && pvHandle.isValid() && pvHandle->size() != 0){
        reco::VertexRef vtx(pvHandle, 0);
        localElectron.setD0( gsfTrack->dxy(vtx->position()) );
        localElectron.setD0Error( sqrt( pow(gsfTrack->dxyError(),2) + pow(vtx->xError(),2) + pow(vtx->yError(),2) ) );
  	localElectron.setDz( gsfTrack->dz(vtx->position()) );
	localElectron.setDzError( gsfTrack->dzError());


	// get the beam spot and use that to get relative position. Used in displaced lepton analysis 
	const reco::BeamSpot &mybeamspot = *beamSpotHandle.product();
	localElectron.setD0BeamSpot(patElectron->gsfTrack()->dxy(mybeamspot.position()));
	localElectron.setD0BeamSpotError( sqrt( pow(patElectron->gsfTrack()->dxyError(),2) + pow(mybeamspot.x0Error(),2) + pow(mybeamspot.y0Error(),2) ) );
	localElectron.setDzBeamSpot(patElectron->gsfTrack()->dz(mybeamspot.position()));
	localElectron.setDzBeamSpotError( sqrt( pow(patElectron->gsfTrack()->dzError(),2) + pow(mybeamspot.x0Error(),2) + pow(mybeamspot.y0Error(),2) ) );

	localElectron.setIp3d( patElectron->ip3d() );

      }
    }
    else if ( myTrackRef.isNonnull() )
    {

      if(doPrimaryVertex_ && pvHandle.isValid() && pvHandle->size() != 0)
	    {
	      reco::VertexRef vtx(pvHandle, 0);
        localElectron.setD0( myTrackRef->dxy(vtx->position()) );
        localElectron.setD0Error( sqrt( pow(myTrackRef->dxyError(),2) + pow(vtx->xError(),2) + pow(vtx->yError(),2) ) );
  	    localElectron.setDz( myTrackRef->dz(vtx->position()) );
      }
    }

    reco::SuperClusterRef superCluster = electron->superCluster();
    if ( superCluster.isNonnull() && runSuperCluster_ )
	  {
	    localElectron.setSuperClusterRawEnergy(superCluster->rawEnergy());
	    localElectron.setSuperClusterEta(superCluster->eta());
	    localElectron.setPreshowerEnergy(superCluster->preshowerEnergy());
      if ( gsfTrack.isNonnull() ) localElectron.setIoEmIoPgsf( (1./superCluster->energy()) - (1./gsfTrack->p()) );
      localElectron.setEtaWidth( superCluster->etaWidth() );
      localElectron.setPhiWidth( superCluster->phiWidth() );
	  }

      if( patElectron->ecalEnergy() > 0.0)  //electron cut based ID variable
      {
          float elESCP = patElectron->eSuperClusterOverP();
          float elinv_ecal_e = 1.0/(patElectron->ecalEnergy());
          float elIoEmIoP = abs(1.0 - elESCP)*elinv_ecal_e;
          localElectron.setIoEmIoP(elIoEmIoP);
      }

    // Some specific methods to pat::Electron
    TLorentzVector ecalDrivenMomentum(patElectron->ecalDrivenMomentum().px(),patElectron->ecalDrivenMomentum().py(),patElectron->ecalDrivenMomentum().pz(),patElectron->ecalDrivenMomentum().energy());
    localElectron.setEcalDrivenMomentum(ecalDrivenMomentum);

    // Matched genParticle
    if(useMC_)
	  {
	    if ((patElectron->genParticleRef()).isNonnull()) localElectron.setGenParticleIndex((patElectron->genParticleRef()).index());
	    else localElectron.setGenParticleIndex(-1);
	  }

    //set pf-isolation
    //default cone size from PAT setup : currently r=0.3
    if(patElectron->chargedHadronIso() != -1) localElectron.setIsoR03_ChargedHadronIso(patElectron->chargedHadronIso());
    if(patElectron->puChargedHadronIso() != -1) localElectron.setIsoR03_PuChargedHadronIso( patElectron->puChargedHadronIso() );
    if(patElectron->photonIso() != -1) localElectron.setIsoR03_PhotonIso(patElectron->photonIso());
    if(patElectron->neutralHadronIso() != -1) localElectron.setIsoR03_NeutralHadronIso(patElectron->neutralHadronIso());

    //this is for cone size r=0.4
    //following EGM POG isolation definition
    AbsVetos veto_ch;
    AbsVetos veto_nh;
    AbsVetos veto_ph;
    Direction Dir = Direction(patElectron->superCluster()->eta(), patElectron->superCluster()->phi());
    if( fabs( patElectron->superCluster()->eta() ) > 1.479 ){
      veto_ch.push_back(new reco::isodeposit::ConeVeto( Dir, 0.015 ));
      veto_ph.push_back(new reco::isodeposit::ConeVeto( Dir, 0.08 ));
    }

    localElectron.setPassConversion(patElectron->passConversionVeto());
    localElectron.setSigmaIphiIphi( patElectron->sigmaIphiIphi() );
    localElectron.setSigmaIetaIphi( patElectron->sigmaIetaIphi() );
    localElectron.setR9( patElectron->r9() );

    // verbose printout of electron IDs available:
    if(verbosity_>2){
      std::vector<std::pair<std::string, float> > eleIds = patElectron->electronIDs();
      std::cout << "electron ID summary: " << std::endl;
      for(UInt_t ii=0; ii<eleIds.size(); ii++){
	  std::cout << eleIds[ii].first << " " << eleIds[ii].second << std::endl;
      }
    }
    bool isPassLoose = (*loose_id_decisions)[el];
    bool isPassMedium = (*medium_id_decisions)[el];
    bool isPassTight  = (*tight_id_decisions)[el];
    float mvaValue = (*mvaValues)[el];
    float mvaCategory =  (*mvaCategories)[el];

    localElectron.setisMVA_TightID( isPassTight );// https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
    localElectron.setisMVA_MediumID( isPassMedium );// https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
    localElectron.setisMVA_LooseID( isPassLoose );// https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
    localElectron.setMVA_value( mvaValue );// https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
    localElectron.setMVA_category( mvaCategory );// https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
    
    new( (*rootElectrons)[j] ) TRootElectron(localElectron);
    if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localElectron << endl;
}

}
