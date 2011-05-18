#ifndef TRootElectron_h
#define TRootElectron_h

#include <map>
#include <iostream>
#include <TLorentzVector.h>


#include "../interface/TRootParticle.h"

using namespace std;

namespace TopTree
{
	class TRootElectron : public TRootParticle
	{

	public:
//		void Print(Option_t* option = "") const;
		TRootElectron() :
			TRootParticle(),
			scPixCharge_(-9999),
			isGsfCtfScPixConsistent_(false),
			isGsfScPixConsistent_(false),
			isGsfCtfConsistent_(false),
			trackerDrivenSeed_(false),
			ecalDrivenSeed_(false),
			eSuperClusterOverPin_(-9999.),
			eSuperClusterOverPout_(-9999.),
			eSeedClusterOverPin_(-9999.),
			eSeedClusterOverPout_(-9999.),
			deltaEtaIn_(-9999.),
			deltaEtaOut_(-9999.),
			deltaPhiIn_(-9999.),
			deltaPhiOut_(-9999.),
			deltaPhiSuperClusterTrackAtCalo_(-9999.),
			deltaEtaSuperClusterTrackAtCalo_(-9999.),
			trackMomentum_(-9999.),
			momentumAtCalo_(-9999.),
			momentumOut_(-9999.),
			momentumAtEleClus_(-9999.),
			momentumAtVtxWithConstraint_(-9999.),
			pixelLayersWithMeasurement_(-9999),
			stripLayersWithMeasurement_(-9999),
			d0_(-9999.),
			dsz_(-9999.),
			d0Error_(-9999.),
			dszError_(-9999.),
			dB_(-9999.),
			dBError_(-9999.),
			missingHits_(-9999),
			ip_(-9999.),
			positionAtVtx_(-9999.,-9999.,-9999.),
			positionAtCalo_(-9999.,-9999.,-9999.),
			normalizedChi2_(9999.),
			ptError_(-9999.),
			trackMomentumError_(-9999.),
			ecalEnergyError_(-9999.),
			ecalEnergy_(-9999.),
			isEcalEnergyCorrected_(false),
			isMomentumCorrected_(false),
			electronMomentumError_(-9999.),
			caloPosition_(-9999.,-9999.,-9999.),
			basicClusterSize_(9999),
			clusterAlgo_(9999),
			caloConeSize_(9999),
			nbClusters_(9999),
			superClusterRawEnergy_(-9999.),
		        superClusterEta_(-9999.),
			preshowerEnergy_(-9999.),
			sigmaEtaEta_(-9999.),
			sigmaIetaIeta_(-9999.),
			e1x5_(-9999.),
			e2x5Max_(-9999.),
			e5x5_(-9999.),
			e2x2_(-9999.),
			e3x3_(-9999.),
			eMax_(-9999.),
			hcalDepth1OverEcal_(-9999.),
			hcalDepth2OverEcal_(-9999.),
			isEB_(false),
			isEE_(false),
			isEBEEGap_(false),
			isEBEtaGap_(false),
			isEBPhiGap_(false),
			isEEDeeGap_(false),
			isEERingGap_(false),
			tkSumPt03_(-9999.),
			ecalRecHitSumEt03_(-9999.),
			hcalDepth1TowerSumEt03_(-9999.),
			hcalDepth2TowerSumEt03_(-9999.),
			tkSumPt04_(-9999.),
			ecalRecHitSumEt04_(-9999.),
			hcalDepth1TowerSumEt04_(-9999.),
			hcalDepth2TowerSumEt04_(-9999.),
			chargedHadronIso_(-9999),
			photonIso_(-9999),
			neutralHadronIso_(-9999),
			idCutBasedRobustLoose_(-9999),
			idCutBasedRobustTight_(-9999),
			idCutBasedRobustHighEnergy_(-9999),
			idCategorizedLoose_(-9999),
			idCategorizedTight_(-9999),
/*			idCiCVeryLoose_(-9999),
			idCiCLoose_(-9999),
			idCiCMedium_(-9999),
			idCiCTight_(-9999),
			idCiCSuperTight_(-9999),
			idCiCHyperTight1_(-9999),
			idCiCHyperTight2_(-9999),
			idCiCHyperTight3_(-9999),
			idCiCHyperTight4_(-9999),*/
			classification_(-9999),
			fBrem_(-9999.),
			isConversion_(true),
		        Dist_(9999),
		        DCot_(9999),
			HLT_Ele10_SW_L1R_(false),
			HLT_Ele15_SW_L1R_(false)
			{;}

		TRootElectron(const TRootElectron& e) :
			TRootParticle(e),
			scPixCharge_(e.scPixCharge_),
			isGsfCtfScPixConsistent_(e.isGsfCtfScPixConsistent_),
			isGsfScPixConsistent_(e.isGsfScPixConsistent_),
			isGsfCtfConsistent_(e.isGsfCtfConsistent_),
			trackerDrivenSeed_(e.trackerDrivenSeed_),
			ecalDrivenSeed_(e.ecalDrivenSeed_),
			eSuperClusterOverPin_(e.eSuperClusterOverPin_),
			eSuperClusterOverPout_(e.eSuperClusterOverPout_),
			eSeedClusterOverPin_(e.eSeedClusterOverPin_),
			eSeedClusterOverPout_(e.eSeedClusterOverPout_),
			deltaEtaIn_(e.deltaEtaIn_),
			deltaEtaOut_(e.deltaEtaOut_),
			deltaPhiIn_(e.deltaPhiIn_),
			deltaPhiOut_(e.deltaPhiOut_),
			deltaPhiSuperClusterTrackAtCalo_(e.deltaPhiSuperClusterTrackAtCalo_),
			deltaEtaSuperClusterTrackAtCalo_(e.deltaEtaSuperClusterTrackAtCalo_),
			trackMomentum_(e.trackMomentum_),
			momentumAtCalo_(e.momentumAtCalo_),
			momentumOut_(e.momentumOut_),
			momentumAtEleClus_(e.momentumAtEleClus_),
			momentumAtVtxWithConstraint_(e.momentumAtVtxWithConstraint_),
			pixelLayersWithMeasurement_(e.pixelLayersWithMeasurement_),
			stripLayersWithMeasurement_(e.stripLayersWithMeasurement_),
			d0_(e.d0_),
			dsz_(e.dsz_),
			d0Error_(e.d0Error_),
			dszError_(e.dszError_),
			dB_(e.dB_),
			dBError_(e.dBError_),
			missingHits_(e.missingHits_),
			ip_(e.ip_),
			positionAtVtx_(e.positionAtVtx_),
			positionAtCalo_(e.positionAtCalo_),
			normalizedChi2_(e.normalizedChi2_),
			ptError_(e.ptError_),
			trackMomentumError_(e.trackMomentumError_),
			ecalEnergyError_(e.ecalEnergyError_),
			ecalEnergy_(e.ecalEnergy_),
			isEcalEnergyCorrected_(e.isEcalEnergyCorrected_),
			isMomentumCorrected_(e.isMomentumCorrected_),
			electronMomentumError_(e.electronMomentumError_),
			caloPosition_(e.caloPosition_),
			basicClusterSize_(e.basicClusterSize_),
			clusterAlgo_(e.clusterAlgo_),
			caloConeSize_(e.caloConeSize_),
			nbClusters_(e.nbClusters_),
			superClusterRawEnergy_(e.superClusterRawEnergy_),
		        superClusterEta_(e.superClusterEta_),    
			preshowerEnergy_(e.preshowerEnergy_),
			sigmaEtaEta_(e.sigmaEtaEta_),
			sigmaIetaIeta_(e.sigmaIetaIeta_),
			e1x5_(e.e1x5_),
			e2x5Max_(e.e2x5Max_),
			e5x5_(e.e5x5_),
			e2x2_(e.e2x2_),
			e3x3_(e.e3x3_),
			eMax_(e.eMax_),
			hcalDepth1OverEcal_(e.hcalDepth1OverEcal_),
			hcalDepth2OverEcal_(e.hcalDepth2OverEcal_),
			isEB_(e.isEB_),
			isEE_(e.isEE_),
			isEBEEGap_(e.isEBEEGap_),
			isEBEtaGap_(e.isEBEtaGap_),
			isEBPhiGap_(e.isEBPhiGap_),
			isEEDeeGap_(e.isEEDeeGap_),
			isEERingGap_(e.isEERingGap_),
			tkSumPt03_(e.tkSumPt03_),
			ecalRecHitSumEt03_(e.ecalRecHitSumEt03_),
			hcalDepth1TowerSumEt03_(e.hcalDepth1TowerSumEt03_),
			hcalDepth2TowerSumEt03_(e.hcalDepth2TowerSumEt03_),
			tkSumPt04_(e.tkSumPt04_),
			ecalRecHitSumEt04_(e.ecalRecHitSumEt04_),
			hcalDepth1TowerSumEt04_(e.hcalDepth1TowerSumEt04_),
			hcalDepth2TowerSumEt04_(e.hcalDepth2TowerSumEt04_),
			chargedHadronIso_(e.chargedHadronIso_),
			photonIso_(e.photonIso_),
			neutralHadronIso_(e.neutralHadronIso_),
			idCutBasedRobustLoose_(e.idCutBasedRobustLoose_),
			idCutBasedRobustTight_(e.idCutBasedRobustTight_),
			idCutBasedRobustHighEnergy_(e.idCutBasedRobustHighEnergy_),
			idCategorizedLoose_(e.idCategorizedLoose_),
			idCategorizedTight_(e.idCategorizedTight_),
/*			idCiCVeryLoose_(e.idCiCVeryLoose_),
			idCiCLoose_(e.idCiCLoose_),
			idCiCMedium_(e.idCiCMedium_),
			idCiCTight_(e.idCiCTight_),
			idCiCSuperTight_(e.idCiCSuperTight_),
			idCiCHyperTight1_(e.idCiCHyperTight1_),
			idCiCHyperTight2_(e.idCiCHyperTight2_),
			idCiCHyperTight3_(e.idCiCHyperTight3_),
			idCiCHyperTight4_(e.idCiCHyperTight4_),*/
			classification_(e.classification_),
			fBrem_(e.fBrem_),
			isConversion_(e.isConversion_),
		        Dist_(e.Dist_),
		        DCot_(e.DCot_),
			HLT_Ele10_SW_L1R_(e.HLT_Ele10_SW_L1R_),
			HLT_Ele15_SW_L1R_(e.HLT_Ele15_SW_L1R_)
			{;}

		TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e) :
			TRootParticle(px,py,pz,e),
			scPixCharge_(-9999),
			isGsfCtfScPixConsistent_(false),
			isGsfScPixConsistent_(false),
			isGsfCtfConsistent_(false),
			trackerDrivenSeed_(false),
			ecalDrivenSeed_(false),
			eSuperClusterOverPin_(-9999.),
			eSuperClusterOverPout_(-9999.),
			eSeedClusterOverPin_(-9999.),
			eSeedClusterOverPout_(-9999.),
			deltaEtaIn_(-9999.),
			deltaEtaOut_(-9999.),
			deltaPhiIn_(-9999.),
			deltaPhiOut_(-9999.),
			deltaPhiSuperClusterTrackAtCalo_(-9999.),
			deltaEtaSuperClusterTrackAtCalo_(-9999.),
			trackMomentum_(-9999.),
			momentumAtCalo_(-9999.),
			momentumOut_(-9999.),
			momentumAtEleClus_(-9999.),
			momentumAtVtxWithConstraint_(-9999.),
			pixelLayersWithMeasurement_(-9999),
			stripLayersWithMeasurement_(-9999),
			d0_(-9999.),
			dsz_(-9999.),
			d0Error_(-9999.),
			dszError_(-9999.),
			dB_(-9999.),
			dBError_(-9999.),
			missingHits_(-9999),
			ip_(-9999.),
			positionAtVtx_(-9999.,-9999.,-9999.),
			positionAtCalo_(-9999.,-9999.,-9999.),
			normalizedChi2_(9999.),
			ptError_(-9999.),
			trackMomentumError_(-9999.),
			ecalEnergyError_(-9999.),
			ecalEnergy_(-9999.),
			isEcalEnergyCorrected_(false),
			isMomentumCorrected_(false),
			electronMomentumError_(-9999.),
			caloPosition_(-9999.,-9999.,-9999.),
			basicClusterSize_(9999),
			clusterAlgo_(9999),
			caloConeSize_(9999),
			nbClusters_(9999),
			superClusterRawEnergy_(-9999.),
		        superClusterEta_(-9999.),
		        preshowerEnergy_(-9999.),
			sigmaEtaEta_(-9999.),
			sigmaIetaIeta_(-9999.),
			e1x5_(-9999.),
			e2x5Max_(-9999.),
			e5x5_(-9999.),
			e2x2_(-9999.),
			e3x3_(-9999.),
			eMax_(-9999.),
			hcalDepth1OverEcal_(-9999.),
			hcalDepth2OverEcal_(-9999.),
			isEB_(false),
			isEE_(false),
			isEBEEGap_(false),
			isEBEtaGap_(false),
			isEBPhiGap_(false),
			isEEDeeGap_(false),
			isEERingGap_(false),
			tkSumPt03_(-9999.),
			ecalRecHitSumEt03_(-9999.),
			hcalDepth1TowerSumEt03_(-9999.),
			hcalDepth2TowerSumEt03_(-9999.),
			tkSumPt04_(-9999.),
			ecalRecHitSumEt04_(-9999.),
			hcalDepth1TowerSumEt04_(-9999.),
			hcalDepth2TowerSumEt04_(-9999.),
			chargedHadronIso_(-9999),
			photonIso_(-9999),
			neutralHadronIso_(-9999),
			idCutBasedRobustLoose_(-9999),
			idCutBasedRobustTight_(-9999),
			idCutBasedRobustHighEnergy_(-9999),
			idCategorizedLoose_(-9999),
			idCategorizedTight_(-9999),
/*			idCiCVeryLoose_(-9999),
			idCiCLoose_(-9999),
			idCiCMedium_(-9999),
			idCiCTight_(-9999),
			idCiCSuperTight_(-9999),
			idCiCHyperTight1_(-9999),
			idCiCHyperTight2_(-9999),
			idCiCHyperTight3_(-9999),
			idCiCHyperTight4_(-9999),*/
		        classification_(-9999),
			fBrem_(-9999.),
			isConversion_(true),
		        Dist_(9999),
		        DCot_(9999),
			HLT_Ele10_SW_L1R_(false),
			HLT_Ele15_SW_L1R_(false)
			{;}
	
		TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z),
			scPixCharge_(-9999),
			isGsfCtfScPixConsistent_(false),
			isGsfScPixConsistent_(false),
			isGsfCtfConsistent_(false),
			trackerDrivenSeed_(false),
			ecalDrivenSeed_(false),
			eSuperClusterOverPin_(-9999.),
			eSuperClusterOverPout_(-9999.),
			eSeedClusterOverPin_(-9999.),
			eSeedClusterOverPout_(-9999.),
			deltaEtaIn_(-9999.),
			deltaEtaOut_(-9999.),
			deltaPhiIn_(-9999.),
			deltaPhiOut_(-9999.),
			deltaPhiSuperClusterTrackAtCalo_(-9999.),
			deltaEtaSuperClusterTrackAtCalo_(-9999.),
			trackMomentum_(-9999.),
			momentumAtCalo_(-9999.),
			momentumOut_(-9999.),
			momentumAtEleClus_(-9999.),
			momentumAtVtxWithConstraint_(-9999.),
			pixelLayersWithMeasurement_(-9999),
			stripLayersWithMeasurement_(-9999),
			d0_(-9999.),
			dsz_(-9999.),
			d0Error_(-9999.),
			dszError_(-9999.),
			dB_(-9999.),
			dBError_(-9999.),
			missingHits_(-9999),
			ip_(-9999.),
			positionAtVtx_(-9999.,-9999.,-9999.),
			positionAtCalo_(-9999.,-9999.,-9999.),
			normalizedChi2_(9999.),
			ptError_(-9999.),
			trackMomentumError_(-9999.),
			ecalEnergyError_(-9999.),
			ecalEnergy_(-9999.),
			isEcalEnergyCorrected_(false),
			isMomentumCorrected_(false),
			electronMomentumError_(-9999.),
			caloPosition_(-9999.,-9999.,-9999.),
			basicClusterSize_(9999),
			clusterAlgo_(9999),
			caloConeSize_(9999),
			nbClusters_(9999),
			superClusterRawEnergy_(-9999.),
  		        superClusterEta_(-9999.),
                        preshowerEnergy_(-9999.),
			sigmaEtaEta_(-9999.),
			sigmaIetaIeta_(-9999.),
			e1x5_(-9999.),
			e2x5Max_(-9999.),
			e5x5_(-9999.),
			e2x2_(-9999.),
			e3x3_(-9999.),
			eMax_(-9999.),
			hcalDepth1OverEcal_(-9999.),
			hcalDepth2OverEcal_(-9999.),
			isEB_(false),
			isEE_(false),
			isEBEEGap_(false),
			isEBEtaGap_(false),
			isEBPhiGap_(false),
			isEEDeeGap_(false),
			isEERingGap_(false),
			tkSumPt03_(-9999.),
			ecalRecHitSumEt03_(-9999.),
			hcalDepth1TowerSumEt03_(-9999.),
			hcalDepth2TowerSumEt03_(-9999.),
			tkSumPt04_(-9999.),
			ecalRecHitSumEt04_(-9999.),
			hcalDepth1TowerSumEt04_(-9999.),
			hcalDepth2TowerSumEt04_(-9999.),
			chargedHadronIso_(-9999),
			photonIso_(-9999),
			neutralHadronIso_(-9999),
			idCutBasedRobustLoose_(-9999),
			idCutBasedRobustTight_(-9999),
			idCutBasedRobustHighEnergy_(-9999),
			idCategorizedLoose_(-9999),
			idCategorizedTight_(-9999),
/*			idCiCVeryLoose_(-9999),
			idCiCLoose_(-9999),
			idCiCMedium_(-9999),
			idCiCTight_(-9999),
			idCiCSuperTight_(-9999),
			idCiCHyperTight1_(-9999),
			idCiCHyperTight2_(-9999),
			idCiCHyperTight3_(-9999),
			idCiCHyperTight4_(-9999),*/
		        classification_(-9999),
			fBrem_(-9999.),
			isConversion_(true),
		        Dist_(9999),
		        DCot_(9999),
			HLT_Ele10_SW_L1R_(false),
			HLT_Ele15_SW_L1R_(false)
			{;}

		TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Int_t charge) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge),
			scPixCharge_(-9999),
			isGsfCtfScPixConsistent_(false),
			isGsfScPixConsistent_(false),
			isGsfCtfConsistent_(false),
			trackerDrivenSeed_(false),
			ecalDrivenSeed_(false),
			eSuperClusterOverPin_(-9999.),
			eSuperClusterOverPout_(-9999.),
			eSeedClusterOverPin_(-9999.),
			eSeedClusterOverPout_(-9999.),
			deltaEtaIn_(-9999.),
			deltaEtaOut_(-9999.),
			deltaPhiIn_(-9999.),
			deltaPhiOut_(-9999.),
			deltaPhiSuperClusterTrackAtCalo_(-9999.),
			deltaEtaSuperClusterTrackAtCalo_(-9999.),
			trackMomentum_(-9999.),
			momentumAtCalo_(-9999.),
			momentumOut_(-9999.),
			momentumAtEleClus_(-9999.),
			momentumAtVtxWithConstraint_(-9999.),
			pixelLayersWithMeasurement_(-9999),
			stripLayersWithMeasurement_(-9999),
			d0_(-9999.),
			dsz_(-9999.),
			d0Error_(-9999.),
			dszError_(-9999.),
			dB_(-9999.),
			dBError_(-9999.),
			missingHits_(-9999),
			ip_(-9999.),
			positionAtVtx_(-9999.,-9999.,-9999.),
			positionAtCalo_(-9999.,-9999.,-9999.),
			normalizedChi2_(9999.),
			ptError_(-9999.),
			trackMomentumError_(-9999.),
			ecalEnergyError_(-9999.),
			ecalEnergy_(-9999.),
			isEcalEnergyCorrected_(false),
			isMomentumCorrected_(false),
			electronMomentumError_(-9999.),
			caloPosition_(-9999.,-9999.,-9999.),
			basicClusterSize_(9999),
			clusterAlgo_(9999),
			caloConeSize_(9999),
			nbClusters_(9999),
			superClusterRawEnergy_(-9999.),
		        superClusterEta_(-9999.),
		        preshowerEnergy_(-9999.),
			sigmaEtaEta_(-9999.),
			sigmaIetaIeta_(-9999.),
			e1x5_(-9999.),
			e2x5Max_(-9999.),
			e5x5_(-9999.),
			e2x2_(-9999.),
			e3x3_(-9999.),
			eMax_(-9999.),
			hcalDepth1OverEcal_(-9999.),
			hcalDepth2OverEcal_(-9999.),
			isEB_(false),
			isEE_(false),
			isEBEEGap_(false),
			isEBEtaGap_(false),
			isEBPhiGap_(false),
			isEEDeeGap_(false),
			isEERingGap_(false),
			tkSumPt03_(-9999.),
			ecalRecHitSumEt03_(-9999.),
			hcalDepth1TowerSumEt03_(-9999.),
			hcalDepth2TowerSumEt03_(-9999.),
			tkSumPt04_(-9999.),
			ecalRecHitSumEt04_(-9999.),
			hcalDepth1TowerSumEt04_(-9999.),
			hcalDepth2TowerSumEt04_(-9999.),
			chargedHadronIso_(-9999),
			photonIso_(-9999),
			neutralHadronIso_(-9999),
			idCutBasedRobustLoose_(-9999),
			idCutBasedRobustTight_(-9999),
			idCutBasedRobustHighEnergy_(-9999),
			idCategorizedLoose_(-9999),
			idCategorizedTight_(-9999),
