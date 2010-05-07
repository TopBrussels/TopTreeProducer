#ifndef TRootTopCandidate_h
#define TRootTopCandidate_h

#include "../interface/TRootWCandidate.h"
#include "../interface/TRootJet.h"

#include <string>
#include <iostream>
#include <vector>

#include "Rtypes.h"
#include "TLorentzVector.h"

using namespace std;

namespace TopTree
{
	class TRootTopCandidate  : public TLorentzVector
	{

	public:
		TRootTopCandidate() : TLorentzVector(0,0,0,0), Wcand_(TRootWCandidate()), bquark_(0), TLbquark_(TLorentzVector()), TLFormat_(false) {;};
		TRootTopCandidate( const TLorentzVector& a) : TLorentzVector(a), Wcand_(TRootWCandidate()), bquark_(0), TLbquark_(TLorentzVector()), TLFormat_(false) {;};
		TRootTopCandidate( TRootWCandidate Wcand, const TRootJet* b) : TLorentzVector( (TLorentzVector)Wcand+*((TLorentzVector*)b)), Wcand_(Wcand), bquark_(b), TLbquark_(TLorentzVector((TLorentzVector)*b)),TLFormat_(false) {;};
		TRootTopCandidate( TRootWCandidate Wcand, const TLorentzVector& b) : TLorentzVector( (TLorentzVector)Wcand+b), Wcand_(Wcand), bquark_(0), TLbquark_(b), TLFormat_(true) {;};
		~TRootTopCandidate() {;}

		virtual TString typeName() const { return "TRootTopCandidate"; }

		TRootWCandidate W() const {return Wcand_;};
		const TRootJet* B() const {return bquark_;};
		TLorentzVector TLB() const {return TLbquark_;};
       
		Bool_t isTLFormat()const {return TLFormat_;};

		friend std::ostream& operator<< (std::ostream& stream, const TRootTopCandidate& part)
		{
			stream << "Top ("<<part.Px()<<","<<part.Py()<<","<<part.Pz()<<","<<part.Energy() << ") mass:"<<part.M()<<endl;
			stream<<"W: ("<<part.W().Px()<<","<<part.W().Py()<<","<<part.W().Pz()<<","<<part.W().Energy()<<")"<<endl;
			stream<<"b: ("<<part.B()->Px()<<","<<part.B()->Py()<<","<<part.B()->Pz()<<","<<part.B()->Energy()<<")"<<endl;
			return stream;
		};

	protected:
		TRootWCandidate Wcand_;
		const TRootJet* bquark_;
		TLorentzVector TLbquark_;
		Bool_t TLFormat_;

		ClassDef (TRootTopCandidate,1);
	};
}

#endif
