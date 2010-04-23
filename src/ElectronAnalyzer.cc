#include <FWCore/Framework/interface/TriggerNames.h>

#include "../interface/ElectronAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0),useMC_(false),runSuperCluster_(false),doPrimaryVertex_(false)

{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	electronProducer_ = producersNames.getParameter<edm::InputTag>("electronProducer");
	primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
	TrackLabel_ = producersNames.getParameter<edm::InputTag>("generalTrackLabel");
	newId_ = producersNames.getUntrackedParameter<bool>("electronNewId",false);
	doTriggerMatching = producersNames.getUntrackedParameter<bool>("electronTriggerMatching",false);
	std::vector<std::string> tmp;
	tmp.clear();
	pathNames = producersNames.getUntrackedParameter<std::vector<std::string> >("electronTriggerPaths",tmp); // electron trigger path names
}

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	electronProducer_ = producersNames.getParameter<edm::InputTag>("electronProducer");
	useMC_ = myConfig.getUntrackedParameter<bool>("doElectronMC");
	runSuperCluster_ = myConfig.getUntrackedParameter<bool>("runSuperCluster",false);
	primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
	doPrimaryVertex_ = myConfig.getUntrackedParameter<bool>("doPrimaryVertex");
	TrackLabel_ = producersNames.getParameter<edm::InputTag>("generalTrackLabel");
	newId_ = producersNames.getUntrackedParameter<bool>("electronNewId",false);
	doTriggerMatching = producersNames.getUntrackedParameter<bool>("electronTriggerMatching",false);
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

	edm::Handle < std::vector <reco::GsfElectron> > recoElectrons;
	if( dataType_=="RECO" || dataType_=="AOD" )
	{
		iEvent.getByLabel(electronProducer_, recoElectrons);
		nElectrons = recoElectrons->size();
	}

	edm::Handle < std::vector <pat::Electron> > patElectrons;
	if( dataType_=="PAT" || dataType_=="PATAOD" )
	{
		iEvent.getByLabel(electronProducer_, patElectrons);
		nElectrons = patElectrons->size();
	}

	edm::Handle< reco::VertexCollection > pvHandle;
	reco::Vertex primaryVertex;
	edm::ESHandle<TransientTrackBuilder> trackBuilder;
	if(doPrimaryVertex_)
	{
		iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", trackBuilder);
		iEvent.getByLabel( primaryVertexProducer_, pvHandle );
		if(pvHandle.isValid())
			primaryVertex = pvHandle->at(0);
	}

	if(verbosity_>1) std::cout << "   Number of electrons = " << nElectrons << "   Label: " << electronProducer_.label() << "   Instance: " << electronProducer_.instance() << std::endl;

	for (unsigned int j=0; j<nElectrons; j++)
	{
		const reco::GsfElectron* electron = 0;	
		if( dataType_=="RECO" || dataType_=="AOD" )
			electron =  &((*recoElectrons)[j]);
		if( dataType_=="PAT" || dataType_=="PATAOD" )
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
		localElectron.setElectronMomentumError( electron->electronMomentumError());
		localElectron.setEnergyScaleCorrected( electron->isEcalEnergyCorrected());
		localElectron.setMomentumCorrected( electron->isMomentumCorrected()) ;
		localElectron.setTrackMomentumError(electron->trackMomentumError());

		reco::GsfTrackRef gsfTrack = electron->gsfTrack();
		if ( gsfTrack.isNonnull() )
		{
			const reco::HitPattern& hit = gsfTrack->hitPattern();

			localElectron.setPixelLayersWithMeasurement(hit.pixelLayersWithMeasurement());
			localElectron.setStripLayersWithMeasurement(hit.stripLayersWithMeasurement());

			localElectron.setD0(gsfTrack->d0());
			localElectron.setD0Error(gsfTrack->d0Error());
			localElectron.setDsz(gsfTrack->dsz());
			localElectron.setDszError(gsfTrack->dszError());

			localElectron.setTrackNormalizedChi2(gsfTrack->normalizedChi2());
			localElectron.setTrackPtError(gsfTrack->ptError());

			localElectron.setTrackMissingHits(gsfTrack->trackerExpectedHitsInner().numberOfHits());
		}

//		Special impact parameter stuff
		if(doPrimaryVertex_ && pvHandle.isValid())
		{
			if(electron->gsfTrack().isNonnull())
			{
				cout << "electron track is non null" << endl;
				reco::TransientTrack tt = trackBuilder->build(electron->gsfTrack());
				std::pair<bool,Measurement1D> resultTransverse = IPTools::absoluteTransverseImpactParameter(tt, primaryVertex);
				std::pair<bool,Measurement1D> result3D = IPTools::absoluteImpactParameter3D(tt, primaryVertex);

				localElectron.setImpactParameter3D(result3D.second.value());
				localElectron.setImpactParameter3DError(result3D.second.error());
				localElectron.setTransverseImpactParameter(resultTransverse.second.value()); 
				localElectron.setTransverseImpactParameterError(resultTransverse.second.error());
			}

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
			if ( seedBasicCluster.isNonnull() )
			{
				localElectron.setE2x2(lazyTools.e2x2(*seedBasicCluster));
				localElectron.setE3x3(lazyTools.e3x3(*seedBasicCluster));
			}
		}

		//setFiducialFlags
		localElectron.setFiducialFlags(electron->isEB(),electron->isEE(), electron->isEBEEGap(),electron->isEBEtaGap(),electron->isEBPhiGap(),electron->isEEDeeGap(),electron->isEERingGap());

		//Isolation
		//localElectron.setIsolation(1, electron->getIsolation(1));
		//localElectron.setIsolation(2, electron->getIsolation(2));

		localElectron.setIsoR03_Depth1HadEt(electron->dr03HcalDepth1TowerSumEt());
		localElectron.setIsoR03_Depth2HadEt(electron->dr03HcalDepth2TowerSumEt());
		localElectron.setIsoR03_emEt(electron->dr03EcalRecHitSumEt());
		localElectron.setIsoR03_sumPt(electron->dr03TkSumPt());

		localElectron.setIsoR04_Depth1HadEt(electron->dr04HcalDepth1TowerSumEt());
		localElectron.setIsoR04_Depth2HadEt(electron->dr04HcalDepth2TowerSumEt());
		localElectron.setIsoR04_emEt(electron->dr04EcalRecHitSumEt());
		localElectron.setIsoR04_sumPt(electron->dr04TkSumPt());

		// localElectron.setIsolation(5, electron->getIsolation(5));
		// TLorentzVector tmpP4(-1000.,-1000.,-1000.,-1000);

		localElectron.setClassification(electron->classification());
		localElectron.setFbrem(electron->fbrem());
//		localElectron.setTriggerInfo(electron->getTriggerInfo());
//		localElectron.setConversion(electron->isFromConversion());

		// Conversion:
		//MagneticFiled at origin:
		edm::ESHandle<MagneticField> magfield;
		iSetup.get<IdealMagneticFieldRecord>().get(magfield);
		GlobalPoint origin_point(0,0,0);
		float Bfied = magfield.product()->inTesla(origin_point).mag();

		edm::Handle<reco::TrackCollection> MyTrackHandle;
		iEvent.getByLabel(TrackLabel_,MyTrackHandle);
		double Dist = 9999.;
		double DCot = 9999.;
		reco::TrackRef partnerTrack = getConversionPartnerTrack(*electron,MyTrackHandle,Bfied,Dist,DCot);
		localElectron.setConversion((bool)partnerTrack.isNonnull());

		// Variables from reco::GsfTrack

		// Cluster Shape variables
		// need reco::SuperCluster and reco::BasicCluster


		if( dataType_=="RECO" || dataType_=="AOD" )
		{
			// Some specific methods requiring  RECO / AOD format
			// Do association to genParticle ?

			// Isolation ?
			// Electron ID ?  RecoEgamma/ElectronIdentification
		}


		if( dataType_=="PATAOD" || dataType_=="PAT" )
		{
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
				localElectron.setIDCiCVeryLoose(int(patElectron->electronID("eidCiCVeryLoose")));
				localElectron.setIDCiCLoose(int(patElectron->electronID("eidCiCLoose")));
				localElectron.setIDCiCMedium(int(patElectron->electronID("eidCiCMedium")));
				localElectron.setIDCiCTight(int(patElectron->electronID("eidCiCTight")));
				localElectron.setIDCiCSuperTight(int(patElectron->electronID("eidCiCSuperTight")));
				localElectron.setIDCiCHyperTight1(int(patElectron->electronID("eidCiCHyperTight1")));
				localElectron.setIDCiCHyperTight2(int(patElectron->electronID("eidCiCHyperTight2")));
				localElectron.setIDCiCHyperTight3(int(patElectron->electronID("eidCiCHyperTight3")));
				localElectron.setIDCiCHyperTight4(int(patElectron->electronID("eidCiCHyperTight4")));                           
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

			//triggerMatching
			if(doTriggerMatching && pathNames.size() != 0)
			{
				for(uint trig = 0; trig < pathNames.size(); trig++)
				{
					localElectron.setTriggerinfo(pathNames.at(trig),(patElectron->triggerObjectMatchesByPath(pathNames.at(trig)).size() != 0));
				}
			}
		}

		new( (*rootElectrons)[j] ) TRootElectron(localElectron);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localElectron << endl;
	}
} 