/*			idCiCVeryLoose_(-9999),
			idCiCLoose_(-9999),
			idCiCMedium_(-9999),
			idCiCTight_(-9999),
			idCiCSuperTight_(-9999),
			idCiCHyperTight1_(-9999),
			idCiCHyperTight2_(-9999),
			idCiCHyperTight3_(-9999),
			idCiCHyperTight4_(-9999),*/
		        classification_(-9999),
			fBrem_(-9999.),
			isConversion_(true),
		        Dist_(9999),
		        DCot_(9999),
			HLT_Ele10_SW_L1R_(false),
			HLT_Ele15_SW_L1R_(false)
			{;}

		TRootElectron(const TLorentzVector &momentum) :
			TRootParticle(momentum),
			scPixCharge_(-9999),
			isGsfCtfScPixConsistent_(false),
			isGsfScPixConsistent_(false),
			isGsfCtfConsistent_(false),
			trackerDrivenSeed_(false),
			ecalDrivenSeed_(false),
			eSuperClusterOverPin_(-9999.),
			eSuperClusterOverPout_(-9999.),
			eSeedClusterOverPin_(-9999.),
			eSeedClusterOverPout_(-9999.),
			deltaEtaIn_(-9999.),
			deltaEtaOut_(-9999.),
			deltaPhiIn_(-9999.),
			deltaPhiOut_(-9999.),
			deltaPhiSuperClusterTrackAtCalo_(-9999.),
			deltaEtaSuperClusterTrackAtCalo_(-9999.),
			trackMomentum_(-9999.),
			momentumAtCalo_(-9999.),
			momentumOut_(-9999.),
			momentumAtEleClus_(-9999.),
			momentumAtVtxWithConstraint_(-9999.),
			pixelLayersWithMeasurement_(-9999),
			stripLayersWithMeasurement_(-9999),
			d0_(-9999.),
			dsz_(-9999.),
			d0Error_(-9999.),
			dszError_(-9999.),
			dB_(-9999.),
			dBError_(-9999.),
			missingHits_(-9999),
			ip_(-9999.),
			positionAtVtx_(-9999.,-9999.,-9999.),
			positionAtCalo_(-9999.,-9999.,-9999.),
			normalizedChi2_(9999.),
			ptError_(-9999.),
			trackMomentumError_(-9999.),
			ecalEnergyError_(-9999.),
			ecalEnergy_(-9999.),
			isEcalEnergyCorrected_(false),
			isMomentumCorrected_(false),
			electronMomentumError_(-9999.),
			caloPosition_(-9999.,-9999.,-9999.),
			basicClusterSize_(9999),
			clusterAlgo_(9999),
			caloConeSize_(9999),
			nbClusters_(9999),
			superClusterRawEnergy_(-9999.),
		        superClusterEta_(-9999.),
		        preshowerEnergy_(-9999.),
			sigmaEtaEta_(-9999.),
			sigmaIetaIeta_(-9999.),
			e1x5_(-9999.),
			e2x5Max_(-9999.),
			e5x5_(-9999.),
			e2x2_(-9999.),
			e3x3_(-9999.),
			eMax_(-9999.),
			hcalDepth1OverEcal_(-9999.),
			hcalDepth2OverEcal_(-9999.),
			isEB_(false),
			isEE_(false),
			isEBEEGap_(false),
			isEBEtaGap_(false),
			isEBPhiGap_(false),
			isEEDeeGap_(false),
			isEERingGap_(false),
			tkSumPt03_(-9999.),
			ecalRecHitSumEt03_(-9999.),
			hcalDepth1TowerSumEt03_(-9999.),
			hcalDepth2TowerSumEt03_(-9999.),
			tkSumPt04_(-9999.),
			ecalRecHitSumEt04_(-9999.),
			hcalDepth1TowerSumEt04_(-9999.),
			hcalDepth2TowerSumEt04_(-9999.),
			chargedHadronIso_(-9999),
			photonIso_(-9999),
			neutralHadronIso_(-9999),
			idCutBasedRobustLoose_(-9999),
			idCutBasedRobustTight_(-9999),
			idCutBasedRobustHighEnergy_(-9999),
			idCategorizedLoose_(-9999),
			idCategorizedTight_(-9999),
