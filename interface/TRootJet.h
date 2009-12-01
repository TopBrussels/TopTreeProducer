#ifndef TRootJet_h
#define TRootJet_h

#include "../interface/TRootParticle.h"

#include "Rtypes.h"
#include "TObject.h"

#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

class TRootJet : public TRootParticle
{
	
public:
	TRootJet() :
		TRootParticle()
		,jetType_(0)
		,nConstituents_(-9999)
		,chargedMultiplicity_(-9999)
		,n90_(-9999)
		,n60_(-9999)
		,jetArea_(-9999.)
		,pileupEnergy_(-9999.)
		,maxDistance_(-9999.)
		,ecalEnergyFraction_(-9999.)
		,hcalEnergyFraction_(-9999.)
		,chargedEnergyFraction_(-9999.)
                ,maxEInEmTowers_(-9999.)
                ,maxEInHadTowers_(-9999.)
	        ,towersArea_(-9999.) 
		,jetIdVariables_(std::map<std::string, Float_t> ())
		,chargedBroadness_(-9999.)
	        ,btag_combinedSecondaryVertexBJetTags_(-9999.)
	        ,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
	        ,btag_impactParameterMVABJetTags_(-9999.)
	        ,btag_jetBProbabilityBJetTags_(-9999.)
	        ,btag_jetProbabilityBJetTags_(-9999.)
	        ,btag_simpleSecondaryVertexBJetTags_(-9999.)
	        ,btag_softElectronBJetTags_(-9999.)
	        ,btag_softMuonBJetTags_(-9999.)
	        ,btag_softMuonNoIPBJetTags_(-9999.)
	        ,btag_trackCountingHighEffBJetTags_(-9999.)
	        ,btag_trackCountingHighPurBJetTags_(-9999.)
		,bCorrection_(-9999.)
		,cCorrection_(-9999.)
		,udsCorrection_(-9999.)
		,gCorrection_(-9999.)
		,partonFlavour_(-999)
		,isTopJet_(false)
		,genParton_(0)
		{;}

	TRootJet(const TRootJet& jet) :
		TRootParticle(jet)
		,jetType_(jet.jetType_)
		,nConstituents_(jet.nConstituents_)
		,chargedMultiplicity_(jet.chargedMultiplicity_)
		,n90_(jet.n90_)
		,n60_(jet.n60_)
		,jetArea_(jet.jetArea_)
		,pileupEnergy_(jet.pileupEnergy_)
		,maxDistance_(jet.maxDistance_)
		,ecalEnergyFraction_(jet.ecalEnergyFraction_)
		,hcalEnergyFraction_(jet.hcalEnergyFraction_)
		,chargedEnergyFraction_(jet.chargedEnergyFraction_)
                ,maxEInEmTowers_(jet.maxEInEmTowers_)
                ,maxEInHadTowers_(jet.maxEInHadTowers_)
	        ,towersArea_(jet.towersArea_) 
		,jetIdVariables_(jet.jetIdVariables_)
		,chargedBroadness_(jet.chargedBroadness_)
	        ,btag_combinedSecondaryVertexBJetTags_(jet.btag_combinedSecondaryVertexBJetTags_)
	        ,btag_combinedSecondaryVertexMVABJetTags_(jet.btag_combinedSecondaryVertexMVABJetTags_)
	        ,btag_impactParameterMVABJetTags_(jet.btag_impactParameterMVABJetTags_)
	        ,btag_jetBProbabilityBJetTags_(jet.btag_jetBProbabilityBJetTags_)
	        ,btag_jetProbabilityBJetTags_(jet.btag_jetProbabilityBJetTags_)
	        ,btag_simpleSecondaryVertexBJetTags_(jet.btag_simpleSecondaryVertexBJetTags_)
	        ,btag_softElectronBJetTags_(jet.btag_softElectronBJetTags_)
	        ,btag_softMuonBJetTags_(jet.btag_softMuonBJetTags_)
	        ,btag_softMuonNoIPBJetTags_(jet.btag_softMuonNoIPBJetTags_)
	        ,btag_trackCountingHighEffBJetTags_(jet.btag_trackCountingHighEffBJetTags_)
	        ,btag_trackCountingHighPurBJetTags_(jet.btag_trackCountingHighPurBJetTags_)
		,bCorrection_(jet.bCorrection_)
		,cCorrection_(jet.cCorrection_)
		,udsCorrection_(jet.udsCorrection_)
		,gCorrection_(jet.gCorrection_)
	        ,partonFlavour_(jet.partonFlavour_)
		,isTopJet_(jet.isTopJet_)
		,genParton_(jet.genParton_)
		{;}

	TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e) :
		TRootParticle(px,py,pz,e)
		,jetType_(0)
		,nConstituents_(-9999)
		,chargedMultiplicity_(-9999)
		,n90_(-9999)
		,n60_(-9999)
		,jetArea_(-9999.)
		,pileupEnergy_(-9999.)
		,maxDistance_(-9999.)
		,ecalEnergyFraction_(-9999.)
		,hcalEnergyFraction_(-9999.)
		,chargedEnergyFraction_(-9999.)
                ,maxEInEmTowers_(-9999.)
                ,maxEInHadTowers_(-9999.)
	        ,towersArea_(-9999.) 
		,jetIdVariables_(std::map<std::string, Float_t> ())
		,chargedBroadness_(-9999.)
	        ,btag_combinedSecondaryVertexBJetTags_(-9999.)
	        ,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
	        ,btag_impactParameterMVABJetTags_(-9999.)
	        ,btag_jetBProbabilityBJetTags_(-9999.)
	        ,btag_jetProbabilityBJetTags_(-9999.)
	        ,btag_simpleSecondaryVertexBJetTags_(-9999.)
	        ,btag_softElectronBJetTags_(-9999.)
	        ,btag_softMuonBJetTags_(-9999.)
	        ,btag_softMuonNoIPBJetTags_(-9999.)
	        ,btag_trackCountingHighEffBJetTags_(-9999.)
	        ,btag_trackCountingHighPurBJetTags_(-9999.)
		,bCorrection_(-9999.)
		,cCorrection_(-9999.)
		,udsCorrection_(-9999.)
		,gCorrection_(-9999.)
		,partonFlavour_(-9999)
		,isTopJet_(false)
		,genParton_(0)
		{;}
	
	TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
		TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
		,jetType_(0)
		,nConstituents_(-9999)
		,chargedMultiplicity_(-9999)
		,n90_(-9999)
		,n60_(-9999)
		,jetArea_(-9999.)
		,pileupEnergy_(-9999.)
		,maxDistance_(-9999.)
		,ecalEnergyFraction_(-9999.)
		,hcalEnergyFraction_(-9999.)
		,chargedEnergyFraction_(-9999.)
                ,maxEInEmTowers_(-9999.)
                ,maxEInHadTowers_(-9999.)
	        ,towersArea_(-9999.) 
		,jetIdVariables_(std::map<std::string, Float_t> ())
		,chargedBroadness_(-9999.)
	        ,btag_combinedSecondaryVertexBJetTags_(-9999.)
	        ,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
	        ,btag_impactParameterMVABJetTags_(-9999.)
	        ,btag_jetBProbabilityBJetTags_(-9999.)
	        ,btag_jetProbabilityBJetTags_(-9999.)
	        ,btag_simpleSecondaryVertexBJetTags_(-9999.)
	        ,btag_softElectronBJetTags_(-9999.)
	        ,btag_softMuonBJetTags_(-9999.)
	        ,btag_softMuonNoIPBJetTags_(-9999.)
	        ,btag_trackCountingHighEffBJetTags_(-9999.)
	        ,btag_trackCountingHighPurBJetTags_(-9999.)
		,bCorrection_(-9999.)
		,cCorrection_(-9999.)
		,udsCorrection_(-9999.)
		,gCorrection_(-9999.)
		,partonFlavour_(-9999)
		,isTopJet_(false)
		,genParton_(0)
		{;}

	TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
		TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
		,jetType_(0)
		,nConstituents_(-9999)
		,chargedMultiplicity_(-9999)
		,n90_(-9999)
		,n60_(-9999)
		,jetArea_(-9999.)
		,pileupEnergy_(-9999.)
		,maxDistance_(-9999.)
		,ecalEnergyFraction_(-9999.)
		,hcalEnergyFraction_(-9999.)
		,chargedEnergyFraction_(-9999.)
                ,maxEInEmTowers_(-9999.)
                ,maxEInHadTowers_(-9999.)
	        ,towersArea_(-9999.) 
		,jetIdVariables_(std::map<std::string, Float_t> ())
		,chargedBroadness_(-9999.)
	        ,btag_combinedSecondaryVertexBJetTags_(-9999.)
	        ,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
	        ,btag_impactParameterMVABJetTags_(-9999.)
	        ,btag_jetBProbabilityBJetTags_(-9999.)
	        ,btag_jetProbabilityBJetTags_(-9999.)
	        ,btag_simpleSecondaryVertexBJetTags_(-9999.)
	        ,btag_softElectronBJetTags_(-9999.)
	        ,btag_softMuonBJetTags_(-9999.)
	        ,btag_softMuonNoIPBJetTags_(-9999.)
	        ,btag_trackCountingHighEffBJetTags_(-9999.)
	        ,btag_trackCountingHighPurBJetTags_(-9999.)
		,bCorrection_(-9999.)
		,cCorrection_(-9999.)
		,udsCorrection_(-9999.)
		,gCorrection_(-9999.)
		,partonFlavour_(-9999)
		,isTopJet_(false)
		,genParton_(0)
		{;}

	TRootJet(const TLorentzVector &momentum) :
		TRootParticle(momentum)
		,jetType_(0)
		,nConstituents_(-9999)
		,chargedMultiplicity_(-9999)
		,n90_(-9999)
		,n60_(-9999)
		,jetArea_(-9999.)
		,pileupEnergy_(-9999.)
		,maxDistance_(-9999.)
		,ecalEnergyFraction_(-9999.)
		,hcalEnergyFraction_(-9999.)
                ,maxEInEmTowers_(-9999.)
                ,maxEInHadTowers_(-9999.)
	        ,towersArea_(-9999.) 
		,jetIdVariables_(std::map<std::string, Float_t> ())
		,chargedBroadness_(-9999.)
	        ,btag_combinedSecondaryVertexBJetTags_(-9999.)
	        ,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
	        ,btag_impactParameterMVABJetTags_(-9999.)
	        ,btag_jetBProbabilityBJetTags_(-9999.)
	        ,btag_jetProbabilityBJetTags_(-9999.)
	        ,btag_simpleSecondaryVertexBJetTags_(-9999.)
	        ,btag_softElectronBJetTags_(-9999.)
	        ,btag_softMuonBJetTags_(-9999.)
	        ,btag_softMuonNoIPBJetTags_(-9999.)
	        ,btag_trackCountingHighEffBJetTags_(-9999.)
	        ,btag_trackCountingHighPurBJetTags_(-9999.)
		,bCorrection_(-9999.)
		,cCorrection_(-9999.)
		,udsCorrection_(-9999.)
		,gCorrection_(-9999.)
		,partonFlavour_(-9999)
		,isTopJet_(false)
		,genParton_(0)
		{;}

	TRootJet(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
		TRootParticle(momentum, vertex, type, charge)
		,jetType_(0)
		,nConstituents_(-9999)
		,chargedMultiplicity_(-9999)
		,n90_(-9999)
		,n60_(-9999)
		,jetArea_(-9999.)
		,pileupEnergy_(-9999.)
		,maxDistance_(-9999.)
		,ecalEnergyFraction_(-9999.)
		,hcalEnergyFraction_(-9999.)
		,chargedEnergyFraction_(-9999.)
                ,maxEInEmTowers_(-9999.)
                ,maxEInHadTowers_(-9999.)
	        ,towersArea_(-9999.) 
		,jetIdVariables_(std::map<std::string, Float_t> ())
		,chargedBroadness_(-9999.)
	        ,btag_combinedSecondaryVertexBJetTags_(-9999.)
	        ,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
	        ,btag_impactParameterMVABJetTags_(-9999.)
	        ,btag_jetBProbabilityBJetTags_(-9999.)
	        ,btag_jetProbabilityBJetTags_(-9999.)
	        ,btag_simpleSecondaryVertexBJetTags_(-9999.)
	        ,btag_softElectronBJetTags_(-9999.)
	        ,btag_softMuonBJetTags_(-9999.)
	        ,btag_softMuonNoIPBJetTags_(-9999.)
	        ,btag_trackCountingHighEffBJetTags_(-9999.)
	        ,btag_trackCountingHighPurBJetTags_(-9999.)
		,bCorrection_(-9999.)
		,cCorrection_(-9999.)
		,udsCorrection_(-9999.)
		,gCorrection_(-9999.)
		,partonFlavour_(-9999)
		,isTopJet_(false)
		,genParton_(0)
		{;}

	~TRootJet() {;}


	Int_t jetType() const { return jetType_; }
	Int_t nConstituents() const { return nConstituents_; }
	Int_t chargedMultiplicity() const { return chargedMultiplicity_; }
	Int_t n90() const { return n90_; }
	Int_t n60() const { return n60_; }
	Float_t jetArea() const { return jetArea_; }
	Float_t pileupEnergy() const { return pileupEnergy_; }
	Float_t maxDistance() const { return maxDistance_; }
	Float_t ecalEnergyFraction() const { return ecalEnergyFraction_; }
	Float_t hcalEnergyFraction() const { return hcalEnergyFraction_; }
	Float_t chargedEnergyFraction() const { return chargedEnergyFraction_; }
        Float_t maxEInEmTowers() const { return maxEInEmTowers_; }
        Float_t maxEInHadTowers() const { return maxEInHadTowers_;}
	Float_t towersArea() const { return towersArea_;} 
	std::map<std::string, Float_t> jetIdVariables() const { return jetIdVariables_; }
	Float_t chargedBroadness() const { return chargedBroadness_; }
	Float_t btag_combinedSecondaryVertexBJetTags() const { return btag_combinedSecondaryVertexBJetTags_;}
	Float_t btag_combinedSecondaryVertexMVABJetTags() const { return btag_combinedSecondaryVertexMVABJetTags_;}
	Float_t btag_impactParameterMVABJetTags() const { return btag_impactParameterMVABJetTags_;}
	Float_t btag_jetBProbabilityBJetTags() const { return btag_jetBProbabilityBJetTags_;}
	Float_t btag_jetProbabilityBJetTags() const { return btag_jetProbabilityBJetTags_;}
	Float_t btag_simpleSecondaryVertexBJetTags() const { return btag_simpleSecondaryVertexBJetTags_;}
	Float_t btag_softElectronBJetTags() const { return btag_softElectronBJetTags_;}
	Float_t btag_softMuonBJetTags() const { return btag_softMuonBJetTags_;}
	Float_t btag_softMuonNoIPBJetTags() const { return btag_softMuonNoIPBJetTags_;}
	Float_t btag_trackCountingHighEffBJetTags() const { return btag_trackCountingHighEffBJetTags_;}
	Float_t btag_trackCountingHighPurBJetTags() const { return btag_trackCountingHighPurBJetTags_;}
	Float_t bCorrection() const { return bCorrection_; }
	Float_t cCorrection() const { return cCorrection_; }
	Float_t udsCorrection() const { return udsCorrection_; }
	Float_t gCorrection() const { return gCorrection_; }
	TObject* genParton() const { return genParton_.GetObject(); }
	Int_t partonFlavour() const {return partonFlavour_; }
	//Float_t partonFlavour() const {return partonFlavour_; }
	Bool_t isTopJet() const { return isTopJet_; }

	virtual TString typeName() const { return "TRootJet"; }


	void setJetType(Int_t jetType) { jetType_ = jetType; }
	void setNConstituents(Int_t nConstituents) { nConstituents_ = nConstituents; }
	void setChargedMultiplicity(Int_t chargedMultiplicity) { chargedMultiplicity_ = chargedMultiplicity; }
	void setN90(Int_t n90) { n90_ = n90; }
	void setN60(Int_t n60) { n60_ = n60; }
	void setJetArea(Float_t jetArea) { jetArea_ = jetArea; }
	void setPileupEnergy(Float_t pileupEnergy) { pileupEnergy_ = pileupEnergy; }
	void setMaxDistance(Float_t maxDistance) { maxDistance_ = maxDistance; }
	void setMaxEInEmTowers(Float_t maxEInEmTowers) { maxEInEmTowers_ = maxEInEmTowers; }
	void setTowersArea(Float_t towersArea) {towersArea_ = towersArea; }
	void setMaxEInHadTowers(Float_t maxEInHadTowers) { maxEInHadTowers_ = maxEInHadTowers; }
	void setEcalEnergyFraction(Float_t ecalEnergyFraction) { ecalEnergyFraction_ = ecalEnergyFraction; }
	void setHcalEnergyFraction(Float_t hcalEnergyFraction) { hcalEnergyFraction_ = hcalEnergyFraction; }
	void setChargedEnergyFraction(Float_t chargedEnergyFraction) { chargedEnergyFraction_ = chargedEnergyFraction; }
	void setJetIdVariables(std::map<std::string, Float_t> jetIdVariables) { jetIdVariables_ = jetIdVariables; }
	void setChargedBroadness(Float_t chargedBroadness) { chargedBroadness_ = chargedBroadness; }
	//btag
	void setBtag_combinedSecondaryVertexBJetTags(Float_t btag_combinedSecondaryVertexBJetTags) { btag_combinedSecondaryVertexBJetTags_ = btag_combinedSecondaryVertexBJetTags;};
	void setBtag_combinedSecondaryVertexMVABJetTags(Float_t btag_combinedSecondaryVertexMVABJetTags ) { btag_combinedSecondaryVertexMVABJetTags_ = btag_combinedSecondaryVertexMVABJetTags;};
	void setBtag_impactParameterMVABJetTags(Float_t btag_impactParameterMVABJetTags ) { btag_impactParameterMVABJetTags_ = btag_impactParameterMVABJetTags;};
	void setBtag_jetBProbabilityBJetTags(Float_t btag_jetBProbabilityBJetTags ) { btag_jetBProbabilityBJetTags_ = btag_jetBProbabilityBJetTags;};
	void setBtag_jetProbabilityBJetTags(Float_t btag_jetProbabilityBJetTags ) { btag_jetProbabilityBJetTags_ = btag_jetProbabilityBJetTags;};
	void setBtag_simpleSecondaryVertexBJetTags(Float_t btag_simpleSecondaryVertexBJetTags ) { btag_simpleSecondaryVertexBJetTags_ = btag_simpleSecondaryVertexBJetTags;};
	void setBtag_softElectronBJetTags(Float_t btag_softElectronBJetTags ) { btag_softElectronBJetTags_ = btag_softElectronBJetTags;};
	void setBtag_softMuonBJetTags(Float_t btag_softMuonBJetTags ) { btag_softMuonBJetTags_ = btag_softMuonBJetTags;};
	void setBtag_softMuonNoIPBJetTags(Float_t btag_softMuonNoIPBJetTags ) { btag_softMuonNoIPBJetTags_ = btag_softMuonNoIPBJetTags;};
	void setBtag_trackCountingHighEffBJetTags(Float_t btag_trackCountingHighEffBJetTags ) { btag_trackCountingHighEffBJetTags_ = btag_trackCountingHighEffBJetTags;};
	void setBtag_trackCountingHighPurBJetTags(Float_t btag_trackCountingHighPurBJetTags) { btag_trackCountingHighPurBJetTags_ = btag_trackCountingHighPurBJetTags;};
	void setBCorrection(Float_t bCorrection) { bCorrection_ = bCorrection; }
	void setCCorrection(Float_t cCorrection) { cCorrection_ = cCorrection; }
	void setUDSCorrection(Float_t udsCorrection) { udsCorrection_ = udsCorrection; }
	void setGCorrection(Float_t gCorrection) { gCorrection_ = gCorrection; }
	void setPartonFlavour(Int_t partonFlavour) { partonFlavour_ = partonFlavour;}
	void setIsTopJet(Bool_t isTopJet) { isTopJet_ = isTopJet; }
	void setGenParton(TObject* genParton) { genParton_ = genParton; }

	friend std::ostream& operator<< (std::ostream& stream, const TRootJet& jet) {
		stream << "TRootJet - Charge=" << setw(2) << jet.charge() << " (Et,eta,phi)=("<< setw(10) << jet.Et() <<","<< setw(10) << jet.Eta() <<","<< setw(10) << jet.Phi() << ")"
				<< " vertex(x,y,z)=("<< jet.vx() <<","<< jet.vy() <<","<< jet.vz() << ")";
		return stream;
	};


private:
        //CaloJet Info
        Int_t jetType_;                     // 0 = Unknown ; 1 = CaloJet ; 2 = PFJet
	Int_t nConstituents_;               // Number of constituents of the jet (calotowers for CaloJet / PFParticles for PFJet)
	Int_t chargedMultiplicity_;         // Number of tracks associated to the jet. Not available for reco::CaloJet
	Int_t n90_;                         // Number of constituents of the jet carrying 90% of tje jet energy
	Int_t n60_;                         // Number of constituents of the jet carrying 60% of tje jet energy
	Float_t jetArea_;                   // Jet area
	Float_t pileupEnergy_;               // Pile-up Energy
	Float_t maxDistance_;               // Maximum distance from jet to constituent
	Float_t ecalEnergyFraction_;        // ECAL Energy Fraction
	Float_t hcalEnergyFraction_;        // HCAL Energy Fraction
        Float_t chargedEnergyFraction_;     // Charged Energy Fraction - Only available for reco::PFJet        
        Float_t maxEInEmTowers_;
        Float_t maxEInHadTowers_;
	Float_t towersArea_; 
	std::map<std::string, Float_t> jetIdVariables_;	// Stores the jetIdVaribles
	
	// Variables from pat::Jet
        
	Float_t chargedBroadness_;          // DR of the cone containing 75% of the jet charged energy 
        
	//btag Info
	Float_t btag_combinedSecondaryVertexBJetTags_;
	Float_t btag_combinedSecondaryVertexMVABJetTags_;
	Float_t btag_impactParameterMVABJetTags_;
	Float_t btag_jetBProbabilityBJetTags_;
	Float_t btag_jetProbabilityBJetTags_;
	Float_t btag_simpleSecondaryVertexBJetTags_;
	Float_t btag_softElectronBJetTags_;
	Float_t btag_softMuonBJetTags_;
	Float_t btag_softMuonNoIPBJetTags_;
	Float_t btag_trackCountingHighEffBJetTags_;
	Float_t btag_trackCountingHighPurBJetTags_;

        //Correction Info
	Float_t bCorrection_;               // correction factor for b hypothesis
	Float_t cCorrection_;               // correction factor for c hypothesis
	Float_t udsCorrection_;             // correction factor for uds hypothesis
	Float_t gCorrection_;               // correction factor for gluon hypothesis

	//MC info
        Int_t partonFlavour_;
	Bool_t isTopJet_;				// Is parton matched to the jet a decay product of the top quark ?
        TRef genParton_;	
  ClassDef (TRootJet,1);
};

#endif
