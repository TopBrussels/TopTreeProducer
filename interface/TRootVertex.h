#ifndef TRootVertex_h
#define TRootVertex_h

#include "../interface/TRootXYZPoint.h"

#include <string>
#include <iostream>

#include "Rtypes.h"
#include "TVector3.h"
#include "TRef.h"

using namespace std;

namespace TopTree
{
	class TRootVertex : public TRootXYZPoint
	{

	public:
		TRootVertex() :
			TRootXYZPoint()
			,isValid_(false)
			,isFake_(true)
			,chi2_(-9999.)
			,ndof_(-9999.)
			,tracksSize_(-9999)
			{;}
	
		TRootVertex(const TRootVertex& vertex) :
			TRootXYZPoint(vertex)
			,isValid_(vertex.isValid_)
			,isFake_(vertex.isFake_)
			,chi2_(vertex.chi2_)
			,ndof_(vertex.ndof_)
			,tracksSize_(vertex.tracksSize_)
			{;}
	
		TRootVertex(Float_t x, Float_t y, Float_t z) :
			TRootXYZPoint(x,y,z)
			,isValid_(false)
			,isFake_(true)
			,chi2_(-9999.)
			,ndof_(-9999.)
			,tracksSize_(-9999)
			{;}

		TRootVertex(Float_t x, Float_t xError, Float_t y, Float_t yError, Float_t z, Float_t zError) :
			TRootXYZPoint(x,xError,y,yError,z,zError)
			,isValid_(false)
			,isFake_(true)
			,chi2_(-9999.)
			,ndof_(-9999.)
			,tracksSize_(-9999)
			{;}
	
		~TRootVertex() {;}
	
		Bool_t isValid() const { return isValid_; }
		Bool_t isFake() const { return isFake_; }
		Float_t chi2() const { return chi2_; }
		Float_t ndof() const { return ndof_; }
		Float_t normalizedChi2() const
		{
			Float_t normalizedChi2_ = -9999;
			if(ndof_ != 0) normalizedChi2_ = chi2_/ndof_;
			return normalizedChi2_;
		}
		Int_t tracksSize() const { return tracksSize_; }
	
		void setIsValid(Bool_t isValid) { isValid_ = isValid; }
		void setIsFake(Bool_t isFake) { isFake_ = isFake; }
		void setChi2(Float_t chi2) { chi2_ = chi2; }
		void setNdof(Float_t ndof) { ndof_ = ndof; }
		void setTracksSize(Float_t tracksSize) { tracksSize_ = tracksSize; }

	private:
	
		Bool_t isValid_;
		Bool_t isFake_;
		Float_t chi2_;			//	Not divided by ndof
		Float_t ndof_;
		Int_t tracksSize_;

		ClassDef (TRootVertex,1);
	};
}

#endif
