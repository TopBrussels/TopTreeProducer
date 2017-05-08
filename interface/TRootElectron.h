#ifndef TRootElectron_h
#define TRootElectron_h

#include <map>
#include <iostream>
#include <TLorentzVector.h>


#include "../interface/TRootLepton.h"

using namespace std;

namespace TopTree {
class TRootElectron : public TRootLepton {

    public:
        TRootElectron() :
            TRootLepton(),
            trackerDrivenSeed_(false),
            ecalDrivenSeed_(false),
            ecalDrivenMomentum_(),
            eSuperClusterOverPin_(-9999.),
            eEleClusterOverPout_(-9999.),
            eSeedClusterOverPout_(-9999.),
            deltaEtaIn_(-9999.),
            deltaEtaOut_(-9999.),
            deltaPhiIn_(-9999.),
            deltaPhiOut_(-9999.),
            deltaPhiSuperClusterTrackAtCalo_(-9999.),
            deltaEtaSuperClusterTrackAtCalo_(-9999.),
	    isEBEEGap_(false),
            ioEmIoP_(9999.),
            ioEmIoPgsf_(9999.),
            pixelLayersWithMeasurement_(-9999),
            stripLayersWithMeasurement_(-9999),
            nValidHits_(-9999),
            missingHits_(-9999),
            normalizedChi2_(9999.),
            normalizedChi2gsf_(9999.),
            chi2_(9999.),
            ndof_(9999),
            superClusterRawEnergy_(-9999.),
            superClusterEta_(-9999.),
            preshowerEnergy_(-9999.),
            sigmaIetaIeta_(-9999.),
	    sigmaIetaIeta_full5x5_(-9999.),
            sigmaIphiIphi_(-9999.),
            sigmaIetaIphi_(-9999.),
            e1x5_(-9999.),
            e5x5_(-9999.),
            hcalDepth1OverEcal_(-9999.),
            hcalDepth2OverEcal_(-9999.),
            etaWidth_(-9999.),
            phiWidth_(-9999.),
            unCalibratedPt_(-9999.),
            r9_(9999.),
            fBrem_(-9999.),
            nBrems_(-9999),
            passConversion_(false),
	    isGsfCtfScPixChargeConsistent_(false),
            isMVA_TightID_(false),
            isMVA_MediumID_(false),
            isMVA_LooseID_(false),
            isCB_HeepID_(false),
            isCB_TightID_(false),
            isCB_MediumID_(false),
            isCB_LooseID_(false),
            isCB_VetoID_(false),
            MVA_value_(-9999.),
            MVA_category_(-9999){
            ;
            }
        TRootElectron(const TRootLepton& l) :
            TRootLepton(l),
            trackerDrivenSeed_(false),
            ecalDrivenSeed_(false),
            ecalDrivenMomentum_(),
            eSuperClusterOverPin_(-9999.),
            eEleClusterOverPout_(-9999.),
            eSeedClusterOverPout_(-9999.),
            deltaEtaIn_(-9999.),
            deltaEtaOut_(-9999.),
            deltaPhiIn_(-9999.),
            deltaPhiOut_(-9999.),
            deltaPhiSuperClusterTrackAtCalo_(-9999.),
            deltaEtaSuperClusterTrackAtCalo_(-9999.),
	          isEBEEGap_(false),
            ioEmIoP_(9999.),
            ioEmIoPgsf_(9999.),
            pixelLayersWithMeasurement_(-9999),
            stripLayersWithMeasurement_(-9999),
            nValidHits_(-9999),
            missingHits_(-9999),
            normalizedChi2_(9999.),
            normalizedChi2gsf_(9999.),
            chi2_(9999.),
            ndof_(9999),
            superClusterRawEnergy_(-9999.),
            superClusterEta_(-9999.),
            preshowerEnergy_(-9999.),
            sigmaIetaIeta_(-9999.),
            sigmaIetaIeta_full5x5_(-9999.),
            sigmaIphiIphi_(-9999.),
            sigmaIetaIphi_(-9999.),
            e1x5_(-9999.),
            e5x5_(-9999.),
            hcalDepth1OverEcal_(-9999.),
            hcalDepth2OverEcal_(-9999.),
            etaWidth_(-9999.),
            phiWidth_(-9999.),
            unCalibratedPt_(-9999.),
            r9_(9999.),
            fBrem_(-9999.),
            nBrems_(-9999),
            passConversion_(false),
	    isGsfCtfScPixChargeConsistent_(false),
            isMVA_TightID_(false),
            isMVA_MediumID_(false),
            isMVA_LooseID_(false),
            isCB_HeepID_(false),
            isCB_TightID_(false),
            isCB_MediumID_(false),
            isCB_LooseID_(false),
            isCB_VetoID_(false),
            MVA_value_(-9999.),
            MVA_category_(-9999){
            ;
            }
        TRootElectron(const TRootElectron& e) :
            TRootLepton(e),
            trackerDrivenSeed_(e.trackerDrivenSeed_),
            ecalDrivenSeed_(e.ecalDrivenSeed_),
            ecalDrivenMomentum_(e.ecalDrivenMomentum_),
            eSuperClusterOverPin_(e.eSuperClusterOverPin_),
            eEleClusterOverPout_(e.eEleClusterOverPout_),
            eSeedClusterOverPout_(e.eSeedClusterOverPout_),
            deltaEtaIn_(e.deltaEtaIn_),
            deltaEtaOut_(e.deltaEtaOut_),
            deltaPhiIn_(e.deltaPhiIn_),
            deltaPhiOut_(e.deltaPhiOut_),
            deltaPhiSuperClusterTrackAtCalo_(e.deltaPhiSuperClusterTrackAtCalo_),
            deltaEtaSuperClusterTrackAtCalo_(e.deltaEtaSuperClusterTrackAtCalo_),
	    isEBEEGap_(e.isEBEEGap_),
            ioEmIoP_(e.ioEmIoP_),
            ioEmIoPgsf_(e.ioEmIoPgsf_),
            pixelLayersWithMeasurement_(e.pixelLayersWithMeasurement_),
            stripLayersWithMeasurement_(e.stripLayersWithMeasurement_),
            nValidHits_(e.nValidHits_),
            missingHits_(e.missingHits_),
            normalizedChi2_(e.normalizedChi2_),
            normalizedChi2gsf_(e.normalizedChi2gsf_),
            chi2_(e.chi2_),
            ndof_(e.ndof_),
            superClusterRawEnergy_(e.superClusterRawEnergy_),
            superClusterEta_(e.superClusterEta_),
            preshowerEnergy_(e.preshowerEnergy_),
            sigmaIetaIeta_(e.sigmaIetaIeta_),
            sigmaIetaIeta_full5x5_(e.sigmaIetaIeta_full5x5_),
            sigmaIphiIphi_(e.sigmaIphiIphi_),
            sigmaIetaIphi_(e.sigmaIetaIphi_),
            e1x5_(e.e1x5_),
            e5x5_(e.e5x5_),
            hcalDepth1OverEcal_(e.hcalDepth1OverEcal_),
            hcalDepth2OverEcal_(e.hcalDepth2OverEcal_),
            etaWidth_(e.etaWidth_),
            phiWidth_(e.phiWidth_),
            unCalibratedPt_(e.unCalibratedPt_),
            r9_(e.r9_),
            fBrem_(e.fBrem_),
            nBrems_(e.nBrems_),
            passConversion_(e.passConversion_),
	    isGsfCtfScPixChargeConsistent_(e.isGsfCtfScPixChargeConsistent_),
            isMVA_TightID_(e.isMVA_TightID_),
            isMVA_MediumID_(e.isMVA_MediumID_),
            isMVA_LooseID_(e.isMVA_LooseID_),
            isCB_HeepID_(e.isCB_HeepID_),
            isCB_TightID_(e.isCB_TightID_),
            isCB_MediumID_(e.isCB_MediumID_),
            isCB_LooseID_(e.isCB_LooseID_),
            isCB_VetoID_(e.isCB_VetoID_),
            MVA_value_(e.MVA_value_),
            MVA_category_(e.MVA_category_)
	    {
            ;
            }

        TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e) :
            TRootLepton(px,py,pz,e),
            trackerDrivenSeed_(false),
            ecalDrivenSeed_(false),
            ecalDrivenMomentum_(),
            eSuperClusterOverPin_(-9999.),
            eEleClusterOverPout_(-9999.),
            eSeedClusterOverPout_(-9999.),
            deltaEtaIn_(-9999.),
            deltaEtaOut_(-9999.),
            deltaPhiIn_(-9999.),
            deltaPhiOut_(-9999.),
            deltaPhiSuperClusterTrackAtCalo_(-9999.),
            deltaEtaSuperClusterTrackAtCalo_(-9999.),
	          isEBEEGap_(false),
            ioEmIoP_(9999.),
            ioEmIoPgsf_(9999.),
            pixelLayersWithMeasurement_(-9999),
            stripLayersWithMeasurement_(-9999),
            nValidHits_(-9999),
            missingHits_(-9999),
            normalizedChi2_(9999.),
            normalizedChi2gsf_(9999.),
            chi2_(9999.),
            ndof_(9999),
            superClusterRawEnergy_(-9999.),
            superClusterEta_(-9999.),
            preshowerEnergy_(-9999.),
            sigmaIetaIeta_(-9999.),
            sigmaIetaIeta_full5x5_(-9999.),
            sigmaIphiIphi_(-9999.),
            sigmaIetaIphi_(-9999.),
            e1x5_(-9999.),
            e5x5_(-9999.),
            hcalDepth1OverEcal_(-9999.),
            hcalDepth2OverEcal_(-9999.),
            etaWidth_(-9999.),
            phiWidth_(-9999.),
            unCalibratedPt_(-9999.),
            r9_(-9999.),
            fBrem_(-9999.),
            nBrems_(-9999),
            passConversion_(false),
	    isGsfCtfScPixChargeConsistent_(false),
            isMVA_TightID_(false),
            isMVA_MediumID_(false),
            isMVA_LooseID_(false),
            isCB_HeepID_(false),
            isCB_TightID_(false),
            isCB_MediumID_(false),
            isCB_LooseID_(false),
            isCB_VetoID_(false),
            MVA_value_(-9999.),
            MVA_category_(-9999){
            ;
            }

        TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
            TRootLepton(px,py,pz,e,vtx_x,vtx_y,vtx_z),
            trackerDrivenSeed_(false),
            ecalDrivenSeed_(false),
            ecalDrivenMomentum_(),
            eSuperClusterOverPin_(-9999.),
            eEleClusterOverPout_(-9999.),
            eSeedClusterOverPout_(-9999.),
            deltaEtaIn_(-9999.),
            deltaEtaOut_(-9999.),
            deltaPhiIn_(-9999.),
            deltaPhiOut_(-9999.),
            deltaPhiSuperClusterTrackAtCalo_(-9999.),
            deltaEtaSuperClusterTrackAtCalo_(-9999.),
	    isEBEEGap_(false),
            ioEmIoP_(9999.),
            ioEmIoPgsf_(9999.),
            pixelLayersWithMeasurement_(-9999),
            stripLayersWithMeasurement_(-9999),
            nValidHits_(-9999),
            missingHits_(-9999),
            normalizedChi2_(9999.),
            normalizedChi2gsf_(9999.),
            chi2_(9999.),
            ndof_(9999),
            superClusterRawEnergy_(-9999.),
            superClusterEta_(-9999.),
            preshowerEnergy_(-9999.),
            sigmaIetaIeta_(-9999.),
            sigmaIetaIeta_full5x5_(-9999.),
            sigmaIphiIphi_(-9999.),
            sigmaIetaIphi_(-9999.),
            e1x5_(-9999.),
            e5x5_(-9999.),
            hcalDepth1OverEcal_(-9999.),
            hcalDepth2OverEcal_(-9999.),
            etaWidth_(-9999.),
            phiWidth_(-9999.),
            unCalibratedPt_(-9999.),
            r9_(-9999.),
            fBrem_(-9999.),
            nBrems_(-9999),
            passConversion_(false),
	    isGsfCtfScPixChargeConsistent_(false),
            isMVA_TightID_(false),
            isMVA_MediumID_(false),
            isMVA_LooseID_(false),
            isCB_HeepID_(false),
            isCB_TightID_(false),
            isCB_MediumID_(false),
            isCB_LooseID_(false),
            isCB_VetoID_(false),
            MVA_value_(-9999.),
            MVA_category_(-9999)
	    {
            ;
            }

        TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Int_t charge) :
            TRootLepton(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge),
            trackerDrivenSeed_(false),
            ecalDrivenSeed_(false),
            ecalDrivenMomentum_(),
            eSuperClusterOverPin_(-9999.),
            eEleClusterOverPout_(-9999.),
            eSeedClusterOverPout_(-9999.),
            deltaEtaIn_(-9999.),
            deltaEtaOut_(-9999.),
            deltaPhiIn_(-9999.),
            deltaPhiOut_(-9999.),
            deltaPhiSuperClusterTrackAtCalo_(-9999.),
            deltaEtaSuperClusterTrackAtCalo_(-9999.),
	          isEBEEGap_(false),
            ioEmIoP_(9999.),
            ioEmIoPgsf_(9999.),
            pixelLayersWithMeasurement_(-9999),
            stripLayersWithMeasurement_(-9999),
            nValidHits_(-9999),
            missingHits_(-9999),
            normalizedChi2_(9999.),
            normalizedChi2gsf_(9999.),
            chi2_(9999.),
            ndof_(9999),
            superClusterRawEnergy_(-9999.),
            superClusterEta_(-9999.),
            preshowerEnergy_(-9999.),
            sigmaIetaIeta_(-9999.),
            sigmaIetaIeta_full5x5_(-9999.),
            sigmaIphiIphi_(-9999.),
            sigmaIetaIphi_(-9999.),
            e1x5_(-9999.),
            e5x5_(-9999.),
            hcalDepth1OverEcal_(-9999.),
            hcalDepth2OverEcal_(-9999.),
            etaWidth_(-9999.),
            phiWidth_(-9999.),
            unCalibratedPt_(-9999.),
            r9_(-9999.),
            fBrem_(-9999.),
            nBrems_(-9999),
            passConversion_(false),
	    isGsfCtfScPixChargeConsistent_(false),
            isMVA_TightID_(false),
            isMVA_MediumID_(false),
            isMVA_LooseID_(false),
            isCB_HeepID_(false),
            isCB_TightID_(false),
            isCB_MediumID_(false),
            isCB_LooseID_(false),
            isCB_VetoID_(false),
            MVA_value_(-9999.),
            MVA_category_(-9999){
            ;
            }

        TRootElectron(const TLorentzVector &momentum) :
            TRootLepton(momentum),
            trackerDrivenSeed_(false),
            ecalDrivenSeed_(false),
            ecalDrivenMomentum_(),
            eSuperClusterOverPin_(-9999.),
            eEleClusterOverPout_(-9999.),
            eSeedClusterOverPout_(-9999.),
            deltaEtaIn_(-9999.),
            deltaEtaOut_(-9999.),
            deltaPhiIn_(-9999.),
            deltaPhiOut_(-9999.),
            deltaPhiSuperClusterTrackAtCalo_(-9999.),
            deltaEtaSuperClusterTrackAtCalo_(-9999.),
	    isEBEEGap_(false),
            ioEmIoP_(9999.),
            ioEmIoPgsf_(9999.),
            pixelLayersWithMeasurement_(-9999),
            stripLayersWithMeasurement_(-9999),
            nValidHits_(-9999),
            missingHits_(-9999),
            normalizedChi2_(9999.),
            normalizedChi2gsf_(9999.),
            chi2_(9999.),
            ndof_(9999),
            superClusterRawEnergy_(-9999.),
            superClusterEta_(-9999.),
            preshowerEnergy_(-9999.),
            sigmaIetaIeta_(-9999.),
            sigmaIetaIeta_full5x5_(-9999.),
            sigmaIphiIphi_(-9999.),
            sigmaIetaIphi_(-9999.),
            e1x5_(-9999.),
            e5x5_(-9999.),
            hcalDepth1OverEcal_(-9999.),
            hcalDepth2OverEcal_(-9999.),
            etaWidth_(-9999.),
            phiWidth_(-9999.),
            unCalibratedPt_(-9999.),
            r9_(-9999.),
            fBrem_(-9999.),
            nBrems_(9999),
            passConversion_(false),
	    isGsfCtfScPixChargeConsistent_(false),
            isMVA_TightID_(false),
            isMVA_MediumID_(false),
            isMVA_LooseID_(false),
            isCB_HeepID_(false),
            isCB_TightID_(false),
            isCB_MediumID_(false),
            isCB_LooseID_(false),
            isCB_VetoID_(false),
            MVA_value_(-9999.),
            MVA_category_(-9999){
            ;
            }

        TRootElectron(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
            TRootLepton(momentum, vertex, type, charge),
            trackerDrivenSeed_(false),
            ecalDrivenSeed_(false),
            ecalDrivenMomentum_(),
            eSuperClusterOverPin_(-9999.),
            eEleClusterOverPout_(-9999.),
            eSeedClusterOverPout_(-9999.),
            deltaEtaIn_(-9999.),
            deltaEtaOut_(-9999.),
            deltaPhiIn_(-9999.),
            deltaPhiOut_(-9999.),
            deltaPhiSuperClusterTrackAtCalo_(-9999.),
            deltaEtaSuperClusterTrackAtCalo_(-9999.),
	    isEBEEGap_(false),
            ioEmIoP_(9999.),
            ioEmIoPgsf_(9999.),
            pixelLayersWithMeasurement_(-9999),
            stripLayersWithMeasurement_(-9999),
            nValidHits_(-9999),
            missingHits_(-9999),
            normalizedChi2_(9999.),
            normalizedChi2gsf_(9999.),
            chi2_(9999.),
            ndof_(9999),
            superClusterRawEnergy_(-9999.),
            superClusterEta_(-9999.),
            preshowerEnergy_(-9999.),
            sigmaIetaIeta_(-9999.),            
	    sigmaIetaIeta_full5x5_(-9999.),
            sigmaIphiIphi_(-9999.),
            sigmaIetaIphi_(-9999.),
            e1x5_(-9999.),
            e5x5_(-9999.),
            hcalDepth1OverEcal_(-9999.),
            hcalDepth2OverEcal_(-9999.),
            etaWidth_(-9999.),
            phiWidth_(-9999.),
            unCalibratedPt_(-9999.),
            r9_(-9999.),
            fBrem_(-9999.),
            nBrems_(9999),
            passConversion_(false),
	    isGsfCtfScPixChargeConsistent_(false),
            isMVA_TightID_(false),
            isMVA_MediumID_(false),
            isMVA_LooseID_(false),
            isCB_HeepID_(false),
            isCB_TightID_(false),
            isCB_MediumID_(false),
            isCB_LooseID_(false),
            isCB_VetoID_(false),
            MVA_value_(-9999.),
            MVA_category_(-9999){
            ;
            }

        ~TRootElectron() {
            ;
            }


    public:
        virtual TString typeName() const {
            return "TRootElectron";
            }

        Bool_t isEcalDrivenSeed() const {
            return ecalDrivenSeed_;
            }
        Bool_t isTrackerDrivenSeed() const {
            return trackerDrivenSeed_;
            }

        TLorentzVector ecalDrivenMomentum() const {
            return ecalDrivenMomentum_;
            }

        Float_t eScOverP() const {
            return eSuperClusterOverPin_;
            }
        Float_t eEleClusterOverPout() const {
            return eEleClusterOverPout_;
            }
        Float_t eSeedClusterOverPout() const {
            return eSeedClusterOverPout_;
            }
        Float_t deltaEtaIn() const {
            return deltaEtaIn_;
            }
        Float_t deltaEtaOut() const {
            return deltaEtaOut_;
            }
        Float_t deltaPhiIn() const {
            return deltaPhiIn_;
            }
        Float_t deltaPhiOut() const {
            return deltaPhiOut_;
            }
        Float_t deltaPhiScTrkOut() const {
            return deltaPhiSuperClusterTrackAtCalo_;
            }
        Float_t deltaEtaScTrkOut() const {
            return deltaEtaSuperClusterTrackAtCalo_;
            }
        Float_t isEBEEGap() const {
	    return isEBEEGap_;
            }
        Float_t ioEmIoP() const {
            return ioEmIoP_;
            }
        Float_t ioEmIoPgsf() const {
            return ioEmIoPgsf_;
            }

        Int_t trackPixelLayersWithMeasurement() const {
            return pixelLayersWithMeasurement_;
            }
        Int_t trackStripLayersWithMeasurement() const {
            return stripLayersWithMeasurement_;
            }
        Int_t trackerLayersWithMeasurement() const {
            return pixelLayersWithMeasurement_+stripLayersWithMeasurement_;
            }
        Int_t trackNValidHits() const {
            return nValidHits_;
            }
        Int_t missingHits() const {
            return missingHits_;
            }
        Float_t trackNormalizedChi2() const {
            return normalizedChi2_;
            }
        Float_t gsfTrackNormalizedChi2() const {
            return normalizedChi2gsf_;
            }
        Float_t gsfTrackChi2() const{
            return chi2_;
            }
        Int_t gsfTrackNdof() const{
            return ndof_;
            }
        Float_t superClusterRawEnergy() const {
            return superClusterRawEnergy_;
            }
        Float_t superClusterEta() const {
            return superClusterEta_;
            }
        Float_t preshowerEnergy() const {
            return preshowerEnergy_;
            }
        Float_t sigmaIEtaIEta() const {
            return sigmaIetaIeta_;
            }
        Float_t sigmaIEtaIEta_full5x5() const {
            return sigmaIetaIeta_full5x5_;
            }
        Float_t sigmaIPhiIPhi() const {
            return sigmaIphiIphi_;
            }
        Float_t sigmaIEtaIPhi() const {
            return sigmaIetaIphi_;
            }
        Float_t e1x5() const {
            return e1x5_;
            }
        Float_t e5x5() const {
            return e5x5_;
            }
        Float_t hadronicOverEm() const {
            return (hcalDepth1OverEcal_ + hcalDepth2OverEcal_);
            }
        Float_t hadronicDepth1OverEm() const {
            return hcalDepth1OverEcal_;
            }
        Float_t hadronicDepth2OverEm() const {
            return hcalDepth2OverEcal_;
            }
        Float_t etaWidth() const {
            return etaWidth_;
            }
        Float_t phiWidth() const {
            return phiWidth_;
            }
        Float_t unCalibratedPt() const {
            return unCalibratedPt_;
            }
        Float_t r9() const {
            return r9_;
            }

        Float_t fbrem() const {
            return fBrem_;
            }
        Int_t numberOfBrems() const {
            return nBrems_;
            }
        Bool_t passConversion() const {
            return passConversion_;
            }
	Bool_t isGsfCtfScPixChargeConsistent() const {
            return isGsfCtfScPixChargeConsistent_;
            }
        Bool_t isMVA_TightID() const {
            return isMVA_TightID_;
            }
        Bool_t isMVA_MediumID() const {
            return isMVA_MediumID_;
            }
        Bool_t isMVA_LooseID() const {
            return isMVA_LooseID_;
            }
        Bool_t isCB_HeepID() const {
            return isCB_HeepID_;
            }
        Bool_t isCB_TightID() const {
            return isCB_TightID_;
            }
        Bool_t isCB_MediumID() const {
            return isCB_MediumID_;
            }
        Bool_t isCB_LooseID() const {
            return isCB_LooseID_;
            }
        Bool_t isCB_VetoID() const {
            return isCB_VetoID_;
            }
        Float_t MVA_value() const {
            return MVA_value_;
            }
        Int_t MVA_category() const {
            return MVA_category_;
            }
	

        //setters
        void setEcalSeeding(Bool_t isEcal) {
            ecalDrivenSeed_ = isEcal;
            }
        void setEcalDrivenMomentum(TLorentzVector ecalDrivenMomentum) {
            ecalDrivenMomentum_ = ecalDrivenMomentum;
            }
        void setTrackerSeeding(Bool_t isTracker) {
            trackerDrivenSeed_ = isTracker;
            }
        void setDeltaEtaIn(Float_t deltaEtaIn) {
            deltaEtaIn_ = deltaEtaIn;
            }
        void setDeltaEtaOut(Float_t deltaEtaOut) {
            deltaEtaOut_ = deltaEtaOut;
            }
        void setDeltaEtaSuperClusterTrackAtCalo(Float_t x) {
            deltaEtaSuperClusterTrackAtCalo_ = x;
            }
        void setIsEBEEGap (Bool_t x) {
            isEBEEGap_ = x;
            }
        void setDeltaPhiIn(Float_t deltaPhiIn) {
            deltaPhiIn_ = deltaPhiIn;
            }
        void setDeltaPhiOut(Float_t deltaPhiOut) {
            deltaPhiOut_ = deltaPhiOut;
            }
        void setDeltaPhiSuperClusterTrackAtCalo(Float_t x) {
            deltaPhiSuperClusterTrackAtCalo_ = x;
            }
        void setEnergySuperClusterOverP(Float_t x) {
            eSuperClusterOverPin_ = x;
            }
        void setEnergyEleClusterOverPout(Float_t x) {
            eEleClusterOverPout_ = x;
            }
        void setEnergySeedClusterOverPout(Float_t x) {
            eSeedClusterOverPout_ = x;
            }
        void setIoEmIoP(Float_t x) {
            ioEmIoP_ = x;
            }
        void setIoEmIoPgsf(Float_t x) {
            ioEmIoPgsf_ = x;
            }

        void setTrackMissingHits(Int_t x) {
            missingHits_ = x;
            }
        void setTrackNormalizedChi2(Float_t x) {
            normalizedChi2_ = x;
            }
        void setGsfTrackNormalizedChi2(Float_t x) {
            normalizedChi2gsf_ = x;
            }
        void setGsfTrackChi2(Float_t x) {
            chi2_ = x;
            }
        void setGsfTrackNdof(Float_t x) {
            ndof_ = x;
            }
        void setPixelLayersWithMeasurement(Int_t x) {
            pixelLayersWithMeasurement_ = x;
            }
        void setStripLayersWithMeasurement(Int_t stripLayersWithMeasurement) {
            stripLayersWithMeasurement_ = stripLayersWithMeasurement;
            }
        void setNValidHits(Int_t nHits) {
            nValidHits_ = nHits;
            }

        void setPreshowerEnergy(Float_t x) {
            preshowerEnergy_ = x;
            }
        void setSuperClusterRawEnergy(Float_t x) {
            superClusterRawEnergy_ = x;
            }
        void setSuperClusterEta(Float_t x) {
            superClusterEta_ = x;
            }

        void setE1x5(Float_t e1x5) {
            e1x5_ = e1x5;
            }
        void setE5x5(Float_t e5x5) {
            e5x5_ = e5x5;
            }
        void setHoverEDepth1(Float_t HoE1) {
            hcalDepth1OverEcal_ = HoE1;
            }
        void setHoverEDepth2(Float_t HoE2) {
            hcalDepth2OverEcal_ = HoE2;
            }
        void setSigmaIetaIeta(Float_t sieie) {
            sigmaIetaIeta_ = sieie;
            }
        void setSigmaIetaIeta_full5x5(Float_t sieie) {
            sigmaIetaIeta_full5x5_ = sieie;
            }
        void setSigmaIphiIphi(Float_t sipip) {
            sigmaIphiIphi_ = sipip;
            }
        void setSigmaIetaIphi(Float_t sieip) {
            sigmaIetaIphi_ = sieip;
            }
        void setEtaWidth(Float_t etaWidth) {
            etaWidth_ = etaWidth;
            }
        void setPhiWidth(Float_t phiWidth) {
            phiWidth_ = phiWidth;
            }
        void setunCalibratedPt(Float_t unCalibratedPt) {
            unCalibratedPt_ = unCalibratedPt;
            }
        void setR9(Float_t r9) {
            r9_ = r9;
            }

        void setFbrem(Float_t f) {
            fBrem_ = f;
            }
        void setNBrems(Int_t n) {
            nBrems_ = n;
            }
        void setPassConversion(Bool_t pass) {
            passConversion_ = pass;
            }
	void setIsGsfCtfScPixChargeConsistent(Bool_t x) {
            isGsfCtfScPixChargeConsistent_ = x;
            }
        void setisMVA_TightID(Bool_t pass) {
            isMVA_TightID_ = pass;
            }
        void setisMVA_MediumID(Bool_t pass) {
            isMVA_MediumID_ = pass;
            }
        void setisMVA_LooseID(Bool_t pass) {
            isMVA_LooseID_ = pass;
            }
        void setisCB_HeepID(Bool_t pass) {
            isCB_HeepID_ = pass;
            }
        void setisCB_TightID(Bool_t pass) {
            isCB_TightID_ = pass;
            }
        void setisCB_MediumID(Bool_t pass) {
            isCB_MediumID_ = pass;
            }
        void setisCB_LooseID(Bool_t pass) {
            isCB_LooseID_ = pass;
            }
        void setisCB_VetoID(Bool_t pass) {
            isCB_VetoID_ = pass;
            }
        void setMVA_value(Float_t value) {
            MVA_value_ = value;
            }
        void setMVA_category(Int_t category) {
            MVA_category_ = category;
            }
	
        friend std::ostream& operator<< (std::ostream& stream, const TRootElectron& electron) {
            stream << "TRootElectron - Charge=" << electron.charge() << " (Et,eta,phi)=("<< electron.Et() <<","<< electron.Eta() <<","<< electron.Phi() << ")"
            << " vertex(x,y,z)=("<< electron.vx() <<","<< electron.vy() <<","<< electron.vz() << ")";
            return stream;
            };


    private:
        Bool_t trackerDrivenSeed_;
        Bool_t ecalDrivenSeed_;
        TLorentzVector ecalDrivenMomentum_;        // ecal driven momentum, equivalent to gsf electron momentum.
        Float_t eSuperClusterOverPin_;             // the supercluster energy / track momentum at the PCA to the beam spot
        Float_t eEleClusterOverPout_;              // the electron cluster energy / track momentum at calo extrapolated from the outermost track state
        Float_t eSeedClusterOverPout_;             // the seed cluster energy / track momentum at calo extrapolated from the outermost track state
        Float_t deltaEtaIn_;                       // the supercluster eta - track eta position at calo extrapolated from innermost track state
        Float_t deltaEtaOut_;                      // the seed cluster eta - track eta position at calo extrapolated from the outermost track state
        Float_t deltaPhiIn_;                       // the supercluster phi - track phi position at calo extrapolated from the innermost track state
        Float_t deltaPhiOut_;                      // the seed cluster phi - track phi position at calo extrapolated from the outermost track state
        Float_t deltaPhiSuperClusterTrackAtCalo_;  // the electron cluster phi - track phi position at calo extrapolated from the outermost track state
        Float_t deltaEtaSuperClusterTrackAtCalo_;  // the electron cluster eta - t
        Bool_t isEBEEGap_;                         // electron in ecal crack region
        Float_t ioEmIoP_;                          // (1.0/(ele.superCluster()->energy())) - (1.0 / ele.p())
        Float_t ioEmIoPgsf_;                       // (1.0/(ele.superCluster()->energy())) - (1.0 / ele.gsfTrack()->p())
	
        //TrackProperties=====================================
        Int_t pixelLayersWithMeasurement_;         // number of pixel layers with at least one valid hit
        Int_t stripLayersWithMeasurement_;         // number of strip layers with at least one valid hit
        Int_t nValidHits_;                         // number of valid hits

        // In the standard PAT configuration, dB and edB are calculated wrt the primary vertex
        // If this was not the case, dB is calculated wrt the beamspot and edb = -1 all the time
        //Float_t dB_;                             // dB from PAT muon
        //Float_t dBError_;                        // dBError from PAT muon
        Int_t missingHits_;                        // Conversion Rejection: number of missing hits near beginning of track (also rejects really bad tracks)
        Float_t normalizedChi2_;                   // chi-squared divided by n.d.o.f. of track fit
        Float_t normalizedChi2gsf_;                // chi2 / ndf from gsfTrack
        Float_t chi2_;                              // Un-normalized Chi2
        Int_t ndof_;                                // Number of Degrees of Freedom

        //SuperClusterProperties ===============================
        Float_t superClusterRawEnergy_;
        Float_t superClusterEta_;
        Float_t preshowerEnergy_;

        //ShowerShape===========================================
        Float_t sigmaIetaIeta_;                    // weighted cluster rms along eta 
        Float_t sigmaIetaIeta_full5x5_;                    // weighted cluster rms along eta and inside 5x5 
        Float_t sigmaIphiIphi_;
        Float_t sigmaIetaIphi_;
        Float_t e1x5_;                             // energy inside 1x5 in etaxphi around the seed Xtal
        Float_t e5x5_;                             // energy inside 5x5 in etaxphi around the seed Xtal
        Float_t hcalDepth1OverEcal_ ;              // hcal over ecal seed cluster energy using first hcal depth (hcal is energy of towers within dR=015)
        Float_t hcalDepth2OverEcal_ ;              // hcal over ecal seed cluster energy using 2nd hcal depth (hcal is energy of towers within dR=015)
        Float_t etaWidth_;
        Float_t phiWidth_;
        Float_t unCalibratedPt_;
        Float_t r9_;

        // Electron classification && fBrem ====================
        Float_t fBrem_;                            // brem fraction from gsf fit: (track momentum in - track momentum out) / track momentum in
        Int_t   nBrems_;                           // number of basic clusters inside the supercluster - 1
        Bool_t  passConversion_;                   // boolean to flag converted candidates
	
	//// Charge info ===================
	Bool_t isGsfCtfScPixChargeConsistent_;     //boolean to match 3 charge agreement cut - select the selective method of charge measurements and it should be true in the analysis  same sign electrons 
	
        
	      Bool_t isMVA_TightID_; // Tight ID from MVA electrons. Newly implemented in 2016, according to https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
        Bool_t isMVA_MediumID_;// Medium ID from MVA electrons. Newly implemented in 2016, according to https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
        Bool_t isMVA_LooseID_;// Loose ID from MVA electrons. Newly implemented in 2016, according to https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
        Bool_t isCB_HeepID_;
        Bool_t isCB_TightID_;
        Bool_t isCB_MediumID_;
        Bool_t isCB_LooseID_;
        Bool_t isCB_VetoID_;

        Float_t MVA_value_; // MVA value of MVA electrons. Newly implemented in 2016, according to https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
        Float_t MVA_category_; // Catefory of MVA electrons. Newly implemented in 2016, according to https://twiki.cern.ch/twiki/bin/view/CMS/MultivariateElectronIdentificationRun2
	

        ClassDef (TRootElectron,16);
    };
}

#endif
