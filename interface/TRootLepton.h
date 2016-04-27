#ifndef TRootLepton_h
#define TRootLepton_h

#include <map>
#include <iostream>
#include <TLorentzVector.h>


#include "../interface/TRootParticle.h"

using namespace std;

namespace TopTree
{
	class TRootLepton : public TRootParticle
	{
		
	public:
		TRootLepton() :
		TRootParticle(),
		ip3d_(-9999.),
		d0_(-9999.),
		d0Error_(-9999.),
		d0BeamSpot_(-9999.),
		d0BeamSpotError_(-9999.),
		dz_(-9999.),
		dzError_(-9999.),
		dzBeamSpot_(-9999.),
		dzBeamSpotError_(-9999.),
		chargedHadronIso03_(-9999),
		puChargedHadronIso03_(-9999.),
		photonIso03_(-9999),
		neutralHadronIso03_(-9999),
		chargedHadronIso04_(-9999),
		puChargedHadronIso04_(-9999.),
		photonIso04_(-9999),
		neutralHadronIso04_(-9999)
		{;}
		
		TRootLepton(const TRootLepton& lepton) :
		TRootParticle(lepton),
		ip3d_(lepton.ip3d_),
		d0_(lepton.d0_),
		d0Error_(lepton.d0Error_),
		d0BeamSpot_(lepton.d0BeamSpot_),
		d0BeamSpotError_(lepton.d0BeamSpotError_),
		dz_(lepton.dz_),
		dzError_(lepton.dzError_),
		dzBeamSpot_(lepton.dzBeamSpot_),
		dzBeamSpotError_(lepton.dzBeamSpotError_),
		chargedHadronIso03_(lepton.chargedHadronIso03_),
		puChargedHadronIso03_(lepton.puChargedHadronIso03_),
		photonIso03_(lepton.photonIso03_),
		neutralHadronIso03_(lepton.neutralHadronIso03_),
		chargedHadronIso04_(lepton.chargedHadronIso04_),
		puChargedHadronIso04_(lepton.puChargedHadronIso04_),
		photonIso04_(lepton.photonIso04_),
		neutralHadronIso04_(lepton.neutralHadronIso04_)
		{;}
		
		TRootLepton(Double_t px, Double_t py, Double_t pz, Double_t e) :
		TRootParticle(px,py,pz,e),
		ip3d_(-9999.),
		d0_(-9999.),
		d0Error_(-9999.),
		d0BeamSpot_(-9999.),
		d0BeamSpotError_(-9999.),
		dz_(-9999.),
		dzError_(-9999.),
		dzBeamSpot_(-9999.),
		dzBeamSpotError_(-9999.),
		chargedHadronIso03_(-9999),
		puChargedHadronIso03_(-9999.),
		photonIso03_(-9999),
		neutralHadronIso03_(-9999),
		chargedHadronIso04_(-9999),
		puChargedHadronIso04_(-9999.),
		photonIso04_(-9999),
		neutralHadronIso04_(-9999)
		{;}
		
		TRootLepton(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
		TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z),
		ip3d_(-9999.),
		d0_(-9999.),
		d0Error_(-9999.),
		d0BeamSpot_(-9999.),
		d0BeamSpotError_(-9999.),
		dz_(-9999.),
		dzError_(-9999.),
		dzBeamSpot_(-9999.),
		dzBeamSpotError_(-9999.),
		chargedHadronIso03_(-9999),
		puChargedHadronIso03_(-9999.),
		photonIso03_(-9999),
		neutralHadronIso03_(-9999),
		chargedHadronIso04_(-9999),
		puChargedHadronIso04_(-9999.),
		photonIso04_(-9999),
		neutralHadronIso04_(-9999)
		{;}
		
