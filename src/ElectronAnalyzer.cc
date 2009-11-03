#include "../interface/ElectronAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0),useMC_(false),runSuperCluster_(false)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	electronProducer_ = producersNames.getParameter<edm::InputTag>("electronProducer");
}

ElectronAnalyzer::ElectronAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	electronProducer_ = producersNames.getParameter<edm::InputTag>("electronProducer");
	useMC_ = myConfig.getUntrackedParameter<bool>("doElectronMC");
	runSuperCluster_ = myConfig.getUntrackedParameter<bool>("runSuperCluster");
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

		// Variables from reco::GsfElectron
		localElectron.setClassification(electron->classification());
		localElectron.setCaloEnergy(electron->caloEnergy());
		localElectron.setCaloEnergyError(electron->caloEnergyError());
		// FIXME - Protect against sqrt(0)
		localElectron.setTrackMomentum(sqrt(electron->trackMomentumAtVtx().Mag2()));
		localElectron.setTrackMomentumError(electron->trackMomentumError());
		localElectron.setHadOverEm(electron->hadronicOverEm());
		localElectron.setDeltaEtaIn(electron->deltaEtaSuperClusterTrackAtVtx());
		localElectron.setDeltaPhiIn(electron->deltaPhiSuperClusterTrackAtVtx());
		localElectron.setEnergySuperClusterOverPin(electron->eSuperClusterOverP());
		localElectron.setDeltaEtaOut(electron->deltaEtaSeedClusterTrackAtCalo());
		localElectron.setDeltaPhiOut(electron->deltaPhiSeedClusterTrackAtCalo());
		localElectron.setEnergySeedClusterOverPout(electron->eSeedClusterOverPout());
		localElectron.setEnergyScaleCorrected(electron->isEnergyScaleCorrected());
		localElectron.setMomentumCorrected(electron->isMomentumCorrected());

		// Variables from reco::GsfTrack
		reco::GsfTrackRef gsfTrack = electron->gsfTrack();
		if ( gsfTrack.isNonnull() )
		{
			const reco::HitPattern& hit = gsfTrack->hitPattern();
			localElectron.setPixelLayersWithMeasurement(hit.pixelLayersWithMeasurement());
			localElectron.setStripLayersWithMeasurement(hit.stripLayersWithMeasurement());
			// FIXME - replace with double dxy(const Point& myBeamSpot) method ?
			localElectron.setD0(gsfTrack->d0());
			localElectron.setD0Error(gsfTrack->d0Error());
			// FIXME - replace with double dsz(const Point& myBeamSpot) method ?
			localElectron.setDsz(gsfTrack->dsz());
			localElectron.setDszError(gsfTrack->dszError());
			localElectron.setNormalizedChi2(gsfTrack->normalizedChi2());
			localElectron.setPtError(gsfTrack->ptError());
			localElectron.setEtaError(gsfTrack->etaError());
			localElectron.setPhiError(gsfTrack->phiError());
		}

		// Variables from reco::SuperCluster
		reco::SuperClusterRef superCluster = electron->superCluster();
		//const reco::SuperCluster* sc = superCluster.get();
		if ( superCluster.isNonnull() && runSuperCluster_ )
		{
			localElectron.setNbClusters(electron->numberOfClusters());
			localElectron.setSuperClusterRawEnergy(superCluster->rawEnergy());
			localElectron.setPreshowerEnergy(superCluster->preshowerEnergy());
			localElectron.setCaloPosition(
				superCluster->position().X()
				,superCluster->position().Y()
				,superCluster->position().Z()
			);

			// FIXME - associator supercluster <-> electron
			//localElectron.setSCRef(superCluster->toto());
		}		


		// Cluster Shape variables
		// need reco::SuperCluster and reco::BasicCluster
		if ( superCluster.isNonnull() && runSuperCluster_ )
		{
			reco::BasicClusterRef seedBasicCluster = superCluster->seed();
			if ( seedBasicCluster.isNonnull() ) localElectron.setClusterAlgo(seedBasicCluster->algo());

			// dR of the cone centered on the reco::GsfElectron and containing all its basic clusters constituents
			Float_t caloConeSize = 0;
			for (reco::basicCluster_iterator basicCluster = (*superCluster).clustersBegin(); basicCluster != (*superCluster).clustersEnd(); ++basicCluster )
			{
				Float_t dR = localElectron.DeltaR(TLorentzVector( (*basicCluster)->position().x(), (*basicCluster)->position().y(), (*basicCluster)->position().z(), 0. ) );
				if (dR > caloConeSize) caloConeSize = dR;
			}
			// FIXME - if no BasicCluster collection, init to -999.
			localElectron.setCaloConeSize(caloConeSize);

			// need reduced Ecal RecHits Collections for EcalClusterLazyTools
			// FIXME - check lazyTools is initialized ==> lazyTools has to be a pointer
			if ( seedBasicCluster.isNonnull() ) 
			{
				localElectron.setE2x2(lazyTools.e2x2(*seedBasicCluster));
				localElectron.setE3x3(lazyTools.e3x3(*seedBasicCluster));
				localElectron.setE5x5(lazyTools.e5x5(*seedBasicCluster));
				localElectron.setEMax(lazyTools.eMax(*seedBasicCluster));
			}
		}


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

			// Isolation
			pair < Float_t, Int_t > trackerIso;

			trackerIso = patElectron->trackerIsoDeposit()->depositAndCountWithin(0.1);
			localElectron.setIsoR01_sumPt(trackerIso.first);
			localElectron.setIsoR01_nTracks(trackerIso.second);

			trackerIso = patElectron->trackerIsoDeposit()->depositAndCountWithin(0.2);
			localElectron.setIsoR02_sumPt(trackerIso.first);
			localElectron.setIsoR02_nTracks(trackerIso.second);

			trackerIso = patElectron->trackerIsoDeposit()->depositAndCountWithin(0.3);
			localElectron.setIsoR03_sumPt(trackerIso.first);
			localElectron.setIsoR03_nTracks(trackerIso.second);
			localElectron.setIsoR03_emEt( patElectron->ecalIsoDeposit()->depositAndCountWithin(0.3).first );
			localElectron.setIsoR03_hadEt( patElectron->hcalIsoDeposit()->depositAndCountWithin(0.3).first );

			trackerIso = patElectron->trackerIsoDeposit()->depositAndCountWithin(0.5);
			localElectron.setIsoR05_sumPt(trackerIso.first );
			localElectron.setIsoR05_nTracks(trackerIso.second);
			localElectron.setIsoR05_emEt( patElectron->ecalIsoDeposit()->depositAndCountWithin(0.5).first );
			localElectron.setIsoR05_hadEt( patElectron->hcalIsoDeposit()->depositAndCountWithin(0.5).first );


			// Electron ID
			
			// Old 2.1.X electron ID
			/*
			localElectron.setIDPTDRLoose(patElectron->leptonID("ptdrLoose"));
			localElectron.setIDPTDRMedium(patElectron->leptonID("ptdrMedium"));
			localElectron.setIDPTDRTight(patElectron->leptonID("ptdrTight"));
			localElectron.setIDCutBasedLoose(patElectron->leptonID("loose"));
			localElectron.setIDCutBasedRobust(patElectron->leptonID("robust"));
			localElectron.setIDCutBasedTight(patElectron->leptonID("tight"));
			localElectron.setIDLikelihood(patElectron->leptonID("likelihood"));
			localElectron.setIDNeuralNet(patElectron->leptonID("neuralnet"));
			*/

			// New 2.2.X electron ID
			// Only Cut Based ID available by default (4 sequential cuts on H/E, DeltaEta, DeltaPhi, SigmaEtaEta)
			// "Robust" ids (eidRobustLoose, eidRobustTight, eidRobustHighEnergy) corresponds to fixed threshold
			// eidLoose and eidTight corresponds to the catagory based identification (E/p, fBrem)
			localElectron.setIDCutBasedFixedThresholdLoose(int(patElectron->electronID("eidRobustLoose")));
			localElectron.setIDCutBasedFixedThresholdTight(int(patElectron->electronID("eidRobustTight")));
			localElectron.setIDCutBasedFixedThresholdHighEnergy(int(patElectron->electronID("eidRobustHighEnergy")));
			localElectron.setIDCutBasedCategorizedLoose(int(patElectron->electronID("eidLoose")));
			localElectron.setIDCutBasedCategorizedTight(int(patElectron->electronID("eidTight")));
			//localElectron.setIDLikelihood(patElectron->leptonID("likelihood"));
			//localElectron.setIDNeuralNet(patElectron->leptonID("neuralnet"));


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
