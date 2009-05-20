#ifndef TRootWCandidate_h
#define TRootWCandidate_h

#include "TRootJet.h"
#include "TRootMuon.h"

#include <string>
#include <iostream>
#include <vector>

#include "Rtypes.h"
#include "TLorentzVector.h"

using namespace std;

class TRootWCandidate  : public TLorentzVector
{

public:
	

	TRootWCandidate() : TLorentzVector(), quarkP_(0), quarkQ_(0), lepton_(0), TLquarkP_(TLorentzVector()), TLquarkQ_(TLorentzVector()), TLlepton_(TLorentzVector()), neutrino_(TLorentzVector()), isLeptonic_(false), TLFormat_(false) {;};
	TRootWCandidate( const TLorentzVector& a) : TLorentzVector(a), quarkP_(0), quarkQ_(0), lepton_(0), TLquarkP_(TLorentzVector()), TLquarkQ_(TLorentzVector()), TLlepton_(TLorentzVector()), neutrino_(TLorentzVector()), isLeptonic_(false), TLFormat_(false) {;};
	TRootWCandidate(const TRootJet* quarkP, const TRootJet* quarkQ) : TLorentzVector(((TLorentzVector)*quarkP)+((TLorentzVector)*quarkQ)), quarkP_(quarkP), quarkQ_(quarkQ), lepton_(0), TLquarkP_(TLorentzVector((TLorentzVector)*quarkP)), TLquarkQ_(TLorentzVector((TLorentzVector)*quarkQ)), TLlepton_(TLorentzVector()), neutrino_(TLorentzVector()), isLeptonic_(false), TLFormat_(false) {;};
	TRootWCandidate(const TRootMuon* lepton, TLorentzVector neutrino) : TLorentzVector(neutrino+(TLorentzVector)*lepton), quarkP_(0), quarkQ_(0), lepton_(lepton), TLquarkP_(TLorentzVector()), TLquarkQ_(TLorentzVector()), TLlepton_(TLorentzVector((TLorentzVector)*lepton)),  neutrino_(neutrino), isLeptonic_(true), TLFormat_(false) {;};
	TRootWCandidate(const TLorentzVector& prod1, const TLorentzVector& prod2, bool isSemiLep) : TLorentzVector(prod1+prod2){
	   quarkP_ = 0;
	   quarkQ_ = 0;
	   lepton_ = 0;
	   isLeptonic_ = isSemiLep;
	   TLFormat_ = true;
	   if(isSemiLep){
	     TLquarkP_ = prod1;
	     TLquarkQ_ = prod2;
	   }
	   else{
	     TLlepton_ = prod1;
	     neutrino_ = prod2;
	   }
	}
	~TRootWCandidate() {;}

	virtual TString typeName() const { return "TRootWCandidate"; }
       
        bool isTLFormat() const { return TLFormat_;};
	bool isLeptonic() const { return isLeptonic_; };
	bool isHadronic() const { return!isLeptonic_; };
        
	const TRootJet* QuarkP() const {return quarkP_;};
	const TRootJet* QuarkQ() const {return quarkQ_;};
	const TRootMuon* Lepton() const {return lepton_;};
	TLorentzVector TLQuarkP() const {return TLquarkP_;};
	TLorentzVector TLQuarkQ() const {return TLquarkQ_;};
	TLorentzVector TLLepton() const {return TLlepton_;};
	TLorentzVector Neutrino() const {return neutrino_;};
        

	friend std::ostream& operator<< (std::ostream& stream, const TRootWCandidate& part)
	{
	        stream << "W ("<<part.Px()<<","<<part.Py()<<","<<part.Pz()<<","<<part.Energy() << ") mass:"<<part.M()<<endl;
		if(part.isLeptonic()){
		  stream<<" is leptonic:"<<endl;
		  stream<<"QuarkP: ("<<part.QuarkP()->Px()<<","<<part.QuarkP()->Py()<<","<<part.QuarkP()->Pz()<<","<<part.QuarkP()->Energy()<<")"<<endl;
		  stream<<"QuarkQ: ("<<part.QuarkQ()->Px()<<","<<part.QuarkQ()->Py()<<","<<part.QuarkQ()->Pz()<<","<<part.QuarkQ()->Energy()<<")"<<endl;
		}
		else{
		  stream<<" is leptonic:"<<endl;
		  stream<<"lepton: ("<<part.Lepton()->Px()<<","<<part.Lepton()->Py()<<","<<part.Lepton()->Pz()<<","<<part.Lepton()->Energy()<<")"<<endl;
		  stream<<"neutrino: ("<<part.Neutrino().Px()<<","<<part.Neutrino().Py()<<","<<part.Neutrino().Pz()<<","<<part.Neutrino().Energy()<<")"<<endl;
		}
	 	return stream;
	};


protected:
	
        const TRootJet* quarkP_;
	const TRootJet* quarkQ_;
	const TRootMuon* lepton_;
        TLorentzVector TLquarkP_;
	TLorentzVector TLquarkQ_;
	TLorentzVector TLlepton_;
	TLorentzVector neutrino_;
	bool isLeptonic_;
        bool TLFormat_;

	ClassDef (TRootWCandidate,1);
};

#endif


