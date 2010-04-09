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
			,xError_(-9999.)
			,y_(-9999.)
			,yError_(-9999.)
			,z_(-9999.)
			,zError_(-9999.)
			{;}

		TRootXYZPoint ( const TRootXYZPoint &point ) :
			x_(point.x_)
			,xError_(point.xError_)
			,y_(point.y_)
			,yError_(point.yError_)
			,z_(point.z_)
			,zError_(point.zError_)
			{;}

		TRootXYZPoint (Float_t x, Float_t y, Float_t z) :
			x_(x)
			,xError_(-9999.)
			,y_(y)
			,yError_(-9999.)
			,z_(z)
			,zError_(-9999.)
			{;}

		TRootXYZPoint (Float_t x, Float_t xError, Float_t y, Float_t yError, Float_t z, Float_t zError) :
			x_(x)
			,xError_(xError)
			,y_(y)
			,yError_(yError)
			,z_(z)
			,zError_(zError)
			{;}
	
		~TRootXYZPoint () {;}
   
		Float_t x () const { return x_; } 
		Float_t xError () const { return xError_; } 
		Float_t y () const { return y_; } 
		Float_t yError () const { return yError_; } 
	   Float_t z () const { return z_; } 
	   Float_t zError () const { return zError_; } 

		void setx ( Float_t x ) { x_ = x; }
		void setxError ( Float_t xError ) { xError_ = xError; }
		void sety ( Float_t y ) { y_ = y; }
		void setyError ( Float_t yError ) { yError_ = yError; }
		void setz ( Float_t z ) { z_ = z; }
		void setzError ( Float_t zError ) { zError_ = zError; }

	private:
		Float_t x_;
		Float_t xError_;
		Float_t y_;
		Float_t yError_;
		Float_t z_;
		Float_t zError_;

		ClassDef(TRootXYZPoint,1);
	};
}

#endif
