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
  electron_ptMin_ = myConfig.getParameter<double>("electron_ptMin");
}

ElectronAnalyzer::~ElectronAnalyzer()
{
}

void ElectronAnalyzer::Process(
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
)
{
  unsigned int nElectrons=0;
  unsigned int nElectrons_passedSkimming = 0;

  edm::Handle < pat::ElectronCollection > patElectrons_calibrated;
  iEvent.getByToken(electronToken_calibrated, patElectrons_calibrated);

  edm::Handle < pat::ElectronCollection > patElectrons_uncalibrated;
  iEvent.getByToken(electronToken_uncalibrated, patElectrons_uncalibrated);

  edm::Handle < edm::View<reco::GsfElectron> > gsfElectrons;
  iEvent.getByToken(GsfelectronToken, gsfElectrons);
  nElectrons = gsfElectrons->size();

  edm::Handle< reco::VertexCollection > pvHandle;
  iEvent.getByToken(vtxToken, pvHandle);

  edm::Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByToken(offlineBSToken, beamSpotHandle);

  // Get the electron ID data from the event stream.
  // Note: this implies that the VID ID modules have been run upstream.
  // If you need more info, check with the EGM group.
  edm::Handle<edm::ValueMap<bool> > MVA_medium_id_decisions;
  edm::Handle<edm::ValueMap<bool> > MVA_tight_id_decisions; 
  edm::Handle<edm::ValueMap<bool> > CB_veto_id_decisions;
  edm::Handle<edm::ValueMap<bool> > CB_loose_id_decisions;
  edm::Handle<edm::ValueMap<bool> > CB_medium_id_decisions;
  edm::Handle<edm::ValueMap<bool> > CB_tight_id_decisions; 
  edm::Handle<edm::ValueMap<bool> > CB_heep_id_decisions;

  iEvent.getByToken(eleMediumMVAIdMapToken,MVA_medium_id_decisions);
  iEvent.getByToken(eleTightMVAIdMapToken,MVA_tight_id_decisions);
  iEvent.getByToken(eleVetoCBIdMapToken,CB_veto_id_decisions);
  iEvent.getByToken(eleLooseCBIdMapToken,CB_loose_id_decisions);
  iEvent.getByToken(eleMediumCBIdMapToken,CB_medium_id_decisions);
  iEvent.getByToken(eleTightCBIdMapToken,CB_tight_id_decisions);
  iEvent.getByToken(eleHEEPCBIdMapToken,CB_heep_id_decisions);

  // Get MVA values and categories (optional)
  edm::Handle<edm::ValueMap<float> > mvaValues;
  edm::Handle<edm::ValueMap<int> > mvaCategories;
  iEvent.getByToken(mvaValuesMapToken,mvaValues);
  iEvent.getByToken(mvaCategoriesMapToken,mvaCategories);

  if(verbosity_>1) std::cout << "   Number of electrons = " << nElectrons << std::endl;

  for (unsigned int j=0; j<nElectrons; j++)
  {
    const pat::Electron&  patElectron_calibrated = patElectrons_calibrated->at(j);
    
    if (patElectron_calibrated.pt() < electron_ptMin_) continue;
    
     
    TRootElectron localElectron(
                                patElectron_calibrated.px()
                                ,patElectron_calibrated.py()
                                ,patElectron_calibrated.pz()
                                ,patElectron_calibrated.energy()
                                ,patElectron_calibrated.vx()
                                ,patElectron_calibrated.vy()
                                ,patElectron_calibrated.vz()
                                ,patElectron_calibrated.pdgId()
                                ,patElectron_calibrated.charge()
                                );

    if(j <= patElectrons_uncalibrated->size())
    {
        const pat::Electron&  patElectron_uncalibrated = patElectrons_uncalibrated->at(j);
        
        localElectron.setunCalibratedPt(patElectron_uncalibrated.pt());
    }

    //cout<<"in electronAnalyzer...1"<<endl;
    //=======================================
    localElectron.setEcalSeeding(patElectron_calibrated.ecalDrivenSeed());
    localElectron.setTrackerSeeding(patElectron_calibrated.trackerDrivenSeed());
    localElectron.setEnergySuperClusterOverP(patElectron_calibrated.eSuperClusterOverP());
    localElectron.setEnergyEleClusterOverPout(patElectron_calibrated.eEleClusterOverPout());
    localElectron.setEnergySeedClusterOverPout(patElectron_calibrated.eSeedClusterOverPout());

    localElectron.setDeltaEtaIn(patElectron_calibrated.deltaEtaSuperClusterTrackAtVtx());
    localElectron.setDeltaEtaOut(patElectron_calibrated.deltaEtaSeedClusterTrackAtCalo());
    localElectron.setDeltaPhiIn(patElectron_calibrated.deltaPhiSuperClusterTrackAtVtx());
    localElectron.setDeltaPhiOut(patElectron_calibrated.deltaPhiSeedClusterTrackAtCalo());
    localElectron.setDeltaPhiSuperClusterTrackAtCalo(patElectron_calibrated.deltaPhiEleClusterTrackAtCalo());
    localElectron.setDeltaEtaSuperClusterTrackAtCalo(patElectron_calibrated.deltaEtaEleClusterTrackAtCalo());
    localElectron.setIsEBEEGap(patElectron_calibrated.isEBEEGap());

    localElectron.setFbrem(patElectron_calibrated.fbrem());
    localElectron.setNBrems(patElectron_calibrated.numberOfBrems());
    // charge Info
    localElectron.setIsGsfCtfScPixChargeConsistent(patElectron_calibrated.isGsfCtfScPixChargeConsistent());

    //setShowerShape
    localElectron.setE1x5( patElectron_calibrated.e1x5() );
    localElectron.setE5x5( patElectron_calibrated.e5x5() );
    localElectron.setHoverEDepth1( patElectron_calibrated.hcalDepth1OverEcal() );
    localElectron.setHoverEDepth2( patElectron_calibrated.hcalDepth2OverEcal() );
    localElectron.setSigmaIetaIeta_full5x5( patElectron_calibrated.full5x5_sigmaIetaIeta() );
    localElectron.setSigmaIetaIeta( patElectron_calibrated.sigmaIetaIeta() );

    // switching to gsf track for miniAOD, seems this is the correct thing for
    //now
    reco::GsfTrackRef myTrackRef = patElectron_calibrated.gsfTrack();

   if ( myTrackRef.isNonnull() )
    {
	    const reco::HitPattern& hit = myTrackRef->hitPattern();
	    localElectron.setPixelLayersWithMeasurement(hit.pixelLayersWithMeasurement());
	    localElectron.setStripLayersWithMeasurement(hit.stripLayersWithMeasurement());
        localElectron.setTrackNormalizedChi2(myTrackRef->normalizedChi2());
        localElectron.setNValidHits(myTrackRef->numberOfValidHits());
    }

    reco::GsfTrackRef gsfTrack = patElectron_calibrated.gsfTrack();

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
	localElectron.setD0BeamSpot(patElectron_calibrated.gsfTrack()->dxy(mybeamspot.position()));
	localElectron.setD0BeamSpotError( sqrt( pow(patElectron_calibrated.gsfTrack()->dxyError(),2) + pow(mybeamspot.x0Error(),2) + pow(mybeamspot.y0Error(),2) ) );
	localElectron.setDzBeamSpot(patElectron_calibrated.gsfTrack()->dz(mybeamspot.position()));
	localElectron.setDzBeamSpotError( sqrt( pow(patElectron_calibrated.gsfTrack()->dzError(),2) + pow(mybeamspot.x0Error(),2) + pow(mybeamspot.y0Error(),2) ) );

	localElectron.setIp3d( patElectron_calibrated.ip3d() );

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

    reco::SuperClusterRef superCluster = patElectron_calibrated.superCluster();
    if ( superCluster.isNonnull() && runSuperCluster_ )
	  {
	    localElectron.setSuperClusterRawEnergy(superCluster->rawEnergy());
	    localElectron.setSuperClusterEta(superCluster->eta());
	    localElectron.setPreshowerEnergy(superCluster->preshowerEnergy());
      if ( gsfTrack.isNonnull() ) localElectron.setIoEmIoPgsf( (1./superCluster->energy()) - (1./gsfTrack->p()) );
      localElectron.setEtaWidth( superCluster->etaWidth() );
      localElectron.setPhiWidth( superCluster->phiWidth() );
	  }

      if( patElectron_calibrated.ecalEnergy() > 0.0)  //patElectron_calibrated cut based ID variable
      {
          float elESCP = patElectron_calibrated.eSuperClusterOverP();
          float elinv_ecal_e = 1.0/(patElectron_calibrated.ecalEnergy());
          float elIoEmIoP = abs(1.0 - elESCP)*elinv_ecal_e;
          localElectron.setIoEmIoP(elIoEmIoP);
      }

    // Some specific methods to pat::Electron
    TLorentzVector ecalDrivenMomentum(patElectron_calibrated.ecalDrivenMomentum().px(),patElectron_calibrated.ecalDrivenMomentum().py(),patElectron_calibrated.ecalDrivenMomentum().pz(),patElectron_calibrated.ecalDrivenMomentum().energy());
    localElectron.setEcalDrivenMomentum(ecalDrivenMomentum);

    // Matched genParticle
    if(useMC_)
	  {
	    if ((patElectron_calibrated.genParticleRef()).isNonnull()) localElectron.setGenParticleIndex((patElectron_calibrated.genParticleRef()).index());
	    else localElectron.setGenParticleIndex(-1);
	  }

    //set pf-isolation
    //default cone size from PAT setup : currently r=0.3
/*    if(patElectron_calibrated.chargedHadronIso() != -1) localElectron.setIsoR03_ChargedHadronIso(patElectron_calibrated.chargedHadronIso());
    if(patElectron_calibrated.puChargedHadronIso() != -1) localElectron.setIsoR03_PuChargedHadronIso( patElectron_calibrated.puChargedHadronIso() );
    if(patElectron_calibrated.photonIso() != -1) localElectron.setIsoR03_PhotonIso(patElectron_calibrated.photonIso());
    if(patElectron_calibrated.neutralHadronIso() != -1) localElectron.setIsoR03_NeutralHadronIso(patElectron_calibrated.neutralHadronIso());
*/

    GsfElectron::PflowIsolationVariables pfIso = patElectron_calibrated.pfIsolationVariables();
    localElectron.setIsoR03_ChargedHadronIso(pfIso.sumChargedHadronPt);
    localElectron.setIsoR03_PuChargedHadronIso(pfIso.sumPUPt);
    localElectron.setIsoR03_PhotonIso(pfIso.sumPhotonEt);
    localElectron.setIsoR03_NeutralHadronIso(pfIso.sumNeutralHadronEt);
    


    //this is for cone size r=0.4  // same as for cone 0.3 , is cone independent. TRootElectron object will be cleaned up later
    localElectron.setIsoR04_ChargedHadronIso(pfIso.sumChargedHadronPt);
    localElectron.setIsoR04_PuChargedHadronIso(pfIso.sumPUPt);
    localElectron.setIsoR04_PhotonIso(pfIso.sumPhotonEt);
    localElectron.setIsoR04_NeutralHadronIso(pfIso.sumNeutralHadronEt);
    //following EGM POG isolation definition
    AbsVetos veto_ch;
    AbsVetos veto_nh;
    AbsVetos veto_ph;
    Direction Dir = Direction(patElectron_calibrated.superCluster()->eta(), patElectron_calibrated.superCluster()->phi());
    if( fabs( patElectron_calibrated.superCluster()->eta() ) > 1.479 ){
      veto_ch.push_back(new reco::isodeposit::ConeVeto( Dir, 0.015 ));
      veto_ph.push_back(new reco::isodeposit::ConeVeto( Dir, 0.08 ));
    }

    localElectron.setPassConversion(patElectron_calibrated.passConversionVeto());
    localElectron.setSigmaIphiIphi( patElectron_calibrated.sigmaIphiIphi() );
    localElectron.setSigmaIetaIphi( patElectron_calibrated.sigmaIetaIphi() );
    localElectron.setR9( patElectron_calibrated.r9() );

    // verbose printout of patElectron_calibrated IDs available:
    if(verbosity_>2){
      std::vector<std::pair<std::string, float> > eleIds = patElectron_calibrated.electronIDs();
      std::cout << "patElectron_calibrated ID summary: " << std::endl;
      for(UInt_t ii=0; ii<eleIds.size(); ii++){
	  std::cout << eleIds[ii].first << " " << eleIds[ii].second << std::endl;
      }
    }

    //Adding mvaValues (need to use the un-calibrated electrons for this)
    const auto el = gsfElectrons->ptrAt(j);


    bool isPassMVAMedium = (*MVA_medium_id_decisions)[el];
    bool isPassMVATight  = (*MVA_tight_id_decisions)[el];
    bool isPassCBVeto = (*CB_veto_id_decisions)[el];
    bool isPassCBLoose  = (*CB_loose_id_decisions)[el];
    bool isPassCBMedium = (*CB_medium_id_decisions)[el];
    bool isPassCBTight  = (*CB_tight_id_decisions)[el];
    bool isPassCBHeep = (*CB_heep_id_decisions)[el];
    float mvaValue = (*mvaValues)[el];
    float mvaCategory =  (*mvaCategories)[el];

    localElectron.setisMVA_MediumID( isPassMVAMedium );
    localElectron.setisMVA_TightID( isPassMVATight );
    localElectron.setisCB_VetoID( isPassCBVeto );
    localElectron.setisCB_LooseID( isPassCBLoose );
    localElectron.setisCB_MediumID( isPassCBMedium );
    localElectron.setisCB_TightID( isPassCBTight );
    localElectron.setisCB_HeepID( isPassCBHeep );

    localElectron.setMVA_value( mvaValue );
    localElectron.setMVA_category( mvaCategory );
     
    new( (*rootElectrons)[nElectrons_passedSkimming] ) TRootElectron(localElectron);
    if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localElectron << endl;
    if(verbosity_>4) cout << "   ["<< setw(3) << j << "] " << "CHIso " << localElectron.chargedHadronIso(3)  << " pat " << patElectron_calibrated.chargedHadronIso() << endl;
    if(verbosity_>4) cout << "   ["<< setw(3) << j << "] " << "PHIso " << localElectron.photonIso(3)  << " pat " << patElectron_calibrated.photonIso()<< endl;
    if(verbosity_>4) cout << "   ["<< setw(3) << j << "] " << "NHIso " << localElectron.neutralHadronIso(3)  << " pat " << patElectron_calibrated.neutralHadronIso()<< endl;
    nElectrons_passedSkimming++;

    
}

}
