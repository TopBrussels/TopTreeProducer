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
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)			
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)			
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,dZ_(-9999.)
			,dRMean_(-9999.)
			,frac01_(-9999.)
			,frac02_(-9999.)
			,frac03_(-9999.)
			,frac04_(-9999.)
			,frac05_(-9999.)
			,frac06_(-9999.)
			,frac07_(-9999.)
			,RMS_(-9999.)
			,beta_(-9999.)
			,betaStar_(-9999.)
			,betaClassic_(-9999.)
			,betaStarClassic_(-9999.)
			,ptD_(-9999.)
			,mvaID_(-9999.)
			{;}

		TRootPFJet(const TRootPFJet& jet) :
			TRootJet(jet)
			,chargedHadronEnergyFraction_(jet.chargedHadronEnergyFraction_)
			,neutralHadronEnergyFraction_(jet.neutralHadronEnergyFraction_)
			,chargedEmEnergyFraction_(jet.chargedEmEnergyFraction_)
			,chargedMuEnergyFraction_(jet.chargedMuEnergyFraction_)
			,neutralEmEnergyFraction_(jet.neutralEmEnergyFraction_)			
			,HFHadronEnergyFraction_(jet.HFHadronEnergyFraction_)
			,HFEMEnergyFraction_(jet.HFEMEnergyFraction_)
			,chargedMultiplicity_(jet.chargedMultiplicity_)
			,neutralMultiplicity_(jet.neutralMultiplicity_)
			,muonMultiplicity_(jet.muonMultiplicity_)
			,HFHadronMultiplicity_(jet.HFHadronMultiplicity_)
			,HFEMMultiplicity_(jet.HFEMMultiplicity_)			
			,dZ_(jet.dZ_)
			,dRMean_(jet.dRMean_)
			,frac01_(jet.frac01_)
			,frac02_(jet.frac02_)
			,frac03_(jet.frac03_)
			,frac04_(jet.frac04_)
			,frac05_(jet.frac05_)
			,frac06_(jet.frac06_)
			,frac07_(jet.frac07_)
			,RMS_(jet.RMS_)
			,beta_(jet.beta_)
			,betaStar_(jet.betaStar_)
			,betaClassic_(jet.betaClassic_)
			,betaStarClassic_(jet.betaStarClassic_)
			,ptD_(jet.ptD_)
			,mvaID_(jet.mvaID_)
			{;}

		TRootPFJet(const TRootJet& jet) :
			TRootJet(jet)		        
			,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)			
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)			
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)			
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,dZ_(-9999.)
			,dRMean_(-9999.)
			,frac01_(-9999.)
			,frac02_(-9999.)
			,frac03_(-9999.)
			,frac04_(-9999.)
			,frac05_(-9999.)
			,frac06_(-9999.)
			,frac07_(-9999.)
			,RMS_(-9999.)
			,beta_(-9999.)
			,betaStar_(-9999.)
			,betaClassic_(-9999.)
			,betaStarClassic_(-9999.)
			,ptD_(-9999.)
			,mvaID_(-9999.)
			{;}

		TRootPFJet(Double_t px, Double_t py, Double_t pz, Double_t e) :
			TRootJet(px,py,px,e)
		  	,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)			
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)			
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)			
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,dZ_(-9999.)
			,dRMean_(-9999.)
			,frac01_(-9999.)
			,frac02_(-9999.)
			,frac03_(-9999.)
			,frac04_(-9999.)
			,frac05_(-9999.)
			,frac06_(-9999.)
			,frac07_(-9999.)
			,RMS_(-9999.)
			,beta_(-9999.)
			,betaStar_(-9999.)
			,betaClassic_(-9999.)
			,betaStarClassic_(-9999.)
			,ptD_(-9999.)
			,mvaID_(-9999.)
			{;}

		TRootPFJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
			TRootJet(px,py,pz,e,vtx_x,vtx_y,vtx_z)
		  	,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)			
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)			
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)			
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,dZ_(-9999.)
			,dRMean_(-9999.)
			,frac01_(-9999.)
			,frac02_(-9999.)
			,frac03_(-9999.)
			,frac04_(-9999.)
			,frac05_(-9999.)
			,frac06_(-9999.)
			,frac07_(-9999.)
			,RMS_(-9999.)
			,beta_(-9999.)
			,betaStar_(-9999.)
			,betaClassic_(-9999.)
			,betaStarClassic_(-9999.)
			,ptD_(-9999.)
			,mvaID_(-9999.)
			{;}

		TRootPFJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
			TRootJet(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
		  	,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)			
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)			
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)			
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,dZ_(-9999.)
			,dRMean_(-9999.)
			,frac01_(-9999.)
			,frac02_(-9999.)
			,frac03_(-9999.)
			,frac04_(-9999.)
			,frac05_(-9999.)
			,frac06_(-9999.)
			,frac07_(-9999.)
			,RMS_(-9999.)
			,beta_(-9999.)
			,betaStar_(-9999.)
			,betaClassic_(-9999.)
			,betaStarClassic_(-9999.)
			,ptD_(-9999.)
			,mvaID_(-9999.)
			{;}

		TRootPFJet(const TLorentzVector &momentum) :
			TRootJet(momentum)
			,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)			
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)			
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)			
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,dZ_(-9999.)
			,dRMean_(-9999.)
			,frac01_(-9999.)
			,frac02_(-9999.)
			,frac03_(-9999.)
			,frac04_(-9999.)
			,frac05_(-9999.)
			,frac06_(-9999.)
			,frac07_(-9999.)
			,RMS_(-9999.)
			,beta_(-9999.)
			,betaStar_(-9999.)
			,betaClassic_(-9999.)
			,betaStarClassic_(-9999.)
			,ptD_(-9999.)
			,mvaID_(-9999.)
			{;}

		TRootPFJet(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
			TRootJet(momentum, vertex, type, charge)
			,chargedHadronEnergyFraction_(-9999.)
			,neutralHadronEnergyFraction_(-9999.)
			,chargedEmEnergyFraction_(-9999.)
			,chargedMuEnergyFraction_(-9999.)
			,neutralEmEnergyFraction_(-9999.)			
			,HFHadronEnergyFraction_(-9999.)
			,HFEMEnergyFraction_(-9999.)			
			,chargedMultiplicity_(-9999.)
			,neutralMultiplicity_(-9999.)
			,muonMultiplicity_(-9999.)			
			,HFHadronMultiplicity_(-9999.)
			,HFEMMultiplicity_(-9999.)
			,dZ_(-9999.)
			,dRMean_(-9999.)
			,frac01_(-9999.)
			,frac02_(-9999.)
			,frac03_(-9999.)
			,frac04_(-9999.)
			,frac05_(-9999.)
			,frac06_(-9999.)
			,frac07_(-9999.)
			,RMS_(-9999.)
			,beta_(-9999.)
			,betaStar_(-9999.)
			,betaClassic_(-9999.)
			,betaStarClassic_(-9999.)
			,ptD_(-9999.)
			,mvaID_(-9999.)
			{;}

		~TRootPFJet() {;}

		Float_t chargedHadronEnergyFraction() const { return chargedHadronEnergyFraction_; }
		Float_t neutralHadronEnergyFraction() const { return neutralHadronEnergyFraction_; }
		Float_t chargedEmEnergyFraction() const { return chargedEmEnergyFraction_; }
		Float_t chargedMuEnergyFraction() const { return chargedMuEnergyFraction_; }
		Float_t neutralEmEnergyFraction() const { return neutralEmEnergyFraction_; }		
		Float_t HFHadronEnergyFraction() const { return HFHadronEnergyFraction_; }
		Float_t HFEMEnergyFraction() const { return HFEMEnergyFraction_; }		
		Float_t chargedMultiplicity() const { return chargedMultiplicity_; }
		Float_t neutralMultiplicity() const { return neutralMultiplicity_; }
		Float_t muonMultiplicity() const { return muonMultiplicity_; }	  
		Float_t HFHadronMultiplicity() const { return HFHadronMultiplicity_; }
		Float_t HFEMMultiplicity() const { return HFEMMultiplicity_; }
		//Pile-up jet ID
		Float_t dZ() const { return dZ_; }
		Float_t dRMean() const { return dRMean_; }
		Float_t frac01() const { return frac01_; }
		Float_t frac02() const { return frac02_; }
		Float_t frac03() const { return frac03_; }
		Float_t frac04() const { return frac04_; }
		Float_t frac05() const { return frac05_; }
		Float_t frac06() const { return frac06_; }
		Float_t frac07() const { return frac07_; }
		Float_t RMS() const { return RMS_; }
		Float_t beta() const { return beta_; } 
		Float_t betaStar() const { return betaStar_; } 
		Float_t betaClassic() const { return betaClassic_; } 
		Float_t betaStarClassic() const { return betaStarClassic_; } 
		Float_t ptD() const { return ptD_; }
		Float_t mvaID() const { return mvaID_; }

		virtual TString typeName() const { return "TRootPFJet"; }

		void setChargedHadronEnergyFraction(Float_t chargedHadronEnergyFraction) { chargedHadronEnergyFraction_ = chargedHadronEnergyFraction; }
		void setNeutralHadronEnergyFraction(Float_t neutralHadronEnergyFraction) { neutralHadronEnergyFraction_ = neutralHadronEnergyFraction; }
		void setChargedEmEnergyFraction(Float_t chargedEmEnergyFraction) { chargedEmEnergyFraction_ = chargedEmEnergyFraction; }
		void setChargedMuEnergyFraction(Float_t chargedMuEnergyFraction) { chargedMuEnergyFraction_ = chargedMuEnergyFraction; }
		void setNeutralEmEnergyFraction(Float_t neutralEmEnergyFraction) { neutralEmEnergyFraction_ = neutralEmEnergyFraction; }		
		void setHFHadronEnergyFraction(Float_t HFHadronEnergyFraction) { HFHadronEnergyFraction_ = HFHadronEnergyFraction; }
		void setHFEMEnergyFraction(Float_t HFEMEnergyFraction) { HFEMEnergyFraction_ = HFEMEnergyFraction; }		
		void setChargedMultiplicity(Float_t chargedMultiplicity) { chargedMultiplicity_ = chargedMultiplicity; }
		void setNeutralMultiplicity(Float_t neutralMultiplicity) { neutralMultiplicity_ = neutralMultiplicity; }
		void setMuonMultiplicity(Float_t muonMultiplicity) { muonMultiplicity_ = muonMultiplicity; }		
		void setHFHadronMultiplicity(Float_t HFHadronMultiplicity) { HFHadronMultiplicity_ = HFHadronMultiplicity; }
		void setHFEMMultiplicity(Float_t HFEMMultiplicity) { HFEMMultiplicity_ = HFEMMultiplicity; }
		// Pile-up jet ID
		void setDZ(Float_t dZ){ dZ_ = dZ; }
		void setDRMean(Float_t dRMean){ dRMean_ = dRMean; }
		void setFrac01(Float_t frac01){ frac01_ = frac01; }
		void setFrac02(Float_t frac02){ frac02_ = frac02; }
		void setFrac03(Float_t frac03){ frac03_ = frac03; }
		void setFrac04(Float_t frac04){ frac04_ = frac04; }
		void setFrac05(Float_t frac05){ frac05_ = frac05; }
		void setFrac06(Float_t frac06){ frac06_ = frac06; }
		void setFrac07(Float_t frac07){ frac07_ = frac07; }
		void setRMS(Float_t RMS){ RMS_ = RMS; }
		void setBeta(Float_t beta){ beta_ = beta; } 
		void setBetaStar(Float_t betaStar){ betaStar_ = betaStar; } 
		void setBetaClassic(Float_t betaClassic){ betaClassic_ = betaClassic; } 
		void setBetaStarClassic(Float_t betaStarClassic){ betaStarClassic_ = betaStarClassic; } 
		void setPtD(Float_t ptD){ ptD_ = ptD; }
		void setMvaID(Float_t mvaID){ mvaID_ = mvaID; }

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
		Float_t HFHadronEnergyFraction_;
		Float_t HFEMEnergyFraction_;
		Float_t chargedMultiplicity_;
		Float_t neutralMultiplicity_;
		Float_t muonMultiplicity_;
		Float_t HFHadronMultiplicity_;
		Float_t HFEMMultiplicity_;

		//Pile-up jet ID variables
		Float_t dZ_;
		Float_t dRMean_;
		Float_t frac01_;
		Float_t frac02_;
		Float_t frac03_;
		Float_t frac04_;
		Float_t frac05_;
		Float_t frac06_;
		Float_t frac07_;
		Float_t RMS_;
		Float_t beta_; 
		Float_t betaStar_; 
		Float_t betaClassic_; 
		Float_t betaStarClassic_; 
		Float_t ptD_;
		Float_t mvaID_;


		ClassDef (TRootPFJet,3);
	};
}

#endif
