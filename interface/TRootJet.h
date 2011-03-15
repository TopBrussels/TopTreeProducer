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
			,maxDistance_(-9999.)
			,btag_jetBProbabilityBJetTags_(-9999.)
			,btag_jetProbabilityBJetTags_(-9999.)
			,btag_trackCountingHighPurBJetTags_(-9999.)
			,btag_trackCountingHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighPurBJetTags_(-9999.)
			,btag_combinedSecondaryVertexBJetTags_(-9999.)
			,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
			,partonFlavour_(-999)
			,isTopJet_(false)
			{;}
	
		TRootJet(const TRootJet& jet) :
			TRootParticle(jet)
			,jetType_(jet.jetType_)
			,nConstituents_(jet.nConstituents_)
			,jetArea_(jet.jetArea_)
			,maxDistance_(jet.maxDistance_)
			,btag_jetBProbabilityBJetTags_(jet.btag_jetBProbabilityBJetTags_)
			,btag_jetProbabilityBJetTags_(jet.btag_jetProbabilityBJetTags_)
			,btag_trackCountingHighPurBJetTags_(jet.btag_trackCountingHighPurBJetTags_)
			,btag_trackCountingHighEffBJetTags_(jet.btag_trackCountingHighEffBJetTags_)
			,btag_simpleSecondaryVertexHighEffBJetTags_(jet.btag_simpleSecondaryVertexHighEffBJetTags_)
			,btag_simpleSecondaryVertexHighPurBJetTags_(jet.btag_simpleSecondaryVertexHighPurBJetTags_)
			,btag_combinedSecondaryVertexBJetTags_(jet.btag_combinedSecondaryVertexBJetTags_)
			,btag_combinedSecondaryVertexMVABJetTags_(jet.btag_combinedSecondaryVertexMVABJetTags_)
			,partonFlavour_(jet.partonFlavour_)
			,isTopJet_(jet.isTopJet_)
		  {
			  unsigned int size = sizeof(JetCorrName_)/sizeof(JetCorrName_[0]);
			  for (unsigned int i=0; i<size; i++)
				{
			    JetCorrName_[i] = jet.JetCorrName_[i];
			    JetCorrValue_[i] = jet.JetCorrValue_[i];
			  }
			}

		TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e) :
			TRootParticle(px,py,pz,e)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,maxDistance_(-9999.)
			,btag_jetBProbabilityBJetTags_(-9999.)
			,btag_jetProbabilityBJetTags_(-9999.)
			,btag_trackCountingHighPurBJetTags_(-9999.)
			,btag_trackCountingHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighPurBJetTags_(-9999.)
			,btag_combinedSecondaryVertexBJetTags_(-9999.)
			,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
			{;}
	
		TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,maxDistance_(-9999.)
			,btag_jetBProbabilityBJetTags_(-9999.)
			,btag_jetProbabilityBJetTags_(-9999.)
			,btag_trackCountingHighPurBJetTags_(-9999.)
			,btag_trackCountingHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighPurBJetTags_(-9999.)
			,btag_combinedSecondaryVertexBJetTags_(-9999.)
			,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
			{;}

		TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,maxDistance_(-9999.)
			,btag_jetBProbabilityBJetTags_(-9999.)
			,btag_jetProbabilityBJetTags_(-9999.)
			,btag_trackCountingHighPurBJetTags_(-9999.)
			,btag_trackCountingHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighPurBJetTags_(-9999.)
			,btag_combinedSecondaryVertexBJetTags_(-9999.)
			,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
			{;}

		TRootJet(const TLorentzVector &momentum) :
			TRootParticle(momentum)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,maxDistance_(-9999.)
			,btag_jetBProbabilityBJetTags_(-9999.)
			,btag_jetProbabilityBJetTags_(-9999.)
			,btag_trackCountingHighPurBJetTags_(-9999.)
			,btag_trackCountingHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighPurBJetTags_(-9999.)
			,btag_combinedSecondaryVertexBJetTags_(-9999.)
			,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
			{;}

		TRootJet(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
			TRootParticle(momentum, vertex, type, charge)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,maxDistance_(-9999.)
			,btag_jetBProbabilityBJetTags_(-9999.)
			,btag_jetProbabilityBJetTags_(-9999.)
			,btag_trackCountingHighPurBJetTags_(-9999.)
			,btag_trackCountingHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighEffBJetTags_(-9999.)
			,btag_simpleSecondaryVertexHighPurBJetTags_(-9999.)
			,btag_combinedSecondaryVertexBJetTags_(-9999.)
			,btag_combinedSecondaryVertexMVABJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
			{;}

		~TRootJet() {;}


		Int_t jetType() const { return jetType_; }
		Int_t nConstituents() const { return nConstituents_; }
		Float_t jetArea() const { return jetArea_; }
		Float_t maxDistance() const { return maxDistance_; }
		Float_t btag_jetBProbabilityBJetTags() const { return btag_jetBProbabilityBJetTags_; }
		Float_t btag_jetProbabilityBJetTags() const { return btag_jetProbabilityBJetTags_; }
		Float_t btag_trackCountingHighPurBJetTags() const { return btag_trackCountingHighPurBJetTags_; }
		Float_t btag_trackCountingHighEffBJetTags() const { return btag_trackCountingHighEffBJetTags_; }
		Float_t btag_simpleSecondaryVertexHighEffBJetTags() const { return btag_simpleSecondaryVertexHighEffBJetTags_; }
		Float_t btag_simpleSecondaryVertexHighPurBJetTags() const { return btag_simpleSecondaryVertexHighPurBJetTags_; }
		Float_t btag_combinedSecondaryVertexBJetTags() const { return btag_combinedSecondaryVertexBJetTags_; }
		Float_t btag_combinedSecondaryVertexMVABJetTags() const { return btag_combinedSecondaryVertexMVABJetTags_; }

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
		void setMaxDistance(Float_t maxDistance) { maxDistance_ = maxDistance; }
		// btag
		void setBtag_jetBProbabilityBJetTags(Float_t btag_jetBProbabilityBJetTags) { btag_jetBProbabilityBJetTags_ = btag_jetBProbabilityBJetTags; }
		void setBtag_jetProbabilityBJetTags(Float_t btag_jetProbabilityBJetTags) { btag_jetProbabilityBJetTags_ = btag_jetProbabilityBJetTags; }
		void setBtag_trackCountingHighPurBJetTags(Float_t btag_trackCountingHighPurBJetTags) { btag_trackCountingHighPurBJetTags_ = btag_trackCountingHighPurBJetTags; }
		void setBtag_trackCountingHighEffBJetTags(Float_t btag_trackCountingHighEffBJetTags) { btag_trackCountingHighEffBJetTags_ = btag_trackCountingHighEffBJetTags; }
		void setBtag_simpleSecondaryVertexHighEffBJetTags(Float_t btag_simpleSecondaryVertexHighEffBJetTags) { btag_simpleSecondaryVertexHighEffBJetTags_ = btag_simpleSecondaryVertexHighEffBJetTags; }
		void setBtag_simpleSecondaryVertexHighPurBJetTags(Float_t btag_simpleSecondaryVertexHighPurBJetTags) { btag_simpleSecondaryVertexHighPurBJetTags_ = btag_simpleSecondaryVertexHighPurBJetTags; }
		void setBtag_combinedSecondaryVertexBJetTags(Float_t btag_combinedSecondaryVertexBJetTags) { btag_combinedSecondaryVertexBJetTags_ = btag_combinedSecondaryVertexBJetTags; }
		void setBtag_combinedSecondaryVertexMVABJetTags(Float_t btag_combinedSecondaryVertexMVABJetTags) { btag_combinedSecondaryVertexMVABJetTags_ = btag_combinedSecondaryVertexMVABJetTags; }
		void setPartonFlavour(Int_t partonFlavour) { partonFlavour_ = partonFlavour; }
		void setIsTopJet(Bool_t isTopJet) { isTopJet_ = isTopJet; }
		// JEC
		void setJetCorrFactor(int pos, std::string name, float factor)
		{  
		  JetCorrName_[pos] = name;
		  JetCorrValue_[pos] = factor;
		}

		friend std::ostream& operator<< (std::ostream& stream, const TRootJet& jet)
		{
			stream << "TRootJet - Charge=" << setw(2) << jet.charge() << " (Et,eta,phi)=("<< setw(10) << jet.Et() <<","<< setw(10) << jet.Eta() <<","<< setw(10) << jet.Phi() << ")"
				<< " vertex(x,y,z)=("<< jet.vx() <<","<< jet.vy() <<","<< jet.vz() << ")";
			return stream;
		};


	private:
		//Jet Info
		Int_t jetType_;                     // 0 = Unknown ; 1 = CaloJet ; 2 = PFJet
		Int_t nConstituents_;               // Number of constituents of the jet (calotowers for CaloJet / PFParticles for PFJet)
		Float_t jetArea_;                   // Jet area
		Float_t maxDistance_;               // Maximum distance from jet to constituent

		// jet correction factors
		std::string JetCorrName_[4]; 			// check in JetAnalyzer.cc that size is big enough to store all corrections!
		float JetCorrValue_[4];

		//btag Info
		Float_t btag_jetBProbabilityBJetTags_;
		Float_t btag_jetProbabilityBJetTags_;
		Float_t btag_trackCountingHighPurBJetTags_;
		Float_t btag_trackCountingHighEffBJetTags_;
		Float_t btag_simpleSecondaryVertexHighEffBJetTags_;
		Float_t btag_simpleSecondaryVertexHighPurBJetTags_;
		Float_t btag_combinedSecondaryVertexBJetTags_;
		Float_t btag_combinedSecondaryVertexMVABJetTags_;

		//MC info
		Int_t partonFlavour_;
		Bool_t isTopJet_;				// Is parton matched to the jet a decay product of the top quark ?

		ClassDef (TRootJet,1);
	};
}

#endif
