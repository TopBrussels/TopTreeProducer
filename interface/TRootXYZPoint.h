#ifndef TRootXYZPoint_h
#define TRootXYZPoint_h

#include "TObject.h"

namespace TopTree
{
	class TRootXYZPoint : public TObject
	{

	public :
		TRootXYZPoint () :
			x_(-9999.)
			,y_(-9999.)
			,z_(-9999.)
			{;}

		TRootXYZPoint ( const TRootXYZPoint &point ) :
			x_(point.x_)
			,y_(point.y_)
			,z_(point.z_)
			{;}

		TRootXYZPoint (Float_t x, Float_t y, Float_t z) :
			x_(x)
			,y_(y)
			,z_(z)
			{;}

		~TRootXYZPoint () {;}
   
		Float_t x () const { return x_; } 
		Float_t y () const { return y_; } 
	   Float_t z () const { return z_; } 

		void setx ( Float_t x ) { x_ = x; }
		void sety ( Float_t y ) { y_ = y; }
		void setz ( Float_t z ) { z_ = z; }

	private:
		Float_t x_;
		Float_t y_;
		Float_t z_;

		ClassDef(TRootXYZPoint,1);
	};
}

#endif
