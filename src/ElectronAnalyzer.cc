#include "../interface/ElectronAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0),useMC_(false),runSuperCluster_(false)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	electronProducer_ = producersNames.getParameter<edm::InputTag>("electronProducer");
        primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
        newId_ = producersNames.getParameter<bool>("electronNewId");
}

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	electronProducer_ = producersNames.getParameter<edm::InputTag>("electronProducer");
	useMC_ = myConfig.getUntrackedParameter<bool>("doElectronMC");
	runSuperCluster_ = myConfig.getUntrackedParameter<bool>("runSuperCluster",false);
        primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
        newId_ = producersNames.getParameter<bool>("electronNewId");
}

ElectronAnalyzer::~ElectronAnalyzer()
{
}

void ElectronAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootElectrons, EcalClusterLazyTools& lazyTools )
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

	if(verbosity_>1) std::cout << "   Number of electrons = " << nElectrons << "   Label: " << electronProducer_.label() << "   Instance: " << electronProducer_.instance() << std::endl;

	for (unsigned int j=0; j<nElectrons; j++)
	{
		const reco::GsfElectron* electron = 0;	
		if( dataType_=="RECO" || dataType_=="AOD" ) electron =  &((*recoElectrons)[j]);
		if( dataType_=="PAT" || dataType_=="PATAOD" ) electron = (const reco::GsfElectron*) ( & ((*patElectrons)[j]) );

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
                
                localElectron.setChargeInfo(electron->scPixCharge(),electron->isGsfCtfScPixChargeConsistent(),electron->isGsfScPixChargeConsistent(),electron->isGsfCtfChargeConsistent());
                localElectron.setSeedingInfo(electron->ecalDrivenSeed(), electron->trackerDrivenSeed());
                localElectron.setTrackClusterMatching(electron->eSuperClusterOverP(),electron->eEleClusterOverPout(),electron->eSeedClusterOverP(),
                        electron->eSeedClusterOverPout(),electron->deltaEtaSuperClusterTrackAtVtx(),electron->deltaEtaSeedClusterTrackAtCalo(),
                        electron->deltaPhiSuperClusterTrackAtVtx(),electron->deltaPhiSeedClusterTrackAtCalo(),electron->deltaPhiEleClusterTrackAtCalo(),
                        electron->deltaEtaEleClusterTrackAtCalo());

                //setTrackProperties:
                localElectron.setTrackMomentum(sqrt(electron->trackMomentumAtVtx().Mag2()));
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

                edm::Handle< reco::VertexCollection > recoVertex;
                iEvent.getByLabel(primaryVertexProducer_, recoVertex);
                //good for eID : http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/CMSSW/RecoEgamma/ElectronIdentification/src/CutBasedElectronID.cc?revision=1.17&view=markup&sortdir=down&pathrev=V00-03-05
                double ip = -9999.;
                if (recoVertex->size() != 0) {
                    reco::VertexRef vtx(recoVertex, 0);
                    ip = fabs(electron->gsfTrack()->dxy(math::XYZPoint(vtx->x(),vtx->y(),vtx->z())));
                } else
                  ip = fabs(electron->gsfTrack()->dxy());

                localElectron.setImpactParameter(ip);
                
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


                //localElectron.setIsolation(5, electron->getIsolation(5));

               

                //            TLorentzVector tmpP4(-1000.,-1000.,-1000.,-1000);

                localElectron.setClassification(electron->classification());
                localElectron.setFbrem(electron->fbrem());
//                localElectron.setTriggerInfo(electron->getTriggerInfo());
//                localElectron.setConversion(electron->isFromConversion());


//=======================================

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
                        if(newId_){
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
				if ((patElectron->genParticleRef()).isNonnull()) {
					localElectron.setGenParticleIndex((patElectron->genParticleRef()).index());
				} else {
					localElectron.setGenParticleIndex(-1);
				}

			}

		}

		new( (*rootElectrons)[j] ) TRootElectron(localElectron);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localElectron << endl;
	}
}
