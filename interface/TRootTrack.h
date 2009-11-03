#ifndef TRootTrack_h
#define TRootTrack_h

#include "../interface/TRootParticle.h"
#include "../interface/TRootXYZPoint.h"

using namespace std;

namespace TopTree{
class TRootTrack : public TRootParticle
{

public:

	TRootTrack() :
	  TRootParticle()
	  ,isValid_(false)
          ,d0_(-9999.)
          ,d0error_(-9999.)
          ,dz_(-9999.)
          ,dzerror_(-9999.)
          ,nofValidHits_(-9999)
	  ,innerPosition_(TRootXYZPoint(-9999.,-9999.,-9999.))
	  ,outerPosition_(TRootXYZPoint(-9999.,-9999.,-9999.))

	{;}

	TRootTrack(const TRootTrack& track) :
          TRootParticle(track)
	  ,isValid_(track.isValid_)
          ,d0_(track.d0_)
          ,d0error_(track.d0error_)
          ,dz_(track.dz_)                                        
          ,dzerror_(track.dzerror_)
          ,nofValidHits_(track.nofValidHits_)
	  ,innerPosition_(track.innerPosition_)
	  ,outerPosition_(track.innerPosition_)

        {;}

	TRootTrack(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type,Float_t charge ) :
	  TRootParticle(momentum,vertex,type,charge)
	  ,isValid_(false)
	  ,d0_(-9999.)
          ,d0error_(-9999.)
          ,dz_(-9999.)
          ,dzerror_(-9999.)
          ,nofValidHits_(-9999)
	  ,innerPosition_(TRootXYZPoint(-9999.,-9999.,-9999.))
	  ,outerPosition_(TRootXYZPoint(-9999.,-9999.,-9999.))

	{;}


	~TRootTrack() {;}

	// OutPut methods

	Bool_t isValid() const { return isValid_; }

	Double_t d0 () const { return d0_; }
	Double_t d0Error () const { return d0error_; }
	Double_t dZ () const { return dz_; }
	Double_t dZError () const { return dzerror_; }

	Int_t nofValidHits () const { return nofValidHits_; }

	TRootXYZPoint innerPosition() const { return innerPosition_; }
	TRootXYZPoint outerPosition() const { return outerPosition_; }

	// input methods

	void SetValid (Bool_t valid) { isValid_ = valid; }

	void SetD0 ( Double_t d0 ) { d0_ = d0;} 
	void SetD0Error ( Double_t d0error ) { d0error_ = d0error;} 
	void SetDZ ( Double_t dz ) { dz_ = dz;} 
	void SetDZError ( Double_t dzerror ) { dzerror_ = dzerror;} 

        void SetInnerPosition (Double_t x, Double_t y, Double_t z) {

	  innerPosition_.setx(x);
	  innerPosition_.sety(y);
	  innerPosition_.setz(z);

	}

        void SetOuterPosition (Double_t x, Double_t y, Double_t z) {

  	  outerPosition_.setx(x);
	  outerPosition_.sety(y);
	  outerPosition_.setz(z);


	}

	void SetNofValidHits (Int_t n) {

	  nofValidHits_ = n;

	}

	virtual TString typeName() const { return "TRootTrack"; }

	friend std::ostream& operator<< (std::ostream& stream, const TRootTrack& track) {
	  stream << "TRootTrack - Charge=" << track.charge() << " (Pt,eta,phi)=("<< track.Pt() <<","<< track.Eta() <<","<< track.Phi() << 
")  vertex(x,y,z)=("<< track.vx() <<","<< track.vy() <<","<< track.vz() << ")" << endl << "  innerPos (x,y,z)=(" << track.innerPosition().x()  
<< "," << track.innerPosition().y() << "," << track.innerPosition().z() << ")" << endl << " d0: " << track.d0() << endl;  

		return stream;
	};


	private:
	
	// Variables from reco::Track

 	// charge momentum eta,phi ,... -> TRootParticle

	Bool_t isValid_;

	Double_t d0_;
	Double_t d0error_;
	Double_t dz_;
	Double_t dzerror_;

	Int_t nofValidHits_;

	TRootXYZPoint innerPosition_;
	TRootXYZPoint outerPosition_;
	

	ClassDef (TRootTrack,1);
};
}
#endif



