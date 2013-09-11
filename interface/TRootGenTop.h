#ifndef TRootGenTop_h
#define TRootGenTop_h
#include "TRootMCParticle.h"

#include <Math/VectorUtil.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

namespace TopTree
{
	class TRootGenTop : public TRootMCParticle
	{
		public:
		TRootGenTop() :
			TRootMCParticle()
			,isHadronic_(false)
			,isLeptonic_(false)
			,W_ (TRootMCParticle())
			,bquark_ (TRootMCParticle())
			,quark_ (TRootMCParticle())
			,quarkBar_ (TRootMCParticle())
			,lepton_ (TRootMCParticle())
			,neutrino_ (TRootMCParticle())
			,production_ (string(""))
			{};

		TRootGenTop(const TRootMCParticle& top) :
			TRootMCParticle(top)
			,isHadronic_(false)
			,isLeptonic_(false)
			,W_ (TRootMCParticle())
			,bquark_ (TRootMCParticle())
			,quark_ (TRootMCParticle())
			,quarkBar_ (TRootMCParticle())
			,lepton_ (TRootMCParticle())
			,neutrino_ (TRootMCParticle())
			,production_ (string(""))
			{};

		//prod1: lepton prod2: neutrino   or prod1: quark   prod2: quarkBar
		TRootGenTop(const bool isLeptonic, TRootMCParticle& top, TRootMCParticle& W, TRootMCParticle& b, TRootMCParticle& prod1, TRootMCParticle& prod2, string production = string("") )
		{
			(*this) = TRootGenTop(top);
			W_ = W;
			bquark_ = b;
			production_ = production;
			if(isLeptonic)
			{
				isLeptonic_ = isLeptonic;
				lepton_ = prod1;
				neutrino_ = prod2;
			}
			else
			{
				isHadronic_ = true;
				quark_ = prod1;
				quarkBar_ = prod2;
			}
		};

		TRootGenTop(const TRootGenTop& top):TRootMCParticle(top){
			//(*this) = (TRootMCParticle) top;
			isHadronic_ = top.isHadronic_;
			isLeptonic_ = top.isLeptonic_;
			W_ = top.W_;
			bquark_ = top.bquark_;
			quark_ = top.quark_;
			quarkBar_ = top.quarkBar_;
			lepton_ = top.lepton_;
			neutrino_ = top.neutrino_;
			production_ = top.production_;
		};
		~TRootGenTop(){;};

		Bool_t isHadronic() const { return isHadronic_; }
		Bool_t isLeptonic() const { return isLeptonic_; }
		Bool_t isLeptonicMu() const { if(isLeptonic_ && abs(lepton().type())==13) return true ; else return false ;}
		Bool_t isLeptonicEl() const { if(isLeptonic_ && abs(lepton().type())==11) return true ; else return false ;}
		Bool_t isLeptonicTau() const { if(isLeptonic_ && abs(lepton().type())==15) return true ; else return false ;}

		Bool_t isHadronicWellSeparated(float deltaMin = 1.0) const;
		Float_t DeltaRMinHadronicTop() const;
 
		void Production() { cout<<production_<<endl; }
		Int_t From() const { return this->motherType(); }
		Bool_t FromGluino() const { return this->motherType()==1000021 ? true:false; }
		Bool_t FromStop() const { return (abs(this->motherType())==1000006 || abs(this->motherType())==2000006 ) ? true:false; }
		Bool_t FromSbottom() const { return (abs(this->motherType())==1000005 || abs(this->motherType())==2000005 ) ? true:false; }
 
		const TRootMCParticle W() const {return W_;};
		const TRootMCParticle bquark() const {return bquark_;};
		const TRootMCParticle quark() const  {return quark_;};
		const TRootMCParticle quarkBar() const {return quarkBar_;};
		const TRootMCParticle lepton() const {return lepton_;};
		const TRootMCParticle neutrino() const {return neutrino_;};
		friend std::ostream& operator<< (std::ostream& stream, const TRootGenTop& top)
		{
			stream<<"-------------------------------------------"<<endl;
			stream <<"Top ";
			if(top.isHadronic()) stream << "hadronic ";
			if(top.isLeptonic()) stream << "leptonic ";
			if(top.isLeptonicMu()) stream <<"muon ";
			if(top.isLeptonicEl()) stream <<"electron ";
			if(top.isLeptonicTau()) stream <<"tau ";
			stream<<endl;
			stream<<top<<endl;
			stream<<"-------------------------------------------"<<endl;
			return stream ;
		};
 
	private:
 
		Bool_t isHadronic_;
		Bool_t isLeptonic_;
		TRootMCParticle W_;
		TRootMCParticle bquark_;
		TRootMCParticle quark_;
		TRootMCParticle quarkBar_;
		TRootMCParticle lepton_;
		TRootMCParticle neutrino_;
		string production_;

		ClassDef (TRootGenTop,1);
	};
}

#endif
