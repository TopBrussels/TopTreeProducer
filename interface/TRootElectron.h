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
		TRootElectron() : TRootParticle(),
			scPixCharge(-9999),
			isGsfCtfScPixConsistent_(false),
			isGsfScPixConsistent_(false),
			isGsfCtfConsistent_(false),
			trackerDrivenSeed(false),
			ecalDrivenSeed(false),
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
			missingHits_(-9999),
			ip_(-9999.),
			positionAtVtx(-9999.,-9999.,-9999.),
			positionAtCalo(-9999.,-9999.,-9999.),
			dsz_(-9999.),
			normalizedChi2_(9999.),
			ptError_(-9999.),
			trackMomentumError_(-9999.),
			ecalEnergyError_(-9999.),
			ecalEnergy_(-9999.),
			isEcalEnergyCorrected_(false),
			isMomentumCorrected_(false),
			electronMomentumError_(-9999.),
			d0Error_(-9999.),
			dszError_(-9999.),
			caloPosition_(-9999.,-9999.,-9999.),
			basicClusterSize_(9999),
			clusterAlgo_(9999),
			caloConeSize_(9999),
			nbClusters_(9999),
			superClusterRawEnergy_(-9999.),
			preshowerEnergy_(-9999.),
			sigmaEtaEta_(-9999.),
			sigmaIetaIeta(-9999.),
			e1x5_(-9999.),
			e2x5Max_(-9999.),
			e5x5_(-9999.),
			e2x2_(-9999.),
			e3x3_(-9999.),
			eMax_(-9999.),
			hcalDepth1OverEcal(-9999.),
			hcalDepth2OverEcal(-9999.),
			isEB_(false),
			isEE_(false),
			isEBEEGap_(false),
			isEBEtaGap_(false),
			isEBPhiGap_(false),
			isEEDeeGap_(false),
			isEERingGap_(false),
			tkSumPt01(-9999.),
			ecalRecHitSumEt01(-9999.),
			hcalDepth1TowerSumEt01(-9999.),
			hcalDepth2TowerSumEt01(-9999.),
			tkSumPt02(-9999.),
			ecalRecHitSumEt02(-9999.),
			hcalDepth1TowerSumEt02(-9999.),
			hcalDepth2TowerSumEt02(-9999.),
			tkSumPt03(-9999.),
			ecalRecHitSumEt03(-9999.),
			hcalDepth1TowerSumEt03(-9999.),
			hcalDepth2TowerSumEt03(-9999.),
			tkSumPt04(-9999.),
			ecalRecHitSumEt04(-9999.),
			hcalDepth1TowerSumEt04(-9999.),
			hcalDepth2TowerSumEt04(-9999.),
			tkSumPt05(-9999.),
			ecalRecHitSumEt05(-9999.),
			hcalDepth1TowerSumEt05(-9999.),
			hcalDepth2TowerSumEt05(-9999.),
			idCutBasedRobustLoose_(-9999),
			idCutBasedRobustTight_(-9999),
			idCutBasedRobustHighEnergy_(-9999),
			idCategorizedLoose_(-9999),
			idCategorizedTight_(-9999),
			idLikelihood_(-9999),
			idNeuralNet_(-9999),
			idCiCVeryLoose_(-9999),
			idCiCLoose_(-9999),
			idCiCMedium_(-9999),
			idCiCTight_(-9999),
			idCiCSuperTight_(-9999),
			idCiCHyperTight1_(-9999),
			idCiCHyperTight2_(-9999),
			idCiCHyperTight3_(-9999),
			idCiCHyperTight4_(-9999),
			momentumMCElectron_(-9999.,-9999.,-9999.,-9999.),
			vertexMCElectron_(-9999.,-9999.,-9999.),
			pdgIdMCElectron_(-9999),
			classification_(-9999),
			fBrem_(-9999.),
			isConversion(true),
			HLT_Ele10_SW_L1R(false),
			HLT_Ele15_SW_L1R(false)
			{
            
//				TriggerMatchingInfo tmpTrig;
//				tmpTrig.clear();
//				setTriggerInfo(tmpTrig);
				;
			}

		TRootElectron(const TRootElectron& e) :TRootParticle(e),
			scPixCharge(e.Charge()),
			isGsfCtfScPixConsistent_(e.isGsfCtfConsistent()),
			isGsfScPixConsistent_(e.isGsfScPixConsistent()),
			isGsfCtfConsistent_(e.isGsfCtfConsistent()),
			trackerDrivenSeed(e.isTrackerDrivenSeed()),
			ecalDrivenSeed(e.isEcalDrivenSeed()),
			eSuperClusterOverPin_(e.eScOverPin()),
			eSuperClusterOverPout_(e.eScOverPout()),
			eSeedClusterOverPin_(e.eSeedOverPin()),
			eSeedClusterOverPout_(e.eSeedOverPout()),
			deltaEtaIn_(e.deltaEtaIn()),
			deltaEtaOut_(e.deltaEtaOut()),
			deltaPhiIn_(e.deltaPhiIn()),
			deltaPhiOut_(e.deltaPhiOut()),
			deltaPhiSuperClusterTrackAtCalo_(e.deltaPhiScTrkOut()),
			deltaEtaSuperClusterTrackAtCalo_(e.deltaEtaScTrkOut()),
			trackMomentum_(e.trackMomentum()),
			momentumAtCalo_(e.trackMomentumAtSuperClusterPosition()),
			momentumOut_(e.trackMomentumAtSeedClusterPosition()),
			momentumAtEleClus_(e.trackMomentumAtElectronClusterPosition()),
			momentumAtVtxWithConstraint_(e.trackMomentumAtVtxWithConstraints()),
			pixelLayersWithMeasurement_(e.trackPixelLayersWithMeasurement()),
			stripLayersWithMeasurement_(e.trackStripLayersWithMeasurement()),
			d0_(e.d0()),
			missingHits_(e.missingHits()),
			ip_(e.impactParameter()),
			positionAtVtx(e.trackPositionAtVtx()),
			positionAtCalo(e.trackPositionAtCalo()),
			dsz_(e.trackDsz()),
			normalizedChi2_(e.trackNormalizedChi2()),
			ptError_(e.trackPtError()),
			trackMomentumError_(e.trackMomentumError()),
			ecalEnergyError_(e.caloEnergyError()),
			ecalEnergy_(e.caloEnergy()),
			isEcalEnergyCorrected_(e.isCaloEnergyCorrected()),
			isMomentumCorrected_(e.isMomentumCorrected()),
			electronMomentumError_(e.electronMomentumError()),
			d0Error_(e.d0Error()),
			dszError_(e.dszError()),
			caloPosition_(e.caloPosition()),
			basicClusterSize_(e.basicClusterSize()),
			clusterAlgo_(e.clusterAlgo()),
			caloConeSize_(e.caloConeSize()),
			nbClusters_(e.nClusters()),
			superClusterRawEnergy_(e.superClusterRawEnergy()),
			preshowerEnergy_(e.preshowerEnergy()),
			sigmaEtaEta_(e.sigmaEtaEta()),
			sigmaIetaIeta(e.sigmaIEtaIEta()),
			e1x5_(e.e1x5()),
			e2x5Max_(e.e2x5Max()),
			e5x5_(e.e5x5()),
			e2x2_(e.e2x2()),
			e3x3_(e.e3x3()),
			eMax_(e.eMax()),
			hcalDepth1OverEcal(e.hadronicDepth1OverEm()),
			hcalDepth2OverEcal(e.hadronicDepth2OverEm()),
			isEB_(e.isEB()),
			isEE_(e.isEE()),
			isEBEEGap_(e.isEBEEGap()),
			isEBEtaGap_(e.isEBEtaGap()),
			isEBPhiGap_(e.isEBPhiGap()),
			isEEDeeGap_(e.isEEDeeGap()),
			isEERingGap_(e.isEERingGap()),
			tkSumPt01(e.trackerIso(1)),
			ecalRecHitSumEt01(e.ecalIso(1)),
			hcalDepth1TowerSumEt01(e.hcalIso_Dept1(1)),
			hcalDepth2TowerSumEt01(e.hcalIso_Dept2(1)),
			tkSumPt02(e.trackerIso(2)),
			ecalRecHitSumEt02(e.ecalIso(2)),
			hcalDepth1TowerSumEt02(e.hcalIso_Dept1(2)),
			hcalDepth2TowerSumEt02(e.hcalIso_Dept2(2)),
			tkSumPt03(e.trackerIso(3)),
			ecalRecHitSumEt03(e.ecalIso(3)),
			hcalDepth1TowerSumEt03(e.hcalIso_Dept1(3)),
			hcalDepth2TowerSumEt03(e.hcalIso_Dept2(3)),
			tkSumPt04(e.trackerIso(4)),
			ecalRecHitSumEt04(e.ecalIso(4)),
			hcalDepth1TowerSumEt04(e.hcalIso_Dept1(4)),
			hcalDepth2TowerSumEt04(e.hcalIso_Dept2(4)),
			tkSumPt05(e.trackerIso(5)),
			ecalRecHitSumEt05(e.ecalIso(5)),
			hcalDepth1TowerSumEt05(e.hcalIso_Dept1(5)),
			hcalDepth2TowerSumEt05(e.hcalIso_Dept2(5)),
			idCutBasedRobustLoose_(e.isRobustLoose()),
			idCutBasedRobustTight_(e.isRobustTight()),
			idCutBasedRobustHighEnergy_(e.isRobustHighEnergy()),
			idCategorizedLoose_(e.isLoose()),
			idCategorizedTight_(e.isTight()),
			idLikelihood_(e.LikelihoodId()),
			idNeuralNet_(e.NeuralNetworkId()),
			idCiCVeryLoose_(e.CiCVeryLooseId()),
			idCiCLoose_(e.CiCLooseId()),
			idCiCMedium_(e.CiCMediumId()),
			idCiCTight_(e.CiCTightId()),
			idCiCSuperTight_(e.CiCSuperTightId()),
			idCiCHyperTight1_(e.CiCHyperTightId_1()),
			idCiCHyperTight2_(e.CiCHyperTightId_2()),
			idCiCHyperTight3_(e.CiCHyperTightId_3()),
			idCiCHyperTight4_(e.CiCHyperTightId_4()),
			momentumMCElectron_(e.MCP4()),
			vertexMCElectron_(e.MCVertex()),
			pdgIdMCElectron_(e.MCId()),
			classification_(e.classification()),
			fBrem_(e.fbrem()),
			isConversion(e.isFromConversion()),
			HLT_Ele10_SW_L1R(e.hasTriggerMatch("HLT_Ele10_SW_L1R")),
			HLT_Ele15_SW_L1R(e.hasTriggerMatch("HLT_Ele15_SW_L1R"))
			{;}

		TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e) :TRootParticle(px,py,pz,e),
			scPixCharge(-9999),
			isGsfCtfScPixConsistent_(false),
			isGsfScPixConsistent_(false),
			isGsfCtfConsistent_(false),
			trackerDrivenSeed(false),
			ecalDrivenSeed(false),
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
			missingHits_(-9999),
			ip_(-9999.),
			positionAtVtx(-9999.,-9999.,-9999.),
			positionAtCalo(-9999.,-9999.,-9999.),
			dsz_(-9999.),
			normalizedChi2_(9999.),
			ptError_(-9999.),
			trackMomentumError_(-9999.),
			ecalEnergyError_(-9999.),
			ecalEnergy_(-9999.),
			isEcalEnergyCorrected_(false),
			isMomentumCorrected_(false),
			electronMomentumError_(-9999.),
			d0Error_(-9999.),
			dszError_(-9999.),
			caloPosition_(-9999.,-9999.,-9999.),
			basicClusterSize_(9999),
			clusterAlgo_(9999),
			caloConeSize_(9999),
			nbClusters_(9999),
			superClusterRawEnergy_(-9999.),
			preshowerEnergy_(-9999.),
			sigmaEtaEta_(-9999.),
			sigmaIetaIeta(-9999.),
			e1x5_(-9999.),
			e2x5Max_(-9999.),
			e5x5_(-9999.),
			e2x2_(-9999.),
			e3x3_(-9999.),
			eMax_(-9999.),
			hcalDepth1OverEcal(-9999.),
			hcalDepth2OverEcal(-9999.),
			isEB_(false),
			isEE_(false),
			isEBEEGap_(false),
			isEBEtaGap_(false),
			isEBPhiGap_(false),
			isEEDeeGap_(false),
			isEERingGap_(false),
			tkSumPt01(-9999.),
			ecalRecHitSumEt01(-9999.),
			hcalDepth1TowerSumEt01(-9999.),
			hcalDepth2TowerSumEt01(-9999.),
			tkSumPt02(-9999.),
			ecalRecHitSumEt02(-9999.),
			hcalDepth1TowerSumEt02(-9999.),
			hcalDepth2TowerSumEt02(-9999.),
			tkSumPt03(-9999.),
			ecalRecHitSumEt03(-9999.),
			hcalDepth1TowerSumEt03(-9999.),
			hcalDepth2TowerSumEt03(-9999.),
			tkSumPt04(-9999.),
			ecalRecHitSumEt04(-9999.),
			hcalDepth1TowerSumEt04(-9999.),
			hcalDepth2TowerSumEt04(-9999.),
			tkSumPt05(-9999.),
			ecalRecHitSumEt05(-9999.),
			hcalDepth1TowerSumEt05(-9999.),
			hcalDepth2TowerSumEt05(-9999.),
			idCutBasedRobustLoose_(-9999),
			idCutBasedRobustTight_(-9999),
			idCutBasedRobustHighEnergy_(-9999),
			idCategorizedLoose_(-9999),
			idCategorizedTight_(-9999),
			idLikelihood_(-9999),
			idNeuralNet_(-9999),
			idCiCVeryLoose_(-9999),
			idCiCLoose_(-9999),
			idCiCMedium_(-9999),
			idCiCTight_(-9999),
			idCiCSuperTight_(-9999),
			idCiCHyperTight1_(-9999),
			idCiCHyperTight2_(-9999),
			idCiCHyperTight3_(-9999),
			idCiCHyperTight4_(-9999),
			momentumMCElectron_(-9999.,-9999.,-9999.,-9999.),
			vertexMCElectron_(-9999.,-9999.,-9999.),
			pdgIdMCElectron_(-9999),
			classification_(-9999),
			fBrem_(-9999.),
			isConversion(true),
			HLT_Ele10_SW_L1R(false),
			HLT_Ele15_SW_L1R(false)
			{

//				TriggerMatchingInfo tmpTrig;
//				tmpTrig.clear();
//				setTriggerInfo(tmpTrig);
            ;
			}
	
		TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z),
			scPixCharge(-9999),
			isGsfCtfScPixConsistent_(false),
			isGsfScPixConsistent_(false),
			isGsfCtfConsistent_(false),
			trackerDrivenSeed(false),
			ecalDrivenSeed(false),
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
			missingHits_(-9999),
			ip_(-9999.),
			positionAtVtx(-9999.,-9999.,-9999.),
			positionAtCalo(-9999.,-9999.,-9999.),
			dsz_(-9999.),
			normalizedChi2_(9999.),
			ptError_(-9999.),
			trackMomentumError_(-9999.),
			ecalEnergyError_(-9999.),
			ecalEnergy_(-9999.),
			isEcalEnergyCorrected_(false),
			isMomentumCorrected_(false),
			electronMomentumError_(-9999.),
			d0Error_(-9999.),
			dszError_(-9999.),
			caloPosition_(-9999.,-9999.,-9999.),
			basicClusterSize_(9999),
			clusterAlgo_(9999),
			caloConeSize_(9999),
			nbClusters_(9999),
			superClusterRawEnergy_(-9999.),
			preshowerEnergy_(-9999.),
			sigmaEtaEta_(-9999.),
			sigmaIetaIeta(-9999.),
			e1x5_(-9999.),
			e2x5Max_(-9999.),
			e5x5_(-9999.),
			e2x2_(-9999.),
			e3x3_(-9999.),
			eMax_(-9999.),
			hcalDepth1OverEcal(-9999.),
			hcalDepth2OverEcal(-9999.),
			isEB_(false),
			isEE_(false),
			isEBEEGap_(false),
			isEBEtaGap_(false),
			isEBPhiGap_(false),
			isEEDeeGap_(false),
			isEERingGap_(false),
			tkSumPt01(-9999.),
			ecalRecHitSumEt01(-9999.),
			hcalDepth1TowerSumEt01(-9999.),
			hcalDepth2TowerSumEt01(-9999.),
			tkSumPt02(-9999.),
			ecalRecHitSumEt02(-9999.),
			hcalDepth1TowerSumEt02(-9999.),
			hcalDepth2TowerSumEt02(-9999.),
			tkSumPt03(-9999.),
			ecalRecHitSumEt03(-9999.),
			hcalDepth1TowerSumEt03(-9999.),
			hcalDepth2TowerSumEt03(-9999.),
			tkSumPt04(-9999.),
			ecalRecHitSumEt04(-9999.),
			hcalDepth1TowerSumEt04(-9999.),
			hcalDepth2TowerSumEt04(-9999.),
			tkSumPt05(-9999.),
			ecalRecHitSumEt05(-9999.),
			hcalDepth1TowerSumEt05(-9999.),
			hcalDepth2TowerSumEt05(-9999.),
			idCutBasedRobustLoose_(-9999),
			idCutBasedRobustTight_(-9999),
			idCutBasedRobustHighEnergy_(-9999),
			idCategorizedLoose_(-9999),
			idCategorizedTight_(-9999),
			idLikelihood_(-9999),
			idNeuralNet_(-9999),
			idCiCVeryLoose_(-9999),
			idCiCLoose_(-9999),
			idCiCMedium_(-9999),
			idCiCTight_(-9999),
			idCiCSuperTight_(-9999),
			idCiCHyperTight1_(-9999),
			idCiCHyperTight2_(-9999),
			idCiCHyperTight3_(-9999),
			idCiCHyperTight4_(-9999),
			momentumMCElectron_(-9999.,-9999.,-9999.,-9999.),
			vertexMCElectron_(-9999.,-9999.,-9999.),
			pdgIdMCElectron_(-9999),
			classification_(-9999),
			fBrem_(-9999.),
			isConversion(true),
			HLT_Ele10_SW_L1R(false),
			HLT_Ele15_SW_L1R(false)
			{
				;
//				TriggerMatchingInfo tmpTrig;
//				tmpTrig.clear();
//				setTriggerInfo(tmpTrig);
			}

		TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Int_t charge) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge),
			scPixCharge(charge),
			isGsfCtfScPixConsistent_(false),
			isGsfScPixConsistent_(false),
			isGsfCtfConsistent_(false),
			trackerDrivenSeed(false),
			ecalDrivenSeed(false),
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
			missingHits_(-9999),
			ip_(-9999.),
			positionAtVtx(-9999.,-9999.,-9999.),
			positionAtCalo(-9999.,-9999.,-9999.),
			dsz_(-9999.),
			normalizedChi2_(9999.),
			ptError_(-9999.),
			trackMomentumError_(-9999.),
			ecalEnergyError_(-9999.),
			ecalEnergy_(-9999.),
			isEcalEnergyCorrected_(false),
			isMomentumCorrected_(false),
			electronMomentumError_(-9999.),
			d0Error_(-9999.),
			dszError_(-9999.),
			caloPosition_(-9999.,-9999.,-9999.),
			basicClusterSize_(9999),
			clusterAlgo_(9999),
			caloConeSize_(9999),
			nbClusters_(9999),
			superClusterRawEnergy_(-9999.),
			preshowerEnergy_(-9999.),
			sigmaEtaEta_(-9999.),
			sigmaIetaIeta(-9999.),
			e1x5_(-9999.),
			e2x5Max_(-9999.),
			e5x5_(-9999.),
			e2x2_(-9999.),
			e3x3_(-9999.),
			eMax_(-9999.),
			hcalDepth1OverEcal(-9999.),
			hcalDepth2OverEcal(-9999.),
			isEB_(false),
			isEE_(false),
			isEBEEGap_(false),
			isEBEtaGap_(false),
			isEBPhiGap_(false),
			isEEDeeGap_(false),
			isEERingGap_(false),
			tkSumPt01(-9999.),
			ecalRecHitSumEt01(-9999.),
			hcalDepth1TowerSumEt01(-9999.),
			hcalDepth2TowerSumEt01(-9999.),
			tkSumPt02(-9999.),
			ecalRecHitSumEt02(-9999.),
			hcalDepth1TowerSumEt02(-9999.),
			hcalDepth2TowerSumEt02(-9999.),
			tkSumPt03(-9999.),
			ecalRecHitSumEt03(-9999.),
			hcalDepth1TowerSumEt03(-9999.),
			hcalDepth2TowerSumEt03(-9999.),
			tkSumPt04(-9999.),
			ecalRecHitSumEt04(-9999.),
			hcalDepth1TowerSumEt04(-9999.),
			hcalDepth2TowerSumEt04(-9999.),
			tkSumPt05(-9999.),
			ecalRecHitSumEt05(-9999.),
			hcalDepth1TowerSumEt05(-9999.),
			hcalDepth2TowerSumEt05(-9999.),
			idCutBasedRobustLoose_(-9999),
			idCutBasedRobustTight_(-9999),
			idCutBasedRobustHighEnergy_(-9999),
			idCategorizedLoose_(-9999),
			idCategorizedTight_(-9999),
			idLikelihood_(-9999),
			idNeuralNet_(-9999),
			idCiCVeryLoose_(-9999),
			idCiCLoose_(-9999),
			idCiCMedium_(-9999),
			idCiCTight_(-9999),
			idCiCSuperTight_(-9999),
			idCiCHyperTight1_(-9999),
			idCiCHyperTight2_(-9999),
			idCiCHyperTight3_(-9999),
			idCiCHyperTight4_(-9999),
			momentumMCElectron_(-9999.,-9999.,-9999.,-9999.),
			vertexMCElectron_(-9999.,-9999.,-9999.),
			pdgIdMCElectron_(-9999),
			classification_(-9999),
			fBrem_(-9999.),
			isConversion(true),
			HLT_Ele10_SW_L1R(false),
			HLT_Ele15_SW_L1R(false)
			{
//				TriggerMatchingInfo tmpTrig;
//				tmpTrig.clear();
//				setTriggerInfo(tmpTrig);
				;
			}

		TRootElectron(const TLorentzVector &momentum) :
			TRootParticle(momentum),
			scPixCharge(-9999),
			isGsfCtfScPixConsistent_(false),
			isGsfScPixConsistent_(false),
			isGsfCtfConsistent_(false),
			trackerDrivenSeed(false),
			ecalDrivenSeed(false),
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
			missingHits_(-9999),
			ip_(-9999.),
			positionAtVtx(-9999.,-9999.,-9999.),
			positionAtCalo(-9999.,-9999.,-9999.),
			dsz_(-9999.),
			normalizedChi2_(9999.),
			ptError_(-9999.),
			trackMomentumError_(-9999.),
			ecalEnergyError_(-9999.),
			ecalEnergy_(-9999.),
			isEcalEnergyCorrected_(false),
			isMomentumCorrected_(false),
			electronMomentumError_(-9999.),
			d0Error_(-9999.),
			dszError_(-9999.),
			caloPosition_(-9999.,-9999.,-9999.),
			basicClusterSize_(9999),
			clusterAlgo_(9999),
			caloConeSize_(9999),
			nbClusters_(9999),
			superClusterRawEnergy_(-9999.),
			preshowerEnergy_(-9999.),
			sigmaEtaEta_(-9999.),
			sigmaIetaIeta(-9999.),
			e1x5_(-9999.),
			e2x5Max_(-9999.),
			e5x5_(-9999.),
			e2x2_(-9999.),
			e3x3_(-9999.),
			eMax_(-9999.),
			hcalDepth1OverEcal(-9999.),
			hcalDepth2OverEcal(-9999.),
			isEB_(false),
			isEE_(false),
			isEBEEGap_(false),
			isEBEtaGap_(false),
			isEBPhiGap_(false),
			isEEDeeGap_(false),
			isEERingGap_(false),
			tkSumPt01(-9999.),
			ecalRecHitSumEt01(-9999.),
			hcalDepth1TowerSumEt01(-9999.),
			hcalDepth2TowerSumEt01(-9999.),
			tkSumPt02(-9999.),
			ecalRecHitSumEt02(-9999.),
			hcalDepth1TowerSumEt02(-9999.),
			hcalDepth2TowerSumEt02(-9999.),
			tkSumPt03(-9999.),
			ecalRecHitSumEt03(-9999.),
			hcalDepth1TowerSumEt03(-9999.),
			hcalDepth2TowerSumEt03(-9999.),
			tkSumPt04(-9999.),
			ecalRecHitSumEt04(-9999.),
			hcalDepth1TowerSumEt04(-9999.),
			hcalDepth2TowerSumEt04(-9999.),
			tkSumPt05(-9999.),
			ecalRecHitSumEt05(-9999.),
			hcalDepth1TowerSumEt05(-9999.),
			hcalDepth2TowerSumEt05(-9999.),
			idCutBasedRobustLoose_(-9999),
			idCutBasedRobustTight_(-9999),
			idCutBasedRobustHighEnergy_(-9999),
			idCategorizedLoose_(-9999),
			idCategorizedTight_(-9999),
			idLikelihood_(-9999),
			idNeuralNet_(-9999),
			idCiCVeryLoose_(-9999),
			idCiCLoose_(-9999),
			idCiCMedium_(-9999),
			idCiCTight_(-9999),
			idCiCSuperTight_(-9999),
			idCiCHyperTight1_(-9999),
			idCiCHyperTight2_(-9999),
			idCiCHyperTight3_(-9999),
			idCiCHyperTight4_(-9999),
			momentumMCElectron_(-9999.,-9999.,-9999.,-9999.),
			vertexMCElectron_(-9999.,-9999.,-9999.),
			pdgIdMCElectron_(-9999),
			classification_(-9999),
			fBrem_(-9999.),
			isConversion(true),
			HLT_Ele10_SW_L1R(false),
			HLT_Ele15_SW_L1R(false)
			{
//				TriggerMatchingInfo tmpTrig;
//				tmpTrig.clear();
//				setTriggerInfo(tmpTrig);
				;
			}

		TRootElectron(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
			TRootParticle(momentum, vertex, type,charge),
			scPixCharge(charge),
			isGsfCtfScPixConsistent_(false),
			isGsfScPixConsistent_(false),
			isGsfCtfConsistent_(false),
			trackerDrivenSeed(false),
			ecalDrivenSeed(false),
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
			missingHits_(-9999),
			ip_(-9999.),
			positionAtVtx(-9999.,-9999.,-9999.),
			positionAtCalo(-9999.,-9999.,-9999.),
			dsz_(-9999.),
			normalizedChi2_(9999.),
			ptError_(-9999.),
			trackMomentumError_(-9999.),
			ecalEnergyError_(-9999.),
			ecalEnergy_(-9999.),
			isEcalEnergyCorrected_(false),
			isMomentumCorrected_(false),
			electronMomentumError_(-9999.),
			d0Error_(-9999.),
			dszError_(-9999.),
			caloPosition_(-9999.,-9999.,-9999.),
			basicClusterSize_(9999),
			clusterAlgo_(9999),
			caloConeSize_(9999),
			nbClusters_(9999),
			superClusterRawEnergy_(-9999.),
			preshowerEnergy_(-9999.),
			sigmaEtaEta_(-9999.),
			sigmaIetaIeta(-9999.),
			e1x5_(-9999.),
			e2x5Max_(-9999.),
			e5x5_(-9999.),
			e2x2_(-9999.),
			e3x3_(-9999.),
			eMax_(-9999.),
			hcalDepth1OverEcal(-9999.),
			hcalDepth2OverEcal(-9999.),
			isEB_(false),
			isEE_(false),
			isEBEEGap_(false),
			isEBEtaGap_(false),
			isEBPhiGap_(false),
			isEEDeeGap_(false),
			isEERingGap_(false),
			tkSumPt01(-9999.),
			ecalRecHitSumEt01(-9999.),
			hcalDepth1TowerSumEt01(-9999.),
			hcalDepth2TowerSumEt01(-9999.),
			tkSumPt02(-9999.),
			ecalRecHitSumEt02(-9999.),
			hcalDepth1TowerSumEt02(-9999.),
			hcalDepth2TowerSumEt02(-9999.),
			tkSumPt03(-9999.),
			ecalRecHitSumEt03(-9999.),
			hcalDepth1TowerSumEt03(-9999.),
			hcalDepth2TowerSumEt03(-9999.),
			tkSumPt04(-9999.),
			ecalRecHitSumEt04(-9999.),
			hcalDepth1TowerSumEt04(-9999.),
			hcalDepth2TowerSumEt04(-9999.),
			tkSumPt05(-9999.),
			ecalRecHitSumEt05(-9999.),
			hcalDepth1TowerSumEt05(-9999.),
			hcalDepth2TowerSumEt05(-9999.),
			idCutBasedRobustLoose_(-9999),
			idCutBasedRobustTight_(-9999),
			idCutBasedRobustHighEnergy_(-9999),
			idCategorizedLoose_(-9999),
			idCategorizedTight_(-9999),
			idLikelihood_(-9999),
			idNeuralNet_(-9999),
			idCiCVeryLoose_(-9999),
			idCiCLoose_(-9999),
			idCiCMedium_(-9999),
			idCiCTight_(-9999),
			idCiCSuperTight_(-9999),
			idCiCHyperTight1_(-9999),
			idCiCHyperTight2_(-9999),
			idCiCHyperTight3_(-9999),
			idCiCHyperTight4_(-9999),
			momentumMCElectron_(-9999.,-9999.,-9999.,-9999.),
			vertexMCElectron_(-9999.,-9999.,-9999.),
			pdgIdMCElectron_(-9999),
			classification_(-9999),
			fBrem_(-9999.),
			isConversion(true),
			HLT_Ele10_SW_L1R(false),
			HLT_Ele15_SW_L1R(false)
			{
//				TriggerMatchingInfo tmpTrig;
//				tmpTrig.clear();
//				setTriggerInfo(tmpTrig);
				;
			}

		~TRootElectron() {;}

	        
		virtual TString typeName() const { return "TRootElectron"; }


		friend std::ostream& operator<< (std::ostream& stream, const TRootElectron& electron) {
			stream << "TRootElectron - Charge=" << electron.charge() << " (Et,eta,phi)=("<< electron.Et() <<","<< electron.Eta() <<","<< electron.Phi() << ")"
				<< " vertex(x,y,z)=("<< electron.vx() <<","<< electron.vy() <<","<< electron.vz() << ")";
			return stream;
		};
    
	private:
		int scPixCharge;
		bool isGsfCtfScPixConsistent_;
		bool isGsfScPixConsistent_;
		bool isGsfCtfConsistent_;
		bool trackerDrivenSeed;
		bool ecalDrivenSeed;

//    TrackClusterMatching myTrackClusterMatching;
		float eSuperClusterOverPin_ ;        // the supercluster energy / track momentum at the PCA to the beam spot
		float eSuperClusterOverPout_ ;       // the electron cluster energy / track momentum at calo extrapolated from the outermost track state
		float eSeedClusterOverPin_ ;         // the seed cluster energy / track momentum at the PCA to the beam spot
		float eSeedClusterOverPout_ ;      // the seed cluster energy / track momentum at calo extrapolated from the outermost track state
		float deltaEtaIn_ ; // the supercluster eta - track eta position at calo extrapolated from innermost track state
		float deltaEtaOut_ ; // the seed cluster eta - track eta position at calo extrapolated from the outermost track state
		float deltaPhiIn_ ; // the supercluster phi - track phi position at calo extrapolated from the innermost track state
		float deltaPhiOut_ ; // the seed cluster phi - track phi position at calo extrapolated from the outermost track state
		float deltaPhiSuperClusterTrackAtCalo_ ;  // the electron cluster phi - track phi position at calo extrapolated from the outermost track state
		float deltaEtaSuperClusterTrackAtCalo_ ;  // the electron cluster eta - t


//		TrackProperties================================
		Float_t trackMomentum_;             // Track momentum at vertex
		Float_t momentumAtCalo_ ;    // the track momentum extrapolated at the supercluster position from the innermost track state
		Float_t momentumOut_ ;       // the track momentum extrapolated at the seed cluster position from the outermost track state
		Float_t momentumAtEleClus_ ; // the track momentum extrapolated at the ele cluster position from the outermost track state
		Float_t momentumAtVtxWithConstraint_ ;     // the track momentum at the PCA to the beam spot using bs constraint
		Int_t pixelLayersWithMeasurement_; // Number of pixel layers with at least one valid hit
		Int_t stripLayersWithMeasurement_; // Number of strip layers with at least one valid hit
		Float_t d0_;
		Int_t missingHits_;// Conversion Rejection: number of missing hits near beginning of track (also rejects really bad tracks)
                       //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideCategoryBasedElectronID#The_Cut_Variables
		Float_t ip_;//Track vertex: Impact Parameter w.r.t. reco vertex , same wiki page
		TVector3  positionAtVtx ;     // the track PCA to the beam spot
		TVector3  positionAtCalo ;    // the track PCA to the supercluster position
		Float_t dsz_;            // dsz parameter
		Float_t normalizedChi2_; // chi-squared divided by n.d.o.f. of track fit
		Float_t ptError_; // needed ?  ptError()

    
 //Corrections===========================

//    Corrections myCorrections_;
		Float_t trackMomentumError_;        // Error on trackMomentum_
		Float_t ecalEnergyError_;           // Error on caloEnergy_
		Float_t ecalEnergy_;                // ecal corrected energy (if !isEcalEnergyCorrected this value is identical to the supercluster energy)
		bool isEcalEnergyCorrected_ ;  // true if ecal energy has been corrected
		bool isMomentumCorrected_ ;    // true if E-p combination has been applied (if not the electron momentum is the ecal corrected energy)
		Float_t electronMomentumError_ ; // the final electron momentum error
		Float_t d0Error_;        // error on d0_
		Float_t dszError_;

//SuperClusterProperties ===============================

		TVector3 caloPosition_;		// SuperCluster centroid position
		Int_t basicClusterSize_;        // number of basic clusters inside the supercluster
		Int_t clusterAlgo_; // reco::BasicCluster::algo() island = 0, hybrid = 1, fixedMatrix = 2, dynamicHybrid = 3, multi5x5 = 4
		Float_t caloConeSize_; // Delta_R of the cone centered on the reco::GsfElectron and containing all its basic clusters constituents
		// need reco::SuperCluster and reco::BasicCluster and reduced Ecal RecHits Collections for EcalClusterLazyTools
		Int_t nbClusters_; // Number of related brem clusters
		Float_t superClusterRawEnergy_;
		Float_t preshowerEnergy_;


//ShowerShape===================================

		Float_t sigmaEtaEta_ ;        // weighted cluster rms along eta and inside 5x5 (absolute eta)
		Float_t sigmaIetaIeta ;      // weighted cluster rms along eta and inside 5x5 (new, Xtal eta)
		Float_t e1x5_ ;               // energy inside 1x5 in etaxphi around the seed Xtal
		Float_t e2x5Max_ ;            // energy inside 2x5 in etaxphi around the seed Xtal (max bwt the 2 possible sums)
		Float_t e5x5_ ;               // energy inside 5x5 in etaxphi around the seed Xtal
		Float_t e2x2_;
		Float_t e3x3_;
		Float_t eMax_;
		Float_t hcalDepth1OverEcal ; // hcal over ecal seed cluster energy using first hcal depth (hcal is energy of towers within dR=015)
		Float_t hcalDepth2OverEcal ; // hcal over ecal seed cluster energy using 2nd hcal depth (hcal is energy of towers within dR=015)


//FiducialFlags=================================

//    FiducialFlags myFiducialFlags_;
		bool isEB_ ;        // true if particle is in ECAL Barrel
		bool isEE_ ;        // true if particle is in ECAL Endcaps
		bool isEBEEGap_ ;   // true if particle is in the crack between EB and EE
		bool isEBEtaGap_ ;  // true if particle is in EB, and inside the eta gaps between modules
		bool isEBPhiGap_ ;  // true if particle is in EB, and inside the phi gaps between modules
		bool isEEDeeGap_ ;  // true if particle is in EE, and inside the gaps between dees
		bool isEERingGap_ ; // true if particle is in EE, and inside the gaps between rings

//Isolation ==================================

		Float_t tkSumPt01;                // track iso deposit with electron footprint removed
		Float_t ecalRecHitSumEt01;        // ecal iso deposit with electron footprint removed
		Float_t hcalDepth1TowerSumEt01;   // hcal depht 1 iso deposit with electron footprint removed
		Float_t hcalDepth2TowerSumEt01;   // hcal depht 2 iso deposit with electron footprint removed
//    Int_t nTracks01;
		Float_t tkSumPt02;                // track iso deposit with electron footprint removed
		Float_t ecalRecHitSumEt02;        // ecal iso deposit with electron footprint removed
		Float_t hcalDepth1TowerSumEt02;   // hcal depht 1 iso deposit with electron footprint removed
		Float_t hcalDepth2TowerSumEt02;   // hcal depht 2 iso deposit with electron footprint removed
//    Int_t nTracks02;
		Float_t tkSumPt03;                // track iso deposit with electron footprint removed
		Float_t ecalRecHitSumEt03;        // ecal iso deposit with electron footprint removed
		Float_t hcalDepth1TowerSumEt03;   // hcal depht 1 iso deposit with electron footprint removed
		Float_t hcalDepth2TowerSumEt03;   // hcal depht 2 iso deposit with electron footprint removed
//		Int_t nTracks03;
		Float_t tkSumPt04;                // track iso deposit with electron footprint removed
		Float_t ecalRecHitSumEt04;        // ecal iso deposit with electron footprint removed
		Float_t hcalDepth1TowerSumEt04;   // hcal depht 1 iso deposit with electron footprint removed
		Float_t hcalDepth2TowerSumEt04;   // hcal depht 2 iso deposit with electron footprint removed
//		Int_t nTracks04;
		Float_t tkSumPt05;                // track iso deposit with electron footprint removed
		Float_t ecalRecHitSumEt05;        // ecal iso deposit with electron footprint removed
		Float_t hcalDepth1TowerSumEt05;   // hcal depht 1 iso deposit with electron footprint removed
		Float_t hcalDepth2TowerSumEt05;   // hcal depht 2 iso deposit with electron footprint removed
//		Int_t nTracks05;



    //Identification ===================================
		Int_t idCutBasedRobustLoose_;      // Simple cut based ID (aka 'robust') - Loose Thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta
		Int_t idCutBasedRobustTight_;      // Simple cut based ID (default in EWK group) - Tight Thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta
		Int_t idCutBasedRobustHighEnergy_; // Simple cut based ID - Thresholds optimized for high energy electron (~TeV)
		Int_t idCategorizedLoose_;         // Category based ID - Different loose thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta, eSeedOverPin for differents regions in the E/p vs fBrem plane
		Int_t idCategorizedTight_;         // Category based ID - Different tight thresholds on H/E, DeltaEta, DeltaPhi, SigmaEtaEta, eSeedOverPin for differents regions in the E/p vs fBrem plane
		Float_t idLikelihood_;                       // Lieklihood ID - not activated by default in 2.2.X
		Float_t idNeuralNet_;                        // NN ID - not activated by default in 2.2.X
		Int_t idCiCVeryLoose_; //Cuts in Categories for 35x: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideCategoryBasedElectronID#The_Cut_Variables
		Int_t idCiCLoose_;
		Int_t idCiCMedium_;
		Int_t idCiCTight_;
		Int_t idCiCSuperTight_;
		Int_t idCiCHyperTight1_;
		Int_t idCiCHyperTight2_;
		Int_t idCiCHyperTight3_;
		Int_t idCiCHyperTight4_;

//MCInfo==========================================

		TLorentzVector momentumMCElectron_;
		TVector3 vertexMCElectron_;
		Int_t pdgIdMCElectron_;

// Electron classification && fBrem ====================
		Int_t classification_;             
		Float_t fBrem_;
		bool isConversion;

//Trigger Info ======================================
		bool HLT_Ele10_SW_L1R;
		bool HLT_Ele15_SW_L1R;


        //ChargeInfo===================================
public:

		int Charge()const{return scPixCharge;}
		bool isGsfCtfScPixConsistent()const{return isGsfCtfScPixConsistent_;}
		bool isGsfScPixConsistent()const{return isGsfScPixConsistent_;}
		bool isGsfCtfConsistent()const{return isGsfCtfConsistent_;}

		//getters
		bool isEcalDrivenSeed()const{
			return ecalDrivenSeed;
		}
		bool isTrackerDrivenSeed()const{
			return trackerDrivenSeed;
		}

		//setters
		void setChargeInfo(int scPix,bool GsfCftScPix, bool GsfScPix, bool GsfCtf )
		{
			scPixCharge = scPix;
			isGsfCtfScPixConsistent_ = GsfCftScPix;
			isGsfScPixConsistent_ = GsfScPix;
			isGsfCtfConsistent_ = GsfCtf;
		}
		void setSuperClusterPixelCharge(int scPix ){ scPixCharge = scPix;}
		void setSuperClusterPixelCtfGsfConsistency(bool GsfCftScPix){ isGsfCtfScPixConsistent_ = GsfCftScPix;}
		void setSuperClusterPixelGsfConsistency(bool GsfScPix){ isGsfScPixConsistent_ = GsfScPix;}
		void setGsfCtfConsistency(bool GsfCtf){ isGsfCtfConsistent_ = GsfCtf;}
		void setSeedingInfo(bool isEcal, bool isTracker)
		{
			ecalDrivenSeed = isEcal;
			trackerDrivenSeed = isTracker;
		}
		void setEcalSeeding(bool isEcal){ ecalDrivenSeed = isEcal;}
		void setTrackerSeeding(bool isTracker){ trackerDrivenSeed = isTracker;}

		//getters:
		float eScOverPin()const{return eSuperClusterOverPin_;};
		float eScOverPout()const{return eSuperClusterOverPout_;};
		float eSeedOverPin()const{return eSeedClusterOverPin_;};
		float eSeedOverPout()const{return eSeedClusterOverPout_;};
		float deltaEtaIn()const{return deltaEtaIn_;};
		float deltaEtaOut()const{return deltaEtaOut_;};
		float deltaPhiIn()const{return deltaPhiIn_;};
		float deltaPhiOut()const{return deltaPhiOut_;};
		float deltaPhiScTrkOut()const{return deltaPhiSuperClusterTrackAtCalo_;};
		float deltaEtaScTrkOut()const{return deltaEtaSuperClusterTrackAtCalo_;};

		//setters
		void setTrackClusterMatching(float eScOverPin,float eScOverPout,float eSeedOverPin,float eSeedOverPout,float dEtaIn,
			float dEtaOut,float dPhiIn,float dPhiOut,float dPhiScTrkOut,float dEtaScTrkOut)
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

		//getters
		Float_t trackMomentum()const{return trackMomentum_;};
		Float_t trackMomentumAtSuperClusterPosition()const{return momentumAtCalo_;};
		Float_t trackMomentumAtSeedClusterPosition()const{return momentumOut_;};
		Float_t trackMomentumAtElectronClusterPosition()const{return momentumAtEleClus_;};
		Float_t trackMomentumAtVtxWithConstraints()const{return momentumAtVtxWithConstraint_;};
		Int_t trackPixelLayersWithMeasurement()const{return pixelLayersWithMeasurement_;};
		Int_t trackStripLayersWithMeasurement()const{return stripLayersWithMeasurement_;};
		Float_t d0()const{return d0_;};
		Int_t missingHits()const{return missingHits_;};
		Float_t impactParameter()const{return ip_;};
		TVector3 trackPositionAtVtx()const{return positionAtVtx;};
		TVector3 trackPositionAtCalo()const{return positionAtCalo;};
		Float_t trackDsz()const{return dsz_;};
		Float_t trackNormalizedChi2()const{return normalizedChi2_;};
		Float_t trackPtError()const{return ptError_;};

		//setter
		void setTrackProperties(float p, float pAtSc, float pAtSeed, float pAtEleC,float pConstraint,
			int pixelLayers, int stripLayers, float d0, int missingHits, float ip,
			TVector3 XatVtx, TVector3 XatCalo, float dsz, float chi2, float PtError)
		{
			trackMomentum_ = p;
			momentumAtCalo_ = pAtSc;
			momentumOut_ = pAtSeed;
			momentumAtEleClus_ = pAtEleC;
			momentumAtVtxWithConstraint_ = pConstraint;
			pixelLayersWithMeasurement_ = pixelLayers;
			stripLayersWithMeasurement_ = stripLayers;
			d0_ = d0;
			missingHits_ = missingHits;
			ip_ = ip;
			positionAtVtx = XatVtx;
			positionAtCalo = XatCalo;
			dsz_ = dsz;
			normalizedChi2_ = chi2;
			ptError_ = PtError;
		};
		void setD0(Float_t x) { d0_ = x; } //-ip
		void setDsz(Float_t x) { dsz_ = x; }
		void setImpactParameter(Float_t x) { ip_ = x; }
		void setTrackMissingHits(Int_t x) { missingHits_ = x; }
		void setTrackMomentumAtCalo(Float_t x) { momentumAtCalo_ = x; }
		void setTrackMomentumAtElectronCluster(Float_t x) { momentumAtEleClus_ = x; }
		void setTrackMomentumAtVtxWithConstraint(Float_t x) { momentumAtVtxWithConstraint_ = x; }
		void setTrackMomentumOut(Float_t x) { momentumOut_ = x; }
		void setTrackNormalizedChi2(Float_t x) { normalizedChi2_ = x; }
		void setPixelLayersWithMeasurement(Int_t x) { pixelLayersWithMeasurement_ = x; }
		void setStripLayersWithMeasurement(Int_t stripLayersWithMeasurement) { stripLayersWithMeasurement_ = stripLayersWithMeasurement; }
		void setTrackPositionAtCalo(Double_t x, Double_t y, Double_t z) { positionAtCalo.SetXYZ(x,y,z); }
		void setTrackPositionAtCalo(TVector3 x) { positionAtCalo = x; }
		void setTrackPositionAtVtx(Double_t x, Double_t y, Double_t z) { positionAtVtx.SetXYZ(x,y,z); }
		void setTrackPositionAtVtx(TVector3 x) { positionAtVtx = x; }
		void setTrackPtError(Float_t x) { ptError_ = x; }
		void setTrackMomentum(Float_t x) { trackMomentum_ = x; }
		Float_t trackMomentumError()const{return trackMomentumError_;};
		Float_t caloEnergyError()const{return ecalEnergyError_;};
		Float_t caloEnergy()const{return ecalEnergy_;};
		bool isCaloEnergyCorrected()const{return isEcalEnergyCorrected_;};
		bool isMomentumCorrected()const{return isMomentumCorrected_;};
		Float_t electronMomentumError()const{return electronMomentumError_;};
		Float_t d0Error()const{return d0Error_;};
		Float_t dszError()const{return dszError_;};

		//setter
		void setCorrections(float tme, float cee, float ce, bool cc, bool mc, float eMc, float d0e, float dsze)
		{
			trackMomentumError_ = tme;        // Error on trackMomentum_
			ecalEnergyError_ = cee;           // Error on caloEnergy_
			ecalEnergy_ = ce;                // ecal corrected energy (if !isEcalEnergyCorrected this value is identical to the supercluster energy)
			isEcalEnergyCorrected_ = cc;  // true if ecal energy has been corrected
			isMomentumCorrected_ = mc;    // true if E-p combination has been applied (if not the electron momentum is the ecal corrected energy)
			electronMomentumError_ = eMc; // the final electron momentum error
			d0Error_ = d0e;        // error on d0_
			dszError_ = dsze;
		};
		void setD0Error(Float_t d0Error) { d0Error_ = d0Error; }
		void setDszError(Float_t x) { dszError_ = x; }
		void setCaloEnergyError(Float_t x) { ecalEnergyError_ = x; }
		void setCaloEnergy(Float_t x) { ecalEnergy_ = x; }
		void setElectronMomentumError(Float_t x) { electronMomentumError_ = x; }
		void setEnergyScaleCorrected(bool x) { isEcalEnergyCorrected_ = x; }
		void setMomentumCorrected(bool x) { isMomentumCorrected_ = x; }
		void setTrackMomentumError(Float_t x) { trackMomentumError_ = x; }
		//getters
		TVector3 caloPosition()const{return caloPosition_;};
		Int_t basicClusterSize()const{return basicClusterSize_;};
		Int_t clusterAlgo()const{return clusterAlgo_;};
		Float_t caloConeSize()const{return caloConeSize_;};
		Int_t nClusters()const{return nbClusters_;};
		Float_t superClusterRawEnergy()const{return superClusterRawEnergy_;};
		Float_t preshowerEnergy()const{return preshowerEnergy_;};
		//setter
		void setSuperCluster(TVector3 pos, Int_t bcs, Int_t ca, Float_t ccs, Int_t nC, Float_t scRawE, Float_t PSE)
		{
			caloPosition_ = pos;
			basicClusterSize_ = bcs;
			clusterAlgo_ = ca;
			caloConeSize_ = ccs;
			nbClusters_ = nC;
			superClusterRawEnergy_ = scRawE;
			preshowerEnergy_ = PSE;
		};
		void setBasicClusterSize(Int_t x) { basicClusterSize_ = x; }
		void setCaloConeSize(Float_t x) { caloConeSize_ = x; }
		void setCaloPosition(Double_t x, Double_t y, Double_t z) { caloPosition_.SetXYZ(x, y ,z); }
		void setCaloPosition(TVector3 x) { caloPosition_ = x; }
		void setClusterAlgo(Int_t x) { clusterAlgo_ = x; }
		void setNbClusters(Int_t x) { nbClusters_ = x; }
		void setPreshowerEnergy(Float_t x) { preshowerEnergy_ = x; }
		void setSuperClusterRawEnergy(Float_t x) { superClusterRawEnergy_ = x; }
		Float_t sigmaEtaEta()const{return sigmaEtaEta_;};
		Float_t sigmaIEtaIEta()const{return sigmaIetaIeta;};
		Float_t e1x5()const{return e1x5_;};
		Float_t e2x5Max()const{return e2x5Max_;};
		Float_t e5x5()const{return e5x5_;};
		Float_t e2x2()const{return e2x2_;};
		Float_t e3x3()const{return e3x3_;};
		Float_t eMax()const{return eMax_;};
		Float_t hadronicOverEm()const{return(hcalDepth1OverEcal + hcalDepth2OverEcal);};
		Float_t hadronicDepth1OverEm()const{return(hcalDepth1OverEcal);};
		Float_t hadronicDepth2OverEm()const{return(hcalDepth2OverEcal);};
		//setter
		void setShowerShape(float see, float sieie, float e15, float e25M, float e55, float e22, float e33, float eMax,
                    float hoe1,float hoe2)
		{
			sigmaEtaEta_ = see;
			sigmaIetaIeta = sieie;
			e1x5_ = e15;
			e2x5Max_ = e25M;
			e5x5_ = e55;
			e2x2_ = e22;
			e3x3_ = e33;
			eMax_ = eMax;
			hcalDepth1OverEcal = hoe1;
			hcalDepth2OverEcal = hoe2;
		};
		void setE1x5(Float_t e1x5) { e1x5_ = e1x5; }
		void setE2x2(Float_t e2x2) { e2x2_ = e2x2; }
		void setE2x5Max(Float_t e2x5Max) { e2x5Max_ = e2x5Max; }
		void setE3x3(Float_t e3x3) { e3x3_ = e3x3; }
		void setE5x5(Float_t e5x5) { e5x5_ = e5x5; }
		void setHoverEDepth1(Float_t HoE1) { hcalDepth1OverEcal = HoE1; }
		void setHoverEDepth2(Float_t HoE2) { hcalDepth2OverEcal = HoE2; }
		void setSigmaEtaEta(Float_t see) { sigmaEtaEta_ = see; }
		void setSigmaIetaIeta(Float_t sieie) { sigmaIetaIeta = sieie; }
		bool isEB()const {return isEB_;};
		bool isEE() const{return isEE_;};
		bool isEBEEGap() const{return isEBEEGap_;};
		bool isEBEtaGap()const {return isEBEtaGap_;};
		bool isEBPhiGap()const {return isEBPhiGap_;};
		bool isEEDeeGap()const {return isEEDeeGap_;};
		bool isEERingGap()const {return isEERingGap_;};
		//setter
		void setFiducialFlags(bool eb, bool ee, bool ebeegap, bool ebetagap, bool ebphigap, bool eedeegap, bool eeR)
		{
			isEB_ = eb;
			isEE_ = ee;
			isEBEEGap_ = ebeegap;
			isEBEtaGap_ = ebetagap;
			isEBPhiGap_ = ebphigap;
			isEEDeeGap_ = eedeegap;
			isEERingGap_ = eeR;
		}
		void setEB(bool is){isEB_ = is;};
		void setEE(bool is){isEE_ = is;};
		void setEBEEGap(bool is){isEBEEGap_ = is;};
		void setEBEtaGap(bool is){isEBEtaGap_ = is;};
		void setEBPhiGap(bool is){isEBPhiGap_ = is;};
		void setEEDeeGap(bool is){isEEDeeGap_ = is;};
		void setEERingGap(bool is){isEERingGap_ = is;};

		Float_t ecalIso(unsigned int cone)const
		{
			if(cone == 1) return ecalRecHitSumEt01;
			else if(cone == 2) return ecalRecHitSumEt02;
			else if(cone == 3) return ecalRecHitSumEt03;
			else if(cone == 4) return ecalRecHitSumEt04;
			else if(cone == 5) return ecalRecHitSumEt05;
			else
			{
				cout<<"Bad Cone Size! It returns -1."<<endl;
				return -1.;
			}
		}
		Float_t hcalIso(unsigned int cone)const
		{
			if(cone == 1) return (hcalDepth1TowerSumEt01 + hcalDepth2TowerSumEt01);
			else if(cone == 2) return (hcalDepth1TowerSumEt02 + hcalDepth2TowerSumEt02);
			else if(cone == 3) return (hcalDepth1TowerSumEt03 + hcalDepth2TowerSumEt03);
			else if(cone == 4) return (hcalDepth1TowerSumEt04 + hcalDepth2TowerSumEt04);
			else if(cone == 5) return (hcalDepth1TowerSumEt05 + hcalDepth2TowerSumEt05);
			else
			{
				cout<<"Bad Cone Size! It returns -1."<<endl;
				return -1.;
			}
		}
		Float_t hcalIso_Dept1(unsigned int cone)const
		{
			if(cone == 1) return (hcalDepth1TowerSumEt01 );
			else if(cone == 2) return (hcalDepth1TowerSumEt02);
			else if(cone == 3) return (hcalDepth1TowerSumEt03);
			else if(cone == 4) return (hcalDepth1TowerSumEt04 );
			else if(cone == 5) return (hcalDepth1TowerSumEt05 );
			else
			{
				cout<<"Bad Cone Size! It returns -1."<<endl;
				return -1.;
			}
		}
		Float_t hcalIso_Dept2(unsigned int cone)const
		{
			if(cone == 1) return ( hcalDepth2TowerSumEt01);
			else if(cone == 2) return (hcalDepth2TowerSumEt02);
			else if(cone == 3) return ( hcalDepth2TowerSumEt03);
			else if(cone == 4) return ( hcalDepth2TowerSumEt04);
			else if(cone == 5) return (hcalDepth2TowerSumEt05);
			else
			{
				cout<<"Bad Cone Size! It returns -1."<<endl;
				return -1.;
			}
		}
		Float_t caloIso(unsigned int cone)const
		{
			return (ecalIso(cone) + hcalIso(cone));
		}
		Float_t trackerIso(unsigned int cone)const
		{
			if(cone == 1) return (tkSumPt01);
			else if(cone == 2) return (tkSumPt02);
			else if(cone == 3) return (tkSumPt03);
			else if(cone == 4) return (tkSumPt04);
			else if(cone == 5) return (tkSumPt05);
			else
			{
				cout<<"Bad Cone Size! It returns -1."<<endl;
				return -1.;
			}
		}
		Float_t combinedIso(unsigned int tkcone, unsigned int ecalcone, unsigned int hcalcone)const
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
    //setters
		void setIsoR01_emEt(Float_t isoR01_emEt) { ecalRecHitSumEt01 = isoR01_emEt; }
		void setIsoR01_Depth1HadEt(Float_t isoR01_hadEt1) { hcalDepth1TowerSumEt01 = isoR01_hadEt1; }
		void setIsoR01_Depth2HadEt(Float_t isoR01_hadEt2) { hcalDepth2TowerSumEt01 = isoR01_hadEt2; }
		void setIsoR01_sumPt(Float_t isoR01_sumPt) { tkSumPt01 = isoR01_sumPt; }
//    void setIsoR01_nTracks(Int_t isoR01_nTracks) { nTracks = isoR01_nTracks; }

		void setIsoR02_emEt(Float_t isoR02_emEt) { ecalRecHitSumEt02 = isoR02_emEt; }
		void setIsoR02_Depth1HadEt(Float_t isoR02_hadEt1) { hcalDepth1TowerSumEt02 = isoR02_hadEt1; }
		void setIsoR02_Depth2HadEt(Float_t isoR02_hadEt2) { hcalDepth2TowerSumEt02 = isoR02_hadEt2; }
		void setIsoR02_sumPt(Float_t isoR02_sumPt) { tkSumPt02 = isoR02_sumPt; }
//    void setIsoR02_nTracks(Int_t isoR02_nTracks) { nTracks = isoR02_nTracks; }

		void setIsoR03_emEt(Float_t isoR03_emEt) { ecalRecHitSumEt03 = isoR03_emEt; }
		void setIsoR03_Depth1HadEt(Float_t isoR03_hadEt1) { hcalDepth1TowerSumEt03 = isoR03_hadEt1; }
		void setIsoR03_Depth2HadEt(Float_t isoR03_hadEt2) { hcalDepth2TowerSumEt03 = isoR03_hadEt2; }
		void setIsoR03_sumPt(Float_t isoR03_sumPt) { tkSumPt03 = isoR03_sumPt; }
//    void setIsoR03_nTracks(Int_t isoR03_nTracks) { nTracks = isoR03_nTracks; }

		void setIsoR04_emEt(Float_t isoR04_emEt) { ecalRecHitSumEt04 = isoR04_emEt; }
		void setIsoR04_Depth1HadEt(Float_t isoR04_hadEt1) { hcalDepth1TowerSumEt04 = isoR04_hadEt1; }
		void setIsoR04_Depth2HadEt(Float_t isoR04_hadEt2) { hcalDepth2TowerSumEt04 = isoR04_hadEt2; }
		void setIsoR04_sumPt(Float_t isoR04_sumPt) { tkSumPt04 = isoR04_sumPt; }
//    void setIsoR04_nTracks(Int_t isoR04_nTracks) { nTracks = isoR04_nTracks; }

		void setIsoR05_emEt(Float_t isoR05_emEt) { ecalRecHitSumEt05 = isoR05_emEt; }
		void setIsoR05_Depth1HadEt(Float_t isoR05_hadEt1) { hcalDepth1TowerSumEt05 = isoR05_hadEt1; }
		void setIsoR05_Depth2HadEt(Float_t isoR05_hadEt2) { hcalDepth2TowerSumEt05 = isoR05_hadEt2; }
		void setIsoR05_sumPt(Float_t isoR05_sumPt) { tkSumPt05 = isoR05_sumPt; }
//    void setIsoR05_nTracks(Int_t isoR05_nTracks) { nTracks = isoR05_nTracks; }
		//getters
		Int_t isRobustLoose()const{return idCutBasedRobustLoose_;};
		Int_t isRobustTight()const{return idCutBasedRobustTight_;};
		Int_t isRobustHighEnergy()const{return idCutBasedRobustHighEnergy_;};
		Int_t isLoose()const{return idCategorizedLoose_;};
		Int_t isTight()const{return idCategorizedTight_;};
		Float_t LikelihoodId()const{return idLikelihood_;};
		Float_t NeuralNetworkId()const{return idNeuralNet_;};
		Int_t CiCVeryLooseId()const{return idCiCVeryLoose_;};
		Int_t CiCLooseId()const{return idCiCLoose_;};
		Int_t CiCMediumId()const{return idCiCMedium_;};
		Int_t CiCTightId()const{return idCiCTight_;};
		Int_t CiCSuperTightId()const{return idCiCSuperTight_;};
		Int_t CiCHyperTightId_1()const{return idCiCHyperTight1_;};
		Int_t CiCHyperTightId_2()const{return idCiCHyperTight2_;};
		Int_t CiCHyperTightId_3()const{return idCiCHyperTight3_;};
		Int_t CiCHyperTightId_4()const{return idCiCHyperTight4_;};

		//setters
		void setIDs(int RL, int RT, int RH, int CL, int CT, float LH, float NN, int cicVL, int cicL,
                int cicM, int cicT, int cicST, int cicHT1,int cicHT2,int cicHT3,int cicHT4)
		{
			idCutBasedRobustLoose_ = RL;
			idCutBasedRobustTight_ = RT;
			idCutBasedRobustHighEnergy_ = RH;
			idCategorizedLoose_ = CL;
			idCategorizedTight_ = CT;
			idLikelihood_ = LH;
			idNeuralNet_ = NN;
			idCiCVeryLoose_ = cicVL;
			idCiCLoose_ = cicL;
			idCiCMedium_ = cicM;
			idCiCTight_ = cicT;
			idCiCSuperTight_ = cicST;
			idCiCHyperTight1_ = cicHT1;
			idCiCHyperTight2_ = cicHT2;
			idCiCHyperTight3_ = cicHT3;
			idCiCHyperTight4_ = cicHT4;
		}
		void setIDCutBasedRobustLoose(Int_t idCutBasedFixedThresholdLoose) { idCutBasedRobustLoose_ = idCutBasedFixedThresholdLoose; }
		void setIDCutBasedRobustTight(Int_t idCutBasedFixedThresholdTight) { idCutBasedRobustTight_ = idCutBasedFixedThresholdTight; }
		void setIDCutBasedRobustHighEnergy(Int_t idCutBasedFixedThresholdHighEnergy) { idCutBasedRobustHighEnergy_ = idCutBasedFixedThresholdHighEnergy; }
		void setIDCategorizedLoose(Int_t idCutBasedCategorizedLoose) { idCategorizedLoose_ = idCutBasedCategorizedLoose; }
		void setIDCategorizedTight(Int_t idCutBasedCategorizedTight) { idCategorizedTight_ = idCutBasedCategorizedTight; }
		void setIDLikelihood(Float_t idLikelihood) { idLikelihood_ = idLikelihood; }
		void setIDNeuralNet(Float_t idNeuralNet) { idNeuralNet_ = idNeuralNet; }
		void setIDCiCVeryLoose(Int_t cicVL) { idCiCVeryLoose_ = cicVL; }
		void setIDCiCLoose(Int_t cicL) { idCiCLoose_ = cicL; }
		void setIDCiCMedium(Int_t cicM) { idCiCMedium_ = cicM; }
		void setIDCiCTight(Int_t cicT) { idCiCTight_ = cicT; }
		void setIDCiCSuperTight(Int_t cicST) { idCiCSuperTight_ = cicST; }
		void setIDCiCHyperTight1(Int_t cicHT1) { idCiCHyperTight1_ = cicHT1; }
		void setIDCiCHyperTight2(Int_t cicHT2) { idCiCHyperTight2_ = cicHT2; }
		void setIDCiCHyperTight3(Int_t cicHT3) { idCiCHyperTight3_ = cicHT3; }
		void setIDCiCHyperTight4(Int_t cicHT4) { idCiCHyperTight4_ = cicHT4; }

		Int_t MCId()const{return pdgIdMCElectron_;};
		TLorentzVector MCP4()const{return momentumMCElectron_;};
		TVector3 MCVertex()const{return vertexMCElectron_;};
		//setter
		void setMCInfo(TLorentzVector P4, TVector3 Vtx, Int_t id)
		{
			momentumMCElectron_ = P4;
			vertexMCElectron_ = Vtx;
			pdgIdMCElectron_ = id;
		}
		void setMCId(Int_t id){pdgIdMCElectron_ = id;};
		void setMCP4(TLorentzVector P4){momentumMCElectron_ = P4;};
		void setMCVertex(TVector3 Vtx){vertexMCElectron_ = Vtx;};

		Float_t fbrem()const{return fBrem_;};
		Int_t numberOfBrems()const{return (basicClusterSize() - 1);};
		//setter
		void setFbrem(float f){fBrem_ = f;};
		//getter
		Int_t classification()const{return classification_;};
		//setter
		void setClassification(int i){classification_ = i;};
		bool isFromConversion()const
		{
			return ((bool)isConversion);
		}
		void setConversion(bool is)
		{
			isConversion = is;
		}
		bool hasTriggerMatch(std::string input)const
		{
			if(input == "HLT_Ele10_SW_L1R") return HLT_Ele10_SW_L1R ;
			if(input == "HLT_Ele15_SW_L1R") return HLT_Ele15_SW_L1R;
        return false;
		}
		void setTriggerinfo(std::string input, bool is)
		{
			if(input == "HLT_Ele10_SW_L1R") HLT_Ele10_SW_L1R = is;
			if(input == "HLT_Ele15_SW_L1R") HLT_Ele15_SW_L1R = is;
		}
	
		ClassDef (TRootElectron,9);
	};
}

//typedef std::pair<int,double> IntDoublePair;
//typedef std::pair<TRootElectron,std::vector<std::pair<int,double> > > MassPair;
#endif
