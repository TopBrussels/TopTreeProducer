#ifndef TRootEvent_h
#define TRootEvent_h

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#include "Rtypes.h"
#include "TObject.h"
#include "TVector3.h"

using namespace std;

namespace TopTree
{

struct triggeredObject
{
  triggeredObject() {};
  Int_t id;
  Float_t pt;
  Float_t eta;
  Float_t phi;
  // this is a virtual destructor:
  virtual ~triggeredObject() { } //cout<<"Destroying triggeredObject";}
  ClassDef(triggeredObject,2);
};


class TRootEvent : public TObject
{
  
  public:
    
    TRootEvent() :
        nb_(0)
        ,eventId_(-1)
        ,runId_(-1)
        ,lumiBlockId_(-1)
        ,flavHistPath_(-1)
        ,fixedGridRhoFastjetAll_(-1)
        ,kt6PFJetsForIsolation_rho_(-1)
        ,nTracks_(-1)
        ,nHighPurityTracks_(-1)
        ,nTruePU_(-1.)
        ,passGlobalHLT_(false)
        ,trigHLT_(0)
        ,idParton1_(-1)
        ,xParton1_(-1.)
        ,idParton2_(-1)
        ,xParton2_(-1.)
        ,factorizationScale_(-1.)
        ,originalXWGTUP_(0)
        ,weights_()
        ,HBHENoiseFilter_(true)
        ,HBHENoiseIsoFilter_(true)
        ,eeBadScFilter_(true)
//        ,CSCTightHalo2015Filter_(true) // use 2015 for 76X
	,globalTightHalo2016Filter_(true) // 80X version 
        ,EcalDeadCellTriggerPrimitiveFilter_(true) // added for 76X
        ,PVFilter_(true)
	,BadChCandFilter_(true) //80X
	,BadPFMuonFilter_(true) // 80X
	,genTTX_id_(-666)
    {
      ;
    }
    
    ~TRootEvent()
    {
      ;
    }
    
    // Event number
    
    Int_t nb() const
    {
      return nb_;
    }
    Long64_t eventId() const  // necessary for data
    {
      return eventId_;
    }
    Int_t runId() const
    {
      return runId_;
    }
    Int_t lumiBlockId() const
    {
      return lumiBlockId_;
    }
    Int_t flavorHistoryPath() const
    {
      return flavHistPath_;
    }
    Float_t fixedGridRhoAll() const
    {
      return fixedGridRhoAll_;
    }
    Float_t fixedGridRhoFastjetAll() const
    {
      return fixedGridRhoFastjetAll_;
    }
    Float_t fixedGridRhoFastjetAllCalo() const
    {
      return fixedGridRhoFastjetAllCalo_;
    }
    Float_t fixedGridRhoFastjetCentralCalo() const
    {
      return fixedGridRhoFastjetCentralCalo_;
    }
    Float_t fixedGridRhoFastjetCentralChargedPileUp() const
    {
      return fixedGridRhoFastjetCentralChargedPileUp_;
    }
    Float_t fixedGridRhoFastjetCentralNeutral() const
    {
      return fixedGridRhoFastjetCentralNeutral_;
    }
    Float_t kt6PFJetsForIsolation_rho() const
    {
      return kt6PFJetsForIsolation_rho_;
    }
    Float_t originalXWGTUP() const
    {
      return originalXWGTUP_;
    }
    
    // generalTracks infos (for cleaning of the scraping events)
    Int_t nTracks() const
    {
      return nTracks_;
    }
    Int_t nHighPurityTracks() const
    {
      return nHighPurityTracks_;
    }
    
    // PileUp info
    Int_t nPu(Int_t nBX)
    {
      return ( nPu_.find(nBX) != nPu_.end() ? nPu_[nBX] : -9999 );
    }
    Float_t nTruePU()
    {
      return nTruePU_;
    }
    
    // Trigger decision
    Bool_t passGlobalHLT() const
    {
      return passGlobalHLT_;
    }
    UInt_t nHLTPaths() const
    {
      return trigHLT_.size();
    }
    std::vector<Bool_t> trigHLT() const
    {
      return trigHLT_;
    }
    Bool_t trigHLT(UInt_t i) const
    {
      if (trigHLT_.size()>i)
      {
        return trigHLT_.at(i);
      }
      else
      {
        cout << "HLT path " << i << " not found" << endl;
        return false;
      }
    }
    
    // PDF infos
    // flavour first incoming parton
    Int_t idParton1() const
    {
      return idParton1_;
    }
    // energy fraction carried by first incoming parton
    Float_t xParton1() const
    {
      return xParton1_;
    }
    // flavour first incoming parton
    Int_t idParton2() const
    {
      return idParton2_;
    }
    // energy fraction carried by first incoming parton
    Float_t xParton2() const
    {
      return xParton2_;
    }
    // Q-scale used in evaluation of PDF's (in GeV).
    Float_t factorizationScale() const
    {
      return factorizationScale_;
    }
    