/*			idCiCVeryLoose_(-9999),
			idCiCLoose_(-9999),
			idCiCMedium_(-9999),
			idCiCTight_(-9999),
			idCiCSuperTight_(-9999),
			idCiCHyperTight1_(-9999),
			idCiCHyperTight2_(-9999),
			idCiCHyperTight3_(-9999),
			idCiCHyperTight4_(-9999),*/
		       classification_(-9999),
			fBrem_(-9999.),
			isConversion_(true),
		        Dist_(9999),
		        DCot_(9999),
			HLT_Ele10_SW_L1R_(false),
			HLT_Ele15_SW_L1R_(false)
			{;}

		TRootElectron(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
			TRootParticle(momentum, vertex, type, charge),
			scPixCharge_(-9999),
			isGsfCtfScPixConsistent_(false),
			isGsfScPixConsistent_(false),
			isGsfCtfConsistent_(false),
			trackerDrivenSeed_(false),
			ecalDrivenSeed_(false),
			eSuperClusterOverPin_(-9999.),
			eSuperClusterOverPout_(-9999.),
			eSeedClusterOverPin_(-9999.),
			eSeedClusterOverPout_(-9999.),
			deltaEtaIn_(-9999.),
			deltaEtaOut_(-9999.),
			deltaPhiIn_(-9999.),
			deltaPhiOut_(-9999.),
			deltaPhiSuperClusterTrackAtCalo_(-9999.),
			deltaEtaSuperClusterTrackAtCalo_(-9999.),
			trackMomentum_(-9999.),
			momentumAtCalo_(-9999.),
			momentumOut_(-9999.),
			momentumAtEleClus_(-9999.),
			momentumAtVtxWithConstraint_(-9999.),
			pixelLayersWithMeasurement_(-9999),
			stripLayersWithMeasurement_(-9999),
			d0_(-9999.),
			dsz_(-9999.),
			d0Error_(-9999.),
			dszError_(-9999.),
			dB_(-9999.),
			dBError_(-9999.),
			missingHits_(-9999),
			ip_(-9999.),
			positionAtVtx_(-9999.,-9999.,-9999.),
			positionAtCalo_(-9999.,-9999.,-9999.),
			normalizedChi2_(9999.),
			ptError_(-9999.),
			trackMomentumError_(-9999.),
			ecalEnergyError_(-9999.),
			ecalEnergy_(-9999.),
			isEcalEnergyCorrected_(false),
			isMomentumCorrected_(false),
			electronMomentumError_(-9999.),
			caloPosition_(-9999.,-9999.,-9999.),
			basicClusterSize_(9999),
			clusterAlgo_(9999),
			caloConeSize_(9999),
			nbClusters_(9999),
			superClusterRawEnergy_(-9999.),
		        superClusterEta_(-9999.),
		        preshowerEnergy_(-9999.),
			sigmaEtaEta_(-9999.),
			sigmaIetaIeta_(-9999.),
			e1x5_(-9999.),
			e2x5Max_(-9999.),
			e5x5_(-9999.),
			e2x2_(-9999.),
			e3x3_(-9999.),
			eMax_(-9999.),
			hcalDepth1OverEcal_(-9999.),
			hcalDepth2OverEcal_(-9999.),
			isEB_(false),
			isEE_(false),
			isEBEEGap_(false),
			isEBEtaGap_(false),
			isEBPhiGap_(false),
			isEEDeeGap_(false),
			isEERingGap_(false),
			tkSumPt03_(-9999.),
			ecalRecHitSumEt03_(-9999.),
			hcalDepth1TowerSumEt03_(-9999.),
			hcalDepth2TowerSumEt03_(-9999.),
			tkSumPt04_(-9999.),
			ecalRecHitSumEt04_(-9999.),
			hcalDepth1TowerSumEt04_(-9999.),
			hcalDepth2TowerSumEt04_(-9999.),
			chargedHadronIso_(-9999),
			photonIso_(-9999),
			neutralHadronIso_(-9999),
			idCutBasedRobustLoose_(-9999),
			idCutBasedRobustTight_(-9999),
			idCutBasedRobustHighEnergy_(-9999),
			idCategorizedLoose_(-9999),
			idCategorizedTight_(-9999),
/*			idCiCVeryLoose_(-9999),
			idCiCLoose_(-9999),
			idCiCMedium_(-9999),
			idCiCTight_(-9999),
			idCiCSuperTight_(-9999),
			idCiCHyperTight1_(-9999),
			idCiCHyperTight2_(-9999),
			idCiCHyperTight3_(-9999),
			idCiCHyperTight4_(-9999),*/
		        classification_(-9999),
			fBrem_(-9999.),
			isConversion_(true),
		        Dist_(9999),
		        DCot_(9999),
			HLT_Ele10_SW_L1R_(false),
			HLT_Ele15_SW_L1R_(false)
			{;}

		~TRootElectron() {;}


	public:
		virtual TString typeName() const { return "TRootElectron"; }

		Int_t Charge() const { return scPixCharge_; }
		Bool_t isGsfCtfScPixConsistent() const { return isGsfCtfScPixConsistent_; }
		Bool_t isGsfScPixConsistent() const { return isGsfScPixConsistent_; }
		Bool_t isGsfCtfConsistent() const { return isGsfCtfConsistent_; }

		Bool_t isEcalDrivenSeed() const { return ecalDrivenSeed_; }
		Bool_t isTrackerDrivenSeed() const { return trackerDrivenSeed_; }

		Float_t eScOverPin() const { return eSuperClusterOverPin_; }
		Float_t eScOverPout() const { return eSuperClusterOverPout_; }
		Float_t eSeedOverPin() const { return eSeedClusterOverPin_; }
		Float_t eSeedOverPout() const { return eSeedClusterOverPout_; }
		Float_t deltaEtaIn() const { return deltaEtaIn_; }
		Float_t deltaEtaOut() const { return deltaEtaOut_; }
		Float_t deltaPhiIn() const { return deltaPhiIn_; }
		Float_t deltaPhiOut() const { return deltaPhiOut_; }
		Float_t deltaPhiScTrkOut() const { return deltaPhiSuperClusterTrackAtCalo_; }
		Float_t deltaEtaScTrkOut() const { return deltaEtaSuperClusterTrackAtCalo_; }

		Float_t trackMomentum() const { return trackMomentum_; }
		Float_t trackMomentumAtSuperClusterPosition() const { return momentumAtCalo_; }
		Float_t trackMomentumAtSeedClusterPosition() const { return momentumOut_; }
		Float_t trackMomentumAtElectronClusterPosition() const { return momentumAtEleClus_; }
		Float_t trackMomentumAtVtxWithConstraints() const { return momentumAtVtxWithConstraint_; }
		Int_t trackPixelLayersWithMeasurement() const { return pixelLayersWithMeasurement_; }
		Int_t trackStripLayersWithMeasurement() const { return stripLayersWithMeasurement_; }
		Float_t d0() const { return d0_; }
		Float_t d0Error()const { return d0Error_; }
		Float_t trackDsz()const { return dsz_; }
		Float_t dszError()const { return dszError_; }
		Float_t dB() const { return dB_; }
		Float_t dBError() const { return dBError_; }
		
		Int_t missingHits() const { return missingHits_; }
		Float_t impactParameter() const { return ip_; }
		TVector3 trackPositionAtVtx() const { return positionAtVtx_; }
		TVector3 trackPositionAtCalo() const { return positionAtCalo_; }
		Float_t trackNormalizedChi2() const { return normalizedChi2_; }
		Float_t trackPtError() const { return ptError_; }

		Float_t trackMomentumError() const { return trackMomentumError_; }
		Float_t caloEnergyError() const { return ecalEnergyError_; }
		Float_t caloEnergy() const { return ecalEnergy_; }
		Bool_t isCaloEnergyCorrected() const { return isEcalEnergyCorrected_; }
		Bool_t isMomentumCorrected() const { return isMomentumCorrected_; }
		Float_t electronMomentumError() const { return electronMomentumError_; }

		TVector3 caloPosition() const { return caloPosition_; }
		Int_t basicClusterSize() const { return basicClusterSize_; }
		Int_t clusterAlgo() const { return clusterAlgo_; }
		Float_t caloConeSize() const { return caloConeSize_; }
		Int_t nClusters() const { return nbClusters_; }
		Float_t superClusterRawEnergy() const { return superClusterRawEnergy_; }
		Float_t superClusterEta() const { return superClusterEta_; }
		Float_t preshowerEnergy() const { return preshowerEnergy_; }

		Float_t sigmaEtaEta() const { return sigmaEtaEta_; }
		Float_t sigmaIEtaIEta() const{ return sigmaIetaIeta_; }
		Float_t e1x5() const { return e1x5_; }
		Float_t e2x5Max() const { return e2x5Max_; }
		Float_t e5x5() const { return e5x5_; }
		Float_t e2x2() const { return e2x2_; }
		Float_t e3x3() const { return e3x3_; }
		Float_t eMax() const { return eMax_; }
		Float_t hadronicOverEm() const { return (hcalDepth1OverEcal_ + hcalDepth2OverEcal_); }
		Float_t hadronicDepth1OverEm() const { return hcalDepth1OverEcal_; }
		Float_t hadronicDepth2OverEm() const { return hcalDepth2OverEcal_; }

		Bool_t isEB() const { return isEB_; }
		Bool_t isEE() const { return isEE_; }
		Bool_t isEBEEGap() const { return isEBEEGap_; }
		Bool_t isEBEtaGap() const { return isEBEtaGap_; }
		Bool_t isEBPhiGap() const { return isEBPhiGap_; }
		Bool_t isEEDeeGap() const { return isEEDeeGap_; }
		Bool_t isEERingGap() const { return isEERingGap_; }

		Float_t ecalIso(unsigned int cone) const
		{
			if(cone == 3) return ecalRecHitSumEt03_;
			else if(cone == 4) return ecalRecHitSumEt04_;
			else
			{
				cout<<"Bad Cone Size! It returns -1."<<endl;
				return -1.;
			}
		}
		Float_t hcalIso(unsigned int cone) const
		{
			if(cone == 3) return (hcalDepth1TowerSumEt03_ + hcalDepth2TowerSumEt03_);
			else if(cone == 4) return (hcalDepth1TowerSumEt04_ + hcalDepth2TowerSumEt04_);
			else
			{
				cout<<"Bad Cone Size! It returns -1."<<endl;
				return -1.;
			}
		}
		Float_t hcalIso_Dept1(unsigned int cone) const
		{
			if(cone == 3) return hcalDepth1TowerSumEt03_;
			else if(cone == 4) return hcalDepth1TowerSumEt04_;
			else
			{
				cout<<"Bad Cone Size! It returns -1."<<endl;
				return -1.;
			}
		}
		Float_t hcalIso_Dept2(unsigned int cone) const
		{
			if(cone == 3) return hcalDepth2TowerSumEt03_;
			else if(cone == 4) return hcalDepth2TowerSumEt04_;
			else
			{
				cout<<"Bad Cone Size! It returns -1."<<endl;
				return -1.;
			}
		}
		Float_t caloIso(unsigned int cone) const
		{
			return (ecalIso(cone) + hcalIso(cone));
		}
		Float_t trackerIso(unsigned int cone) const
		{
			if(cone == 3) return tkSumPt03_;
			else if(cone == 4) return tkSumPt04_;
			else
			{
				cout<<"Bad Cone Size! It returns -1."<<endl;
				return -1.;
			}
		}
		Float_t combinedIso(unsigned int tkcone, unsigned int ecalcone, unsigned int hcalcone) const
		{
			return (trackerIso(tkcone) + hcalIso(hcalcone) + ecalIso(ecalcone));
		}
//    Int_t nTracks(unsigned int cone)const{
//        if(cone == 1)
//            return (nTracks);
//        else if(cone == 2)
//            return (nTracks);
//        else if(cone == 3)
//            return (myIsolation03.nTracks);
//        else if(cone == 4)
//            return (nTracks);
//        else if(cone == 5)
//            return (nTracks);
//        else {
//            cout<<"Bad Cone Size! It returns -1."<<endl;
//            return -1.;
//        }
//    }
		Float_t chargedHadronIso() const { return chargedHadronIso_; }
		Float_t photonIso() const { return photonIso_; }
		Float_t neutralHadronIso() const { return neutralHadronIso_; }

		Int_t isRobustLoose() const { return idCutBasedRobustLoose_; }
		Int_t isRobustTight() const { return idCutBasedRobustTight_; }
		Int_t isRobustHighEnergy() const{ return idCutBasedRobustHighEnergy_; }
		Int_t isLoose() const { return idCategorizedLoose_; }
		Int_t isTight() const { return idCategorizedTight_; }
/*		Int_t CiCVeryLooseId() const { return idCiCVeryLoose_; }
		Int_t CiCLooseId() const { return idCiCLoose_; }
		Int_t CiCMediumId() const { return idCiCMedium_; }
		Int_t CiCTightId() const { return idCiCTight_; }
		Int_t CiCSuperTightId() const { return idCiCSuperTight_; }
		Int_t CiCHyperTightId_1() const { return idCiCHyperTight1_; }
		Int_t CiCHyperTightId_2() const{ return idCiCHyperTight2_; }
		Int_t CiCHyperTightId_3() const{ return idCiCHyperTight3_; }
		Int_t CiCHyperTightId_4() const{ return idCiCHyperTight4_; } */
		
		Float_t fbrem() const { return fBrem_; };
		Int_t numberOfBrems() const { return (basicClusterSize() - 1); }
		Int_t classification() const { return classification_; }
		Bool_t isFromConversion() const	{ return ((bool)isConversion_); }
		Float_t Dist() const { return Dist_; }
		Float_t DCot() const { return DCot_; }

		Bool_t hasTriggerMatch(std::string input) const
		{
			if(input == "HLT_Ele10_SW_L1R") return HLT_Ele10_SW_L1R_;
			if(input == "HLT_Ele15_SW_L1R") return HLT_Ele15_SW_L1R_;
			return false;
		}
		
		//setters
		void setChargeInfo(Int_t scPix, Bool_t GsfCftScPix, Bool_t GsfScPix, Bool_t GsfCtf )
		{
			scPixCharge_ = scPix;
			isGsfCtfScPixConsistent_ = GsfCftScPix;
			isGsfScPixConsistent_ = GsfScPix;
			isGsfCtfConsistent_ = GsfCtf;
		}
		void setSuperClusterPixelCharge(Int_t scPix ){ scPixCharge_ = scPix; }
		void setSuperClusterPixelCtfGsfConsistency(Bool_t GsfCftScPix){ isGsfCtfScPixConsistent_ = GsfCftScPix; }
		void setSuperClusterPixelGsfConsistency(Bool_t GsfScPix){ isGsfScPixConsistent_ = GsfScPix; }
		void setGsfCtfConsistency(Bool_t GsfCtf){ isGsfCtfConsistent_ = GsfCtf; }
		void setSeedingInfo(Bool_t isEcal, Bool_t isTracker)
		{
			ecalDrivenSeed_ = isEcal;
			trackerDrivenSeed_ = isTracker;
		}
		void setEcalSeeding(Bool_t isEcal){ ecalDrivenSeed_ = isEcal; }
		void setTrackerSeeding(Bool_t isTracker){ trackerDrivenSeed_ = isTracker; }
		void setTrackClusterMatching(Float_t eScOverPin, Float_t eScOverPout, Float_t eSeedOverPin, Float_t eSeedOverPout,
			Float_t dEtaIn, Float_t dEtaOut, Float_t dPhiIn, Float_t dPhiOut, Float_t dPhiScTrkOut, Float_t dEtaScTrkOut)
		{
			eSuperClusterOverPin_ = eScOverPin;
			eSuperClusterOverPout_ = eScOverPout;
			eSeedClusterOverPin_ = eSeedOverPin;
			eSeedClusterOverPout_ = eSeedOverPout;
			deltaEtaIn_ = dEtaIn;
			deltaEtaOut_ = dEtaOut;
			deltaPhiIn_ = dPhiIn;
			deltaPhiOut_ = dPhiOut;
			deltaPhiSuperClusterTrackAtCalo_ = dPhiScTrkOut;
			deltaEtaSuperClusterTrackAtCalo_ = dEtaScTrkOut;
		}
		void setDeltaEtaIn(Float_t deltaEtaIn) { deltaEtaIn_ = deltaEtaIn; }
		void setDeltaEtaOut(Float_t deltaEtaOut) { deltaEtaOut_ = deltaEtaOut; }
		void setDeltaEtaSuperClusterTrackAtCalo(Float_t x) { deltaEtaSuperClusterTrackAtCalo_ = x; }
		void setDeltaPhiIn(Float_t deltaPhiIn) { deltaPhiIn_ = deltaPhiIn; }
		void setDeltaPhiOut(Float_t deltaPhiOut) { deltaPhiOut_ = deltaPhiOut; }
		void setDeltaPhiSuperClusterTrackAtCalo(Float_t x) { deltaPhiSuperClusterTrackAtCalo_ = x; }
		void setEnergySeedClusterOverPin(Float_t x) { eSeedClusterOverPin_ = x; }
		void setEnergySeedClusterOverPout(Float_t x) { eSeedClusterOverPout_ = x; }
		void setEnergySuperClusterOverPin(Float_t x) { eSuperClusterOverPin_ = x; }
		void setEnergySuperClusterOverPout(Float_t x) { eSuperClusterOverPout_ = x; }

		void setd0(Float_t x) { d0_ = x; }
		void setdsz(Float_t x) { dsz_ = x; }
		void setd0Error(Float_t d0Error) { d0Error_ = d0Error; }
		void setdszError(Float_t x) { dszError_ = x; }
		void setdB(Float_t dB) { dB_ = dB; }
		void setdBError(Float_t dBError) { dBError_ = dBError; }
		void setImpactParameter(Float_t x) { ip_ = x; }
		void setTrackMissingHits(Int_t x) { missingHits_ = x; }
		void setTrackMomentumAtCalo(Float_t x) { momentumAtCalo_ = x; }
		void setTrackMomentumAtElectronCluster(Float_t x) { momentumAtEleClus_ = x; }
		void setTrackMomentumAtVtxWithConstraint(Float_t x) { momentumAtVtxWithConstraint_ = x; }
		void setTrackMomentumOut(Float_t x) { momentumOut_ = x; }
		void setTrackNormalizedChi2(Float_t x) { normalizedChi2_ = x; }
		void setPixelLayersWithMeasurement(Int_t x) { pixelLayersWithMeasurement_ = x; }
		void setStripLayersWithMeasurement(Int_t stripLayersWithMeasurement) { stripLayersWithMeasurement_ = stripLayersWithMeasurement; }
		void setTrackPositionAtCalo(Double_t x, Double_t y, Double_t z) { positionAtCalo_.SetXYZ(x,y,z); }
		void setTrackPositionAtCalo(TVector3 x) { positionAtCalo_ = x; }
		void setTrackPositionAtVtx(Double_t x, Double_t y, Double_t z) { positionAtVtx_.SetXYZ(x,y,z); }
		void setTrackPositionAtVtx(TVector3 x) { positionAtVtx_ = x; }
		void setTrackPtError(Float_t x) { ptError_ = x; }
		void setTrackMomentum(Float_t x) { trackMomentum_ = x; }

		void setCorrections(Float_t tme, Float_t cee, Float_t ce, Float_t cc, Float_t mc, Float_t eMc, Float_t d0e, Float_t dsze)
		{
			trackMomentumError_ = tme;			// Error on trackMomentum_
			ecalEnergyError_ = cee;				// Error on caloEnergy_
			ecalEnergy_ = ce;						// ecal corrected energy (if !isEcalEnergyCorrected this value is identical to the supercluster energy)
			isEcalEnergyCorrected_ = cc;		// true if ecal energy has been corrected
			isMomentumCorrected_ = mc;			// true if E-p combination has been applied (if not the electron momentum is the ecal corrected energy)
			electronMomentumError_ = eMc;		// the final electron momentum error
			d0Error_ = d0e;						// error on d0_
			dszError_ = dsze;
		}

		void setCaloEnergyError(Float_t x) { ecalEnergyError_ = x; }
		void setCaloEnergy(Float_t x) { ecalEnergy_ = x; }
		void setElectronMomentumError(Float_t x) { electronMomentumError_ = x; }
		void setEnergyScaleCorrected(Bool_t x) { isEcalEnergyCorrected_ = x; }
		void setMomentumCorrected(Bool_t x) { isMomentumCorrected_ = x; }
		void setTrackMomentumError(Float_t x) { trackMomentumError_ = x; }

		void setSuperCluster(TVector3 pos, Int_t bcs, Int_t ca, Float_t ccs, Int_t nC, Float_t scRawE, Float_t scEta, Float_t PSE)
		{
			caloPosition_ = pos;
			basicClusterSize_ = bcs;
			clusterAlgo_ = ca;
			caloConeSize_ = ccs;
			nbClusters_ = nC;
			superClusterRawEnergy_ = scRawE;
			superClusterEta_ = scEta;
			preshowerEnergy_ = PSE;
		}

		void setBasicClusterSize(Int_t x) { basicClusterSize_ = x; }
		void setCaloConeSize(Float_t x) { caloConeSize_ = x; }
		void setCaloPosition(Double_t x, Double_t y, Double_t z) { caloPosition_.SetXYZ(x, y ,z); }
		void setCaloPosition(TVector3 x) { caloPosition_ = x; }
		void setClusterAlgo(Int_t x) { clusterAlgo_ = x; }
		void setNbClusters(Int_t x) { nbClusters_ = x; }
		void setPreshowerEnergy(Float_t x) { preshowerEnergy_ = x; }
		void setSuperClusterRawEnergy(Float_t x) { superClusterRawEnergy_ = x; }
		void setSuperClusterEta(Float_t x) { superClusterEta_ = x; }

		void setE1x5(Float_t e1x5) { e1x5_ = e1x5; }
		void setE2x2(Float_t e2x2) { e2x2_ = e2x2; }
		void setE2x5Max(Float_t e2x5Max) { e2x5Max_ = e2x5Max; }
		void setE3x3(Float_t e3x3) { e3x3_ = e3x3; }
		void setE5x5(Float_t e5x5) { e5x5_ = e5x5; }
		void setHoverEDepth1(Float_t HoE1) { hcalDepth1OverEcal_ = HoE1; }
		void setHoverEDepth2(Float_t HoE2) { hcalDepth2OverEcal_ = HoE2; }
		void setSigmaEtaEta(Float_t see) { sigmaEtaEta_ = see; }
		void setSigmaIetaIeta(Float_t sieie) { sigmaIetaIeta_ = sieie; }
		void setFiducialFlags(Bool_t eb, Bool_t ee, Bool_t ebeegap, Bool_t ebetagap, Bool_t ebphigap, Bool_t eedeegap, Bool_t eeR)
		{
			isEB_ = eb;
			isEE_ = ee;
			isEBEEGap_ = ebeegap;
			isEBEtaGap_ = ebetagap;
			isEBPhiGap_ = ebphigap;
			isEEDeeGap_ = eedeegap;
			isEERingGap_ = eeR;
		}

		void setEB(Bool_t is) { isEB_ = is; }
		void setEE(Bool_t is) { isEE_ = is; }
		void setEBEEGap(Bool_t is) { isEBEEGap_ = is; }
		void setEBEtaGap(Bool_t is) { isEBEtaGap_ = is; }
		void setEBPhiGap(Bool_t is) { isEBPhiGap_ = is; }
		void setEEDeeGap(Bool_t is) { isEEDeeGap_ = is; }
		void setEERingGap(Bool_t is) { isEERingGap_ = is; }

		void setIsoR03_emEt(Float_t isoR03_emEt) { ecalRecHitSumEt03_ = isoR03_emEt; }
		void setIsoR03_Depth1HadEt(Float_t isoR03_hadEt1) { hcalDepth1TowerSumEt03_ = isoR03_hadEt1; }
		void setIsoR03_Depth2HadEt(Float_t isoR03_hadEt2) { hcalDepth2TowerSumEt03_ = isoR03_hadEt2; }
		void setIsoR03_sumPt(Float_t isoR03_sumPt) { tkSumPt03_ = isoR03_sumPt; }
//    void setIsoR03_nTracks(Int_t isoR03_nTracks) { nTracks_ = isoR03_nTracks; }

		void setIsoR04_emEt(Float_t isoR04_emEt) { ecalRecHitSumEt04_ = isoR04_emEt; }
		void setIsoR04_Depth1HadEt(Float_t isoR04_hadEt1) { hcalDepth1TowerSumEt04_ = isoR04_hadEt1; }
		void setIsoR04_Depth2HadEt(Float_t isoR04_hadEt2) { hcalDepth2TowerSumEt04_ = isoR04_hadEt2; }
		void setIsoR04_sumPt(Float_t isoR04_sumPt) { tkSumPt04_ = isoR04_sumPt; }
//    void setIsoR04_nTracks(Int_t isoR04_nTracks) { nTracks_ = isoR04_nTracks; }
		void setChargedHadronIso(Float_t chargedHadronIso){chargedHadronIso_ = chargedHadronIso;}
		void setPhotonIso(Float_t photonIso){photonIso_ = photonIso;}
		void setNeutralHadronIso(Float_t neutralHadronIso){neutralHadronIso_ = neutralHadronIso;}

		void setIDCutBasedRobustLoose(Int_t idCutBasedFixedThresholdLoose) { idCutBasedRobustLoose_ = idCutBasedFixedThresholdLoose; }
		void setIDCutBasedRobustTight(Int_t idCutBasedFixedThresholdTight) { idCutBasedRobustTight_ = idCutBasedFixedThresholdTight; }
		void setIDCutBasedRobustHighEnergy(Int_t idCutBasedFixedThresholdHighEnergy) { idCutBasedRobustHighEnergy_ = idCutBasedFixedThresholdHighEnergy; }
		void setIDCategorizedLoose(Int_t idCutBasedCategorizedLoose) { idCategorizedLoose_ = idCutBasedCategorizedLoose; }
		void setIDCategorizedTight(Int_t idCutBasedCategorizedTight) { idCategorizedTight_ = idCutBasedCategorizedTight; }

/*		void setIDCiCVeryLoose(Int_t cicVL) { idCiCVeryLoose_ = cicVL; }
		void setIDCiCLoose(Int_t cicL) { idCiCLoose_ = cicL; }
		void setIDCiCMedium(Int_t cicM) { idCiCMedium_ = cicM; }
		void setIDCiCTight(Int_t cicT) { idCiCTight_ = cicT; }
		void setIDCiCSuperTight(Int_t cicST) { idCiCSuperTight_ = cicST; }
		void setIDCiCHyperTight1(Int_t cicHT1) { idCiCHyperTight1_ = cicHT1; }
		void setIDCiCHyperTight2(Int_t cicHT2) { idCiCHyperTight2_ = cicHT2; }
		void setIDCiCHyperTight3(Int_t cicHT3) { idCiCHyperTight3_ = cicHT3; }
		void setIDCiCHyperTight4(Int_t cicHT4) { idCiCHyperTight4_ = cicHT4; } */

		void setFbrem(Float_t f) { fBrem_ = f; }
		void setClassification(Int_t i) { classification_ = i; }
		void setConversion(Bool_t is) {	isConversion_ = is; }
		void setDist(float dist) { Dist_ = dist; }
		void setDCot(float dcot) { DCot_ = dcot; }
		void setTriggerinfo(std::string input, Bool_t is)
		{
			if(input == "HLT_Ele10_SW_L1R") HLT_Ele10_SW_L1R_ = is;
			if(input == "HLT_Ele15_SW_L1R") HLT_Ele15_SW_L1R_ = is;
		}
		
		friend std::ostream& operator<< (std::ostream& stream, const TRootElectron& electron) {
			stream << "TRootElectron - Charge=" << electron.charge() << " (Et,eta,phi)=("<< electron.Et() <<","<< electron.Eta() <<","<< electron.Phi() << ")"
				<< " vertex(x,y,z)=("<< electron.vx() <<","<< electron.vy() <<","<< electron.vz() << ")";
			return stream;
		};


	private:
		Int_t scPixCharge_;
		Bool_t isGsfCtfScPixConsistent_;
		Bool_t isGsfScPixConsistent_;
		Bool_t isGsfCtfConsistent_;
		Bool_t trackerDrivenSeed_;
		Bool_t ecalDrivenSeed_;

//    TrackClusterMatching myTrackClusterMatching;
		Float_t eSuperClusterOverPin_;             // the supercluster energy / track momentum at the PCA to the beam spot
		Float_t eSuperClusterOverPout_;            // the electron cluster energy / track momentum at calo extrapolated from the outermost track state
		Float_t eSeedClusterOverPin_;              // the seed cluster energy / track momentum at the PCA to the beam spot
		Float_t eSeedClusterOverPout_;             // the seed cluster energy / track momentum at calo extrapolated from the outermost track state
		Float_t deltaEtaIn_;                       // the supercluster eta - track eta position at calo extrapolated from innermost track state
		Float_t deltaEtaOut_;                      // the seed cluster eta - track eta position at calo extrapolated from the outermost track state
		Float_t deltaPhiIn_;                       // the supercluster phi - track phi position at calo extrapolated from the innermost track state
		Float_t deltaPhiOut_;                      // the seed cluster phi - track phi position at calo extrapolated from the outermost track state
		Float_t deltaPhiSuperClusterTrackAtCalo_;  // the electron cluster phi - track phi position at calo extrapolated from the outermost track state
		Float_t deltaEtaSuperClusterTrackAtCalo_;  // the electron cluster eta - t


//		TrackProperties================================
		Float_t trackMomentum_;                // Track momentum at vertex
		Float_t momentumAtCalo_;               // the track momentum extrapolated at the supercluster position from the innermost track state
		Float_t momentumOut_;                  // the track momentum extrapolated at the seed cluster position from the outermost track state
		Float_t momentumAtEleClus_;            // the track momentum extrapolated at the ele cluster position from the outermost track state
		Float_t momentumAtVtxWithConstraint_;  // the track momentum at the PCA to the beam spot using bs constraint
		Int_t pixelLayersWithMeasurement_;     // Number of pixel layers with at least one valid hit
		Int_t stripLayersWithMeasurement_;     // Number of strip layers with at least one valid hit
		Float_t d0_;                         	// Original d0
		Float_t dsz_;                          // dsz parameter
		Float_t d0Error_;                      // error on d0_
		Float_t dszError_;

		// In the standard PAT configuration, dB and edB are calculated wrt the primary vertex
		// If this was not the case, dB is calculated wrt the beamspot and edb = -1 all the time
		Float_t dB_;                           // dB from PAT muon
		Float_t dBError_;                      // dBError from PAT muon

		Int_t missingHits_;                    // Conversion Rejection: number of missing hits near beginning of track (also rejects really bad tracks)
      //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideCategoryBasedElectronID#The_Cut_Variables

		Float_t ip_;                           //Track vertex: Impact Parameter w.r.t. reco vertex , same wiki page
		TVector3  positionAtVtx_;              // the track PCA to the beam spot
		TVector3  positionAtCalo_;             // the track PCA to the supercluster position
		Float_t normalizedChi2_;               // chi-squared divided by n.d.o.f. of track fit
		Float_t ptError_;                      // needed ?  ptError()

    
 //Corrections===========================

//    Corrections myCorrections_;
		Float_t trackMomentumError_;        // Error on trackMomentum_
		Float_t ecalEnergyError_;           // Error on caloEnergy_
		Float_t ecalEnergy_;                // ecal corrected energy (if !isEcalEnergyCorrected this value is identical to the supercluster energy)
		Bool_t isEcalEnergyCorrected_ ;       // true if ecal energy has been corrected
		Bool_t isMomentumCorrected_ ;         // true if E-p combination has been applied (if not the electron momentum is the ecal corrected energy)
		Float_t electronMomentumError_ ;    // the final electron momentum error

//SuperClusterProperties ===============================

		TVector3 caloPosition_;          // SuperCluster centroid position
		Int_t basicClusterSize_;         // number of basic clusters inside the supercluster
		Int_t clusterAlgo_;              // reco::BasicCluster::algo() island = 0, hybrid = 1, fixedMatrix = 2, dynamicHybrid = 3, multi5x5 = 4
		Float_t caloConeSize_;           // Delta_R of the cone centered on the reco::GsfElectron and containing all its basic clusters constituents
		// need reco::SuperCluster and reco::BasicCluster and reduced Ecal RecHits Collections for EcalClusterLazyTools
		Int_t nbClusters_;               // Number of related brem clusters
		Float_t superClusterRawEnergy_;
		Float_t superClusterEta_;
		Float_t preshowerEnergy_;


//ShowerShape===================================

		Float_t sigmaEtaEta_;        // weighted cluster rms along eta and inside 5x5 (absolute eta)
		Float_t sigmaIetaIeta_;      // weighted cluster rms along eta and inside 5x5 (new, Xtal eta)
		Float_t e1x5_;               // energy inside 1x5 in etaxphi around the seed Xtal
		Float_t e2x5Max_;            // energy inside 2x5 in etaxphi around the seed Xtal (max bwt the 2 possible sums)
		Float_t e5x5_;               // energy inside 5x5 in etaxphi around the seed Xtal
		Float_t e2x2_;
		Float_t e3x3_;
		Float_t eMax_;
		Float_t hcalDepth1OverEcal_ ; // hcal over ecal seed cluster energy using first hcal depth (hcal is energy of towers within dR=015)
		Float_t hcalDepth2OverEcal_ ; // hcal over ecal seed cluster energy using 2nd hcal depth (hcal is energy of towers within dR=015)


//FiducialFlags=================================

//    FiducialFlags myFiducialFlags_;
		Bool_t isEB_;        // true if particle is in ECAL Barrel
		Bool_t isEE_;        // true if particle is in ECAL Endcaps
		Bool_t isEBEEGap_;   // true if particle is in the crack between EB and EE
		Bool_t isEBEtaGap_;  // true if particle is in EB, and inside the eta gaps between modules
		Bool_t isEBPhiGap_;  // true if particle is in EB, and inside the phi gaps between modules
		Bool_t isEEDeeGap_;  // true if particle is in EE, and inside the gaps between dees
		Bool_t isEERingGap_; // true if particle is in EE, and inside the gaps between rings

//Isolation ==================================

		Float_t tkSumPt03_;                // track iso deposit with electron footprint removed
		Float_t ecalRecHitSumEt03_;        // ecal iso deposit with electron footprint removed
		Float_t hcalDepth1TowerSumEt03_;   // hcal depht 1 iso deposit with electron footprint removed
		Float_t hcalDepth2TowerSumEt03_;   // hcal depht 2 iso deposit with electron footprint removed
//		Int_t nTracks03_;
		Float_t tkSumPt04_;                // track iso deposit with electron footprint removed
		Float_t ecalRecHitSumEt04_;        // ecal iso deposit with electron footprint removed
		Float_t hcalDepth1TowerSumEt04_;   // hcal depht 1 iso deposit with electron footprint removed
		Float_t hcalDepth2TowerSumEt04_;   // hcal depht 2 iso deposit with electron footprint removed
//		Int_t nTracks04_;
		Float_t chargedHadronIso_;         // charged hadron isolation value computed in the PF2PAT sequence, and stored in the pat electron
		Float_t photonIso_;		   // photon isolation value computed in the PF2PAT sequence, and stored in the pat electron
		Float_t neutralHadronIso_;	   // neutral hadron isolation value computed in the PF2PAT sequence, and stored in the pat electron

//Identification ===================================
		Int_t idCutBasedRobustLoose_;      // Simple cut based ID (aka 'robust') - Loose Thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta
		Int_t idCutBasedRobustTight_;      // Simple cut based ID (default in EWK group) - Tight Thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta
		Int_t idCutBasedRobustHighEnergy_; // Simple cut based ID - Thresholds optimized for high energy electron (~TeV)
		Int_t idCategorizedLoose_;         // Category based ID - Different loose thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta, eSeedOverPin for differents regions in the E/p vs fBrem plane
		Int_t idCategorizedTight_;         // Category based ID - Different tight thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta, eSeedOverPin for differents regions in the E/p vs fBrem plane

// New Identification
/*		Int_t idCiCVeryLoose_;             //Cuts in Categories for 35x: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideCategoryBasedElectronID#The_Cut_Variables
		Int_t idCiCLoose_;
		Int_t idCiCMedium_;
		Int_t idCiCTight_;
		Int_t idCiCSuperTight_;
		Int_t idCiCHyperTight1_;
		Int_t idCiCHyperTight2_;
		Int_t idCiCHyperTight3_;
		Int_t idCiCHyperTight4_;*/

// Electron classification && fBrem ====================
		Int_t classification_;             
		Float_t fBrem_;
		Bool_t isConversion_;
		Float_t Dist_;
		Float_t DCot_;

//Trigger Info ======================================
		Bool_t HLT_Ele10_SW_L1R_;
		Bool_t HLT_Ele15_SW_L1R_;

// Noise Cleanin
	
		ClassDef (TRootElectron,9);
	};
}

//typedef std::pair<int,double> IntDoublePair;
//typedef std::pair<TRootElectron,std::vector<std::pair<int,double> > > MassPair;
#endif
