#ifndef TRootPhoton_h
#define TRootPhoton_h

#include <map>
#include <iostream>
#include <TLorentzVector.h>

#include "../interface/TRootParticle.h"

using namespace std;

namespace TopTree
{
	class TRootPhoton : public TRootParticle 
	{

	public:
		TRootPhoton() :
			TRootParticle()
			{;}
	
		TRootPhoton(const TRootPhoton& photon) :
			TRootParticle(photon)
			{;}
                TRootPhoton(Double_t px, Double_t py, Double_t pz, Double_t e) :
                        TRootParticle(px,py,pz,e)
                        {;}
      	
		~TRootPhoton() {;}
	
	private:
	
		ClassDef (TRootPhoton,0);
	};
}

#endif
