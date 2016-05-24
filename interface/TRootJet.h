#ifndef TRootJet_h
#define TRootJet_h

#include "../interface/TRootParticle.h"

#include "Rtypes.h"
#include "TObject.h"
#include "TString.h"

#include <iostream>
#include <iomanip>
#include <map>

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
			,btag_combinedInclusiveSecondaryVertexV2BJetTags_(-9999.)
			,btag_PFCombinedMVAV2BJetTags_(-9999.)
			,btag_softPFElectronBJetsTags_(-9999.)
			,btag_softPFMuonBJetsTags_(-9999.)
			,ctag_pfCombinedCvsLJetTags_(-9999.)
			,ctag_pfCombinedCvsBJetTags_(-9999.)
			,partonFlavour_(-999)
			,isTopJet_(false)
                        ,puID_(-9999.)
			{;}

		TRootJet(const TRootJet& jet) :
			TRootParticle(jet)
			,jetType_(jet.jetType_)
			,nConstituents_(jet.nConstituents_)
			,jetArea_(jet.jetArea_)
			,maxDistance_(jet.maxDistance_)
			,btag_combinedInclusiveSecondaryVertexV2BJetTags_(jet.btag_combinedInclusiveSecondaryVertexV2BJetTags_)
			,btag_PFCombinedMVAV2BJetTags_(jet.btag_PFCombinedMVAV2BJetTags_)
			,btag_softPFElectronBJetsTags_(jet.btag_softPFElectronBJetsTags_)
			,btag_softPFMuonBJetsTags_(jet.btag_softPFMuonBJetsTags_)
			,ctag_pfCombinedCvsLJetTags_(jet.ctag_pfCombinedCvsLJetTags_)
			,ctag_pfCombinedCvsBJetTags_(jet.ctag_pfCombinedCvsBJetTags_)
			,partonFlavour_(jet.partonFlavour_)
			,isTopJet_(jet.isTopJet_)
                        ,puID_(-9999.)
		  {
			unsigned int size = sizeof(JetCorrName_)/sizeof(JetCorrName_[0]);
			for (unsigned int i=0; i<size; i++)
			{
				JetCorrName_[i] = jet.JetCorrName_[i];
			    	JetCorrValue_[i] = jet.JetCorrValue_[i];
			}
			for(std::map<std::string,float>::const_iterator it = jet.mistag_SF_.begin(); it != jet.mistag_SF_.end(); it++) {
				mistag_SF_[it->first] = it->second;
			}
			for(std::map<std::string,float>::const_iterator it = jet.btag_SF_.begin(); it != jet.btag_SF_.end(); it++) {
				btag_SF_[it->first] = it->second;
			}
			for(std::map<std::string,float>::const_iterator it = jet.mistag_SFerr_.begin(); it != jet.mistag_SFerr_.end(); it++) {
				mistag_SFerr_[it->first] = it->second;
			}
			for(std::map<std::string,float>::const_iterator it = jet.btag_SFerr_.begin(); it != jet.btag_SFerr_.end(); it++) {
				btag_SFerr_[it->first] = it->second;
			}
		}

		TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e) :
			TRootParticle(px,py,pz,e)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,maxDistance_(-9999.)
			,btag_combinedInclusiveSecondaryVertexV2BJetTags_(-9999.)
			,btag_PFCombinedMVAV2BJetTags_(-9999.)
			,btag_softPFElectronBJetsTags_(-9999.)
			,btag_softPFMuonBJetsTags_(-9999.)
			,ctag_pfCombinedCvsLJetTags_(-9999.)
			,ctag_pfCombinedCvsBJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
                        ,puID_(-9999.)
			{;}

		TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,maxDistance_(-9999.)
			,btag_combinedInclusiveSecondaryVertexV2BJetTags_(-9999.)
			,btag_PFCombinedMVAV2BJetTags_(-9999.)
			,btag_softPFElectronBJetsTags_(-9999.)
			,btag_softPFMuonBJetsTags_(-9999.)
			,ctag_pfCombinedCvsLJetTags_(-9999.)
			,ctag_pfCombinedCvsBJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
                        ,puID_(-9999.)
			{;}

		TRootJet(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
			TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,maxDistance_(-9999.)
			,btag_combinedInclusiveSecondaryVertexV2BJetTags_(-9999.)
			,btag_PFCombinedMVAV2BJetTags_(-9999.)
			,btag_softPFElectronBJetsTags_(-9999.)
			,btag_softPFMuonBJetsTags_(-9999.)
			,ctag_pfCombinedCvsLJetTags_(-9999.)
			,ctag_pfCombinedCvsBJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
                        ,puID_(-9999.)
			{;}

		TRootJet(const TLorentzVector &momentum) :
			TRootParticle(momentum)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,maxDistance_(-9999.)
			,btag_combinedInclusiveSecondaryVertexV2BJetTags_(-9999.)
			,btag_PFCombinedMVAV2BJetTags_(-9999.)
			,btag_softPFElectronBJetsTags_(-9999.)
			,btag_softPFMuonBJetsTags_(-9999.)
			,ctag_pfCombinedCvsLJetTags_(-9999.)
			,ctag_pfCombinedCvsBJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
                        ,puID_(-9999.)
			{;}

		TRootJet(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
			TRootParticle(momentum, vertex, type, charge)
			,jetType_(0)
			,nConstituents_(-9999)
			,jetArea_(-9999.)
			,maxDistance_(-9999.)
			,btag_combinedInclusiveSecondaryVertexV2BJetTags_(-9999.)
			,btag_PFCombinedMVAV2BJetTags_(-9999.)
			,btag_softPFElectronBJetsTags_(-9999.)
			,btag_softPFMuonBJetsTags_(-9999.)
			,ctag_pfCombinedCvsLJetTags_(-9999.)
			,ctag_pfCombinedCvsBJetTags_(-9999.)
			,partonFlavour_(-9999)
			,isTopJet_(false)
                        ,puID_(-9999.)
			{;}

		~TRootJet() {;}

		Int_t jetType() const { return jetType_; }
		Int_t nConstituents() const { return nConstituents_; }
		Float_t jetArea() const { return jetArea_; }
		Float_t maxDistance() const { return maxDistance_; }
		Float_t btag_combinedInclusiveSecondaryVertexV2BJetTags() const {return btag_combinedInclusiveSecondaryVertexV2BJetTags_; }
		Float_t btag_PFCombinedMVAV2BJetTags() const {return btag_PFCombinedMVAV2BJetTags_; }
		Float_t	btag_softPFElectronBJetsTags() const { return btag_softPFElectronBJetsTags_; }
    Float_t	btag_softPFMuonBJetsTags() const { return btag_softPFMuonBJetsTags_; }
		Float_t ctag_pfCombinedCvsLJetTags() const { return ctag_pfCombinedCvsLJetTags_; }
		Float_t ctag_pfCombinedCvsBJetTags() const { return ctag_pfCombinedCvsBJetTags_; }
    Float_t	puID() const { return puID_; }

		std::map<std::string, float> getMistag_SF() const {
			std::cout << mistag_SF_.size() << endl;
			return mistag_SF_;
		}
		std::map<std::string, float> getBtag_SF() const { return btag_SF_;}
		std::map<std::string, float> getMistag_SFerr() const { return mistag_SFerr_;}
		std::map<std::string, float> getBtag_SFerr() const { return btag_SFerr_;}


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
		void setBtag_combinedInclusiveSecondaryVertexV2BJetTags(Float_t btag_combinedInclusiveSecondaryVertexV2BJetTags) { btag_combinedInclusiveSecondaryVertexV2BJetTags_ = btag_combinedInclusiveSecondaryVertexV2BJetTags; }
		void setBtag_PFCombinedMVAV2BJetTags(Float_t btag_PFCombinedMVAV2BJetTags) { btag_PFCombinedMVAV2BJetTags_ = btag_PFCombinedMVAV2BJetTags; }
    void setBtag_softPFElectronBJetsTags(Float_t btag_softPFElectronBJetsTags) { btag_softPFElectronBJetsTags_ = btag_softPFElectronBJetsTags; }
    void setBtag_softPFMuonBJetsTags(Float_t btag_softPFMuonBJetsTags) { btag_softPFMuonBJetsTags_ = btag_softPFMuonBJetsTags; }
    void setCtag_pfCombinedCvsLJetTags(Float_t ctag_pfCombinedCvsLJetTags){ ctag_pfCombinedCvsLJetTags_ = ctag_pfCombinedCvsLJetTags; }
	  void setCtag_pfCombinedCvsBJetTags(Float_t ctag_pfCombinedCvsBJetTags){ ctag_pfCombinedCvsBJetTags_ = ctag_pfCombinedCvsBJetTags; }

		void setPartonFlavour(Int_t partonFlavour) { partonFlavour_ = partonFlavour; }
		void setIsTopJet(Bool_t isTopJet) { isTopJet_ = isTopJet; }
        	void setpuID(Float_t puID) { puID_ = puID; }

		//btag scalefactors
		void setMistag_SF(std::map<std::string, float> mistag_SF) {
			for(std::map<std::string,float>::const_iterator it = mistag_SF.begin(); it != mistag_SF.end(); it++) {
				mistag_SF_[it->first] = it->second;
			}
		}
		void setBtag_SF(std::map<std::string, float> btag_SF) {
			for(std::map<std::string,float>::const_iterator it = btag_SF.begin(); it != btag_SF.end(); it++) {
				btag_SF_[it->first] = it->second;
			}
		}
		void setMistag_SFerr(std::map<std::string, float> mistag_SFerr) {
			for(std::map<std::string,float>::const_iterator it = mistag_SFerr.begin(); it != mistag_SFerr.end(); it++) {
				mistag_SFerr_[it->first] = it->second;
			}
		}
		void setBtag_SFerr(std::map<std::string, float> btag_SFerr) {
			for(std::map<std::string,float>::const_iterator it = btag_SFerr.begin(); it != btag_SFerr.end(); it++) {
				btag_SFerr_[it->first] = it->second;
			}
		}


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
		TString JetCorrName_[4]; 			// check in JetAnalyzer.cc that size is big enough to store all corrections!
		float JetCorrValue_[4];

		//btag Info
		Float_t btag_combinedInclusiveSecondaryVertexV2BJetTags_;
		Float_t btag_PFCombinedMVAV2BJetTags_;
		Float_t btag_softPFElectronBJetsTags_;
		Float_t btag_softPFMuonBJetsTags_;
		Float_t ctag_pfCombinedCvsLJetTags_;
		Float_t ctag_pfCombinedCvsBJetTags_;


		//btag scalefactors
		std::map<std::string, float> mistag_SF_;
		std::map<std::string, float> btag_SF_;
		std::map<std::string, float> mistag_SFerr_;
		std::map<std::string, float> btag_SFerr_;


		//MC info
		Int_t partonFlavour_;
		Bool_t isTopJet_;				// Is parton matched to the jet a decay product of the top quark ?
                Float_t puID_;

		ClassDef (TRootJet,3);
	};
}

#endif
