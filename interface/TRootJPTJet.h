#ifndef TRootJPTJet_h
#define TRootJPTJet_h

#include "../interface/TRootParticle.h"
#include "../interface/TRootJet.h"

#include "Rtypes.h"
#include "TObject.h"

#include <iostream>
#include <iomanip>

using namespace std;

namespace TopTree
{
	class TRootJPTJet : public TRootJet
	{

	public:
		TRootJPTJet() :
			TRootJet()
			,n90_(-9999)
			,n60_(-9999)
			,fHPD_(-9999)
			,fRBX_(-9999.)
			,n90Hits_(-9999.)
			,nHCALTowers_(-9999)
			,nECALTowers_(-9999)
			,chargedMultiplicity_(-9999)
		        ,chargedHadronEnergy_(-9999.)
		        ,chargedHadronEnergyFraction_(-9999.)
		        ,neutralHadronEnergy_(-9999.)
		        ,neutralHadronEnergyFraction_(-9999.)
		        ,chargedEmEnergy_(-9999.)
		        ,chargedEmEnergyFraction_(-9999.)
		        ,neutralEmEnergy_(-9999.)
		        ,neutralEmEnergyFraction_(-9999.)
			{;}
		
		TRootJPTJet(const TRootJPTJet& jet) :
			TRootJet(jet)
			,n90_(jet.n90_)
			,n60_(jet.n60_)
			,fHPD_(jet.fHPD_)
			,fRBX_(jet.fRBX_)
			,n90Hits_(jet.n90Hits_)
			,nHCALTowers_(jet.nHCALTowers_)
			,nECALTowers_(jet.nECALTowers_)
			,chargedMultiplicity_(jet.chargedMultiplicity_)
		        ,chargedHadronEnergy_(-9999.)
		        ,chargedHadronEnergyFraction_(-9999.)
		        ,neutralHadronEnergy_(-9999.)
		        ,neutralHadronEnergyFraction_(-9999.)
		        ,chargedEmEnergy_(-9999.)
		        ,chargedEmEnergyFraction_(-9999.)
		        ,neutralEmEnergy_(-9999.)
		        ,neutralEmEnergyFraction_(-9999.)
			{;}
	
		TRootJPTJet(const TRootJet& jet) :
			TRootJet(jet)
			,n90_(-9999)
			,n60_(-9999)
			,fHPD_(-9999)
			,fRBX_(-9999.)
			,n90Hits_(-9999.)
			,nHCALTowers_(-9999)
			,nECALTowers_(-9999)
			,chargedMultiplicity_(-9999)
		        ,chargedHadronEnergy_(-9999.)
		        ,chargedHadronEnergyFraction_(-9999.)
		        ,neutralHadronEnergy_(-9999.)
		        ,neutralHadronEnergyFraction_(-9999.)
		        ,chargedEmEnergy_(-9999.)
		        ,chargedEmEnergyFraction_(-9999.)
		        ,neutralEmEnergy_(-9999.)
		        ,neutralEmEnergyFraction_(-9999.)
			{;}
	
		TRootJPTJet(Double_t px, Double_t py, Double_t pz, Double_t e) :
			TRootJet(px,py,px,e)
			,n90_(-9999)
			,n60_(-9999)
			,fHPD_(-9999)
			,fRBX_(-9999.)
			,n90Hits_(-9999.)
			,nHCALTowers_(-9999)
			,nECALTowers_(-9999)
			,chargedMultiplicity_(-9999)
		        ,chargedHadronEnergy_(-9999.)
		        ,chargedHadronEnergyFraction_(-9999.)
		        ,neutralHadronEnergy_(-9999.)
		        ,neutralHadronEnergyFraction_(-9999.)
		        ,chargedEmEnergy_(-9999.)
		        ,chargedEmEnergyFraction_(-9999.)
		        ,neutralEmEnergy_(-9999.)
		        ,neutralEmEnergyFraction_(-9999.)
			{;}
	
		TRootJPTJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
			TRootJet(px,py,pz,e,vtx_x,vtx_y,vtx_z)
			,n90_(-9999)
			,n60_(-9999)
			,fHPD_(-9999)
			,fRBX_(-9999.)
			,n90Hits_(-9999.)
			,nHCALTowers_(-9999)
			,nECALTowers_(-9999)
			,chargedMultiplicity_(-9999)
		        ,chargedHadronEnergy_(-9999.)
		        ,chargedHadronEnergyFraction_(-9999.)
		        ,neutralHadronEnergy_(-9999.)
		        ,neutralHadronEnergyFraction_(-9999.)
		        ,chargedEmEnergy_(-9999.)
		        ,chargedEmEnergyFraction_(-9999.)
		        ,neutralEmEnergy_(-9999.)
		        ,neutralEmEnergyFraction_(-9999.)
			{;}
	
		TRootJPTJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
			TRootJet(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
			,n60_(-9999)
			,fHPD_(-9999)
			,fRBX_(-9999.)
			,n90Hits_(-9999.)
			,nHCALTowers_(-9999)
			,nECALTowers_(-9999)
			,chargedMultiplicity_(-9999)
		        ,chargedHadronEnergy_(-9999.)
		        ,chargedHadronEnergyFraction_(-9999.)
		        ,neutralHadronEnergy_(-9999.)
		        ,neutralHadronEnergyFraction_(-9999.)
		        ,chargedEmEnergy_(-9999.)
		        ,chargedEmEnergyFraction_(-9999.)
		        ,neutralEmEnergy_(-9999.)
		        ,neutralEmEnergyFraction_(-9999.)
			{;}
	
		TRootJPTJet(const TLorentzVector &momentum) :
			TRootJet(momentum)
			,n90_(-9999)
			,n60_(-9999)
			,fHPD_(-9999)
			,fRBX_(-9999.)
			,n90Hits_(-9999.)
			,nHCALTowers_(-9999)
			,nECALTowers_(-9999)
			,chargedMultiplicity_(-9999)
		        ,chargedHadronEnergy_(-9999.)
		        ,chargedHadronEnergyFraction_(-9999.)
		        ,neutralHadronEnergy_(-9999.)
		        ,neutralHadronEnergyFraction_(-9999.)
		        ,chargedEmEnergy_(-9999.)
		        ,chargedEmEnergyFraction_(-9999.)
		        ,neutralEmEnergy_(-9999.)
		        ,neutralEmEnergyFraction_(-9999.)
			{;}
	
		TRootJPTJet(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
			TRootJet(momentum, vertex, type, charge)
			,n90_(-9999)
			,n60_(-9999)
			,fHPD_(-9999)
			,fRBX_(-9999.)
			,n90Hits_(-9999.)
			,nHCALTowers_(-9999)
			,nECALTowers_(-9999)
			,chargedMultiplicity_(-9999)
		        ,chargedHadronEnergy_(-9999.)
		        ,chargedHadronEnergyFraction_(-9999.)
		        ,neutralHadronEnergy_(-9999.)
		        ,neutralHadronEnergyFraction_(-9999.)
		        ,chargedEmEnergy_(-9999.)
		        ,chargedEmEnergyFraction_(-9999.)
		        ,neutralEmEnergy_(-9999.)
		        ,neutralEmEnergyFraction_(-9999.)
			{;}
		
		~TRootJPTJet() {;}
	
       
		Int_t n90() const { return n90_; }
		Int_t n60() const { return n60_; }
		Float_t fHPD() const { return fHPD_; }
		Float_t fRBX() const { return fRBX_; }
		Float_t n90Hits() const { return n90Hits_; }
		Int_t nHCALTowers() const { return nHCALTowers_; }
		Int_t nECALTowers() const { return nECALTowers_; }
		Int_t chargedMultiplicity() const { return chargedMultiplicity_; }

		Float_t chargedHadronEnergy () const {return chargedHadronEnergy_;}
		Float_t chargedHadronEnergyFraction () const {return chargedHadronEnergyFraction_;}
		Float_t neutralHadronEnergy () const {return neutralHadronEnergy_;}
		Float_t neutralHadronEnergyFraction () const {return neutralHadronEnergyFraction_;}	
		Float_t chargedEmEnergy () const {return chargedEmEnergy_;}
		Float_t chargedEmEnergyFraction () const {return chargedEmEnergyFraction_;}
		Float_t neutralEmEnergy () const {return neutralEmEnergy_;}
		Float_t neutralEmEnergyFraction () const {return neutralEmEnergyFraction_;}

		virtual TString typeName() const { return "TRootJPTJet"; }
		
		void setN90(Int_t n90) { n90_ = n90; }
		void setN60(Int_t n60) { n60_ = n60; }
		void setfHPD(Float_t fHPD) { fHPD_ = fHPD; }
		void setfRBX(Float_t fRBX) { fRBX_ = fRBX; }
		void setn90Hits(Float_t n90Hits) { n90Hits_ = n90Hits; }
		void setnHCALTowers(Int_t nHCALTowers) { nHCALTowers_ = nHCALTowers; }
		void setnECALTowers(Int_t nECALTowers) { nECALTowers_ = nECALTowers; }
		void setChargedMultiplicity(Int_t chargedMultiplicity) { chargedMultiplicity_ = chargedMultiplicity; }

		void chargedHadronEnergy (Float_t x) { chargedHadronEnergy_ = x;}
		void chargedHadronEnergyFraction (Float_t x) { chargedHadronEnergyFraction_ = x;}
		void neutralHadronEnergy (Float_t x) { neutralHadronEnergy_ = x;}
		void neutralHadronEnergyFraction (Float_t x) { neutralHadronEnergyFraction_ = x;}	
		void chargedEmEnergy (Float_t x) { chargedEmEnergy_ = x;}
		void chargedEmEnergyFraction (Float_t x) { chargedEmEnergyFraction_ = x;}
		void neutralEmEnergy (Float_t x) { neutralEmEnergy_ = x;}
		void neutralEmEnergyFraction (Float_t x) { neutralEmEnergyFraction_ = x;}

		
		friend std::ostream& operator<< (std::ostream& stream, const TRootJPTJet& jet) {
			stream << "TRootJPTJet - Charge=" << setw(2) << jet.charge() << " (Et,eta,phi)=("<< setw(10) << jet.Et() <<","<< setw(10) << jet.Eta() <<","<< setw(10) << jet.Phi() << ")"
					<< " vertex(x,y,z)=("<< jet.vx() <<","<< jet.vy() <<","<< jet.vz() << ")";
			return stream;
		};


	private:

   
		Int_t n90_;                         // Number of constituents of the jet carrying 90% of tje jet energy
		Int_t n60_;                         // Number of constituents of the jet carrying 60% of tje jet energy
		Float_t fHPD_;
		Float_t fRBX_;
		Float_t n90Hits_;
		Int_t nHCALTowers_;
		Int_t nECALTowers_;
		Int_t chargedMultiplicity_;

		Float_t chargedHadronEnergy_;
		Float_t chargedHadronEnergyFraction_;
		Float_t neutralHadronEnergy_;
		Float_t neutralHadronEnergyFraction_;
		Float_t chargedEmEnergy_;
		Float_t chargedEmEnergyFraction_;
		Float_t neutralEmEnergy_;
		Float_t neutralEmEnergyFraction_;


		ClassDef (TRootJPTJet,1);
	};
}

#endif
