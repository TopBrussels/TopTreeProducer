#ifndef TRootJet_h
#define TRootJet_h

#include "../interface/TRootParticle.h"

#include "Rtypes.h"
#include "TObject.h"

#include <iostream>
#include <iomanip>

// Specific methods for PF and Calo can be found on:
// http://cms-service-sdtweb.web.cern.ch/cms-service-sdtweb/doxygen/CMSSW_3_5_2/doc/html/df/d60/DataFormats_2PatCandidates_2interface_2Jet_8h-source.html#l00212

using namespace std;

namespace TopTree
{
	class TRootJet : public TRootParticle
	{
	
	public:
		TRootJet() :
			TRootParticle()
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,pileupEnergy_(-9999.)
			,maxDistance_(-9999.)
			,chargedBroadness_(-9999.)
			,btag_jetBProbabilityBJetTags_(-9999.)
			,btag_jetProbabilityBJetTags_(-9999.)
			,btag_trackCountingHighPurBJetTags_(-9999.)
			,btag_trackCountingHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighPurBJetTags_(-9999.)
			,btag_combinedSecondaryVertexBJetTags_(-9999.)
			,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
		  	,btag_combinedMVABJetTags_(-9999.)
			,btag_softMuonBJetTags_(-9999.)
			,btag_softMuonByPtBJetTags_(-9999.)
			,btag_softMuonByIP3dBJetTags_(-9999.)
		        ,btag_softElectronBJetTags_(-9999.)
			,btag_softElectronByPtBJetTags_(-9999.)
			,btag_softElectronByIP3dBJetTags_(-9999.)
		        ,btag_ghostTrackBJetTags_(-9999.)
			,partonFlavour_(-999)
			,isTopJet_(false)
			,genParton_(0)
			{;}
	
		TRootJet(const TRootJet& jet) :
			TRootParticle(jet)
			,jetType_(jet.jetType_)
			,nConstituents_(jet.nConstituents_)
			,jetArea_(jet.jetArea_)
			,pileupEnergy_(jet.pileupEnergy_)
			,maxDistance_(jet.maxDistance_)
			,chargedBroadness_(jet.chargedBroadness_)
			,btag_jetBProbabilityBJetTags_(jet.btag_jetBProbabilityBJetTags_)
			,btag_jetProbabilityBJetTags_(jet.btag_jetProbabilityBJetTags_)
			,btag_trackCountingHighPurBJetTags_(jet.btag_trackCountingHighPurBJetTags_)
			,btag_trackCountingHighEffBJetTags_(jet.btag_trackCountingHighEffBJetTags_)
			,btag_simpleSecondaryVertexHighEffBJetTags_(jet.btag_simpleSecondaryVertexHighEffBJetTags_)
			,btag_simpleSecondaryVertexHighPurBJetTags_(jet.btag_simpleSecondaryVertexHighPurBJetTags_)
			,btag_combinedSecondaryVertexBJetTags_(jet.btag_combinedSecondaryVertexBJetTags_)
			,btag_combinedSecondaryVertexMVABJetTags_(jet.btag_combinedSecondaryVertexMVABJetTags_)
			,btag_combinedMVABJetTags_(jet.btag_combinedMVABJetTags_)
			,btag_softMuonBJetTags_(jet.btag_softMuonBJetTags_)
			,btag_softMuonByPtBJetTags_(jet.btag_softMuonByPtBJetTags_)
			,btag_softMuonByIP3dBJetTags_(jet.btag_softMuonByIP3dBJetTags_)
		        ,btag_softElectronBJetTags_(jet.btag_softElectronBJetTags_)
			,btag_softElectronByPtBJetTags_(jet.btag_softElectronByPtBJetTags_)
			,btag_softElectronByIP3dBJetTags_(jet.btag_softElectronByIP3dBJetTags_)
		        ,btag_ghostTrackBJetTags_(jet.btag_ghostTrackBJetTags_)
			,partonFlavour_(jet.partonFlavour_)
			,isTopJet_(jet.isTopJet_)
			,genParton_(jet.genParton_)
		        {
			  unsigned int size = sizeof(JetCorrName_)/sizeof(JetCorrName_[0]);
			  for (unsigned int i=0; i<size; i++) {
			    JetCorrName_[i] = jet.JetCorrName_[i];
			    JetCorrValue_[i] = jet.JetCorrValue_[i];
			  }
			}

		TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e) :
			TRootParticle(px,py,pz,e)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,pileupEnergy_(-9999.)
			,maxDistance_(-9999.)
			,chargedBroadness_(-9999.)
			,btag_jetBProbabilityBJetTags_(-9999.)
			,btag_jetProbabilityBJetTags_(-9999.)
			,btag_trackCountingHighPurBJetTags_(-9999.)
			,btag_trackCountingHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighPurBJetTags_(-9999.)
			,btag_combinedSecondaryVertexBJetTags_(-9999.)
			,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
		        ,btag_combinedMVABJetTags_(-9999.)
			,btag_softMuonBJetTags_(-9999.)
			,btag_softMuonByPtBJetTags_(-9999.)
			,btag_softMuonByIP3dBJetTags_(-9999.)
		        ,btag_softElectronBJetTags_(-9999.)
			,btag_softElectronByPtBJetTags_(-9999.)
			,btag_softElectronByIP3dBJetTags_(-9999.)
		        ,btag_ghostTrackBJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
			,genParton_(0)
			{;}
	
		TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,pileupEnergy_(-9999.)
			,maxDistance_(-9999.)
			,chargedBroadness_(-9999.)
			,btag_jetBProbabilityBJetTags_(-9999.)
			,btag_jetProbabilityBJetTags_(-9999.)
			,btag_trackCountingHighPurBJetTags_(-9999.)
			,btag_trackCountingHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighPurBJetTags_(-9999.)
			,btag_combinedSecondaryVertexBJetTags_(-9999.)
			,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
		        ,btag_combinedMVABJetTags_(-9999.)
			,btag_softMuonBJetTags_(-9999.)
			,btag_softMuonByPtBJetTags_(-9999.)
			,btag_softMuonByIP3dBJetTags_(-9999.)
		        ,btag_softElectronBJetTags_(-9999.)
			,btag_softElectronByPtBJetTags_(-9999.)
			,btag_softElectronByIP3dBJetTags_(-9999.)
		        ,btag_ghostTrackBJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
			,genParton_(0)
			{;}

		TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,pileupEnergy_(-9999.)
			,maxDistance_(-9999.)
			,chargedBroadness_(-9999.)
			,btag_jetBProbabilityBJetTags_(-9999.)
			,btag_jetProbabilityBJetTags_(-9999.)
			,btag_trackCountingHighPurBJetTags_(-9999.)
			,btag_trackCountingHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighPurBJetTags_(-9999.)
			,btag_combinedSecondaryVertexBJetTags_(-9999.)
			,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
		        ,btag_combinedMVABJetTags_(-9999.)
			,btag_softMuonBJetTags_(-9999.)
			,btag_softMuonByPtBJetTags_(-9999.)
			,btag_softMuonByIP3dBJetTags_(-9999.)
		        ,btag_softElectronBJetTags_(-9999.)
			,btag_softElectronByPtBJetTags_(-9999.)
			,btag_softElectronByIP3dBJetTags_(-9999.)
		        ,btag_ghostTrackBJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
			,genParton_(0)
			{;}

