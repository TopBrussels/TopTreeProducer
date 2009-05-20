#include "../interface/TRootSemiLepEvent.h"

// find corresponding hypotheses based on JetLepComb
int TRootSemiLepEvent::correspondingHypo(const HypoClassKey& key1, const unsigned& hyp1, const HypoClassKey& key2) const
{
  for(unsigned hyp2 = 0; hyp2 < this->numberOfAvailableHypos(key2); ++hyp2) {
    if( this->jetLepComb(key1, hyp1) == this->jetLepComb(key2, hyp2) )
      return hyp2;
  }
  return -1; // if no corresponding hypothesis was found
}

void TRootSemiLepEvent::print(){
  // get number of available hypothesis classes
  cout << " Number of available event hypothesis classes: " << this->numberOfAvailableHypoClasses() << " \n";
  
  // get details from the hypotheses
  typedef std::map<HypoClassKey, std::vector<HypoCombPair> >::const_iterator EventHypo;
  for(EventHypo hyp = evtHyp_.begin(); hyp != evtHyp_.end(); ++hyp) {
    HypoClassKey hypKey = (*hyp).first;
    // header for each hypothesis
    cout << "-------------------------------------------------- \n";
    switch(hypKey) {
    case kGeom          : cout << " Geom"         ; break;
    case kWMassMaxSumPt : cout << " WMassMaxSumPt"; break;
    case kMaxSumPtWMass : cout << " MaxSumPtWMass"; break;
    case kGenMatch      : cout << " GenMatch"     ; break;
    case kMVADisc       : cout << " MVADisc"      ; break;
    case kKinFit        : cout << " KinFit"       ; break;
    default             : cout << " Unknown";
    }
    cout << "-Hypothesis: \n";
    if( this->numberOfAvailableHypos(hypKey) > 1 ) {
      cout << " * Number of available jet combinations: "
	  << this->numberOfAvailableHypos(hypKey) << " \n"
	  << " The following was found to be the best one: \n";
    }
    // check if hypothesis is valid
    if( !this->isHypoValid( hypKey ) )
      cout << " * Not valid! \n";
    // get meta information for valid hypothesis
    else {
      // jetLepComb
      cout << " * JetLepComb:";
      std::vector<int> jets = this->jetLepComb( hypKey );
      for(unsigned int iJet = 0; iJet < jets.size(); iJet++) {
	cout << "   " << jets[iJet] << "   ";
      }
      cout << "\n";
      // specialties for some hypotheses
      switch(hypKey) {
      case kGenMatch : cout << " * Sum(DeltaR) : " << this->genMatchSumDR() << " \n"
			   << " * Sum(DeltaPt): " << this->genMatchSumPt() << " \n"; break;
      case kMVADisc  : cout << " * Method  : "     << this->mvaMethod()     << " \n"
			   << " * Discrim.: "     << this->mvaDisc()       << " \n"; break;
      case kKinFit   : cout << " * Chi^2      : "  << this->fitChi2()       << " \n"
			   << " * Prob(Chi^2): "  << this->fitProb()       << " \n"; break;
      default        : break;
      }
    }
  }

  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++";  
}

ClassImp(TRootSemiLepEvent)
