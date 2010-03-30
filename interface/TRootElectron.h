#ifndef TRootElectron_h
#define TRootElectron_h

#include <map>
#include <iostream>
#include <TLorentzVector.h>


#include "../interface/TRootParticle.h"

using namespace std;

class TRootElectron : public TRootParticle
{

public:

	TRootElectron() : TRootParticle(){
            setChargeInfo(100,false, false,false);
            setSeedingInfo(false, false);
            setTrackClusterMatching(-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.);
            TVector3 tmp(-1000.,-1000.,-1000.);
            setTrackProperties(-9999., -9999., -9999., -9999.,-9999.,-9999, -9999, -9999., -9999, -9999.,tmp, tmp, -9999., -9999.,-9999.);
            setCorrections(-9999., -9999., -9999.,false,false,-9999., -9999., -9999.);
            setSuperCluster(tmp,-9999, -9999,-9999.,-9999,-9999., -9999.);
            setShowerShape(-9999., -9999., -9999.,-9999.,-9999.,-9999., -9999., -9999.,-9999.,-9999.);
            setFiducialFlags(false, false,false, false, false,false, false);
            Isolation tmpIso = makeIsolation(-9999.,-9999.,-9999.,-9999.,-9999);
            setIsolation(1, tmpIso);
            setIsolation(2, tmpIso);
            setIsolation(3, tmpIso);
            setIsolation(4, tmpIso);
            setIsolation(5, tmpIso);
            setIDs(-9999, -9999, -9999, -9999,-9999, -9999.,-9999., -9999, -9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999);
            TLorentzVector tmpP4(-1000.,-1000.,-1000.,-1000);
            setMCInfo(tmpP4,tmp,-9999);
            setClassification(-9999);
            setFbrem(-9999.);
            TriggerMatchingInfo tmpTrig;
            tmpTrig.clear();
            setTriggerInfo(tmpTrig);
            setConversion(true);
        }

	TRootElectron(const TRootElectron& e) :TRootParticle(e){
            
            setChargeInfo(e.Charge(),e.isGsfCtfScPixConsistent(),e.isGsfScPixConsistent(),e.isGsfCtfConsistent());
            setSeedingInfo(e.isEcalDrivenSeed(), e.isTrackerDrivenSeed());
            setTrackClusterMatching(e.eScOverPin(),e.eScOverPout(),e.eSeedOverPin(),e.eSeedOverPout(),e.deltaEtaIn(),e.deltaEtaOut(),e.deltaPhiIn(),e.deltaPhiOut(),e.deltaPhiScTrkOut(),e.deltaEtaScTrkOut());
            //TVector3 tmp(-1000.,-1000.,-1000.);
            setTrackProperties(e.trackMomentum(),e.trackMomentumAtSuperClusterPosition(),e.trackMomentumAtSeedClusterPosition(),e.trackMomentumAtElectronClusterPosition(),
            e.trackMomentumAtVtxWithConstraints(),e.trackPixelLayersWithMeasurement(),e.trackStripLayersWithMeasurement(),e.d0(),e.missingHits(),e.impactParameter(),
            e.trackPositionAtVtx(),e.trackPositionAtCalo(),e.trackDsz(),e.trackNormalizedChi2(),e.trackPtError());
            
            setCorrections(e.trackMomentumError(),e.caloEnergyError(),e.caloEnergy(),e.isCaloEnergyCorrected(),
            e.isMomentumCorrected(),e.electronMomentumError(),e.d0Error(),e.dszError());

            setSuperCluster(e.caloPosition(),e.basicClusterSize(), e.clusterAlgo(),e.caloConeSize(),e.nClusters(),e.superClusterRawEnergy(),e.preshowerEnergy());

            setShowerShape(e.sigmaEtaEta(),e.sigmaIEtaIEta(),e.e1x5(),e.e2x5Max(),e.e5x5(),e.e2x2(),e.e3x3(),e.eMax(),
            e.hadronicDepth1OverEm(),e.hadronicDepth2OverEm());

            setFiducialFlags(e.isEB(),e.isEE(), e.isEBEEGap(),e.isEBEtaGap(),e.isEBPhiGap(),e.isEEDeeGap(),e.isEERingGap());
            
//            Isolation tmpIso = makeIsolation(-9999.,-9999.,-9999.,-9999.,-9999);
            setIsolation(1, e.getIsolation(1));
            setIsolation(2, e.getIsolation(2));
            setIsolation(3, e.getIsolation(3));
            setIsolation(4, e.getIsolation(4));
            setIsolation(5, e.getIsolation(5));

            setIDs(e.isRobustLoose(),e.isRobustTight(),e.isRobustHighEnergy(),e.isLoose(),e.isTight(),e.LikelihoodId(),
            e.NeuralNetworkId(),e.CiCVeryLooseId(),e.CiCLooseId(),e.CiCMediumId(),e.CiCTightId(),e.CiCSuperTightId(),
            e.CiCHyperTightId_1(),e.CiCHyperTightId_3(),e.CiCHyperTightId_3(),e.CiCHyperTightId_4());

//            TLorentzVector tmpP4(-1000.,-1000.,-1000.,-1000);
            setMCInfo(e.MCP4(),e.MCVertex(),e.MCId());
            setClassification(e.classification());
            setFbrem(e.fbrem());
            setTriggerInfo(e.getTriggerInfo());
            setConversion(e.isFromConversion());
            
        }

	TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e) :TRootParticle(px,py,pz,e){
            setChargeInfo(100,false, false,false);
            setSeedingInfo(false, false);
            setTrackClusterMatching(-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.);
            TVector3 tmp(-1000.,-1000.,-1000.);
            setTrackProperties(-9999., -9999., -9999., -9999.,-9999.,-9999, -9999, -9999., -9999, -9999.,tmp, tmp, -9999., -9999.,-9999.);
            setCorrections(-9999., -9999., -9999.,false,false,-9999., -9999., -9999.);
            setSuperCluster(tmp,-9999, -9999,-9999.,-9999,-9999., -9999.);
            setShowerShape(-9999., -9999., -9999.,-9999.,-9999.,-9999., -9999., -9999.,-9999.,-9999.);
            setFiducialFlags(false, false,false, false, false,false, false);
            Isolation tmpIso = makeIsolation(-9999.,-9999.,-9999.,-9999.,-9999);
            setIsolation(1, tmpIso);
            setIsolation(2, tmpIso);
            setIsolation(3, tmpIso);
            setIsolation(4, tmpIso);
            setIsolation(5, tmpIso);
            setIDs(-9999, -9999, -9999, -9999,-9999, -9999.,-9999., -9999, -9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999);
            TLorentzVector tmpP4(-1000.,-1000.,-1000.,-1000);
            setMCInfo(tmpP4,tmp,-9999);
            setClassification(-9999);
            setFbrem(-9999.);
            TriggerMatchingInfo tmpTrig;
            tmpTrig.clear();
            setTriggerInfo(tmpTrig);
            setConversion(true);
        }
	
	TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
		TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z){
                        setChargeInfo(100,false, false,false);
            setSeedingInfo(false, false);
            setTrackClusterMatching(-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.);
            TVector3 tmp(-1000.,-1000.,-1000.);
            setTrackProperties(-9999., -9999., -9999., -9999.,-9999.,-9999, -9999, -9999., -9999, -9999.,tmp, tmp, -9999., -9999.,-9999.);
            setCorrections(-9999., -9999., -9999.,false,false,-9999., -9999., -9999.);
            setSuperCluster(tmp,-9999, -9999,-9999.,-9999,-9999., -9999.);
            setShowerShape(-9999., -9999., -9999.,-9999.,-9999.,-9999., -9999., -9999.,-9999.,-9999.);
            setFiducialFlags(false, false,false, false, false,false, false);
            Isolation tmpIso = makeIsolation(-9999.,-9999.,-9999.,-9999.,-9999);
            setIsolation(1, tmpIso);
            setIsolation(2, tmpIso);
            setIsolation(3, tmpIso);
            setIsolation(4, tmpIso);
            setIsolation(5, tmpIso);
            setIDs(-9999, -9999, -9999, -9999,-9999, -9999.,-9999., -9999, -9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999);
            TLorentzVector tmpP4(-1000.,-1000.,-1000.,-1000);
            setMCInfo(tmpP4,tmp,-9999);
            setClassification(-9999);
            setFbrem(-9999.);
            TriggerMatchingInfo tmpTrig;
            tmpTrig.clear();
            setTriggerInfo(tmpTrig);
            setConversion(true);

        }
		
	

	TRootElectron(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Int_t charge) :
		TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge){
            setChargeInfo(charge,false, false,false);
            setSeedingInfo(false, false);
            setTrackClusterMatching(-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.);
            TVector3 tmp(-1000.,-1000.,-1000.);
            setTrackProperties(-9999., -9999., -9999., -9999.,-9999.,-9999, -9999, -9999., -9999, -9999.,tmp, tmp, -9999., -9999.,-9999.);
            setCorrections(-9999., -9999., -9999.,false,false,-9999., -9999., -9999.);
            setSuperCluster(tmp,-9999, -9999,-9999.,-9999,-9999., -9999.);
            setShowerShape(-9999., -9999., -9999.,-9999.,-9999.,-9999., -9999., -9999.,-9999.,-9999.);
            setFiducialFlags(false, false,false, false, false,false, false);
            Isolation tmpIso = makeIsolation(-9999.,-9999.,-9999.,-9999.,-9999);
            setIsolation(1, tmpIso);
            setIsolation(2, tmpIso);
            setIsolation(3, tmpIso);
            setIsolation(4, tmpIso);
            setIsolation(5, tmpIso);
            setIDs(-9999, -9999, -9999, -9999,-9999, -9999.,-9999., -9999, -9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999);
            TLorentzVector tmpP4(-1000.,-1000.,-1000.,-1000);
            setMCInfo(tmpP4,tmp,-9999);
            setClassification(-9999);
            setFbrem(-9999.);
            TriggerMatchingInfo tmpTrig;
            tmpTrig.clear();
            setTriggerInfo(tmpTrig);
            setConversion(true);
        }
		

	TRootElectron(const TLorentzVector &momentum) :
		TRootParticle(momentum){
            setChargeInfo(100,false, false,false);
            setSeedingInfo(false, false);
            setTrackClusterMatching(-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.);
            TVector3 tmp(-1000.,-1000.,-1000.);
            setTrackProperties(-9999., -9999., -9999., -9999.,-9999.,-9999, -9999, -9999., -9999, -9999.,tmp, tmp, -9999., -9999.,-9999.);
            setCorrections(-9999., -9999., -9999.,false,false,-9999., -9999., -9999.);
            setSuperCluster(tmp,-9999, -9999,-9999.,-9999,-9999., -9999.);
            setShowerShape(-9999., -9999., -9999.,-9999.,-9999.,-9999., -9999., -9999.,-9999.,-9999.);
            setFiducialFlags(false, false,false, false, false,false, false);
            Isolation tmpIso = makeIsolation(-9999.,-9999.,-9999.,-9999.,-9999);
            setIsolation(1, tmpIso);
            setIsolation(2, tmpIso);
            setIsolation(3, tmpIso);
            setIsolation(4, tmpIso);
            setIsolation(5, tmpIso);
            setIDs(-9999, -9999, -9999, -9999,-9999, -9999.,-9999., -9999, -9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999);
            TLorentzVector tmpP4(-1000.,-1000.,-1000.,-1000);
            setMCInfo(tmpP4,tmp,-9999);
            setClassification(-9999);
            setFbrem(-9999.);
            TriggerMatchingInfo tmpTrig;
            tmpTrig.clear();
            setTriggerInfo(tmpTrig);
            setConversion(true);
        }


	TRootElectron(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
		TRootParticle(momentum, vertex, type,charge)
        {
            setChargeInfo(charge,false, false,false);
            setSeedingInfo(false, false);
            setTrackClusterMatching(-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.,-9999.);
            TVector3 tmp(-1000.,-1000.,-1000.);
            setTrackProperties(-9999., -9999., -9999., -9999.,-9999.,-9999, -9999, -9999., -9999, -9999.,tmp, tmp, -9999., -9999.,-9999.);
            setCorrections(-9999., -9999., -9999.,false,false,-9999., -9999., -9999.);
            setSuperCluster(tmp,-9999, -9999,-9999.,-9999,-9999., -9999.);
            setShowerShape(-9999., -9999., -9999.,-9999.,-9999.,-9999., -9999., -9999.,-9999.,-9999.);
            setFiducialFlags(false, false,false, false, false,false, false);
            Isolation tmpIso = makeIsolation(-9999.,-9999.,-9999.,-9999.,-9999);
            setIsolation(1, tmpIso);
            setIsolation(2, tmpIso);
            setIsolation(3, tmpIso);
            setIsolation(4, tmpIso);
            setIsolation(5, tmpIso);
            setIDs(-9999, -9999, -9999, -9999,-9999, -9999.,-9999., -9999, -9999,-9999,-9999,-9999,-9999,-9999,-9999,-9999);
            TLorentzVector tmpP4(-1000.,-1000.,-1000.,-1000);
            setMCInfo(tmpP4,tmp,-9999);
            setClassification(-9999);
            setFbrem(-9999.);
            TriggerMatchingInfo tmpTrig;
            tmpTrig.clear();
            setTriggerInfo(tmpTrig);
            setConversion(true);
        }

	~TRootElectron() {;}


	        
	virtual TString typeName() const { return "TRootElectron"; }


	friend std::ostream& operator<< (std::ostream& stream, const TRootElectron& electron) {
		stream << "TRootElectron - Charge=" << electron.charge() << " (Et,eta,phi)=("<< electron.Et() <<","<< electron.Eta() <<","<< electron.Phi() << ")"
				<< " vertex(x,y,z)=("<< electron.vx() <<","<< electron.vy() <<","<< electron.vz() << ")";
		return stream;
	};

        //ChargeInfo===================================
public:
    struct ChargeInfo
    {
       int scPixCharge ;
       bool isGsfCtfScPixConsistent ;
       bool isGsfScPixConsistent ;
       bool isGsfCtfConsistent ;
    } ;

    //getters
    ChargeInfo getChargeInfo()const{
        return thisChargeInfo;
    }
    int Charge()const{return thisChargeInfo.scPixCharge;}
    bool isGsfCtfScPixConsistent()const{return thisChargeInfo.isGsfCtfScPixConsistent;}
    bool isGsfScPixConsistent()const{return thisChargeInfo.isGsfScPixConsistent;}
    bool isGsfCtfConsistent()const{return thisChargeInfo.isGsfCtfConsistent;}

    //setters
    void setChargeInfo(int scPix,bool GsfCftScPix, bool GsfScPix, bool GsfCtf ){
        thisChargeInfo.scPixCharge = scPix;
        thisChargeInfo.isGsfCtfScPixConsistent = GsfCftScPix;
        thisChargeInfo.isGsfScPixConsistent = GsfScPix;
        thisChargeInfo.isGsfCtfConsistent = GsfCtf;
    }
    void setSuperClusterPixelCharge(int scPix ){ thisChargeInfo.scPixCharge = scPix;}
    void setSuperClusterPixelCtfGsfConsistency(bool GsfCftScPix){ thisChargeInfo.isGsfCtfScPixConsistent = GsfCftScPix;}
    void setSuperClusterPixelGsfConsistency(bool GsfScPix){ thisChargeInfo.isGsfScPixConsistent = GsfScPix;}
    void setGsfCtfConsistency(bool GsfCtf){ thisChargeInfo.isGsfCtfConsistent = GsfCtf;}

private:
    ChargeInfo thisChargeInfo;
    bool trackerDrivenSeed;
    bool ecalDrivenSeed;

//seedingInfo==========================
public:
    //setters
    void setSeedingInfo(bool isEcal, bool isTracker){
        ecalDrivenSeed = isEcal;
        trackerDrivenSeed = isTracker;
    }
    void setEcalSeeding(bool isEcal){ ecalDrivenSeed = isEcal;}
    void setTrackerSeeding(bool isTracker){ trackerDrivenSeed = isTracker;}

    //getters
    bool isEcalDrivenSeed()const{
        return ecalDrivenSeed;
    }
    bool isTrackerDrivenSeed()const{
        return trackerDrivenSeed;
    }

//TrackClusterMatching=======================

public:
     struct TrackClusterMatching
      {
        float eSuperClusterOverPin_ ;        // the supercluster energy / track momentum at the PCA to the beam spot
        float eSuperClusterOverPout_ ;       // the electron cluster energy / track momentum at calo extrapolated from the outermost track state
        float eSeedClusterOverPin_ ;         // the seed cluster energy / track momentum at the PCA to the beam spot
        float eSeedClusterOverPout_ ;      // the seed cluster energy / track momentum at calo extrapolated from the outermost track state
        float deltaEtaIn_ ; // the supercluster eta - track eta position at calo extrapolated from innermost track state
        float deltaEtaOut_ ; // the seed cluster eta - track eta position at calo extrapolated from the outermost track state
        float deltaPhiIn_ ; // the supercluster phi - track phi position at calo extrapolated from the innermost track state
        float deltaPhiOut_ ; // the seed cluster phi - track phi position at calo extrapolated from the outermost track state
        float deltaPhiSuperClusterTrackAtCalo_ ;  // the electron cluster phi - track phi position at calo extrapolated from the outermost track state
        float deltaEtaSuperClusterTrackAtCalo_ ;  // the electron cluster eta - track eta position at calo extrapolated from the outermost state
      } ;

      //getters:
      float eScOverPin()const{return myTrackClusterMatching.eSuperClusterOverPin_;};
      float eScOverPout()const{return myTrackClusterMatching.eSuperClusterOverPout_;};
      float eSeedOverPin()const{return myTrackClusterMatching.eSeedClusterOverPin_;};
      float eSeedOverPout()const{return myTrackClusterMatching.eSeedClusterOverPout_;};
      float deltaEtaIn()const{return myTrackClusterMatching.deltaEtaIn_;};
      float deltaEtaOut()const{return myTrackClusterMatching.deltaEtaOut_;};
      float deltaPhiIn()const{return myTrackClusterMatching.deltaPhiIn_;};
      float deltaPhiOut()const{return myTrackClusterMatching.deltaPhiOut_;};
      float deltaPhiScTrkOut()const{return myTrackClusterMatching.deltaPhiSuperClusterTrackAtCalo_;};
      float deltaEtaScTrkOut()const{return myTrackClusterMatching.deltaEtaSuperClusterTrackAtCalo_;};

      //setters
      void setTrackClusterMatching(float eScOverPin,float eScOverPout,float eSeedOverPin,float eSeedOverPout,float dEtaIn,
                                    float dEtaOut,float dPhiIn,float dPhiOut,float dPhiScTrkOut,float dEtaScTrkOut){
          myTrackClusterMatching.eSuperClusterOverPin_ = eScOverPin;
          myTrackClusterMatching.eSuperClusterOverPout_ = eScOverPout;
          myTrackClusterMatching.eSeedClusterOverPin_ = eSeedOverPin;
          myTrackClusterMatching.eSeedClusterOverPout_ = eSeedOverPout;
          myTrackClusterMatching.deltaEtaIn_ = dEtaIn;
          myTrackClusterMatching.deltaEtaOut_ = dEtaOut;
          myTrackClusterMatching.deltaPhiIn_ = dPhiIn;
          myTrackClusterMatching.deltaPhiOut_ = dPhiOut;
          myTrackClusterMatching.deltaPhiSuperClusterTrackAtCalo_ = dPhiScTrkOut;
          myTrackClusterMatching.deltaEtaSuperClusterTrackAtCalo_ = dEtaScTrkOut;
      }
        void setDeltaEtaIn(Float_t deltaEtaIn) { myTrackClusterMatching.deltaEtaIn_ = deltaEtaIn; }
        void setDeltaEtaOut(Float_t deltaEtaOut) { myTrackClusterMatching.deltaEtaOut_ = deltaEtaOut; }
        void setDeltaEtaSuperClusterTrackAtCalo(Float_t x) { myTrackClusterMatching.deltaEtaSuperClusterTrackAtCalo_ = x; }
        void setDeltaPhiIn(Float_t deltaPhiIn) { myTrackClusterMatching.deltaPhiIn_ = deltaPhiIn; }
        void setDeltaPhiOut(Float_t deltaPhiOut) { myTrackClusterMatching.deltaPhiOut_ = deltaPhiOut; }
        void setDeltaPhiSuperClusterTrackAtCalo(Float_t x) { myTrackClusterMatching.deltaPhiSuperClusterTrackAtCalo_ = x; }
        void setEnergySeedClusterOverPin(Float_t x) { myTrackClusterMatching.eSeedClusterOverPin_ = x; }
        void setEnergySeedClusterOverPout(Float_t x) { myTrackClusterMatching.eSeedClusterOverPout_ = x; }
        void setEnergySuperClusterOverPin(Float_t x) { myTrackClusterMatching.eSuperClusterOverPin_ = x; }
        void setEnergySuperClusterOverPout(Float_t x) { myTrackClusterMatching.eSuperClusterOverPout_ = x; }
      
private:

    TrackClusterMatching myTrackClusterMatching;


  //TrackProperties================================
  
public:
    struct TrackProperties{
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
    };
    //getters
    Float_t trackMomentum()const{return myTrackProperties_.trackMomentum_;};
    Float_t trackMomentumAtSuperClusterPosition()const{return myTrackProperties_.momentumAtCalo_;};
    Float_t trackMomentumAtSeedClusterPosition()const{return myTrackProperties_.momentumOut_;};
    Float_t trackMomentumAtElectronClusterPosition()const{return myTrackProperties_.momentumAtEleClus_;};
    Float_t trackMomentumAtVtxWithConstraints()const{return myTrackProperties_.momentumAtVtxWithConstraint_;};
    Int_t trackPixelLayersWithMeasurement()const{return myTrackProperties_.pixelLayersWithMeasurement_;};
    Int_t trackStripLayersWithMeasurement()const{return myTrackProperties_.stripLayersWithMeasurement_;};
    Float_t d0()const{return myTrackProperties_.d0_;};
    Int_t missingHits()const{return myTrackProperties_.missingHits_;};
    Float_t impactParameter()const{return myTrackProperties_.ip_;};
    TVector3 trackPositionAtVtx()const{return myTrackProperties_.positionAtVtx;};
    TVector3 trackPositionAtCalo()const{return myTrackProperties_.positionAtCalo;};
    Float_t trackDsz()const{return myTrackProperties_.dsz_;};
    Float_t trackNormalizedChi2()const{return myTrackProperties_.normalizedChi2_;};
    Float_t trackPtError()const{return myTrackProperties_.ptError_;};

    //setter
    void setTrackProperties(float p, float pAtSc, float pAtSeed, float pAtEleC,float pConstraint,
                            int pixelLayers, int stripLayers, float d0, int missingHits, float ip,
                            TVector3 XatVtx, TVector3 XatCalo, float dsz, float chi2, float PtError){
        myTrackProperties_.trackMomentum_ = p;
        myTrackProperties_.momentumAtCalo_ = pAtSc;
        myTrackProperties_.momentumOut_ = pAtSeed;
        myTrackProperties_.momentumAtEleClus_ = pAtEleC;
        myTrackProperties_.momentumAtVtxWithConstraint_ = pConstraint;
        myTrackProperties_.pixelLayersWithMeasurement_ = pixelLayers;
        myTrackProperties_.stripLayersWithMeasurement_ = stripLayers;
        myTrackProperties_.d0_ = d0;
        myTrackProperties_.missingHits_ = missingHits;
        myTrackProperties_.ip_ = ip;
        myTrackProperties_.positionAtVtx = XatVtx;
        myTrackProperties_.positionAtCalo = XatCalo;
        myTrackProperties_.dsz_ = dsz;
        myTrackProperties_.normalizedChi2_ = chi2;
        myTrackProperties_.ptError_ = PtError;        
    };
    void setD0(Float_t x) { myTrackProperties_.d0_ = x; } //-ip
    void setDsz(Float_t x) { myTrackProperties_.dsz_ = x; }
    void setImpactParameter(Float_t x) { myTrackProperties_.ip_ = x; }
    void setTrackMissingHits(Int_t x) { myTrackProperties_.missingHits_ = x; }
    void setTrackMomentumAtCalo(Float_t x) { myTrackProperties_.momentumAtCalo_ = x; }
    void setTrackMomentumAtElectronCluster(Float_t x) { myTrackProperties_.momentumAtEleClus_ = x; }
    void setTrackMomentumAtVtxWithConstraint(Float_t x) { myTrackProperties_.momentumAtVtxWithConstraint_ = x; }
    void setTrackMomentumOut(Float_t x) { myTrackProperties_.momentumOut_ = x; }
    void setTrackNormalizedChi2(Float_t x) { myTrackProperties_.normalizedChi2_ = x; }
    void setPixelLayersWithMeasurement(Int_t x) { myTrackProperties_.pixelLayersWithMeasurement_ = x; }
    void setStripLayersWithMeasurement(Int_t stripLayersWithMeasurement) { myTrackProperties_.stripLayersWithMeasurement_ = stripLayersWithMeasurement; }
    void setTrackPositionAtCalo(Double_t x, Double_t y, Double_t z) { myTrackProperties_.positionAtCalo.SetXYZ(x,y,z); }
    void setTrackPositionAtCalo(TVector3 x) { myTrackProperties_.positionAtCalo = x; }
    void setTrackPositionAtVtx(Double_t x, Double_t y, Double_t z) { myTrackProperties_.positionAtVtx.SetXYZ(x,y,z); }
    void setTrackPositionAtVtx(TVector3 x) { myTrackProperties_.positionAtVtx = x; }
    void setTrackPtError(Float_t x) { myTrackProperties_.ptError_ = x; }
    void setTrackMomentum(Float_t x) { myTrackProperties_.trackMomentum_ = x; }

private:
    TrackProperties myTrackProperties_;

    
 //Corrections===========================

public:
    struct Corrections{
	Float_t trackMomentumError_;        // Error on trackMomentum_
	Float_t ecalEnergyError_;           // Error on caloEnergy_
        Float_t ecalEnergy_;                // ecal corrected energy (if !isEcalEnergyCorrected this value is identical to the supercluster energy)
        bool isEcalEnergyCorrected_ ;  // true if ecal energy has been corrected
        bool isMomentumCorrected_ ;    // true if E-p combination has been applied (if not the electron momentum is the ecal corrected energy)
        Float_t electronMomentumError_ ; // the final electron momentum error
        Float_t d0Error_;        // error on d0_
        Float_t dszError_;       // error on dsz_
    };
    //getters
    Float_t trackMomentumError()const{return myCorrections_.trackMomentumError_;};
    Float_t caloEnergyError()const{return myCorrections_.ecalEnergyError_;};
    Float_t caloEnergy()const{return myCorrections_.ecalEnergy_;};
    bool isCaloEnergyCorrected()const{return myCorrections_.isEcalEnergyCorrected_;};
    bool isMomentumCorrected()const{return myCorrections_.isMomentumCorrected_;};
    Float_t electronMomentumError()const{return myCorrections_.electronMomentumError_;};
    Float_t d0Error()const{return myCorrections_.d0Error_;};
    Float_t dszError()const{return myCorrections_.dszError_;};

    //setter
    void setCorrections(float tme, float cee, float ce, bool cc, bool mc, float eMc, float d0e, float dsze){
        myCorrections_.trackMomentumError_ = tme;        // Error on trackMomentum_
	myCorrections_.ecalEnergyError_ = cee;           // Error on caloEnergy_
        myCorrections_.ecalEnergy_ = ce;                // ecal corrected energy (if !isEcalEnergyCorrected this value is identical to the supercluster energy)
        myCorrections_.isEcalEnergyCorrected_ = cc;  // true if ecal energy has been corrected
        myCorrections_.isMomentumCorrected_ = mc;    // true if E-p combination has been applied (if not the electron momentum is the ecal corrected energy)
        myCorrections_.electronMomentumError_ = eMc; // the final electron momentum error
        myCorrections_.d0Error_ = d0e;        // error on d0_
        myCorrections_.dszError_ = dsze;
    };
    void setD0Error(Float_t d0Error) { myCorrections_.d0Error_ = d0Error; }
    void setDszError(Float_t x) { myCorrections_.dszError_ = x; }
    void setCaloEnergyError(Float_t x) { myCorrections_.ecalEnergyError_ = x; }
    void setCaloEnergy(Float_t x) { myCorrections_.ecalEnergy_ = x; }
    void setElectronMomentumError(Float_t x) { myCorrections_.electronMomentumError_ = x; }
    void setEnergyScaleCorrected(bool x) { myCorrections_.isEcalEnergyCorrected_ = x; }
    void setMomentumCorrected(bool x) { myCorrections_.isMomentumCorrected_ = x; }
    void setTrackMomentumError(Float_t x) { myCorrections_.trackMomentumError_ = x; }
    
private:
    Corrections myCorrections_;

//SuperClusterProperties ===============================
public:
    struct SuperClusterProperties{
	TVector3 caloPosition_;		// SuperCluster centroid position
        Int_t basicClusterSize_;        // number of basic clusters inside the supercluster
	Int_t clusterAlgo_; // reco::BasicCluster::algo() island = 0, hybrid = 1, fixedMatrix = 2, dynamicHybrid = 3, multi5x5 = 4
	Float_t caloConeSize_; // Delta_R of the cone centered on the reco::GsfElectron and containing all its basic clusters constituents
	// need reco::SuperCluster and reco::BasicCluster and reduced Ecal RecHits Collections for EcalClusterLazyTools
	Int_t nbClusters_; // Number of related brem clusters
        Float_t superClusterRawEnergy_;
        Float_t preshowerEnergy_;
    };
    //getters
    TVector3 caloPosition()const{return mysuperClusterProperties_.caloPosition_;};
    Int_t basicClusterSize()const{return mysuperClusterProperties_.basicClusterSize_;};
    Int_t clusterAlgo()const{return mysuperClusterProperties_.clusterAlgo_;};
    Float_t caloConeSize()const{return mysuperClusterProperties_.caloConeSize_;};
    Int_t nClusters()const{return mysuperClusterProperties_.nbClusters_;};
    Float_t superClusterRawEnergy()const{return mysuperClusterProperties_.superClusterRawEnergy_;};
    Float_t preshowerEnergy()const{return mysuperClusterProperties_.preshowerEnergy_;};
    //setter
    void setSuperCluster(TVector3 pos, Int_t bcs, Int_t ca, Float_t ccs, Int_t nC, Float_t scRawE, Float_t PSE){
        mysuperClusterProperties_.caloPosition_ = pos;
        mysuperClusterProperties_.basicClusterSize_ = bcs;
        mysuperClusterProperties_.clusterAlgo_ = ca;
        mysuperClusterProperties_.caloConeSize_ = ccs;
        mysuperClusterProperties_.nbClusters_ = nC;
        mysuperClusterProperties_.superClusterRawEnergy_ = scRawE;
        mysuperClusterProperties_.preshowerEnergy_ = PSE;
    };
    void setBasicClusterSize(Int_t x) { mysuperClusterProperties_.basicClusterSize_ = x; }
    void setCaloConeSize(Float_t x) { mysuperClusterProperties_.caloConeSize_ = x; }
    void setCaloPosition(Double_t x, Double_t y, Double_t z) { mysuperClusterProperties_.caloPosition_.SetXYZ(x, y ,z); }
    void setCaloPosition(TVector3 x) { mysuperClusterProperties_.caloPosition_ = x; }
    void setClusterAlgo(Int_t x) { mysuperClusterProperties_.clusterAlgo_ = x; }
    void setNbClusters(Int_t x) { mysuperClusterProperties_.nbClusters_ = x; }
    void setPreshowerEnergy(Float_t x) { mysuperClusterProperties_.preshowerEnergy_ = x; }
    void setSuperClusterRawEnergy(Float_t x) { mysuperClusterProperties_.superClusterRawEnergy_ = x; }
private:
    SuperClusterProperties mysuperClusterProperties_;


//ShowerShape===================================
public:
    struct ShowerShape{
        Float_t sigmaEtaEta ;        // weighted cluster rms along eta and inside 5x5 (absolute eta)
        Float_t sigmaIetaIeta ;      // weighted cluster rms along eta and inside 5x5 (new, Xtal eta)
        Float_t e1x5 ;               // energy inside 1x5 in etaxphi around the seed Xtal
        Float_t e2x5Max ;            // energy inside 2x5 in etaxphi around the seed Xtal (max bwt the 2 possible sums)
        Float_t e5x5 ;               // energy inside 5x5 in etaxphi around the seed Xtal
	Float_t e2x2_;
	Float_t e3x3_;
	Float_t eMax_;
        Float_t hcalDepth1OverEcal ; // hcal over ecal seed cluster energy using first hcal depth (hcal is energy of towers within dR=015)
        Float_t hcalDepth2OverEcal ; // hcal over ecal seed cluster energy using 2nd hcal depth (hcal is energy of towers within dR=015)
    };
    //getters
    Float_t sigmaEtaEta()const{return myShowerShape_.sigmaEtaEta;};
    Float_t sigmaIEtaIEta()const{return myShowerShape_.sigmaIetaIeta;};
    Float_t e1x5()const{return myShowerShape_.e1x5;};
    Float_t e2x5Max()const{return myShowerShape_.e2x5Max;};
    Float_t e5x5()const{return myShowerShape_.e5x5;};
    Float_t e2x2()const{return myShowerShape_.e2x2_;};
    Float_t e3x3()const{return myShowerShape_.e3x3_;};
    Float_t eMax()const{return myShowerShape_.eMax_;};
    Float_t hadronicOverEm()const{return(myShowerShape_.hcalDepth1OverEcal + myShowerShape_.hcalDepth2OverEcal);};
    Float_t hadronicDepth1OverEm()const{return(myShowerShape_.hcalDepth1OverEcal);};
    Float_t hadronicDepth2OverEm()const{return(myShowerShape_.hcalDepth2OverEcal);};
    //setter
    void setShowerShape(float see, float sieie, float e15, float e25M, float e55, float e22, float e33, float eMax,
                    float hoe1,float hoe2){
        myShowerShape_.sigmaEtaEta = see;
        myShowerShape_.sigmaIetaIeta = sieie;
        myShowerShape_.e1x5 = e15;
        myShowerShape_.e2x5Max = e25M;
        myShowerShape_.e5x5 = e55;
        myShowerShape_.e2x2_ = e22;
        myShowerShape_.e3x3_ = e33;
        myShowerShape_.eMax_ = eMax;
        myShowerShape_.hcalDepth1OverEcal = hoe1;
        myShowerShape_.hcalDepth2OverEcal = hoe2;
    };
    void setE1x5(Float_t e1x5) { myShowerShape_.e1x5 = e1x5; }
    void setE2x2(Float_t e2x2) { myShowerShape_.e2x2_ = e2x2; }
    void setE2x5Max(Float_t e2x5Max) { myShowerShape_.e2x5Max = e2x5Max; }
    void setE3x3(Float_t e3x3) { myShowerShape_.e3x3_ = e3x3; }
    void setE5x5(Float_t e5x5) { myShowerShape_.e5x5 = e5x5; }
    void setHoverEDepth1(Float_t HoE1) { myShowerShape_.hcalDepth1OverEcal = HoE1; }
    void setHoverEDepth2(Float_t HoE2) { myShowerShape_.hcalDepth2OverEcal = HoE2; }
    void setSigmaEtaEta(Float_t see) { myShowerShape_.sigmaEtaEta = see; }
    void setSigmaIetaIeta(Float_t sieie) { myShowerShape_.sigmaIetaIeta = sieie; }

private:
    ShowerShape myShowerShape_;


//FiducialFlags=================================
public:
    struct FiducialFlags{
        bool isEB ;        // true if particle is in ECAL Barrel
        bool isEE ;        // true if particle is in ECAL Endcaps
        bool isEBEEGap ;   // true if particle is in the crack between EB and EE
        bool isEBEtaGap ;  // true if particle is in EB, and inside the eta gaps between modules
        bool isEBPhiGap ;  // true if particle is in EB, and inside the phi gaps between modules
        bool isEEDeeGap ;  // true if particle is in EE, and inside the gaps between dees
        bool isEERingGap ; // true if particle is in EE, and inside the gaps between rings
    };
    //getters
    bool isEB()const {return myFiducialFlags_.isEB;};
    bool isEE() const{return myFiducialFlags_.isEE;};
    bool isEBEEGap() const{return myFiducialFlags_.isEBEEGap;};
    bool isEBEtaGap()const {return myFiducialFlags_.isEBEtaGap;};
    bool isEBPhiGap()const {return myFiducialFlags_.isEBPhiGap;};
    bool isEEDeeGap()const {return myFiducialFlags_.isEEDeeGap;};
    bool isEERingGap()const {return myFiducialFlags_.isEERingGap;};
    //setter
    void setFiducialFlags(bool eb, bool ee, bool ebeegap, bool ebetagap, bool ebphigap, bool eedeegap, bool eeR){
        myFiducialFlags_.isEB = eb;
        myFiducialFlags_.isEE = ee;
        myFiducialFlags_.isEBEEGap = ebeegap;
        myFiducialFlags_.isEBEtaGap = ebetagap;
        myFiducialFlags_.isEBPhiGap = ebphigap;
        myFiducialFlags_.isEEDeeGap = eedeegap;
        myFiducialFlags_.isEERingGap = eeR;
    }
    void setEB(bool is){myFiducialFlags_.isEB = is;};
    void setEE(bool is){myFiducialFlags_.isEE = is;};
    void setEBEEGap(bool is){myFiducialFlags_.isEBEEGap = is;};
    void setEBEtaGap(bool is){myFiducialFlags_.isEBEtaGap = is;};
    void setEBPhiGap(bool is){myFiducialFlags_.isEBPhiGap = is;};
    void setEEDeeGap(bool is){myFiducialFlags_.isEEDeeGap = is;};
    void setEERingGap(bool is){myFiducialFlags_.isEERingGap = is;};
private:
    FiducialFlags myFiducialFlags_;

//Isolation ==================================
public:
    struct Isolation{
        Float_t tkSumPt ;                // track iso deposit with electron footprint removed
        Float_t ecalRecHitSumEt ;        // ecal iso deposit with electron footprint removed
        Float_t hcalDepth1TowerSumEt ;   // hcal depht 1 iso deposit with electron footprint removed
        Float_t hcalDepth2TowerSumEt ;   // hcal depht 2 iso deposit with electron footprint removed
        Int_t nTracks;
    };
    //getters
    Isolation getIsolation(int cone)const{
        if(cone == 1)
            return myIsolation01;
        else if(cone == 2)
            return myIsolation02;
        else if(cone == 3)
            return myIsolation03;
        else if(cone == 4)
            return myIsolation04;
        else if(cone == 5)
            return myIsolation05;
        else {
            cout<<"Bad Cone Size! It returns -1."<<endl;
            Isolation tmp = makeIsolation(-1.,-1.,-1.,-1.,-1);
            return tmp;
        }
    }
    Float_t ecalIso(unsigned int cone)const{
        if(cone == 1)
            return myIsolation01.ecalRecHitSumEt;
        else if(cone == 2)
            return myIsolation02.ecalRecHitSumEt;
        else if(cone == 3)
            return myIsolation03.ecalRecHitSumEt;
        else if(cone == 4)
            return myIsolation04.ecalRecHitSumEt;
        else if(cone == 5)
            return myIsolation05.ecalRecHitSumEt;
        else {
            cout<<"Bad Cone Size! It returns -1."<<endl;
            return -1.;
        }
    }
    Float_t hcalIso(unsigned int cone)const{
        if(cone == 1)
            return (myIsolation01.hcalDepth1TowerSumEt + myIsolation01.hcalDepth2TowerSumEt);
        else if(cone == 2)
            return (myIsolation02.hcalDepth1TowerSumEt + myIsolation02.hcalDepth2TowerSumEt);
        else if(cone == 3)
            return (myIsolation03.hcalDepth1TowerSumEt + myIsolation03.hcalDepth2TowerSumEt);
        else if(cone == 4)
            return (myIsolation04.hcalDepth1TowerSumEt + myIsolation04.hcalDepth2TowerSumEt);
        else if(cone == 5)
            return (myIsolation05.hcalDepth1TowerSumEt + myIsolation05.hcalDepth2TowerSumEt);
        else {
            cout<<"Bad Cone Size! It returns -1."<<endl;
            return -1.;
        }
    }
    Float_t caloIso(unsigned int cone)const{
        return (ecalIso(cone) + hcalIso(cone));
    }
    Float_t trackerIso(unsigned int cone)const{
        if(cone == 1)
            return (myIsolation01.tkSumPt);
        else if(cone == 2)
            return (myIsolation02.tkSumPt);
        else if(cone == 3)
            return (myIsolation03.tkSumPt);
        else if(cone == 4)
            return (myIsolation04.tkSumPt);
        else if(cone == 5)
            return (myIsolation05.tkSumPt);
        else {
            cout<<"Bad Cone Size! It returns -1."<<endl;
            return -1.;
        }
    }
    Float_t combinedIso(unsigned int tkcone, unsigned int ecalcone, unsigned int hcalcone)const{
        return (trackerIso(tkcone) + hcalIso(hcalcone) + ecalIso(ecalcone));
    }
//    Int_t nTracks(unsigned int cone)const{
//        if(cone == 1)
//            return (myIsolation01.nTracks);
//        else if(cone == 2)
//            return (myIsolation02.nTracks);
//        else if(cone == 3)
//            return (myIsolation03.nTracks);
//        else if(cone == 4)
//            return (myIsolation04.nTracks);
//        else if(cone == 5)
//            return (myIsolation05.nTracks);
//        else {
//            cout<<"Bad Cone Size! It returns -1."<<endl;
//            return -1.;
//        }
//    }
    //setters
    Isolation makeIsolation(float tkSumPt,float ecalRecHitSumEt,float hcalDepth1TowerSumEt,float hcalDepth2TowerSumEt , int nTracks)const{
        Isolation res;
        res.tkSumPt = tkSumPt;
        res.ecalRecHitSumEt = ecalRecHitSumEt;
        res.hcalDepth1TowerSumEt = hcalDepth1TowerSumEt;
        res.hcalDepth2TowerSumEt = hcalDepth2TowerSumEt;
//        res.nTracks = nTracks;
        return res;
    }
    void setIsolation(unsigned int cone, Isolation Iso){
        if(cone == 1)
            myIsolation01 = Iso;
        else if(cone == 2)
            myIsolation02 = Iso;
        else if(cone == 3)
            myIsolation03 = Iso;
        else if(cone == 4)
            myIsolation04 = Iso;
        else if(cone == 5)
            myIsolation05 = Iso;
    }
    void setIsoR01_emEt(Float_t isoR01_emEt) { myIsolation01.ecalRecHitSumEt = isoR01_emEt; }
    void setIsoR01_Depth1HadEt(Float_t isoR01_hadEt1) { myIsolation01.hcalDepth1TowerSumEt = isoR01_hadEt1; }
    void setIsoR01_Depth2HadEt(Float_t isoR01_hadEt2) { myIsolation01.hcalDepth2TowerSumEt = isoR01_hadEt2; }
    void setIsoR01_sumPt(Float_t isoR01_sumPt) { myIsolation01.tkSumPt = isoR01_sumPt; }
//    void setIsoR01_nTracks(Int_t isoR01_nTracks) { myIsolation01.nTracks = isoR01_nTracks; }

    void setIsoR02_emEt(Float_t isoR02_emEt) { myIsolation02.ecalRecHitSumEt = isoR02_emEt; }
    void setIsoR02_Depth1HadEt(Float_t isoR02_hadEt1) { myIsolation02.hcalDepth1TowerSumEt = isoR02_hadEt1; }
    void setIsoR02_Depth2HadEt(Float_t isoR02_hadEt2) { myIsolation02.hcalDepth2TowerSumEt = isoR02_hadEt2; }
    void setIsoR02_sumPt(Float_t isoR02_sumPt) { myIsolation02.tkSumPt = isoR02_sumPt; }
//    void setIsoR02_nTracks(Int_t isoR02_nTracks) { myIsolation02.nTracks = isoR02_nTracks; }

    void setIsoR03_emEt(Float_t isoR03_emEt) { myIsolation03.ecalRecHitSumEt = isoR03_emEt; }
    void setIsoR03_Depth1HadEt(Float_t isoR03_hadEt1) { myIsolation03.hcalDepth1TowerSumEt = isoR03_hadEt1; }
    void setIsoR03_Depth2HadEt(Float_t isoR03_hadEt2) { myIsolation03.hcalDepth2TowerSumEt = isoR03_hadEt2; }
    void setIsoR03_sumPt(Float_t isoR03_sumPt) { myIsolation03.tkSumPt = isoR03_sumPt; }
//    void setIsoR03_nTracks(Int_t isoR03_nTracks) { myIsolation03.nTracks = isoR03_nTracks; }

    void setIsoR04_emEt(Float_t isoR04_emEt) { myIsolation04.ecalRecHitSumEt = isoR04_emEt; }
    void setIsoR04_Depth1HadEt(Float_t isoR04_hadEt1) { myIsolation04.hcalDepth1TowerSumEt = isoR04_hadEt1; }
    void setIsoR04_Depth2HadEt(Float_t isoR04_hadEt2) { myIsolation04.hcalDepth2TowerSumEt = isoR04_hadEt2; }
    void setIsoR04_sumPt(Float_t isoR04_sumPt) { myIsolation04.tkSumPt = isoR04_sumPt; }
//    void setIsoR04_nTracks(Int_t isoR04_nTracks) { myIsolation04.nTracks = isoR04_nTracks; }

    void setIsoR05_emEt(Float_t isoR05_emEt) { myIsolation05.ecalRecHitSumEt = isoR05_emEt; }
    void setIsoR05_Depth1HadEt(Float_t isoR05_hadEt1) { myIsolation05.hcalDepth1TowerSumEt = isoR05_hadEt1; }
    void setIsoR05_Depth2HadEt(Float_t isoR05_hadEt2) { myIsolation05.hcalDepth2TowerSumEt = isoR05_hadEt2; }
    void setIsoR05_sumPt(Float_t isoR05_sumPt) { myIsolation05.tkSumPt = isoR05_sumPt; }
//    void setIsoR05_nTracks(Int_t isoR05_nTracks) { myIsolation05.nTracks = isoR05_nTracks; }
private:
    Isolation myIsolation01;
    Isolation myIsolation02;
    Isolation myIsolation03;
    Isolation myIsolation04;
    Isolation myIsolation05;

    //Identification ===================================
public:
    struct Identification{
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
    };
    //getters
    Int_t isRobustLoose()const{return myIdentification_.idCutBasedRobustLoose_;};
    Int_t isRobustTight()const{return myIdentification_.idCutBasedRobustTight_;};
    Int_t isRobustHighEnergy()const{return myIdentification_.idCutBasedRobustHighEnergy_;};
    Int_t isLoose()const{return myIdentification_.idCategorizedLoose_;};
    Int_t isTight()const{return myIdentification_.idCategorizedTight_;};
    Float_t LikelihoodId()const{return myIdentification_.idLikelihood_;};
    Float_t NeuralNetworkId()const{return myIdentification_.idNeuralNet_;};
    Int_t CiCVeryLooseId()const{return myIdentification_.idCiCVeryLoose_;};
    Int_t CiCLooseId()const{return myIdentification_.idCiCLoose_;};
    Int_t CiCMediumId()const{return myIdentification_.idCiCMedium_;};
    Int_t CiCTightId()const{return myIdentification_.idCiCTight_;};
    Int_t CiCSuperTightId()const{return myIdentification_.idCiCSuperTight_;};
    Int_t CiCHyperTightId_1()const{return myIdentification_.idCiCHyperTight1_;};
    Int_t CiCHyperTightId_2()const{return myIdentification_.idCiCHyperTight2_;};
    Int_t CiCHyperTightId_3()const{return myIdentification_.idCiCHyperTight3_;};
    Int_t CiCHyperTightId_4()const{return myIdentification_.idCiCHyperTight4_;};
    
    //setters
    void setIDs(int RL, int RT, int RH, int CL, int CT, float LH, float NN, int cicVL, int cicL,
                int cicM, int cicT, int cicST, int cicHT1,int cicHT2,int cicHT3,int cicHT4){
        myIdentification_.idCutBasedRobustLoose_ = RL;
        myIdentification_.idCutBasedRobustTight_ = RT;
        myIdentification_.idCutBasedRobustHighEnergy_ = RH;
        myIdentification_.idCategorizedLoose_ = CL;
        myIdentification_.idCategorizedTight_ = CT;
        myIdentification_.idLikelihood_ = LH;
        myIdentification_.idNeuralNet_ = NN;
        myIdentification_.idCiCVeryLoose_ = cicVL;
        myIdentification_.idCiCLoose_ = cicL;
        myIdentification_.idCiCMedium_ = cicM;
        myIdentification_.idCiCTight_ = cicT;
        myIdentification_.idCiCSuperTight_ = cicST;
        myIdentification_.idCiCHyperTight1_ = cicHT1;
        myIdentification_.idCiCHyperTight2_ = cicHT2;
        myIdentification_.idCiCHyperTight3_ = cicHT3;
        myIdentification_.idCiCHyperTight4_ = cicHT4;
    }
    void setIDCutBasedRobustLoose(Int_t idCutBasedFixedThresholdLoose) { myIdentification_.idCutBasedRobustLoose_ = idCutBasedFixedThresholdLoose; }
    void setIDCutBasedRobustTight(Int_t idCutBasedFixedThresholdTight) { myIdentification_.idCutBasedRobustTight_ = idCutBasedFixedThresholdTight; }
    void setIDCutBasedRobustHighEnergy(Int_t idCutBasedFixedThresholdHighEnergy) { myIdentification_.idCutBasedRobustHighEnergy_ = idCutBasedFixedThresholdHighEnergy; }
    void setIDCategorizedLoose(Int_t idCutBasedCategorizedLoose) { myIdentification_.idCategorizedLoose_ = idCutBasedCategorizedLoose; }
    void setIDCategorizedTight(Int_t idCutBasedCategorizedTight) { myIdentification_.idCategorizedTight_ = idCutBasedCategorizedTight; }
    void setIDLikelihood(Float_t idLikelihood) { myIdentification_.idLikelihood_ = idLikelihood; }
    void setIDNeuralNet(Float_t idNeuralNet) { myIdentification_.idNeuralNet_ = idNeuralNet; }
    void setIDCiCVeryLoose(Int_t cicVL) { myIdentification_.idCiCVeryLoose_ = cicVL; }
    void setIDCiCLoose(Int_t cicL) { myIdentification_.idCiCLoose_ = cicL; }
    void setIDCiCMedium(Int_t cicM) { myIdentification_.idCiCMedium_ = cicM; }
    void setIDCiCTight(Int_t cicT) { myIdentification_.idCiCTight_ = cicT; }
    void setIDCiCSuperTight(Int_t cicST) { myIdentification_.idCiCSuperTight_ = cicST; }
    void setIDCiCHyperTight1(Int_t cicHT1) { myIdentification_.idCiCHyperTight1_ = cicHT1; }
    void setIDCiCHyperTight2(Int_t cicHT2) { myIdentification_.idCiCHyperTight2_ = cicHT2; }
    void setIDCiCHyperTight3(Int_t cicHT3) { myIdentification_.idCiCHyperTight3_ = cicHT3; }
    void setIDCiCHyperTight4(Int_t cicHT4) { myIdentification_.idCiCHyperTight4_ = cicHT4; }
private:
    Identification myIdentification_;

//MCInfo==========================================
public:
    struct MCInfo{
        TLorentzVector momentumMCElectron_;
        TVector3 vertexMCElectron_;
        Int_t pdgIdMCElectron_;
    };
    //getter
    MCInfo getMCInfo()const{return myMCInfo_;};
    Int_t MCId()const{return myMCInfo_.pdgIdMCElectron_;};
    TLorentzVector MCP4()const{return myMCInfo_.momentumMCElectron_;};
    TVector3 MCVertex()const{return myMCInfo_.vertexMCElectron_;};
    //setter
    void setMCInfo(TLorentzVector P4, TVector3 Vtx, Int_t id){
        myMCInfo_.momentumMCElectron_ = P4;
        myMCInfo_.vertexMCElectron_ = Vtx;
        myMCInfo_.pdgIdMCElectron_ = id;
    }
    void setMCId(Int_t id){myMCInfo_.pdgIdMCElectron_ = id;};
    void setMCP4(TLorentzVector P4){myMCInfo_.momentumMCElectron_ = P4;};
    void setMCVertex(TVector3 Vtx){myMCInfo_.vertexMCElectron_ = Vtx;};
private:
    MCInfo myMCInfo_;

// Electron classification && fBrem ====================
    Int_t classification_;             
    Float_t fBrem_;
public:
    //getter
    Float_t fbrem()const{return fBrem_;};
    Int_t numberOfBrems()const{return (basicClusterSize() - 1);};
    //setter
    void setFbrem(float f){fBrem_ = f;};
    //getter
    Int_t classification()const{return classification_;};
    //setter
    void setClassification(int i){classification_ = i;};

//Trigger Info ======================================
    typedef std::vector<std::pair<std::string , bool > > TriggerMatchingInfo;
private:
    TriggerMatchingInfo myTriggerInfo;
public:
    void setTriggerInfo(TriggerMatchingInfo input){
        myTriggerInfo = input;
    }
    bool isTriggerMatched(std::string pathName)const{
        bool res = false;
        for(uint i = 0; i<myTriggerInfo.size(); i++){
            if(myTriggerInfo.at(i).first != pathName)
                continue;
            res = myTriggerInfo.at(i).second;
        }
        return(res);
    }
    TriggerMatchingInfo getTriggerInfo()const{
        return myTriggerInfo;
    }
private:
    bool isConversion;
public:
    bool isFromConversion()const{
        return isConversion;
    }
    void setConversion(bool is){
        isConversion = is;
    }
     
//     Float_t etaError_; // needed ?  etaError()
//     Float_t phiError_; // needed ?  phiError()


	
	ClassDef (TRootElectron,6);
};
//typedef std::pair<int,double> IntDoublePair;
//typedef std::pair<TRootElectron,std::vector<std::pair<int,double> > > MassPair;
#endif
