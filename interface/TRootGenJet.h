#ifndef TRootGenJet_h
#define TRootGenJet_h

#include "../interface/TRootParticle.h"

#include "Rtypes.h"
#include "TObject.h"

#include <iostream>
#include <iomanip>

using namespace std;

namespace TopTree
{
	class TRootGenJet : public TRootParticle
	{

	public:
		TRootGenJet() :
			TRootParticle()
			,etaetaMoment_(-9999.)
			,phiphiMoment_(-9999.)
			,emEnergy_(-9999.)
			,hadEnergy_(-9999.)
			,invisibleEnergy_(-9999.)
			,n90_(-9999)
			,n60_(-9999)
			,nConstituents_(-9999)
			,maxDistance_(-9999)
			{;}
			
		TRootGenJet(const TRootGenJet& genJet) :
			TRootParticle(genJet)
			,etaetaMoment_(genJet.etaetaMoment_)
			,phiphiMoment_(genJet.phiphiMoment_)
			,emEnergy_(genJet.emEnergy_)
			,hadEnergy_(genJet.hadEnergy_)
			,invisibleEnergy_(genJet.invisibleEnergy_)
			,n90_(genJet.n90_)
			,n60_(genJet.n60_)
			,nConstituents_(genJet.nConstituents_)
			,maxDistance_(genJet.maxDistance_)
			{;}
	
		TRootGenJet(Double_t px, Double_t py, Double_t pz, Double_t e) :
			TRootParticle(px,py,px,e)
			,etaetaMoment_(-9999.)
			,phiphiMoment_(-9999.)
			,emEnergy_(-9999.)
			,hadEnergy_(-9999.)
			,invisibleEnergy_(-9999.)
			,n90_(-9999)
			,n60_(-9999)
			,nConstituents_(-9999)
			,maxDistance_(-9999)
			{;}
	
		TRootGenJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
			,etaetaMoment_(-9999.)
			,phiphiMoment_(-9999.)
			,emEnergy_(-9999.)
			,hadEnergy_(-9999.)
			,invisibleEnergy_(-9999.)
			,n90_(-9999)
			,n60_(-9999)
			,nConstituents_(-9999)
			,maxDistance_(-9999)
			{;}
	
		TRootGenJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
			,etaetaMoment_(-9999.)
			,phiphiMoment_(-9999.)
			,emEnergy_(-9999.)
			,hadEnergy_(-9999.)
			,invisibleEnergy_(-9999.)
			,n90_(-9999)
			,n60_(-9999)
			,nConstituents_(-9999)
			,maxDistance_(-9999)
			{;}
	
		TRootGenJet(const TLorentzVector &momentum) :
			TRootParticle(momentum)
			,etaetaMoment_(-9999.)
			,phiphiMoment_(-9999.)
			,emEnergy_(-9999.)
			,hadEnergy_(-9999.)
			,invisibleEnergy_(-9999.)
			,n90_(-9999)
			,n60_(-9999)
			,nConstituents_(-9999)
			,maxDistance_(-9999)
			{;}
	
		TRootGenJet(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
			TRootParticle(momentum, vertex, type, charge)
			,etaetaMoment_(-9999.)
			,phiphiMoment_(-9999.)
			,emEnergy_(-9999.)
			,hadEnergy_(-9999.)
			,invisibleEnergy_(-9999.)
			,n90_(-9999)
			,n60_(-9999)
			,nConstituents_(-9999)
			,maxDistance_(-9999)
			{;}
		
		~TRootGenJet() {;}


		Float_t etaetaMoment() const { return etaetaMoment_; }
		Float_t phiphiMoment() const { return phiphiMoment_; }
		Float_t emEnergy() const { return emEnergy_; }
		Float_t hadEnergy() const { return hadEnergy_; }
		Float_t invisibleEnergy() const { return invisibleEnergy_; }
		Int_t n90() const { return n90_; }
		Int_t n60() const { return n60_; }
		Int_t nConstituents() const { return nConstituents_; }
		Float_t maxDistance() const { return maxDistance_; }

		virtual TString typeName() const { return "TRootGenJet"; }
		
		void setetaetaMoment(Float_t etaetaMoment) { etaetaMoment_ = etaetaMoment; }
		void setphiphiMoment(Float_t phiphiMoment) { phiphiMoment_ = phiphiMoment; }
		void setEMEnergy(Float_t emEnergy) { emEnergy_ = emEnergy; }
		void setHadEnergy(Float_t hadEnergy) { hadEnergy_ = hadEnergy; }
		void setInvisibleEnergy(Float_t invisibleEnergy) { invisibleEnergy_ = invisibleEnergy; }
		void setN90(Int_t n90) { n90_ = n90; }
		void setN60(Int_t n60) { n60_ = n60; }
		void setNConstituents(Int_t nConstituents) { nConstituents_ = nConstituents; }
		void setMaxDistance(Float_t maxDistance) { maxDistance_ = maxDistance; }
		
		friend std::ostream& operator<< (std::ostream& stream, const TRootGenJet& genJet) {
			stream << "TRootGenJet - Charge=" << setw(2) << genJet.charge() << " (Et,eta,phi)=("<< setw(10) << genJet.Et() <<","<< setw(10) << genJet.Eta() <<","<< setw(10) << genJet.Phi() << ")"
					<< " vertex(x,y,z)=("<< genJet.vx() <<","<< genJet.vy() <<","<< genJet.vz() << ")";
			return stream;
		};

	private:
		Float_t etaetaMoment_;					// Added to CaloJet since they seem to be empty for PF
		Float_t phiphiMoment_;					// Added to CaloJet since they seem to be empty for PF
		Float_t emEnergy_;						// EM Energy 
		Float_t hadEnergy_;						// Hadronic Energy
		Float_t invisibleEnergy_;				// Invisible Energy
		Int_t n90_;                         // Number of constituents of the genJet carrying 90% of tje genJet energy
		Int_t n60_;                         // Number of constituents of the genJet carrying 60% of tje genJet energy
		Int_t nConstituents_;               // Number of constituents of the jet
		Float_t maxDistance_;					// Maximum distance from jet to constituent
	
		ClassDef (TRootGenJet,1);
	};
}

#endif