    std::map<std::string, std::vector<TopTree::triggeredObject> >  getTriggerFilters() const
    {
      return triggerFilters_;
    }
    
    
    void setWeight(int idx, float weight)
    {
      if(weights_.find(idx)==weights_.end())
      {
        weights_[idx] = weight;
        //if(weights_.find(idx)!=weights_.end()) cout << "assignment check 1 : " << weights_.find(idx)->second << endl;
        //else cout << "Assignment failed" << endl;
        //cout << "Last Element: " << weights_.rbegin()->first << " : " << weights_.rbegin()->second << endl;
      }
      else
      {
        cout << "Weight at index " << idx << " has already been set as " << weights_[idx] << endl;
      }
    }
    
    float getWeight(int idx)
    {
      return (weights_.find(idx)!=weights_.end() ?  weights_.find(idx)->second : -9999 );
    }
    
    void setNb(Int_t nb)
    {
      nb_ = nb;
    }
    void setEventId(Long64_t eventId)
    {
      eventId_ = eventId;
    }
    void setRunId(Int_t runId)
    {
      runId_ = runId;
    }
    void setLumiBlockId(Int_t lumiBlockId)
    {
      lumiBlockId_ = lumiBlockId;
    }
    void setflavorHistoryPath(Int_t flavHistPath)
    {
      flavHistPath_ = flavHistPath;
    }
    void setfixedGridRhoAll(double fixedGridRhoAll)
    {
      fixedGridRhoAll_ = fixedGridRhoAll;
    }
    void setfixedGridRhoFastjetAll(double fixedGridRhoFastjetAll)
    {
      fixedGridRhoFastjetAll_ = fixedGridRhoFastjetAll;
    }
    void setfixedGridRhoFastjetAllCalo(double fixedGridRhoFastjetAllCalo)
    {
      fixedGridRhoFastjetAllCalo_ = fixedGridRhoFastjetAllCalo;
    }
    void setfixedGridRhoFastjetCentralCalo(double fixedGridRhoFastjetCentralCalo)
    {
      fixedGridRhoFastjetCentralCalo_ = fixedGridRhoFastjetCentralCalo;
    }
    void setfixedGridRhoFastjetCentralChargedPileUp(double fixedGridRhoFastjetCentralChargedPileUp)
    {
      fixedGridRhoFastjetCentralChargedPileUp_ = fixedGridRhoFastjetCentralChargedPileUp;
    }
    void setfixedGridRhoFastjetCentralNeutral(double fixedGridRhoFastjetCentralNeutral)
    {
      fixedGridRhoFastjetCentralNeutral_ = fixedGridRhoFastjetCentralNeutral;
    }
    void setKt6PFJetsForIsolation_rho(double kt6PFJetsForIsolation_rho)
    {
      kt6PFJetsForIsolation_rho_ = kt6PFJetsForIsolation_rho;
    }
    void setOriginalXWGTUP(double originalXWGTUP)
    {
      originalXWGTUP_ = originalXWGTUP;
    }
    void setNTracks(Int_t nTracks)
    {
      nTracks_ = nTracks;
    }
    void setNPu(Int_t nBX, Int_t nPu)
    {
      nPu_[nBX] = nPu;
    }
    void setNTruePU(Float_t nTruePU)
    {
      nTruePU_ = nTruePU;
    }
    void setNHighPurityTracks(Int_t nHighPurityTracks)
    {
      nHighPurityTracks_ = nHighPurityTracks;
    }
    
    void setGlobalHLT(Bool_t passGlobalHLT)
    {
      passGlobalHLT_ = passGlobalHLT;
    }
    void setTrigHLT(std::vector<Bool_t> trigHLT)
    {
      trigHLT_.resize(trigHLT.size());
      for (unsigned int i=0; i!=trigHLT.size(); ++i) trigHLT_[i]=trigHLT[i];
    }
    
    void setIdParton1(Int_t idParton1)
    {
      idParton1_=idParton1;
    }
    void setXParton1(Float_t xParton1)
    {
      xParton1_=xParton1;
    }
    void setIdParton2(Int_t idParton2)
    {
      idParton2_=idParton2;
    }
    void setXParton2(Float_t xParton2)
    {
      xParton2_=xParton2;
    }
    void setFactorizationScale(Float_t factorizationScale)
    {
      factorizationScale_=factorizationScale;
    }
    
    void AddTriggerObject(string path, Int_t id, Float_t pt, Float_t eta, Float_t phi)
    {
      TopTree::triggeredObject object;
      object.id = id;
      object.pt = pt;
      object.eta = eta;
      object.phi = phi;
      triggerFilters_[path].push_back(object);
    }
    