//methods for conversion============================================
const reco::Track* ElectronAnalyzer::getElectronTrack(const reco::GsfElectron& electron, const float minFracSharedHits){
    if(electron.closestCtfTrackRef().isNonnull() && electron.shFracInnerHits() > minFracSharedHits)
        return (const reco::Track*)electron.closestCtfTrackRef().get();
    return (const reco::Track*)(electron.gsfTrack().get());

}

std::pair<double, double> ElectronAnalyzer::getConversionInfo(TLorentzVector trk1_p4,int trk1_q, float trk1_d0,TLorentzVector trk2_p4,int trk2_q, float trk2_d0,float bFieldAtOrigin){
    double tk1Curvature = -0.3*bFieldAtOrigin*(trk1_q/trk1_p4.Pt())/100.;
    double rTk1 = fabs(1./tk1Curvature);
    double xTk1 = (1./tk1Curvature - trk1_d0)*cos(trk1_p4.Phi());
    double yTk1 = (1./tk1Curvature - trk1_d0)*sin(trk1_p4.Phi());

    double tk2Curvature = -0.3*bFieldAtOrigin*(trk2_q/trk2_p4.Pt())/100.;
    double rTk2 = fabs(1./tk2Curvature);
    double xTk2 = (1./tk2Curvature - trk2_d0)*cos(trk2_p4.Phi());
    double yTk2 = (1./tk2Curvature - trk2_d0)*sin(trk2_p4.Phi());

    double dist = sqrt(pow(xTk1-xTk2, 2) + pow(yTk1-yTk2 , 2));
    dist = dist - (rTk1 + rTk2);

    double dcot = 1/tan(trk1_p4.Theta()) - 1/tan(trk2_p4.Theta());

    return std::make_pair(dist, dcot);
}
reco::TrackRef ElectronAnalyzer::getConversionPartnerTrack(const reco::GsfElectron& gsfElectron,
					 const edm::Handle<reco::TrackCollection>& track_h,
					 const float bFieldAtOrigin,
					 double& Dist,
					 double& DCot,
					 const float maxAbsDist,
					 const float maxAbsDCot,
					 const float minFracSharedHits){

    const reco::TrackRef el_ctftrack = gsfElectron.closestCtfTrackRef();
    const TrackCollection *ctftracks = track_h.product();


    const reco::Track* el_track = getElectronTrack(gsfElectron, minFracSharedHits);
    int ctfidx = -999;
    int el_q   = el_track->charge();
    TLorentzVector el_tk_p4(el_track->px(), el_track->py(), el_track->pz(), el_track->p());
    double el_d0 = el_track->d0();


    if(el_ctftrack.isNonnull() && gsfElectron.shFracInnerHits() > minFracSharedHits)
    ctfidx = static_cast<int>(el_ctftrack.key());

    int tk_i = 0;
    double mindR = 999;

    //make a null Track Ref
    TrackRef ctfTrackRef = TrackRef() ;

    for(TrackCollection::const_iterator tk = ctftracks->begin(); tk != ctftracks->end(); tk++, tk_i++) {
    //if the general Track is the same one as made by the electron, skip it
        if((tk_i == ctfidx)  &&  (gsfElectron.shFracInnerHits() > minFracSharedHits))
            continue;


        TLorentzVector tk_p4(tk->px(), tk->py(), tk->pz(), tk->p());

        //look only in a cone of 0.3

        double dR = deltaR(el_tk_p4.Eta(), el_tk_p4.Phi(), tk_p4.Eta(), tk_p4.Phi());
        if(dR > 0.3)
            continue;

        int tk_q = tk->charge();
        double tk_d0 = tk->d0();

        //the electron and track must be opposite charge
        if(tk_q + el_q != 0)
            continue;

        std::pair<double, double> convInfo =  getConversionInfo(el_tk_p4, el_q, el_d0,tk_p4, tk_q, tk_d0,bFieldAtOrigin);

        double dist = convInfo.first;
        double dcot = convInfo.second;

        if(fabs(dist) < maxAbsDist && fabs(dcot) < maxAbsDCot && dR < mindR) {
            ctfTrackRef = reco::TrackRef(track_h, tk_i);
            mindR = dR;
            Dist = dist ;
            DCot = dcot ;
        }

    }//track loop

    return ctfTrackRef;
}
