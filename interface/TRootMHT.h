#ifndef TRootMHT_h
#define TRootMHT_h

#include "../interface/TRootParticle.h"

#include "Rtypes.h"
#include "TObject.h"

using namespace std;

namespace TopTree
{
	class TRootMHT : public TRootParticle
	{
	public:

		TRootMHT() :
			TRootParticle()
			,hT_(-9999.)
			,significance_(-9999.)
			,nJets_(-9999)
			,nElectrons_(-9999)
			,nMuons_(-9999)
			{;}

		TRootMHT(const TRootMHT& mht) :
			TRootParticle(mht)
			,hT_(mht.hT_)
			,significance_(mht.significance_)
			,nJets_(mht.nJets_)
			,nElectrons_(mht.nElectrons_)
			,nMuons_(mht.nMuons_)
			{;}

		TRootMHT(Double_t px, Double_t py, Double_t pz, Double_t e) :
			TRootParticle(px,py,pz,e)
			,hT_(-9999.)
			,significance_(-9999.)
			,nJets_(-9999)
			,nElectrons_(-9999)
			,nMuons_(-9999)
			{;}
	
		TRootMHT(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
			,hT_(-9999.)
			,significance_(-9999.)
			,nJets_(-9999)
			,nElectrons_(-9999)
			,nMuons_(-9999)
			{;}

		TRootMHT(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
			,hT_(-9999.)
			,significance_(-9999.)
			,nJets_(-9999)
			,nElectrons_(-9999)
			,nMuons_(-9999)
			{;}

		TRootMHT(const TLorentzVector &momentum) :
			TRootParticle(momentum)
			,hT_(-9999.)
			,significance_(-9999.)
			,nJets_(-9999)
			,nElectrons_(-9999)
			,nMuons_(-9999)
			{;}

		TRootMHT(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
			TRootParticle(momentum, vertex, type, charge)
			,hT_(-9999.)
			,significance_(-9999.)
			,nJets_(-9999)
			,nElectrons_(-9999)
			,nMuons_(-9999)
			{;}

		~TRootMHT() {;}
		
		Float_t mht() const { return Pt(); }
		Float_t ht() const { return hT_; }
		Float_t significance() const { return significance_; }
		Float_t error() const { return 0.5*significance_*Pt()*Pt(); }
		Int_t nJets() const { return nJets_;}
		Int_t nMuons() const { return nMuons_;}
		Int_t nElectrons() const { return nElectrons_;}
		virtual TString typeName() const { return "TRootMHT"; }

		void setHT(Float_t hT) { hT_ = hT; }
		void setSignificance(Float_t significance) { significance_ = significance; }
		void setNJets(Int_t nJets) { nJets_ = nJets; }
		void setNElectrons(Int_t nElectrons) { nElectrons_ = nElectrons; }
		void setNMuons(Int_t nMuons) { nMuons_ = nMuons; }

		friend std::ostream& operator<< (std::ostream& stream, const TRootMHT& mHT)
		{
			stream << "TRootMHT  (Pt,Px,Py)=("<< mHT.Pt() <<","<< mHT.Px() <<","<< mHT.Py() << ")";
			return stream;
		};


	private:
		Float_t hT_;
		Float_t significance_;

		Int_t nJets_;
		Int_t nElectrons_;
		Int_t nMuons_;

		ClassDef (TRootMHT,1);
	};
}

#endif
