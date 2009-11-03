#ifndef TRootSemiLepEvent_h
#define TRootSemiLepEvent_h

#include "TRootGenEvent.h"
#include "TRootCompositeCandidate.h"

#include <vector>
#include <string>
#include <map>
#include <utility>

#include "TLorentzVector.h"

namespace TopTree{
namespace TRootSemiLepDaughter{
  /// semi-leptonic daughter names for common
  /// use and use with the hypotheses
  static const std::string Nu  ="Nu"  , Lep ="Lep" , LepW="LepW", LepB="LepB", LepTop="LepTop";
  static const std::string HadQ="HadQ", HadP="HadP", HadW="HadW", HadB="HadB", HadTop="HadTop"; 
}

class TRootSemiLepEvent: public TObject {

 public:

  /// supported classes of event hypotheses
  enum HypoClassKey {kGeom, kWMassMaxSumPt, kMaxSumPtWMass, kGenMatch, kMVADisc, kKinFit};
  /// pair of hypothesis and lepton jet combinatorics for a given hypothesis
  typedef std::pair<TRootCompositeCandidate, std::vector<int> > HypoCombPair;
  
 public:

  /// empty constructor
  TRootSemiLepEvent(){};
  /// default destructor
  virtual ~TRootSemiLepEvent(){};

  /// get leptonic decay channels
  std::pair<TRootGenEvent::LeptonType, TRootGenEvent::LeptonType> lepDecays() const { return lepDecays_; }
  /// get event hypothesis; there can be more hypotheses of a certain 
  /// class (sorted by quality); per default the best hypothesis is returned
  const TRootCompositeCandidate& eventHypo(const HypoClassKey& key, const unsigned& cmb=0) const { return (evtHyp_.find(key)->second)[cmb].first; };

  /// check if hypothesis class 'key' was added to the event structure
  bool isHypoClassAvailable(const HypoClassKey& key) const { return (evtHyp_.find(key)!=evtHyp_.end()); };
  /// check if hypothesis 'cmb' is available within the hypothesis class
  bool isHypoAvailable(const HypoClassKey& key, const unsigned& cmb=0) const { return isHypoClassAvailable(key) ? (cmb<evtHyp_.find(key)->second.size()) : false; };
  /// check if hypothesis 'cmb' within the hypothesis class
  /// was valid; if not it lead to an empty CompositeCandidate
  bool isHypoValid(const HypoClassKey& key, const unsigned& cmb=0) const { return isHypoAvailable(key,cmb) ? !eventHypo(key,cmb).daughters().empty() : false; };
  /// return number of available hypothesis classes
  unsigned int numberOfAvailableHypoClasses() const { return evtHyp_.size();};
  /// return number of available hypotheses within a given hypothesis class
  unsigned int numberOfAvailableHypos(const HypoClassKey& key) const { return isHypoAvailable(key) ? evtHyp_.find(key)->second.size() : 0;};
  /// return the vector of jet lepton combinatorics for a given hypothesis and class
  std::vector<int> jetLepComb(const HypoClassKey& key, const unsigned& cmb=0) const { return (evtHyp_.find(key)->second)[cmb].second; };
  /// return the sum pt of the generator match if available; -1 else
  double genMatchSumPt(const unsigned& cmb=0) const { return (cmb<genMatchSumPt_.size() ? genMatchSumPt_[cmb] : -1.); };
  /// return the sum dr of the generator match if available; -1 else
  double genMatchSumDR(const unsigned& cmb=0) const { return (cmb<genMatchSumDR_.size() ? genMatchSumDR_[cmb] : -1.); };
  /// return the label of the mva method in use for the jet parton association; 
  /// if kMVADisc is not available the string is empty
  std::string mvaMethod() const { return mvaMethod_; }
  /// return the mva discriminant value of hypothesis 'cmb' if available; -1 else
  double mvaDisc(const unsigned& cmb=0) const { return (cmb<mvaDisc_.size() ? mvaDisc_[cmb] : -1.); }
  /// return the chi2 of the kinemtaic fit of hypothesis 'cmb' if available; -1 else
  double fitChi2(const unsigned& cmb=0) const { return (cmb<fitChi2_.size() ? fitChi2_[cmb] : -1.); }
  /// return the fit probability of hypothesis 'cmb' if available; -1 else
  double fitProb(const unsigned& cmb=0) const { return (cmb<fitProb_.size() ? fitProb_[cmb] : -1.); }
  /// return the hypothesis in hypothesis class 'key2', which 
  /// corresponds to hypothesis 'hyp1' in hypothesis class 'key1'
  int correspondingHypo(const HypoClassKey& key1, const unsigned& hyp1, const HypoClassKey& key2) const;

