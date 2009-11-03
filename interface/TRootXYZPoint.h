#ifndef TRootXYZPoint_h
#define TRootXYZPoint_h

#include "TObject.h"
namespace TopTree{
class TRootXYZPoint : public TObject {

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

	TRootXYZPoint (Double_t x,Double_t y,Double_t z) {

	  x_ = x;
	  y_ = y;
	  z_ = z;

	}


	~TRootXYZPoint ()
	
	{;}
   
   Double_t x () const { return x_; } 
   Double_t y () const { return y_; } 
   Double_t z () const { return z_; } 

   void setx ( Double_t x ) { x_ = x; }
   void sety ( Double_t y ) { y_ = y; }
   void setz ( Double_t z ) { z_ = z; }

   private:

	Double_t x_;
	Double_t y_;
	Double_t z_;

   ClassDef(TRootXYZPoint,1);

};
}
#endif