    /*
    // FIXME
    friend std::ostream& operator<< (std::ostream& stream, const TRootEvent& event)
    {
      stream << "Event #"<< event.nb() <<"  HLT="<< event.trigHLT();
      return stream;
    };
    */
    
    // accessors noise results:
    void setHBHENoiseFilter(Bool_t res) {HBHENoiseFilter_=res;} // false = reject event
    Bool_t getHBHENoiseFilter(void) const {return HBHENoiseFilter_;} // false = reject event
    void setHBHENoiseIsoFilter(Bool_t res){HBHENoiseIsoFilter_=res;} // false = reject event
    Bool_t getHBHENoiseIsoFilter(void) const { return HBHENoiseIsoFilter_;} // false = reject event
    void setEEBadScFilter(Bool_t res) { eeBadScFilter_ = res;} // false = reject event
    Bool_t getEEBadScFilter(void) const { return eeBadScFilter_; } // false = reject event
//    void setCSCTightHalo2015Filter(Bool_t res) { CSCTightHalo2015Filter_ = res;} // false = reject event
//    Bool_t getCSCTightHalo2015Filter(void) const { return CSCTightHalo2015Filter_; } // false = reject event
    //80X version
    void setglobalTightHalo2016Filter(Bool_t res) { globalTightHalo2016Filter_ = res;} // false = reject event
    Bool_t getglobalTightHalo2016Filter(void) const { return globalTightHalo2016Filter_; } // false = reject event
    void setEcalDeadCellTriggerPrimitiveFilter(Bool_t res) { EcalDeadCellTriggerPrimitiveFilter_ = res;} // false = reject event
    Bool_t getEcalDeadCellTriggerPrimitiveFilter(void) {return EcalDeadCellTriggerPrimitiveFilter_; } // false = reject event
    void setPVFilter(Bool_t res) { PVFilter_ = res;}
    Bool_t getPVFilter(void) {return PVFilter_;}  // added for 80X
     void setBadChCandFilter(Bool_t res) { BadChCandFilter_ = res; } // false = reject event
     Bool_t getBadChCandFilter(void) const{ return BadChCandFilter_;}
      void setBadPFMuonFilter(Bool_t res) { BadPFMuonFilter_ = res; } // false = reject event
     Bool_t getBadPFMuonFilter(void) const {return BadPFMuonFilter_; }
      void setgenTTX_id(Int_t res) { genTTX_id_ = res; } // false = reject event
     Int_t getgenTTX_id(void) const {return genTTX_id_; }

    void setBFragmentationWeights( const std::map<std::string,double> weights ) { bFragWeights_ = weights; }
    std::map<std::string,double> getBFragmentationWeights() const {return bFragWeights_;}
    
  private:
    
    Int_t nb_;
    Long64_t eventId_;
    Int_t runId_;
    Int_t lumiBlockId_;
    
    
    Int_t flavHistPath_; // flavor history path, see https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideFlavorHistory
    Float_t fixedGridRhoAll_, fixedGridRhoFastjetAll_, fixedGridRhoFastjetAllCalo_, fixedGridRhoFastjetCentralCalo_, fixedGridRhoFastjetCentralChargedPileUp_, fixedGridRhoFastjetCentralNeutral_;
    Float_t kt6PFJetsForIsolation_rho_;
    // generalTracks infos (for cleaning of the scraping events)
    Int_t nTracks_;
    Int_t nHighPurityTracks_;
    
    
    // PileUp info
    std::map<Int_t,Int_t> nPu_;
    Float_t nTruePU_;
    // Trigger Infos
    Bool_t passGlobalHLT_;
    std::vector<Bool_t> trigHLT_;
    
    // PDF infos
    Int_t idParton1_;
    Float_t xParton1_;
    Int_t idParton2_;
    Float_t xParton2_;
    Float_t factorizationScale_;
    
    Float_t originalXWGTUP_;
    
    std::map<int,float> weights_;
    
    std::map<std::string, std::vector<TopTree::triggeredObject> > triggerFilters_;
    
    
    // event cleaning bools. True = good, false=bad
    Bool_t HBHENoiseFilter_;
    Bool_t HBHENoiseIsoFilter_;
    Bool_t eeBadScFilter_;
//    Bool_t CSCTightHalo2015Filter_;
    Bool_t globalTightHalo2016Filter_; 
    Bool_t EcalDeadCellTriggerPrimitiveFilter_;
    Bool_t PVFilter_;
    Bool_t BadChCandFilter_; 
    Bool_t BadPFMuonFilter_;

    Int_t genTTX_id_;

    map<string,double> bFragWeights_; //BFragmentation weights from pseudotop and BFragmentationWeights producers

    ClassDef (TRootEvent,10);
};
}

#endif