  /// set leptonic decay channels
  void setLepDecays(const TRootGenEvent::LeptonType& lepDecTop1, const TRootGenEvent::LeptonType& lepDecTop2) { lepDecays_=std::make_pair(lepDecTop1, lepDecTop2); };
  /// add new hypotheses
  void addEventHypo(const HypoClassKey& key, HypoCombPair hyp) { evtHyp_[key].push_back(hyp); };
  /// set sum pt of kGenMatch hypothesis
  void setGenMatchSumPt(const std::vector<double>& val) {genMatchSumPt_=val;};
  /// set sum dr of kGenMatch hypothesis
  void setGenMatchSumDR(const std::vector<double>& val) {genMatchSumDR_=val;};
  /// set label of mva method for kMVADisc hypothesis
  void setMvaMethod(const std::string& name) { mvaMethod_=name; };
  /// set mva discriminant values of kMVADisc hypothesis
  void setMvaDiscriminators(const std::vector<double>& val) { mvaDisc_=val; };
  /// set chi2 of kKinFit hypothesis
  void setFitChi2(const std::vector<double>& val) { fitChi2_=val; };
  /// set fit probability of kKinFit hypothesis
  void setFitProb(const std::vector<double>& val) { fitProb_=val; };

  const TRootWCandidate hadronicW  (const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? TRootWCandidate() : hadronicTop(key,cmb).W(); };
  const TRootWCandidate leptonicW  (const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? TRootWCandidate() : leptonicTop(key,cmb).W(); };
  const TRootTopCandidate hadronicTop(const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? TRootTopCandidate() : eventHypo  (key,cmb). daughter(TRootSemiLepDaughter::HadTop); };
  const TRootTopCandidate leptonicTop(const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? TRootTopCandidate() : eventHypo  (key,cmb). daughter(TRootSemiLepDaughter::LepTop); };
  
  const TLorentzVector neutrino   (const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? TLorentzVector() : leptonicW  (key,cmb).Neutrino(); };
  
  //Muon or Electron ... to be fixed
  const TRootMuon* lepton     (const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? 0 : leptonicW  (key,cmb).Lepton(); };
  const TRootJet* hadronicB  (const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? 0 : hadronicTop(key,cmb).B(); };
  const TRootJet* lightQuarkP(const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? 0 : hadronicW  (key,cmb).QuarkP(); };
  const TRootJet* lightQuarkQ(const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? 0 : hadronicW  (key,cmb).QuarkQ(); };
  const TRootJet* leptonicB  (const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? 0 : leptonicTop(key,cmb).B(); };
 
  TLorentzVector TLlepton     (const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? TLorentzVector() : leptonicW  (key,cmb).TLLepton(); };
  TLorentzVector TLhadronicB  (const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? TLorentzVector() : hadronicTop(key,cmb).TLB(); };
  TLorentzVector TLlightQuarkP(const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? TLorentzVector() : hadronicW  (key,cmb).TLQuarkP(); };
  TLorentzVector TLlightQuarkQ(const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? TLorentzVector() : hadronicW  (key,cmb).TLQuarkQ(); };
  TLorentzVector TLleptonicB  (const HypoClassKey& key, const unsigned& cmb=0) const { return !isHypoValid(key,cmb) ? TLorentzVector() : leptonicTop(key,cmb).TLB(); };
  
  
  bool isTLFormat(const HypoClassKey& key, const unsigned& cmb=0) const {
    if(leptonicW(key,cmb).isTLFormat() || leptonicTop(key,cmb).isTLFormat() || hadronicW(key,cmb).isTLFormat() || hadronicTop(key,cmb).isTLFormat()) return true;
    return false;
  }
  void print();

 protected:

  /// leptonic decay channels
  std::pair<TRootGenEvent::LeptonType, TRootGenEvent::LeptonType> lepDecays_;
  /// map of hypotheses; for each HypoClassKey a vector of 
  /// hypothesis and their lepton jet combinatorics are kept
  std::map<HypoClassKey, std::vector<HypoCombPair> > evtHyp_;
  
  /// result of kinematic fit
  std::vector<double> fitChi2_;        
  /// result of kinematic fit
  std::vector<double> fitProb_;        
  /// result of gen match
  std::vector<double> genMatchSumPt_;  
  /// result of gen match
  std::vector<double> genMatchSumDR_;   
  /// label of the MVA method
  std::string mvaMethod_;               
  /// MVA discriminants
  std::vector<double> mvaDisc_;         

  ClassDef (TRootSemiLepEvent,1);

};
}
#endif
