#ifndef TRootGenJet_h
#define TRootGenJet_h

#include "../interface/TRootParticle.h"
#include "../interface/TRootJet.h"

#include "Rtypes.h"
#include "TObject.h"

#include <iostream>
#include <iomanip>

using namespace std;

class TRootGenJet : public TRootJet
{

public:
	TRootGenJet() :
		TRootJet()
		,etaetaMoment_(-9999.)
		,phiphiMoment_(-9999.)
		,ecalEnergy_(-9999.)
		,hcalEnergy_(-9999.)
		,n90_(-9999)
		,n60_(-9999)
		{;}
		
	TRootGenJet(const TRootGenJet& genJet) :
		TRootJet(genJet)
		,etaetaMoment_(genJet.etaetaMoment_)
		,phiphiMoment_(genJet.phiphiMoment_)
		,ecalEnergy_(genJet.ecalEnergy_)
		,hcalEnergy_(genJet.hcalEnergy_)
		,n90_(genJet.n90_)
		,n60_(genJet.n60_)
		{;}
	
	TRootGenJet(const TRootJet& genJet) :
		TRootJet(genJet)
		,etaetaMoment_(-9999.)
		,phiphiMoment_(-9999.)
		,ecalEnergy_(-9999.)
		,hcalEnergy_(-9999.)
		,n90_(-9999)
		,n60_(-9999)
		{;}
	
	TRootGenJet(Double_t px, Double_t py, Double_t pz, Double_t e) :
		TRootJet(px,py,px,e)
		,etaetaMoment_(-9999.)
		,phiphiMoment_(-9999.)
		,ecalEnergy_(-9999.)
		,hcalEnergy_(-9999.)
		,n90_(-9999)
		,n60_(-9999)
		{;}
	
	TRootGenJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
		TRootJet(px,py,pz,e,vtx_x,vtx_y,vtx_z)
		,etaetaMoment_(-9999.)
		,phiphiMoment_(-9999.)
		,ecalEnergy_(-9999.)
		,hcalEnergy_(-9999.)
		,n90_(-9999)
		,n60_(-9999)
		{;}
	
	TRootGenJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
		TRootJet(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
		,etaetaMoment_(-9999.)
		,phiphiMoment_(-9999.)
		,ecalEnergy_(-9999.)
		,hcalEnergy_(-9999.)
		,n90_(-9999)
		,n60_(-9999)
		{;}
	
	TRootGenJet(const TLorentzVector &momentum) :
		TRootJet(momentum)
		,etaetaMoment_(-9999.)
		,phiphiMoment_(-9999.)
		,ecalEnergy_(-9999.)
		,hcalEnergy_(-9999.)
		,n90_(-9999)
		,n60_(-9999)
		{;}
	
	TRootGenJet(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
		TRootJet(momentum, vertex, type, charge)
		,etaetaMoment_(-9999.)
		,phiphiMoment_(-9999.)
		,ecalEnergy_(-9999.)
		,hcalEnergy_(-9999.)
		,n90_(-9999)
		,n60_(-9999)
		{;}
		
	~TRootGenJet() {;}
	
	
	Float_t etaetaMoment() const { return etaetaMoment_; }
	Float_t phiphiMoment() const { return phiphiMoment_; }
	Float_t ecalEnergy() const { return ecalEnergy_; }
	Float_t hcalEnergy() const { return hcalEnergy_; }
	Int_t n90() const { return n90_; }
	Int_t n60() const { return n60_; }

	virtual TString typeName() const { return "TRootGenJet"; }
		
	void setetaetaMoment(Float_t etaetaMoment) { etaetaMoment_ = etaetaMoment; }
	void setphiphiMoment(Float_t phiphiMoment) { phiphiMoment_ = phiphiMoment; }
	void setEcalEnergy(Float_t ecalEnergy) { ecalEnergy_ = ecalEnergy; }
	void setHcalEnergy(Float_t hcalEnergy) { hcalEnergy_ = hcalEnergy; }
	void setN90(Int_t n90) { n90_ = n90; }
	void setN60(Int_t n60) { n60_ = n60; }
		
	friend std::ostream& operator<< (std::ostream& stream, const TRootGenJet& genJet) {
		stream << "TRootGenJet - Charge=" << setw(2) << genJet.charge() << " (Et,eta,phi)=("<< setw(10) << genJet.Et() <<","<< setw(10) << genJet.Eta() <<","<< setw(10) << genJet.Phi() << ")"
				<< " vertex(x,y,z)=("<< genJet.vx() <<","<< genJet.vy() <<","<< genJet.vz() << ")";
		return stream;
	};


private:

	Float_t etaetaMoment_;					// Added to CaloJet since they seem to be empty for PF
	Float_t phiphiMoment_;					// Added to CaloJet since they seem to be empty for PF
	Float_t ecalEnergy_;        // ECAL Energy 
	Float_t hcalEnergy_;        // HCAL Energy 
	Int_t n90_;                         // Number of constituents of the genJet carrying 90% of tje genJet energy
	Int_t n60_;                         // Number of constituents of the genJet carrying 60% of tje genJet energy
	
	ClassDef (TRootGenJet,1);
};

#endif
