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
			,muonEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,hadronFlavour_(-9999.)
			,inclusiveJetCharge_(-9999.)
			{;}

		TRootPFJet(const TRootPFJet& jet) :
			TRootJet(jet)
			,chargedHadronEnergyFraction_(jet.chargedHadronEnergyFraction_)
			,neutralHadronEnergyFraction_(jet.neutralHadronEnergyFraction_)
			,chargedEmEnergyFraction_(jet.chargedEmEnergyFraction_)
			,chargedMuEnergyFraction_(jet.chargedMuEnergyFraction_)
			,muonEnergyFraction_(jet.muonEnergyFraction_)
			,neutralEmEnergyFraction_(jet.neutralEmEnergyFraction_)
			,HFHadronEnergyFraction_(jet.HFHadronEnergyFraction_)
			,HFEMEnergyFraction_(jet.HFEMEnergyFraction_)
			,chargedMultiplicity_(jet.chargedMultiplicity_)
			,neutralMultiplicity_(jet.neutralMultiplicity_)
			,muonMultiplicity_(jet.muonMultiplicity_)
			,HFHadronMultiplicity_(jet.HFHadronMultiplicity_)
			,HFEMMultiplicity_(jet.HFEMMultiplicity_)
			,hadronFlavour_(jet.hadronFlavour_)
			,inclusiveJetCharge_(jet.inclusiveJetCharge_)
			{;}

		TRootPFJet(const TRootJet& jet) :
			TRootJet(jet)
			,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,muonEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,hadronFlavour_(-9999.)
			,inclusiveJetCharge_(-9999.)
			{;}

		TRootPFJet(Double_t px, Double_t py, Double_t pz, Double_t e) :
			TRootJet(px,py,px,e)
			,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,muonEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,hadronFlavour_(-9999.)
			,inclusiveJetCharge_(-9999.)
			{;}

		TRootPFJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
			TRootJet(px,py,pz,e,vtx_x,vtx_y,vtx_z)
			,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,muonEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,hadronFlavour_(-9999.)
			,inclusiveJetCharge_(-9999.)
			{;}

		TRootPFJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
			TRootJet(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
		  ,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,muonEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,hadronFlavour_(-9999.)
			,inclusiveJetCharge_(-9999.)
			{;}

		TRootPFJet(const TLorentzVector &momentum) :
			TRootJet(momentum)
			,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,muonEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,hadronFlavour_(-9999.)
			,inclusiveJetCharge_(-9999.)
			{;}

		TRootPFJet(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
			TRootJet(momentum, vertex, type, charge)
			,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,muonEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,hadronFlavour_(-9999.)
			,inclusiveJetCharge_(-9999.)
			{;}

		~TRootPFJet() {;}

		Float_t chargedHadronEnergyFraction() const { return chargedHadronEnergyFraction_; }
		Float_t neutralHadronEnergyFraction() const { return neutralHadronEnergyFraction_; }
		Float_t chargedEmEnergyFraction() const { return chargedEmEnergyFraction_; }
		Float_t chargedMuEnergyFraction() const { return chargedMuEnergyFraction_; }
		Float_t muonEnergyFraction() const { return muonEnergyFraction_; }
		Float_t neutralEmEnergyFraction() const { return neutralEmEnergyFraction_; }
		Float_t HFHadronEnergyFraction() const { return HFHadronEnergyFraction_; }
		Float_t HFEMEnergyFraction() const { return HFEMEnergyFraction_; }
		Float_t chargedMultiplicity() const { return chargedMultiplicity_; }
		Float_t neutralMultiplicity() const { return neutralMultiplicity_; }
		Float_t muonMultiplicity() const { return muonMultiplicity_; }
		Float_t HFHadronMultiplicity() const { return HFHadronMultiplicity_; }
		Float_t HFEMMultiplicity() const { return HFEMMultiplicity_; }
		Float_t hadronFlavour() const { return hadronFlavour_; }
		Float_t inclusiveJetCharge() const { return inclusiveJetCharge_; }


		virtual TString typeName() const { return "TRootPFJet"; }

		void setChargedHadronEnergyFraction(Float_t chargedHadronEnergyFraction) { chargedHadronEnergyFraction_ = chargedHadronEnergyFraction; }
		void setNeutralHadronEnergyFraction(Float_t neutralHadronEnergyFraction) { neutralHadronEnergyFraction_ = neutralHadronEnergyFraction; }
		void setChargedEmEnergyFraction(Float_t chargedEmEnergyFraction) { chargedEmEnergyFraction_ = chargedEmEnergyFraction; }
		void setChargedMuEnergyFraction(Float_t chargedMuEnergyFraction) { chargedMuEnergyFraction_ = chargedMuEnergyFraction; }
		void setMuonEnergyFraction(Float_t muonEnergyFraction) { muonEnergyFraction_ = muonEnergyFraction; }
		void setNeutralEmEnergyFraction(Float_t neutralEmEnergyFraction) { neutralEmEnergyFraction_ = neutralEmEnergyFraction; }
		void setHFHadronEnergyFraction(Float_t HFHadronEnergyFraction) { HFHadronEnergyFraction_ = HFHadronEnergyFraction; }
		void setHFEMEnergyFraction(Float_t HFEMEnergyFraction) { HFEMEnergyFraction_ = HFEMEnergyFraction; }
		void setChargedMultiplicity(Float_t chargedMultiplicity) { chargedMultiplicity_ = chargedMultiplicity; }
		void setNeutralMultiplicity(Float_t neutralMultiplicity) { neutralMultiplicity_ = neutralMultiplicity; }
		void setMuonMultiplicity(Float_t muonMultiplicity) { muonMultiplicity_ = muonMultiplicity; }
		void setHFHadronMultiplicity(Float_t HFHadronMultiplicity) { HFHadronMultiplicity_ = HFHadronMultiplicity; }
		void setHFEMMultiplicity(Float_t HFEMMultiplicity) { HFEMMultiplicity_ = HFEMMultiplicity; }
		void setHadronFlavour(Float_t hadronFlavour) { hadronFlavour_ = hadronFlavour; }
		void setinclusiveJetCharge(Float_t inclusiveJetCharge) { inclusiveJetCharge_ = inclusiveJetCharge; }


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
		Float_t muonEnergyFraction_;
		Float_t neutralEmEnergyFraction_;
		Float_t HFHadronEnergyFraction_;
		Float_t HFEMEnergyFraction_;
		Float_t chargedMultiplicity_;
		Float_t neutralMultiplicity_;
		Float_t muonMultiplicity_;
		Float_t HFHadronMultiplicity_;
		Float_t HFEMMultiplicity_;
		Float_t hadronFlavour_;
    Float_t inclusiveJetCharge_;

		ClassDef (TRootPFJet,3);
	};
}

#endif