		TRootLepton(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Int_t charge) :
		TRootParticle(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge),
		ip3d_(-9999.),
		d0_(-9999.),
		d0Error_(-9999.),
		d0BeamSpot_(-9999.),
		d0BeamSpotError_(-9999.),
		dz_(-9999.),
		dzError_(-9999.),
		dzBeamSpot_(-9999.),
		dzBeamSpotError_(-9999.),
		chargedHadronIso03_(-9999),
		puChargedHadronIso03_(-9999.),
		photonIso03_(-9999),
		neutralHadronIso03_(-9999),
		chargedHadronIso04_(-9999),
		puChargedHadronIso04_(-9999.),
		photonIso04_(-9999),
		neutralHadronIso04_(-9999)
		{;}
		
		TRootLepton(const TLorentzVector &momentum) :
		TRootParticle(momentum),
		ip3d_(-9999.),
		d0_(-9999.),
		d0Error_(-9999.),
		d0BeamSpot_(-9999.),
		d0BeamSpotError_(-9999.),
		dz_(-9999.),
		dzError_(-9999.),
		dzBeamSpot_(-9999.),
		dzBeamSpotError_(-9999.),
		chargedHadronIso03_(-9999),
		puChargedHadronIso03_(-9999.),
		photonIso03_(-9999),
		neutralHadronIso03_(-9999),
		chargedHadronIso04_(-9999),
		puChargedHadronIso04_(-9999.),
		photonIso04_(-9999),
		neutralHadronIso04_(-9999)
		{;}
		
