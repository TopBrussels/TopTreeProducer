#ifndef TRootSubstructureJet_h
#define TRootSubstructureJet_h

#include "../interface/TRootParticle.h"
#include "../interface/TRootPFJet.h"

#include "Rtypes.h"
#include "TObject.h"

#include <iostream>
#include <iomanip>

using namespace std;

namespace TopTree
{
	class TRootSubstructureJet : public TRootPFJet
	{

	public:
		TRootSubstructureJet() :
			TRootPFJet()
            ,_filteredMass(-9999.)
            ,_prunedMass(-9999.)
            ,_trimmedMass(-9999.)
            ,_tau1(-9999.)
            ,_tau2(-9999.)
            ,_tau3(-9999.)
            ,_cmsTopTagMinMass(-9999.)
            ,_cmsTopTagMass(-9999.)
            ,_cmsTopTagNsubjets(-9999)

        
        {;}
		
		TRootSubstructureJet(const TRootSubstructureJet& jet) :
        TRootPFJet(jet)
        ,_filteredMass(jet._filteredMass)
        ,_prunedMass(jet._prunedMass)
        ,_trimmedMass(jet._trimmedMass)
        ,_tau1(jet._tau1)
        ,_tau2(jet._tau2)
        ,_tau3(jet._tau3)
        ,_cmsTopTagMinMass(jet._cmsTopTagMinMass)
        ,_cmsTopTagMass(jet._cmsTopTagMass)
        ,_cmsTopTagNsubjets(jet._cmsTopTagNsubjets)
        {;}
	
		TRootSubstructureJet(const TRootPFJet& jet) :
        TRootPFJet(jet)
        ,_filteredMass(-9999.)
        ,_prunedMass(-9999.)
        ,_trimmedMass(-9999.)
        ,_tau1(-9999.)
        ,_tau2(-9999.)
        ,_tau3(-9999.)
        ,_cmsTopTagMinMass(-9999.)
        ,_cmsTopTagMass(-9999.)
        ,_cmsTopTagNsubjets(-9999)
        {;}
	
		TRootSubstructureJet(Double_t px, Double_t py, Double_t pz, Double_t e) :
        TRootPFJet(px,py,px,e)
        ,_filteredMass(-9999.)
        ,_prunedMass(-9999.)
        ,_trimmedMass(-9999.)
        ,_tau1(-9999.)
        ,_tau2(-9999.)
        ,_tau3(-9999.)
        ,_cmsTopTagMinMass(-9999.)
        ,_cmsTopTagMass(-9999.)
        ,_cmsTopTagNsubjets(-9999)

        {;}
	
		TRootSubstructureJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
        TRootPFJet(px,py,pz,e,vtx_x,vtx_y,vtx_z)
        ,_filteredMass(-9999.)
        ,_prunedMass(-9999.)
        ,_trimmedMass(-9999.)
        ,_tau1(-9999.)
        ,_tau2(-9999.)
        ,_tau3(-9999.)
        ,_cmsTopTagMinMass(-9999.)
        ,_cmsTopTagMass(-9999.)
        ,_cmsTopTagNsubjets(-9999)
        {;}
	
		TRootSubstructureJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
        TRootPFJet(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
        ,_filteredMass(-9999.)
        ,_prunedMass(-9999.)
        ,_trimmedMass(-9999.)
        ,_tau1(-9999.)
        ,_tau2(-9999.)
        ,_tau3(-9999.)
        ,_cmsTopTagMinMass(-9999.)
        ,_cmsTopTagMass(-9999.)
        ,_cmsTopTagNsubjets(-9999)

        {;}
	
		TRootSubstructureJet(const TLorentzVector &momentum) :
        TRootPFJet(momentum)
        ,_filteredMass(-9999.)
        ,_prunedMass(-9999.)
        ,_trimmedMass(-9999.)
        ,_tau1(-9999.)
        ,_tau2(-9999.)
        ,_tau3(-9999.)
        ,_cmsTopTagMinMass(-9999.)
        ,_cmsTopTagMass(-9999.)
        ,_cmsTopTagNsubjets(-9999)

        {;}
	
		TRootSubstructureJet(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
        TRootPFJet(momentum, vertex, type, charge)
        ,_filteredMass(-9999.)
        ,_prunedMass(-9999.)
        ,_trimmedMass(-9999.)
        ,_tau1(-9999.)
        ,_tau2(-9999.)
        ,_tau3(-9999.)
        ,_cmsTopTagMinMass(-9999.)
        ,_cmsTopTagMass(-9999.)
        ,_cmsTopTagNsubjets(-9999)

        {;}
		
		~TRootSubstructureJet() {;}
		
		
		virtual TString typeName() const { return "TRootSubstructureJet"; }
		friend std::ostream& operator<< (std::ostream& stream, const TRootSubstructureJet& jet) {
			stream << "TRootSubstructureJet - Charge=" << setw(2) << jet.charge() << " (Et,eta,phi)=("<< setw(10) << jet.Et() <<","<< setw(10) << jet.Eta() <<","<< setw(10) << jet.Phi() << ")"
					<< " vertex(x,y,z)=("<< jet.vx() <<","<< jet.vy() <<","<< jet.vz() << ")";
			return stream;
		};

        void setFilteredMass(Float_t filteredMass){ _filteredMass=filteredMass;}
        void setPrunedMass(Float_t prunedMass){_prunedMass=prunedMass;}
        void setTrimmedMass(Float_t trimmedMass){_trimmedMass=trimmedMass;}
        void setTau1(Float_t tau1){_tau1=tau1;}
        void setTau2(Float_t tau2){_tau2=tau2;}
        void setTau3(Float_t tau3){_tau3=tau3;}
        void setCmsTopTagMinMass(Float_t minMass){_cmsTopTagMinMass=minMass;}
        void setCmsTopTagMass(Float_t mass){_cmsTopTagMass=mass;}
        void setCmsTopTagNsubjets(Int_t nsubjets){_cmsTopTagNsubjets=nsubjets;}
        
        Float_t FilteredMass() const {return _filteredMass;}
        Float_t PrunedMass() const {return _prunedMass;}
        Float_t TrimmedMass() const {return _trimmedMass;}
        Float_t Tau1() const {return _tau1;}
        Float_t Tau2() const {return _tau2;}
        Float_t Tau3() const {return _tau3;}
        Float_t CmsTopTagMinMass() const {return _cmsTopTagMinMass;}
        Float_t CmsTopTagMass() const {return _cmsTopTagMass;}
        Float_t CmsTopTagNsubjets() const {return _cmsTopTagNsubjets;}
        
        bool TopTag() const {
                if(_cmsTopTagNsubjets > 2 && _cmsTopTagMinMass > 50.0 && _cmsTopTagMass > 150.0)
                    return true;
            return false;
        }
        bool WTag() const {
            if( (_tau2/_tau1) > 0.6 && _prunedMass > 50.0)
                return true;
            return false;
        }
        
            
        

	private:
        
        ClassDef (TRootSubstructureJet,1);

        Float_t _filteredMass;
        Float_t _prunedMass;
        Float_t _trimmedMass;
        Float_t _tau1;
        Float_t _tau2;
        Float_t _tau3;
        
        Float_t _cmsTopTagMinMass;
        Float_t _cmsTopTagMass;
        Int_t _cmsTopTagNsubjets;
        
        
	};
}

#endif
