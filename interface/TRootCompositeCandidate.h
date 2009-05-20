#ifndef TRootCompositeCandidate_h
#define TRootCompositeCandidate_h

#include "TRootTopCandidate.h"

#include <string>
#include <iostream>
#include <vector>

#include "Rtypes.h"
#include "TLorentzVector.h"

using namespace std;

class TRootCompositeCandidate  : public TLorentzVector
{

public:
	

	TRootCompositeCandidate() : TLorentzVector() {;};
	TRootCompositeCandidate( const TLorentzVector& a) : TLorentzVector(a) {;};
	TRootCompositeCandidate( std::vector <std::pair<TRootTopCandidate,std::string> > daughters) {
	   TLorentzVector a;
	   for(unsigned int i=0;i<daughters.size();i++)
	   	a+=daughters[i].first;
	   const TLorentzVector b;
	   (*this) = TLorentzVector(b);
	   daughters_ = daughters;  
	}
	~TRootCompositeCandidate() {;}

	virtual TString typeName() const { return "TRootCompositeCandidate"; }


        TRootTopCandidate	daughter(const std::string& s) const { for(unsigned int i=0;i<daughters_.size();i++) if(daughters_[i].second == s) return daughters_[i].first;};
	std::vector< std::pair<TRootTopCandidate,std::string> > daughters() const { return daughters_;};
	int NofDaughters() const { return daughters_.size(); };
	void SetDaughters( std::vector< std::pair<TRootTopCandidate,std::string> > daughters) { daughters_ = daughters; };
        

	friend std::ostream& operator<< (std::ostream& stream, const TRootCompositeCandidate& part)
	{
	        stream << "CompositeCandidate composed by "<<part.NofDaughters() << "daughters:"<<endl;
		for(unsigned int i=0;i<part.daughters().size();i++){
		  stream << i+1 << " - "<<part.daughters()[i].second<<" P4: (";
		  stream <<part.daughters()[i].first.Px()<<","<<part.daughters()[i].first.Py()<<","<<part.daughters()[i].first.Pz()<<","<<part.daughters()[i].first.Energy()<<")"<<endl;
		}
		stream << "ComposedCandidate : " << part <<" mass: " << part.M() << endl;
	 	return stream;
	};


protected:
	
	std::vector< std::pair<TRootTopCandidate,std::string> > daughters_;

	ClassDef (TRootCompositeCandidate,1);
};

#endif