		TRootLepton(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
		TRootParticle(momentum,vertex,type,charge),
		ip3d_(-9999.),
		d0_(-9999.),
		d0Error_(-9999.),
		d0BeamSpot_(-9999.),
		d0BeamSpotError_(-9999.),
		dz_(-9999.),
		dzError_(-9999.),
		dzBeamSpot_(-9999.),
		dzBeamSpotError_(-9999.),
		chargedHadronIso03_(-9999),
		puChargedHadronIso03_(-9999.),
		photonIso03_(-9999),
		neutralHadronIso03_(-9999),
		chargedHadronIso04_(-9999),
		puChargedHadronIso04_(-9999.),
		photonIso04_(-9999),
		neutralHadronIso04_(-9999)
		{;}
		
		~TRootLepton() {;}
		
		
	public:
		virtual TString typeName() const { return "TRootLepton"; }
		
		Float_t ip3d() const { return ip3d_; }
		Float_t d0() const { return d0_; }
		Float_t d0Error()const { return d0Error_; }
		Float_t d0BeamSpot() const { return d0BeamSpot_; }
		Float_t d0BeamSpotError()const { return d0BeamSpotError_; }
		Float_t dz()const { return dz_; }
		Float_t dzError()const { return dzError_; }
		Float_t dzBeamSpot() const { return dzBeamSpot_; }
		Float_t dzBeamSpotError()const { return dzBeamSpotError_; }
	
		//particle based isolation
		Float_t chargedHadronIso(unsigned int cone) const
		{
			if(cone == 3) return chargedHadronIso03_;
			else if(cone == 4) return chargedHadronIso04_;
			else cout <<"Bad Cone Size! It returns 9999."<<endl;
			return 9999;
		}
		Float_t puChargedHadronIso(unsigned int cone) const
		{
			if(cone == 3) return puChargedHadronIso03_;
			else if(cone == 4) return puChargedHadronIso04_;
			else cout <<"Bad Cone Size! It returns 9999."<<endl;
			return 9999;
		}
		Float_t photonIso(unsigned int cone) const
		{
			if(cone == 3) return photonIso03_;
			else if(cone == 4) return photonIso04_;
			else cout <<"Bad Cone Size! It returns 9999."<<endl;
			return 9999;
		}
		Float_t neutralHadronIso(unsigned int cone) const
		{
			if(cone == 3) return neutralHadronIso03_;
			else if(cone == 4) return neutralHadronIso04_;
			else cout <<"Bad Cone Size! It returns 9999."<<endl;
			return 9999;
		}
		Float_t absPfIso(unsigned int cone, float dBetaFactor=0) const
		{
			// in this case, dbeta correction is asked, but
			// the input for this correction is not available.
			// better returning an unphysical result than applying a wrong correction.
			if(dBetaFactor>0 && puChargedHadronIso(cone)<0) return -1;
			
			double neutralIso = neutralHadronIso(cone) + photonIso(cone);
			double corNeutralIso = neutralIso - dBetaFactor * puChargedHadronIso(cone);
			double charged = chargedHadronIso(cone);
			
			return charged + ( corNeutralIso>0 ? corNeutralIso : 0 ) ;
		}
		Float_t relPfIso(unsigned int cone, float dBetaFactor=0) const
		{
			double relIso = absPfIso(cone, dBetaFactor)/((TLorentzVector)(*this)).Pt();
			return relIso;
		}
		
		//setters
		void setIp3d(Float_t x) { ip3d_ = x; }
		void setD0(Float_t x) { d0_ = x; }
		void setD0Error(Float_t x) { d0Error_ = x; }
		void setD0BeamSpot(Float_t x) { d0BeamSpot_ = x; }
		void setD0BeamSpotError(Float_t x) { d0BeamSpotError_ = x; }
		void setDz(Float_t x) { dz_ = x; }
		void setDzError(Float_t x) { dzError_ = x; }
		void setDzBeamSpot(Float_t x) { dzBeamSpot_ = x; }
		void setDzBeamSpotError(Float_t x) { dzBeamSpotError_ = x; }
		
		//particle based isolation
		void setIsoR03_ChargedHadronIso(Float_t chargedHadronIso){ chargedHadronIso03_ = chargedHadronIso; }
		void setIsoR03_PuChargedHadronIso(Float_t iso) { puChargedHadronIso03_ = iso; }
		void setIsoR03_PhotonIso(Float_t photonIso){ photonIso03_ = photonIso; }
		void setIsoR03_NeutralHadronIso(Float_t neutralHadronIso){ neutralHadronIso03_ = neutralHadronIso; }
		void setIsoR04_ChargedHadronIso(Float_t chargedHadronIso){ chargedHadronIso04_ = chargedHadronIso; }
		void setIsoR04_PuChargedHadronIso(Float_t iso) { puChargedHadronIso04_ = iso; }
		void setIsoR04_PhotonIso(Float_t photonIso){ photonIso04_ = photonIso; }
		void setIsoR04_NeutralHadronIso(Float_t neutralHadronIso){ neutralHadronIso04_ = neutralHadronIso; }
	 
	protected:
		
		//TrackProperties=====================================
		Float_t ip3d_;                             // 3D impact parameter
		Float_t d0_;                         	     // transverse impact parameter (wrt to PV)
		Float_t d0Error_;                          // error on d0_
		Float_t d0BeamSpot_;                         	     // transverse impact parameter (wrt to beam spot)
		Float_t d0BeamSpotError_;                          // error on d0BeamSpot_
		Float_t dz_;                               // longitudinal impact parameter (wrt to PV)
		Float_t dzError_;                          // error on dz_
		Float_t dzBeamSpot_;                         	     // longitudinal impact parameter (wrt to beam spot)
		Float_t dzBeamSpotError_;                          // error on dzBeamSpot_
		
		//particle based isolation
		Float_t chargedHadronIso03_;                 // isolation calculated with only the charged hadron candidates
		Float_t puChargedHadronIso03_;               // isolation calculated with only the pile-up charged hadron candidates
		Float_t photonIso03_;                        // isolation calculated with only the gamma candidates
		Float_t neutralHadronIso03_;	               // isolation calculated with only the neutral hadron candidates
		Float_t chargedHadronIso04_;                 // isolation calculated with only the charged hadron candidates
		Float_t puChargedHadronIso04_;               // isolation calculated with only the pile-up charged hadron candidates
		Float_t photonIso04_;                        // isolation calculated with only the gamma candidates
		Float_t neutralHadronIso04_;                     // isolation calculated with only the neutral hadron candidates
		
		ClassDef (TRootLepton,3);
	};
}

#endif
