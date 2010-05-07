#ifndef TRootSpinCorrGen_h
#define TRootSpinCorrGen_h

#include "../interface/TRootParticle.h"

#include "Rtypes.h"
#include "TObject.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include "TLorentzVector.h"

using namespace std;

namespace TopTree
{
	class TRootSpinCorrGen : public TObject 
	{
	
	public: 
		//	semiletponic decay channel
		//	enum LeptonType {kNone, kElec, kMuon, kTau};

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
			cosPhi_(gevt.cosPhi_),
			topsZMFMass_(gevt.topsZMFMass_)
			{;}
	
		~TRootSpinCorrGen(){;}

		Double_t cosThetaTLHel() const { return cosThetaTLHel_;}
		Double_t cosThetaTBHel() const { return cosThetaTBHel_;}
		Double_t cosThetaTQHel() const { return cosThetaTQHel_;}
		Double_t cosPhi() const { return cosPhi_;}
		Double_t topsZMFMass() const { return topsZMFMass_;}

		void setcosThetaTLHel(Double_t cosThetaTLHel) { cosThetaTLHel_ = cosThetaTLHel; }
		void setcosThetaTBHel(Double_t cosThetaTBHel) { cosThetaTBHel_ = cosThetaTBHel; }
		void setcosThetaTQHel(Double_t cosThetaTQHel) { cosThetaTQHel_ = cosThetaTQHel; }
		void setcosPhi(Double_t cosPhi) { cosPhi_ = cosPhi; }
		void settopsZMFMass(Double_t topsZMFMass) { topsZMFMass_ = topsZMFMass; }

		virtual TString typeName() const { return "TRootSpinCorrGen"; }


	private:

		Double_t cosThetaTLHel_;
		Double_t cosThetaTBHel_;
		Double_t cosThetaTQHel_;
		Double_t cosPhi_;
		Double_t topsZMFMass_ ; 
	
		ClassDef (TRootSpinCorrGen,2);
	};
}

#endif