		TRootJet(const TLorentzVector &momentum) :
			TRootParticle(momentum)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,pileupEnergy_(-9999.)
			,maxDistance_(-9999.)
			,chargedBroadness_(-9999.)
			,btag_jetBProbabilityBJetTags_(-9999.)
			,btag_jetProbabilityBJetTags_(-9999.)
			,btag_trackCountingHighPurBJetTags_(-9999.)
			,btag_trackCountingHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighPurBJetTags_(-9999.)
			,btag_combinedSecondaryVertexBJetTags_(-9999.)
			,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
		        ,btag_combinedMVABJetTags_(-9999.)
			,btag_softMuonBJetTags_(-9999.)
			,btag_softMuonByPtBJetTags_(-9999.)
			,btag_softMuonByIP3dBJetTags_(-9999.)
		        ,btag_softElectronBJetTags_(-9999.)
			,btag_softElectronByPtBJetTags_(-9999.)
			,btag_softElectronByIP3dBJetTags_(-9999.)
		        ,btag_ghostTrackBJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
			,genParton_(0)
			{;}

		TRootJet(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
			TRootParticle(momentum, vertex, type, charge)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,pileupEnergy_(-9999.)
			,maxDistance_(-9999.)
			,chargedBroadness_(-9999.)
			,btag_jetBProbabilityBJetTags_(-9999.)
			,btag_jetProbabilityBJetTags_(-9999.)
			,btag_trackCountingHighPurBJetTags_(-9999.)
			,btag_trackCountingHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighPurBJetTags_(-9999.)
			,btag_combinedSecondaryVertexBJetTags_(-9999.)
			,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
		        ,btag_combinedMVABJetTags_(-9999.)
			,btag_softMuonBJetTags_(-9999.)
			,btag_softMuonByPtBJetTags_(-9999.)
			,btag_softMuonByIP3dBJetTags_(-9999.)
		        ,btag_softElectronBJetTags_(-9999.)
			,btag_softElectronByPtBJetTags_(-9999.)
			,btag_softElectronByIP3dBJetTags_(-9999.)
		        ,btag_ghostTrackBJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
			,genParton_(0)
			{;}

		~TRootJet() {;}


		Int_t jetType() const { return jetType_; }
		Int_t nConstituents() const { return nConstituents_; }
		Float_t jetArea() const { return jetArea_; }
		Float_t pileupEnergy() const { return pileupEnergy_; }
		Float_t maxDistance() const { return maxDistance_; }
		Float_t chargedBroadness() const { return chargedBroadness_; }
		Float_t btag_jetBProbabilityBJetTags() const { return btag_jetBProbabilityBJetTags_; }
		Float_t btag_jetProbabilityBJetTags() const { return btag_jetProbabilityBJetTags_; }
		Float_t btag_trackCountingHighPurBJetTags() const { return btag_trackCountingHighPurBJetTags_; }
		Float_t btag_trackCountingHighEffBJetTags() const { return btag_trackCountingHighEffBJetTags_; }
		Float_t btag_simpleSecondaryVertexHighEffBJetTags() const { return btag_simpleSecondaryVertexHighEffBJetTags_; }
		Float_t btag_simpleSecondaryVertexHighPurBJetTags() const { return btag_simpleSecondaryVertexHighPurBJetTags_; }
		Float_t btag_combinedSecondaryVertexBJetTags() const { return btag_combinedSecondaryVertexBJetTags_; }
		Float_t btag_combinedSecondaryVertexMVABJetTags() const { return btag_combinedSecondaryVertexMVABJetTags_; }
		Float_t btag_combinedMVABJetTags() const { return btag_combinedMVABJetTags_; }
		Float_t btag_softMuonBJetTags() const { return btag_softMuonBJetTags_; }
		Float_t btag_softMuonByPtBJetTags() const { return btag_softMuonByPtBJetTags_; }
		Float_t btag_softMuonByIP3dBJetTags() const { return btag_softMuonByIP3dBJetTags_; }
		Float_t btag_softElectronBJetTags() const { return btag_softElectronBJetTags_; }
		Float_t btag_softElectronByPtBJetTags() const { return btag_softElectronByPtBJetTags_; }
		Float_t btag_softElectronByIP3dBJetTags() const { return btag_softElectronByIP3dBJetTags_; }
		Float_t btag_ghostTrackBJetTags() const { return btag_ghostTrackBJetTags_; }

		TObject* genParton() const { return genParton_.GetObject(); }
		Int_t partonFlavour() const {return partonFlavour_; }
		//Float_t partonFlavour() const {return partonFlavour_; }
		Bool_t isTopJet() const { return isTopJet_; }

		float getJetCorrFactor(std::string name) {

		  unsigned int size = sizeof(JetCorrName_)/sizeof(JetCorrName_[0]);

		  for (unsigned int i=0; i<size; i++) {

		    if ( JetCorrName_[i] == name )
		      return JetCorrValue_[i];

		  }

		  // if we reach this point, the correction factor was not found -> print all possible names
		  cout << "JetCorrFactor " << name << " was not found, possible names are: ";

		  for (unsigned int i=0; i<size; i++)
		    if (JetCorrName_[i] != "")
		      cout << JetCorrName_[i] << endl;

		  cout << endl;
		  
		  return 0;

		}

		virtual TString typeName() const { return "TRootJet"; }


		void setJetType(Int_t jetType) { jetType_ = jetType; }
		void setNConstituents(Int_t nConstituents) { nConstituents_ = nConstituents; }
		void setJetArea(Float_t jetArea) { jetArea_ = jetArea; }
		void setPileupEnergy(Float_t pileupEnergy) { pileupEnergy_ = pileupEnergy; }
		void setMaxDistance(Float_t maxDistance) { maxDistance_ = maxDistance; }
		void setChargedBroadness(Float_t chargedBroadness) { chargedBroadness_ = chargedBroadness; }
		//btag
		void setBtag_jetBProbabilityBJetTags(Float_t btag_jetBProbabilityBJetTags) { btag_jetBProbabilityBJetTags_ = btag_jetBProbabilityBJetTags; }
		void setBtag_jetProbabilityBJetTags(Float_t btag_jetProbabilityBJetTags) { btag_jetProbabilityBJetTags_ = btag_jetProbabilityBJetTags; }
		void setBtag_trackCountingHighPurBJetTags(Float_t btag_trackCountingHighPurBJetTags) { btag_trackCountingHighPurBJetTags_ = btag_trackCountingHighPurBJetTags; }
		void setBtag_trackCountingHighEffBJetTags(Float_t btag_trackCountingHighEffBJetTags) { btag_trackCountingHighEffBJetTags_ = btag_trackCountingHighEffBJetTags; }
		void setBtag_simpleSecondaryVertexHighEffBJetTags(Float_t btag_simpleSecondaryVertexHighEffBJetTags) { btag_simpleSecondaryVertexHighEffBJetTags_ = btag_simpleSecondaryVertexHighEffBJetTags; }
		void setBtag_simpleSecondaryVertexHighPurBJetTags(Float_t btag_simpleSecondaryVertexHighPurBJetTags) { btag_simpleSecondaryVertexHighPurBJetTags_ = btag_simpleSecondaryVertexHighPurBJetTags; }
		void setBtag_combinedSecondaryVertexBJetTags(Float_t btag_combinedSecondaryVertexBJetTags) { btag_combinedSecondaryVertexBJetTags_ = btag_combinedSecondaryVertexBJetTags; }
		void setBtag_combinedSecondaryVertexMVABJetTags(Float_t btag_combinedSecondaryVertexMVABJetTags) { btag_combinedSecondaryVertexMVABJetTags_ = btag_combinedSecondaryVertexMVABJetTags; }
		void setBtag_combinedMVABJetTags(Float_t btag_combinedMVABJetTags) { btag_combinedMVABJetTags_ = btag_combinedMVABJetTags; }
		void setBtag_softMuonBJetTags(Float_t btag_softMuonBJetTags) { btag_softMuonBJetTags_ = btag_softMuonBJetTags; }
		void setBtag_softMuonByPtBJetTags(Float_t btag_softMuonByPtBJetTags) { btag_softMuonByPtBJetTags_ = btag_softMuonByPtBJetTags; }
		void setBtag_softMuonByIP3dBJetTags(Float_t btag_softMuonByIP3dBJetTags) { btag_softMuonByIP3dBJetTags_ = btag_softMuonByIP3dBJetTags; }
		void setBtag_softElectronBJetTags(Float_t btag_softElectronBJetTags) { btag_softElectronBJetTags_ = btag_softElectronBJetTags; }
		void setBtag_softElectronByPtBJetTags(Float_t btag_softElectronByPtBJetTags) { btag_softElectronByPtBJetTags_ = btag_softElectronByPtBJetTags; }
		void setBtag_softElectronByIP3dBJetTags(Float_t btag_softElectronByIP3dBJetTags) { btag_softElectronByIP3dBJetTags_ = btag_softElectronByIP3dBJetTags; }
		void setBtag_ghostTrackBJetTags(Float_t btag_ghostTrackBJetTags) { btag_ghostTrackBJetTags_ = btag_ghostTrackBJetTags; }
		
		void setPartonFlavour(Int_t partonFlavour) { partonFlavour_ = partonFlavour; }
		void setIsTopJet(Bool_t isTopJet) { isTopJet_ = isTopJet; }
		void setGenParton(TObject* genParton) { genParton_ = genParton; }

		friend std::ostream& operator<< (std::ostream& stream, const TRootJet& jet)
		{
			stream << "TRootJet - Charge=" << setw(2) << jet.charge() << " (Et,eta,phi)=("<< setw(10) << jet.Et() <<","<< setw(10) << jet.Eta() <<","<< setw(10) << jet.Phi() << ")"
				<< " vertex(x,y,z)=("<< jet.vx() <<","<< jet.vy() <<","<< jet.vz() << ")";
			return stream;
		};

		void setJetCorrFactor(int pos, std::string name, float factor) {
		  
		  //cout << "Setting factor " << name << " to " << factor << " in position " << pos << endl;
		  JetCorrName_[pos] = name;
		  JetCorrValue_[pos] = factor;
		  
		}


	private:
		//Jet Info
		Int_t jetType_;                     // 0 = Unknown ; 1 = CaloJet ; 2 = PFJet
		Int_t nConstituents_;               // Number of constituents of the jet (calotowers for CaloJet / PFParticles for PFJet)
		Float_t jetArea_;                   // Jet area
		Float_t pileupEnergy_;               // Pile-up Energy
		Float_t maxDistance_;               // Maximum distance from jet to constituent

		// Variables from pat::Jet
		Float_t chargedBroadness_;          // DR of the cone containing 75% of the jet charged energy 
        
		// jet correction factors

		std::string JetCorrName_[17];
		float JetCorrValue_[17];

		//btag Info
		Float_t btag_jetBProbabilityBJetTags_;
		Float_t btag_jetProbabilityBJetTags_;
		Float_t btag_trackCountingHighPurBJetTags_;
		Float_t btag_trackCountingHighEffBJetTags_;
		Float_t btag_simpleSecondaryVertexHighEffBJetTags_;
		Float_t btag_simpleSecondaryVertexHighPurBJetTags_;
		Float_t btag_combinedSecondaryVertexBJetTags_;
		Float_t btag_combinedSecondaryVertexMVABJetTags_;
		Float_t btag_combinedMVABJetTags_;
		Float_t btag_softMuonBJetTags_;
		Float_t btag_softMuonByPtBJetTags_;
		Float_t btag_softMuonByIP3dBJetTags_;
		Float_t btag_softElectronBJetTags_;
		Float_t btag_softElectronByPtBJetTags_;
		Float_t btag_softElectronByIP3dBJetTags_;
		Float_t btag_ghostTrackBJetTags_;

		//MC info
		Int_t partonFlavour_;
		Bool_t isTopJet_;				// Is parton matched to the jet a decay product of the top quark ?
		TRef genParton_;	

		ClassDef (TRootJet,1);
	};
}

#endif
