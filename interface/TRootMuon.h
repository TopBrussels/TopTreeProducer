#ifndef TRootMuon_h
#define TRootMuon_h

#include "../interface/TRootParticle.h"


using namespace std;

class TRootMuon : public TRootParticle
{

public:

	TRootMuon() :
		TRootParticle()
		,et_em_(-9999.)
		,et_had_(-9999.)
		,et_ho_(-9999.)
		,caloCompatibility_(-9999.)
		,isoR03_emEt_(-9999.)
		,isoR03_hadEt_(-9999.)
		,isoR03_hoEt_(-9999.)
		,isoR03_sumPt_(-9999.)
		,isoR03_nTracks_(-9999)
		,isoR03_nJets_(-9999)
		,energyValid_(false)
		,matchesValid_(false)
		,isolationValid_(false)
                ,vetoIso_(false)
		,vetoEm_(-9999)
		,vetoHad_(-9999)
	        ,d0_(-9999.)
	        ,d0error_(-9999.)
		,chi2_(-9999.)
		,nofValidHits_(-9999)
                ,innerTrack_(TLorentzVector())
		,direction_(-9999)
		,algo_(-9999)
		,id_(-9999)
		{;}

	TRootMuon(const TRootMuon& muon) :
		TRootParticle(muon)
		,et_em_(muon.et_em_)
		,et_had_(muon.et_had_)
		,et_ho_(muon.et_ho_)
		,caloCompatibility_(muon.caloCompatibility_)
		,isoR03_emEt_(muon.isoR03_emEt_)
		,isoR03_hadEt_(muon.isoR03_hadEt_)
		,isoR03_hoEt_(muon.isoR03_hoEt_)
		,isoR03_sumPt_(muon.isoR03_sumPt_)
		,isoR03_nTracks_(muon.isoR03_nTracks_)
		,isoR03_nJets_(muon.isoR03_nJets_)
		,energyValid_(muon.energyValid_)
		,matchesValid_(muon.matchesValid_)
		,isolationValid_(muon.isolationValid_)
                ,vetoIso_(muon.vetoIso_)
                ,vetoEm_(muon.vetoEm_)
                ,vetoHad_(muon.vetoHad_)
	        ,d0_(muon.d0_)
	        ,d0error_(muon.d0error_)
		,chi2_(muon.chi2_)
		,nofValidHits_(muon.nofValidHits_)
                ,innerTrack_(muon.innerTrack_)
		,direction_(muon.direction_)
		,algo_(muon.algo_)
		,id_(muon.id_)
		{;}

	TRootMuon(Double_t px, Double_t py, Double_t pz, Double_t e) :
		TRootParticle(px,py,pz,e)
		,et_em_(-9999.)
		,et_had_(-9999.)
		,et_ho_(-9999.)
		,caloCompatibility_(-9999.)
		,isoR03_emEt_(-9999.)
		,isoR03_hadEt_(-9999.)
		,isoR03_hoEt_(-9999.)
		,isoR03_sumPt_(-9999.)
		,isoR03_nTracks_(-9999)
		,isoR03_nJets_(-9999)
		,energyValid_(false)
		,matchesValid_(false)
		,isolationValid_(false)
                ,vetoIso_(false)
		,vetoEm_(-9999)
		,vetoHad_(-9999)
	        ,d0_(-9999.)
	        ,d0error_(-9999.)
		,chi2_(-9999.)
		,nofValidHits_(-9999)
                ,innerTrack_(TLorentzVector())
		,direction_(-9999)
		,algo_(-9999)
		,id_(-9999)
		{;}

	TRootMuon(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
		TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z)
		,et_em_(-9999.)
		,et_had_(-9999.)
		,et_ho_(-9999.)
		,caloCompatibility_(-9999.)
		,isoR03_emEt_(-9999.)
		,isoR03_hadEt_(-9999.)
		,isoR03_hoEt_(-9999.)
		,isoR03_sumPt_(-9999.)
		,isoR03_nTracks_(-9999)
		,isoR03_nJets_(-9999)
		,energyValid_(false)
		,matchesValid_(false)
		,isolationValid_(false)
                ,vetoIso_(false)
		,vetoEm_(-9999)
		,vetoHad_(-9999)
	        ,d0_(-9999.)
	        ,d0error_(-9999.)
		,chi2_(-9999.)
		,nofValidHits_(-9999)
                ,innerTrack_(TLorentzVector())
		,direction_(-9999)
		,algo_(-9999)
		,id_(-9999)
		{;}

