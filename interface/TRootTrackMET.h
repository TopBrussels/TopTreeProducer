#ifndef TRootTrackMET_h
#define TRootTrackMET_h

#include "../interface/TRootParticle.h"
#include "../interface/TRootMET.h"

#include "Rtypes.h"
#include "TObject.h"

using namespace std;

namespace TopTree
{
	class TRootTrackMET : public TRootMET
	{
	public:

		TRootTrackMET() :
		  TRootMET()
		
		  {;}

		TRootTrackMET(const TRootTrackMET& met) :
		  TRootMET(met)
		  
		  {;}
		  

		  TRootTrackMET(const TRootMET& met) :
		    TRootMET(met)
		   
		    {;}


		  TRootTrackMET(Double_t px, Double_t py, Double_t pz, Double_t e) :
		    TRootMET(px,py,pz,e)
		    
		    {;}
	
		TRootTrackMET(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z) :
		  TRootMET(px,py,pz,e,vtx_x,vtx_y,vtx_z)
		  		
		  {;}

		TRootTrackMET(Double_t px, Double_t py, Double_t pz, Double_t e, Double_t vtx_x, Double_t vtx_y, Double_t vtx_z, Int_t type, Float_t charge) :
		  TRootMET(px,py,pz,e,vtx_x,vtx_y,vtx_z,type,charge)
		 
		  {;}

		TRootTrackMET(const TLorentzVector &momentum) :
		  TRootMET(momentum)
		
		  {;}

		TRootTrackMET(const TLorentzVector &momentum, const TVector3 &vertex, Int_t type, Float_t charge) :
		  TRootMET(momentum, vertex, type, charge)
		  		
		  {;}

		~TRootTrackMET() {;}

		
	        virtual TString typeName() const { return "TRootTrackMET"; }

		
		friend std::ostream& operator<< (std::ostream& stream, const TRootTrackMET& met)
		{
			stream << "TRootTrackMET  (Pt,Px,Py)=("<< met.Pt() <<","<< met.Px() <<","<< met.Py() << ")";
			return stream;
		};


	private:

		

		ClassDef (TRootTrackMET,2);
	};
}

#endif
