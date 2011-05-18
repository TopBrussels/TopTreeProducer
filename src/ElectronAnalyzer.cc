#include "../interface/ElectronAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0),useMC_(false),runSuperCluster_(false),doPrimaryVertex_(false),isData_(false)

{
	electronProducer_ = producersNames.getParameter<edm::InputTag>("electronProducer");
	primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
	TrackLabel_ = producersNames.getParameter<edm::InputTag>("generalTrackLabel");
	newId_ = producersNames.getUntrackedParameter<bool>("electronNewId",false);
	std::vector<std::string> tmp;
	tmp.clear();
	pathNames = producersNames.getUntrackedParameter<std::vector<std::string> >("electronTriggerPaths",tmp); // electron trigger path names
}

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	electronProducer_ = producersNames.getParameter<edm::InputTag>("electronProducer");
	useMC_ = myConfig.getUntrackedParameter<bool>("doElectronMC");
	isData_ = myConfig.getUntrackedParameter<bool>("isData");
	runSuperCluster_ = myConfig.getUntrackedParameter<bool>("runSuperCluster",false);
	primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
	doPrimaryVertex_ = myConfig.getUntrackedParameter<bool>("doPrimaryVertex");
	TrackLabel_ = producersNames.getParameter<edm::InputTag>("generalTrackLabel");
	newId_ = producersNames.getUntrackedParameter<bool>("electronNewId",false);
	std::vector<std::string> tmp;
	tmp.clear();
	pathNames = producersNames.getUntrackedParameter<std::vector<std::string> >("electronTriggerPaths",tmp); // electron trigger path names
}

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	vElectronProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("velectronProducer");
	electronProducer_ =	edm::InputTag(vElectronProducer[iter]);
	useMC_ = myConfig.getUntrackedParameter<bool>("doElectronMC");
	isData_ = myConfig.getUntrackedParameter<bool>("isData");
	runSuperCluster_ = myConfig.getUntrackedParameter<bool>("runSuperCluster",false);
	primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
	doPrimaryVertex_ = myConfig.getUntrackedParameter<bool>("doPrimaryVertex");
	TrackLabel_ = producersNames.getParameter<edm::InputTag>("generalTrackLabel");
	newId_ = producersNames.getUntrackedParameter<bool>("electronNewId",false);
	std::vector<std::string> tmp;
	tmp.clear();
	pathNames = producersNames.getUntrackedParameter<std::vector<std::string> >("electronTriggerPaths",tmp); // electron trigger path names
}

ElectronAnalyzer::~ElectronAnalyzer()
{
}

void ElectronAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootElectrons, EcalClusterLazyTools& lazyTools, const edm::EventSetup& iSetup )
{
	unsigned int nElectrons=0;

	edm::Handle < std::vector <pat::Electron> > patElectrons;
	iEvent.getByLabel(electronProducer_, patElectrons);
	nElectrons = patElectrons->size();

	edm::Handle< reco::VertexCollection > pvHandle;

	edm::Handle<reco::BeamSpot> beamSpotHandle;
	iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);
	const reco::TrackBase::Point & beamSpot = reco::TrackBase::Point(beamSpotHandle->x0(), beamSpotHandle->y0(), beamSpotHandle->z0());

	if(verbosity_>1) std::cout << "   Number of electrons = " << nElectrons << "   Label: " << electronProducer_.label() << "   Instance: " << electronProducer_.instance() << std::endl;

	for (unsigned int j=0; j<nElectrons; j++)
	{
		const reco::GsfElectron* electron = 0;	
		electron = (const reco::GsfElectron*) ( & ((*patElectrons)[j]) );

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
                
//=======================================
		//std::cout<<"electron->isGsfCtfScPixChargeConsistent(): "<<electron->isGsfCtfScPixChargeConsistent()<<endl;
		localElectron.setChargeInfo(electron->scPixCharge(),electron->isGsfCtfScPixChargeConsistent(),electron->isGsfScPixChargeConsistent(),electron->isGsfCtfChargeConsistent());
		//std::cout<<"localElectron.isGsfCtfScPixConsistent(): "<<localElectron.isGsfCtfScPixConsistent()<<endl;
		localElectron.setSeedingInfo(electron->ecalDrivenSeed(), electron->trackerDrivenSeed());
		localElectron.setTrackClusterMatching(electron->eSuperClusterOverP(),electron->eEleClusterOverPout(),electron->eSeedClusterOverP(),
			electron->eSeedClusterOverPout(),electron->deltaEtaSuperClusterTrackAtVtx(),electron->deltaEtaSeedClusterTrackAtCalo(),
			electron->deltaPhiSuperClusterTrackAtVtx(),electron->deltaPhiSeedClusterTrackAtCalo(),electron->deltaPhiEleClusterTrackAtCalo(),
			electron->deltaEtaEleClusterTrackAtCalo());

		//setTrackProperties:
		//std::cout<<"sqrt(electron->trackMomentumAtVtx().Mag2()): "<<sqrt(electron->trackMomentumAtVtx().Mag2())<<endl;
		localElectron.setTrackMomentum(sqrt(electron->trackMomentumAtVtx().Mag2()));
		//std::cout<<"localElectron.trackMomentum(): "<<localElectron.trackMomentum()<<endl;
		localElectron.setTrackMomentumAtCalo(sqrt(electron->trackMomentumAtCalo().Mag2()));
		localElectron.setTrackMomentumAtElectronCluster( sqrt(electron->trackMomentumAtEleClus().Mag2()));
		localElectron.setTrackMomentumAtVtxWithConstraint( sqrt(electron->trackMomentumAtVtxWithConstraint().Mag2()));
		localElectron.setTrackMomentumOut( sqrt(electron->trackMomentumOut().Mag2()));
		localElectron.setTrackPositionAtCalo(electron->trackPositionAtCalo().x(),  electron->trackPositionAtCalo().Y(),  electron->trackPositionAtCalo().Z());
		localElectron.setTrackPositionAtVtx( electron->trackPositionAtVtx().x(),  electron->trackPositionAtVtx().y(),  electron->trackPositionAtVtx().z());

		//setCorrections
		localElectron.setCaloEnergyError( electron->ecalEnergyError()) ;
		localElectron.setCaloEnergy(electron->caloEnergy()) ;
		//localElectron.setElectronMomentumError( electron->electronMomentumError());
		localElectron.setEnergyScaleCorrected( electron->isEcalEnergyCorrected());
		//localElectron.setMomentumCorrected( electron->isMomentumCorrected()) ;
		localElectron.setTrackMomentumError(electron->trackMomentumError());

		reco::GsfTrackRef gsfTrack = electron->gsfTrack();
		if ( gsfTrack.isNonnull() )
		{
			const reco::HitPattern& hit = gsfTrack->hitPattern();

			localElectron.setPixelLayersWithMeasurement(hit.pixelLayersWithMeasurement());
			localElectron.setStripLayersWithMeasurement(hit.stripLayersWithMeasurement());

			localElectron.setd0( gsfTrack->dxy(beamSpot) );
			localElectron.setd0Error( sqrt( pow(gsfTrack->dxyError(),2) + pow(beamSpotHandle->BeamWidthX(),2) + pow(beamSpotHandle->BeamWidthY(),2) ) );
			localElectron.setdsz(gsfTrack->dsz());
			localElectron.setdszError(gsfTrack->dszError());

			localElectron.setTrackNormalizedChi2(gsfTrack->normalizedChi2());
			localElectron.setTrackPtError(gsfTrack->ptError());

			localElectron.setTrackMissingHits(gsfTrack->trackerExpectedHitsInner().numberOfHits());
		}

		if(doPrimaryVertex_ && pvHandle.isValid())
		{
			//good for eID : http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/CMSSW/RecoEgamma/ElectronIdentification/src/CutBasedElectronID.cc?revision=1.17&view=markup&sortdir=down&pathrev=V00-03-05
			double ip = -9999.;
			if (pvHandle->size() != 0)
			{
				reco::VertexRef vtx(pvHandle, 0);
				ip = fabs(electron->gsfTrack()->dxy(math::XYZPoint(vtx->x(),vtx->y(),vtx->z())));
			}
			else
				ip = fabs(electron->gsfTrack()->dxy());

			localElectron.setImpactParameter(ip);
		}

		//setSuperCluster
		localElectron.setCaloPosition(electron->caloPosition().x(),electron->caloPosition().y(),electron->caloPosition().z());
		localElectron.setBasicClusterSize(electron->basicClustersSize());
                
		//setShowerShape
		localElectron.setE1x5( electron->e1x5());
		localElectron.setE2x5Max( electron->e2x5Max());
		localElectron.setE5x5( electron->e5x5());
		localElectron.setHoverEDepth1( electron->hcalDepth1OverEcal());
		localElectron.setHoverEDepth2( electron->hcalDepth2OverEcal());
		localElectron.setSigmaEtaEta( electron->sigmaEtaEta());
		localElectron.setSigmaIetaIeta( electron->sigmaIetaIeta());

		reco::SuperClusterRef superCluster = electron->superCluster();
		if ( superCluster.isNonnull() && runSuperCluster_ )
		{
			localElectron.setNbClusters(superCluster->clustersSize ());
			localElectron.setSuperClusterRawEnergy(superCluster->rawEnergy());
			localElectron.setSuperClusterEta(superCluster->eta());
			localElectron.setPreshowerEnergy(superCluster->preshowerEnergy());
			reco::CaloClusterPtr seedBasicCluster = superCluster->seed();
			if ( seedBasicCluster.isNonnull() ) localElectron.setClusterAlgo(seedBasicCluster->algo());
			Float_t caloConeSize = 0;
			for (reco::CaloCluster_iterator  basicCluster = (*superCluster).clustersBegin(); basicCluster != (*superCluster).clustersEnd(); ++basicCluster )
			{
				Float_t dR = localElectron.DeltaR(TLorentzVector( (*basicCluster)->position().x(), (*basicCluster)->position().y(), (*basicCluster)->position().z(), 0. ) );
				if (dR > caloConeSize) caloConeSize = dR;
			}
			// FIXME - if no BasicCluster collection, init to -999.
			localElectron.setCaloConeSize(caloConeSize);
		}

		//setFiducialFlags
		localElectron.setFiducialFlags(electron->isEB(),electron->isEE(), electron->isEBEEGap(),electron->isEBEtaGap(),electron->isEBPhiGap(),electron->isEEDeeGap(),electron->isEERingGap());

		//Isolation
		localElectron.setIsoR03_Depth1HadEt(electron->dr03HcalDepth1TowerSumEt());
		localElectron.setIsoR03_Depth2HadEt(electron->dr03HcalDepth2TowerSumEt());
		localElectron.setIsoR03_emEt(electron->dr03EcalRecHitSumEt());
		localElectron.setIsoR03_sumPt(electron->dr03TkSumPt());

		localElectron.setIsoR04_Depth1HadEt(electron->dr04HcalDepth1TowerSumEt());
		localElectron.setIsoR04_Depth2HadEt(electron->dr04HcalDepth2TowerSumEt());
		localElectron.setIsoR04_emEt(electron->dr04EcalRecHitSumEt());
		localElectron.setIsoR04_sumPt(electron->dr04TkSumPt());

		// TLorentzVector tmpP4(-1000.,-1000.,-1000.,-1000);

		localElectron.setClassification(electron->classification());
		localElectron.setFbrem(electron->fbrem());
//		localElectron.setTriggerInfo(electron->getTriggerInfo());
//		localElectron.setConversion(electron->isFromConversion());

		// Conversion:
		
		double evt_bField = 0;

		// need the magnetic field
		//
		// if isData_ then derive bfield using the
		// magnet current from DcsStatus
		// otherwise take it from the IdealMagneticFieldRecord

		if (!isData_) {
		  ESHandle<MagneticField> magneticField;
		  iSetup.get<IdealMagneticFieldRecord>().get(magneticField);
		  evt_bField = magneticField->inTesla(GlobalPoint(0.,0.,0.)).z();
		} else {
		  edm::Handle<DcsStatusCollection> dcsHandle;
		  iEvent.getByLabel("scalersRawToDigi", dcsHandle);
		  // scale factor = 3.801/18166.0 which are
		  // average values taken over a stable two
		  // week period
		  float currentToBFieldScaleFactor = 2.09237036221512717e-04;
		  float current = (*dcsHandle)[0].magnetCurrent();
		  evt_bField = current*currentToBFieldScaleFactor;
		}
  
		edm::Handle<reco::TrackCollection> tracks_h;
		iEvent.getByLabel(TrackLabel_, tracks_h);

		ConversionFinder convFinder;
		const ConversionInfo convInfo = convFinder.getConversionInfo(*electron, tracks_h, evt_bField,0.45);
   
		double Dist = convInfo.dist();
		double DCot = convInfo.dcot();

		localElectron.setDist(Dist);
		localElectron.setDCot(DCot);
		
		localElectron.setConversion(convFinder.isFromConversion(convInfo,0.02, 0.02));

		// Variables from reco::GsfTrack

		// Cluster Shape variables
		// need reco::SuperCluster and reco::BasicCluster


			// Some specific methods to pat::Electron
			const pat::Electron *patElectron = dynamic_cast<const pat::Electron*>(&*electron);

			//identification
			localElectron.setIDCutBasedRobustLoose(int(patElectron->electronID("eidRobustLoose")));
			localElectron.setIDCutBasedRobustTight(int(patElectron->electronID("eidRobustTight")));
			localElectron.setIDCutBasedRobustHighEnergy(int(patElectron->electronID("eidRobustHighEnergy")));
			localElectron.setIDCategorizedLoose(int(patElectron->electronID("eidLoose")));
			localElectron.setIDCategorizedTight(int(patElectron->electronID("eidTight")));
		
			if(newId_)
			{
/*				localElectron.setIDCiCVeryLoose(int(patElectron->electronID("eidCiCVeryLoose")));
				localElectron.setIDCiCLoose(int(patElectron->electronID("eidCiCLoose")));
				localElectron.setIDCiCMedium(int(patElectron->electronID("eidCiCMedium")));
				localElectron.setIDCiCTight(int(patElectron->electronID("eidCiCTight")));
				localElectron.setIDCiCSuperTight(int(patElectron->electronID("eidCiCSuperTight")));
				localElectron.setIDCiCHyperTight1(int(patElectron->electronID("eidCiCHyperTight1")));
				localElectron.setIDCiCHyperTight2(int(patElectron->electronID("eidCiCHyperTight2")));
				localElectron.setIDCiCHyperTight3(int(patElectron->electronID("eidCiCHyperTight3")));
				localElectron.setIDCiCHyperTight4(int(patElectron->electronID("eidCiCHyperTight4")));                           
*/			}

			if(patElectron->gsfTrack().isNonnull() && patElectron->gsfTrack().isAvailable())
			{
				localElectron.setdB(patElectron->dB());
				localElectron.setdBError(patElectron->edB());
			}
                        
			// Matched genParticle
			if(useMC_)
			{
				// MC truth associator index
				if ((patElectron->genParticleRef()).isNonnull())
				{
					localElectron.setGenParticleIndex((patElectron->genParticleRef()).index());
				}
				else
				{
					localElectron.setGenParticleIndex(-1);
				}

			}
			
			if(patElectron->chargedHadronIso() != -1) localElectron.setChargedHadronIso(patElectron->chargedHadronIso());
		  	if(patElectron->photonIso() != -1) localElectron.setPhotonIso(patElectron->photonIso());
			if(patElectron->neutralHadronIso() != -1) localElectron.setNeutralHadronIso(patElectron->neutralHadronIso());

		new( (*rootElectrons)[j] ) TRootElectron(localElectron);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localElectron << endl;
	}
} 