	TRootMuon(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
		TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
		,et_em_(-9999.)
		,et_had_(-9999.)
		,et_ho_(-9999.)
		,caloCompatibility_(-9999.)
		,isoR03_emEt_(-9999.)
		,isoR03_hadEt_(-9999.)
		,isoR03_hoEt_(-9999.)
		,isoR03_sumPt_(-9999.)
		,isoR03_nTracks_(-9999)
		,isoR03_nJets_(-9999)
		,energyValid_(false)
		,matchesValid_(false)
		,isolationValid_(false)
                ,vetoIso_(false)
		,vetoEm_(-9999)
		,vetoHad_(-9999)
	        ,d0_(-9999.)
	        ,d0error_(-9999.)
		,chi2_(-9999.)
		,nofValidHits_(-9999)
                ,innerTrack_(TLorentzVector())
		,direction_(-9999)
		,algo_(-9999)
		,id_(-9999)
		{;}

	TRootMuon(const TLorentzVector &momentum) :
		TRootParticle(momentum)
		,et_em_(-9999.)
		,et_had_(-9999.)
		,et_ho_(-9999.)
		,caloCompatibility_(-9999.)
		,isoR03_emEt_(-9999.)
		,isoR03_hadEt_(-9999.)
		,isoR03_hoEt_(-9999.)
		,isoR03_sumPt_(-9999.)
		,isoR03_nTracks_(-9999)
		,isoR03_nJets_(-9999)
		,energyValid_(false)
		,matchesValid_(false)
		,isolationValid_(false)
                ,vetoIso_(false)
		,vetoEm_(-9999)
		,vetoHad_(-9999)
	        ,d0_(-9999.)
	        ,d0error_(-9999.)
		,chi2_(-9999.)
		,nofValidHits_(-9999)
                ,innerTrack_(TLorentzVector())
		,direction_(-9999)
		,algo_(-9999)
		,id_(-9999)
		{;}

	TRootMuon(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
		TRootParticle(momentum, vertex, type, charge)
		,et_em_(-9999.)
		,et_had_(-9999.)
		,et_ho_(-9999.)
		,caloCompatibility_(-9999.)
		,isoR03_emEt_(-9999.)
		,isoR03_hadEt_(-9999.)
		,isoR03_hoEt_(-9999.)
		,isoR03_sumPt_(-9999.)
		,isoR03_nTracks_(-9999)
		,isoR03_nJets_(-9999)
		,energyValid_(false)
		,matchesValid_(false)
		,isolationValid_(false)
                ,vetoIso_(false)
		,vetoEm_(-9999)
		,vetoHad_(-9999)
	        ,d0_(-9999.)
	        ,d0error_(-9999.)
		,chi2_(-9999.)
		,nofValidHits_(-9999)
                ,innerTrack_(TLorentzVector())
		,direction_(-9999)
		,algo_(-9999)
		,id_(-9999)
		{;}

	~TRootMuon() {;}


	Float_t et_em() const { return et_em_;}
	Float_t et_had() const { return et_had_;}
	Float_t et_ho() const { return et_ho_;}
	Float_t caloCompatibility() const { return caloCompatibility_;}
	
	Float_t isoR03_emEt() const { return isoR03_emEt_;}
	Float_t isoR03_hadEt() const { return isoR03_hadEt_;}
	Float_t isoR03_hoEt() const { return isoR03_hoEt_;}
	Float_t isoR03_sumPt() const { return isoR03_sumPt_;}
	Int_t isoR03_nTracks() const { return isoR03_nTracks_;}
	Int_t isoR03_nJets() const { return isoR03_nJets_;}

        Float_t relativeIso03() const { return( ((TLorentzVector)(*this)).Pt()/(isoR03_emEt_+isoR03_hadEt_+isoR03_sumPt_));}

	
	Bool_t energyValid() const { return energyValid_;}
	Bool_t matchesValid() const { return matchesValid_;}
	Bool_t isolationValid() const { return isolationValid_;}
	
	Int_t direction() const { return direction_;}
	Int_t algo() const { return algo_;}

	Bool_t isGlobalMuon() const { return algo_ & 2; }
	Bool_t isTrackerMuon() const { return algo_ & 4; }
	Bool_t isStandAloneMuon() const { return algo_ & 8; }
	Bool_t isCaloMuon() const { return algo_ & 16; }

	Int_t id() const { return id_;}
	Bool_t idAllGlobalMuons() const { return id_ & 1; }
	Bool_t idAllTrackerMuons() const { return id_ & 2; }
	Bool_t idAllStandAloneMuons() const { return id_ & 4; }
        Bool_t idTrackerMuonArbitrated() const { return id_ & 8; }
        Bool_t idAllArbitrated() const { return id_ & 16; }
	Bool_t idGlobalMuonPromptTight() const { return id_ & 32; }
	Bool_t idTMLastStationLoose() const { return id_ & 64; }
	Bool_t idTMLastStationTight() const { return id_ & 128; }
	Bool_t idTMOneStationLoose() const { return id_ & 256; }
	Bool_t idTMOneStationTight() const { return id_ & 512; }
	Bool_t idTMLastStationOptimizedLowPtLoose() const { return id_ & 1024; }
	Bool_t idTMLastStationOptimizedLowPtTight() const { return id_ & 2048; }
	Bool_t idTM2DCompatibilityLoose() const { return id_ & 4096; }
	Bool_t idTM2DCompatibilityTight() const { return id_ & 8192; }


        Bool_t vetoIso() const { return vetoIso_;} 
        Float_t vetoEm() const { return vetoEm_;} 
        Float_t vetoHad() const { return vetoHad_;} 
	Float_t d0() const { return d0_;}  
	Float_t d0error() const { return d0error_;}  
	Float_t chi2() const { return chi2_;}
        Int_t nofValidHits() const { return nofValidHits_;}  
        TLorentzVector innerTrack() const { return innerTrack_;}

	//TObject* genMuon() const { return genMuon_.GetObject() ;}
	virtual TString typeName() const { return "TRootMuon"; }


	void setCaloEnergy(Float_t et_em, Float_t et_had, Float_t et_ho, Float_t caloCompatibility)
	{
		et_em_ = et_em; 
		et_had_ = et_had;
		et_ho_ = et_ho;
		caloCompatibility_ = caloCompatibility;
	}
	
	void setIsoR03(Float_t isoR03_emEt, Float_t isoR03_hadEt, Float_t isoR03_hoEt, Float_t isoR03_sumPt, Int_t isoR03_nTracks, Int_t isoR03_nJets)
	{ 
		isoR03_emEt_ = isoR03_emEt;
		isoR03_hadEt_ = isoR03_hadEt;
		isoR03_hoEt_ = isoR03_hoEt;
		isoR03_sumPt_ = isoR03_sumPt;
		isoR03_nTracks_ = isoR03_nTracks;
		isoR03_nJets_ = isoR03_nJets;
	}
	
	
	void setValidity(Bool_t energyValid, Bool_t matchesValid, Bool_t isolationValid)
	{ 
		energyValid_ = energyValid;
		matchesValid_ = matchesValid;
		isolationValid_ = isolationValid;
	}

	void setDirection(Int_t direction) { direction_ = direction; }
	void setAlgo(Int_t algo) { algo_ = algo; }
	void setID(Int_t id) { id_ = id; }
	void setID(
	        Int_t AllGlobalMuons,
		Int_t AllTrackerMuons,
		Int_t AllStandAloneMuons,
		Int_t TrackerMuonArbitrated,
		Int_t AllArbitrated,
		Int_t GlobalMuonPromptTight,
	        Int_t TMLastStationLoose,
	        Int_t TMLastStationTight,
	        Int_t TMOneStationLoose,
	        Int_t TMOneStationTight,
	        Int_t TMLastStationOptimizedLowPtLoose,
	        Int_t TMLastStationOptimizedLowPtTight,
	        Int_t TM2DCompatibilityLoose,
	        Int_t TM2DCompatibilityTight
	) 
	{ id_ = AllGlobalMuons*1 + AllTrackerMuons*2 + AllStandAloneMuons*4 + TrackerMuonArbitrated*8 + AllArbitrated*16 + GlobalMuonPromptTight*32
	+ TMLastStationLoose*64 + TMLastStationTight*128 + TMOneStationLoose*256 + TMOneStationTight*512 + TMLastStationOptimizedLowPtLoose*1024 
	+ TMLastStationOptimizedLowPtTight*2048 + TM2DCompatibilityLoose*4096 + TM2DCompatibilityTight*8192; }
        
	void SetVetoIso(Bool_t vetoIso) { vetoIso_ = vetoIso;}
	void SetVetoEm(Float_t vetoEm) { vetoEm_ = vetoEm;}
	void SetVetoHad(Float_t vetoHad) { vetoHad_ = vetoHad;}
	void SetD0(Float_t d0) { d0_ = d0;}    
	void SetD0Error(Float_t d0Error) { d0error_ = d0Error;}    
	void SetChi2(Float_t chi2){ chi2_ = chi2;}
        void SetNofValidHits(Int_t nofValidHits){ nofValidHits_ = nofValidHits;}
        void SetInnerTrack (TLorentzVector innerTrack) { innerTrack_ = innerTrack;}


	friend std::ostream& operator<< (std::ostream& stream, const TRootMuon& muon) {
		stream << "TRootMuon - Charge=" << muon.charge() << " (Et,eta,phi)=("<< muon.Et() <<","<< muon.Eta() <<","<< muon.Phi() << ")  vertex(x,y,z)=("<< muon.vx() <<","<< muon.vy() <<","<< muon.vz() << ")" << endl
				<< "            Type(G,T,S,C)=(" << muon.isGlobalMuon() << ","  << muon.isTrackerMuon() << ","  << muon.isStandAloneMuon() << ","  << muon.isCaloMuon() << ") "
				<< "  ID=(" << muon.idTrackerMuonArbitrated() << ","  << muon.idAllArbitrated() << ","  << muon.idGlobalMuonPromptTight() << ","  << muon.idTMLastStationLoose()
				<< ","  << muon.idTMLastStationTight() << ","  << muon.idTM2DCompatibilityLoose() << ","  << muon.idTM2DCompatibilityTight() << ")" << "  Direction=" << muon.direction_ 
				<< "  caloCompatibility="<<  muon.caloCompatibility_ << "  validity(energy,matches,isolation)=(" << muon.energyValid_ <<","<< muon.matchesValid_ <<","<< muon.isolationValid_ << ")" << endl
				<< "            Et_em=" << muon.et_em_ << "  Et_had=" << muon.et_had_ << "  Et_ho=" << muon.et_ho_ <<  endl
				<< "            isolation cone 0.3: Et_em=" << muon.isoR03_emEt_ << "  Et_had=" << muon.isoR03_hadEt_ <<"  Et_ho=" << muon.isoR03_hoEt_  << "  nTracks=" << muon.isoR03_nTracks_ <<"  nJets=" << muon.isoR03_nJets_ << endl;
		return stream;
	};

	
	private:
	
	// Variables from reco::Muon
	Float_t et_em_;
	Float_t et_had_;
	Float_t et_ho_;
	Float_t caloCompatibility_;
	
	Float_t isoR03_emEt_;
	Float_t isoR03_hadEt_;
	Float_t isoR03_hoEt_;
	Float_t isoR03_sumPt_;
	Int_t isoR03_nTracks_;
	Int_t isoR03_nJets_;

	Bool_t energyValid_;
	Bool_t matchesValid_;
	Bool_t isolationValid_;

        //New variables
        Bool_t vetoIso_;            //veto conesize is 0.07  in the ecal and 0.1 in the hcal
	                            // if true-> Isolated
	Float_t vetoEm_;            //veto conesize is 0.07  in the ecal
	Float_t vetoHad_;           //veto conesize is 0.1  in the hcal
	Float_t d0_;                // d0 of global Muon
	Float_t d0error_;           // d0 error of global Muon
	Float_t chi2_;              // chi2 of global Muon
        Int_t nofValidHits_;        // nof hits of inner track
        TLorentzVector innerTrack_; // inner track 

	Int_t direction_;	//  OutsideIn = -1, Undefined = 0, InsideOut = 1
	Int_t algo_; // binary => GlobalMuon=00010 , TrackerMuon=00100 , StandAloneMuon=01000 , CaloMuon=10000
	// MuonId coded in binary word id_ ==> TrackerMuonArbitrated=0000001 , AllArbitrated=0000010 , GlobalMuonPromptTight=0000100 ,
	// TMLastStationLoose=0001000 , TMLastStationTight=0010000 , TM2DCompatibilityLoose=0100000 , TM2DCompatibilityTight=1000000
	Int_t id_;

	ClassDef (TRootMuon,1);
};

#endif



