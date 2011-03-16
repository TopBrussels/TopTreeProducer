#ifndef TRootPFJet_h
#define TRootPFJet_h

#include "../interface/TRootParticle.h"
#include "../interface/TRootJet.h"

#include "Rtypes.h"
#include "TObject.h"

#include <iostream>
#include <iomanip>

using namespace std;

namespace TopTree
{
	class TRootPFJet : public TRootJet
	{

	public:
		TRootPFJet() :
			TRootJet()
			,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			{;}

		TRootPFJet(const TRootPFJet& jet) :
			TRootJet(jet)
			,chargedHadronEnergyFraction_(jet.chargedHadronEnergyFraction_)
			,neutralHadronEnergyFraction_(jet.neutralHadronEnergyFraction_)
			,chargedEmEnergyFraction_(jet.chargedEmEnergyFraction_)
			,chargedMuEnergyFraction_(jet.chargedMuEnergyFraction_)
			,neutralEmEnergyFraction_(jet.neutralEmEnergyFraction_)
			,chargedMultiplicity_(jet.chargedMultiplicity_)
			,neutralMultiplicity_(jet.neutralMultiplicity_)
			,muonMultiplicity_(jet.muonMultiplicity_)
			{;}

		TRootPFJet(const TRootJet& jet) :
			TRootJet(jet)		        
			,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			{;}

		TRootPFJet(Double_t px, Double_t py, Double_t pz, Double_t e) :
			TRootJet(px,py,px,e)
		  ,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			{;}

		TRootPFJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
			TRootJet(px,py,pz,e,vtx_x,vtx_y,vtx_z)
		  ,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			{;}

		TRootPFJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
			TRootJet(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
		  ,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			{;}

		TRootPFJet(const TLorentzVector &momentum) :
			TRootJet(momentum)
			,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			{;}

		TRootPFJet(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
			TRootJet(momentum, vertex, type, charge)
			,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			{;}

		~TRootPFJet() {;}

		Float_t chargedHadronEnergyFraction() const { return chargedHadronEnergyFraction_; }
		Float_t neutralHadronEnergyFraction() const { return neutralHadronEnergyFraction_; }
		Float_t chargedEmEnergyFraction() const { return chargedEmEnergyFraction_; }
		Float_t chargedMuEnergyFraction() const { return chargedMuEnergyFraction_; }
		Float_t neutralEmEnergyFraction() const { return neutralEmEnergyFraction_; }
		Float_t chargedMultiplicity() const { return chargedMultiplicity_; }
		Float_t neutralMultiplicity() const { return neutralMultiplicity_; }
		Float_t muonMultiplicity() const { return muonMultiplicity_; }

		virtual TString typeName() const { return "TRootPFJet"; }

		void setChargedHadronEnergyFraction(Float_t chargedHadronEnergyFraction) { chargedHadronEnergyFraction_ = chargedHadronEnergyFraction; }
		void setNeutralHadronEnergyFraction(Float_t neutralHadronEnergyFraction) { neutralHadronEnergyFraction_ = neutralHadronEnergyFraction; }
		void setChargedEmEnergyFraction(Float_t chargedEmEnergyFraction) { chargedEmEnergyFraction_ = chargedEmEnergyFraction; }
		void setChargedMuEnergyFraction(Float_t chargedMuEnergyFraction) { chargedMuEnergyFraction_ = chargedMuEnergyFraction; }
		void setNeutralEmEnergyFraction(Float_t neutralEmEnergyFraction) { neutralEmEnergyFraction_ = neutralEmEnergyFraction; }
		void setChargedMultiplicity(Float_t chargedMultiplicity) { chargedMultiplicity_ = chargedMultiplicity; }
		void setNeutralMultiplicity(Float_t neutralMultiplicity) { neutralMultiplicity_ = neutralMultiplicity; }
		void setMuonMultiplicity(Float_t muonMultiplicity) { muonMultiplicity_ = muonMultiplicity; }

		friend std::ostream& operator<< (std::ostream& stream, const TRootPFJet& jet)
		{
			stream << "TRootPFJet - Charge=" << setw(2) << jet.charge() << " (Et,eta,phi)=("<< setw(10) << jet.Et() <<","<< setw(10) << jet.Eta() <<","<< setw(10) << jet.Phi() << ")"
				<< " vertex(x,y,z)=("<< jet.vx() <<","<< jet.vy() <<","<< jet.vz() << ")";
			return stream;
		};


	private:

		Float_t chargedHadronEnergyFraction_;
		Float_t neutralHadronEnergyFraction_;
		Float_t chargedEmEnergyFraction_;
		Float_t chargedMuEnergyFraction_;
		Float_t neutralEmEnergyFraction_;
		Float_t chargedMultiplicity_;
		Float_t neutralMultiplicity_;
		Float_t muonMultiplicity_;

		ClassDef (TRootPFJet,1);
	};
}

#endif
