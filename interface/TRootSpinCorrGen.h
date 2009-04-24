#ifndef TRootSpinCorrGen_h
#define TRootSpinCorrGen_h

#include "../interface/TRootParticle.h"

#include "Rtypes.h"
#include "TObject.h"

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class TRootSpinCorrGen : public TObject 
{
	
public: 
        // semiletponic decay channel
  //    enum LeptonType {kNone, kElec, kMuon, kTau};

public:
	TRootSpinCorrGen() :
	        TObject()
	  /*	semiLeptonicChannel_(kNone),
                isTtBar_(false),
	        isFullHadronic_(false),
	        isSemiLeptonic_(false),
	        isFullLeptonic_(false)	*/
		{;}

	TRootSpinCorrGen(const TRootSpinCorrGen& gevt) :
	  TObject(gevt),
	  cosThetaTLHel_(gevt.cosThetaTLHel_),
	  cosThetaTBHel_(gevt.cosThetaTBHel_),
	  cosThetaTQHel_(gevt.cosThetaTQHel_),
	  topsZMFMass_(gevt.topsZMFMass_)
	  {;}
	
	~TRootSpinCorrGen(){;}

	Double_t cosThetaTLHel() const { return cosThetaTLHel_;}
	Double_t cosThetaTBHel() const { return cosThetaTBHel_;}
	Double_t cosThetaTQHel() const { return cosThetaTQHel_;}
	Double_t topsZMFMass() const { return topsZMFMass_;}


	void setcosThetaTLHel(Double_t cosThetaTLHel) { cosThetaTLHel_ = cosThetaTLHel; }
	void setcosThetaTBHel(Double_t cosThetaTBHel) { cosThetaTBHel_ = cosThetaTBHel; }
	void setcosThetaTQHel(Double_t cosThetaTQHel) { cosThetaTQHel_ = cosThetaTQHel; }
	void settopsZMFMass(Double_t topsZMFMass) { topsZMFMass_ = topsZMFMass; }
 
	virtual TString typeName() const { return "TRootSpinCorrGen"; }


	///	friend std::ostream& operator<< (std::ostream& stream, const TRootSpinCorrGen& genEvt) {
	  /*		stream << "TRootSpinCorrGen - is ";
	        if(genEvt.isTtBar()) stream <<"not ";
		stream <<"Ttbar event ";
		if(genEvt.isFullHadronic()) stream <<" FullHadronic ";
		if(genEvt.isFullLeptonic()) stream <<" FullLeptonic ";
		if(genEvt.isSemiLeptonic()) stream <<" SemiLeptonic ";
		if(genEvt.semiLeptonicChannel()==kMuon) stream <<" muonic";
		if(genEvt.semiLeptonicChannel()==kElec) stream <<" electronic";
		if(genEvt.semiLeptonicChannel()==kTau) stream <<" tauonic";
		stream << std::endl;
		stream << "Nof ISR: "<< genEvt.ISR().size();
		stream << "Nof Top radiations: "<< genEvt.leptonicDecayTopRadiation().size() + genEvt.hadronicDecayTopRadiation().size();
		//stream << "TRootSpinCorrGen - Charge=" << setw(2) << jet.charge() << " (Et,eta,phi)=("<< setw(10) << jet.Et() <<","<< setw(10) << jet.Eta() <<","<< setw(10) << jet.Phi() << ")"
		return stream;*/
	//	};


private:

	double cosThetaTLHel_;
	double cosThetaTBHel_;
	double cosThetaTQHel_;
	double topsZMFMass_ ; 

	
  ClassDef (TRootSpinCorrGen,1);
};

#endif
