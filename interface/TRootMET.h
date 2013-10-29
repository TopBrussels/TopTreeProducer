#ifndef TRootMET_h
#define TRootMET_h

#include "../interface/TRootParticle.h"

#include "Rtypes.h"
#include "TObject.h"

using namespace std;

namespace TopTree
{
	class TRootMET : public TRootParticle
	{
	public:

		TRootMET() :
			TRootParticle()
      ,METType_(0)
			,sumEt_(-9999.)
			{;}

		TRootMET(const TRootMET& met) :
			TRootParticle(met)
			,METType_(met.METType_)
			,sumEt_(met.sumEt_)
			{;}

		TRootMET(Double_t px, Double_t py, Double_t pz, Double_t e) :
			TRootParticle(px,py,pz,e)
			,METType_(0)
			,sumEt_(-9999.)
			{;}
	
		TRootMET(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
			,METType_(0)
			,sumEt_(-9999.)
			{;}

		TRootMET(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
			,METType_(0)
			,sumEt_(-9999.)
			{;}

		TRootMET(const TLorentzVector &momentum) :
			TRootParticle(momentum)
			,METType_(0)
			,sumEt_(-9999.)
			{;}

		TRootMET(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
			TRootParticle(momentum, vertex, type, charge)
			,METType_(0)
			,sumEt_(-9999.)
			{;}

		~TRootMET() {;}
		
		Int_t METType() const { return METType_; }
		Float_t sumEt() const { return sumEt_; }
		virtual TString typeName() const { return "TRootMET"; }

		void setMETType(Int_t METType) { METType_ = METType; }
		void setSumEt(Float_t sumEt) { sumEt_ = sumEt; }

		friend std::ostream& operator<< (std::ostream& stream, const TRootMET& met)
		{
			stream << "TRootMET  (Pt,Px,Py)=("<< met.Pt() <<","<< met.Px() <<","<< met.Py() << ")";
			return stream;
		};


	private:

		Int_t METType_;
		Float_t sumEt_;

		ClassDef (TRootMET,2);
	};
}

#endif
