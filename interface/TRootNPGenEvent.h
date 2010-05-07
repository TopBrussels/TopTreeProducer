#ifndef TRootNPGenEvent_h
#define TRootNPGenEvent_h
#include "../interface/TRootGenTop.h"

#include <iostream>
#include <iomanip>
#include <vector>

#include "TObject.h"
#include "Rtypes.h"

using namespace std;

namespace TopTree
{
	class TRootNPGenEvent: public TObject{

	public:
		TRootNPGenEvent(){isNewPhysics_ = false;};
		TRootNPGenEvent(const Bool_t isNewPhysics, const vector<TRootGenTop> tops, const vector<TRootMCParticle> leptons, const vector<TRootMCParticle> quarks, const vector<TRootMCParticle> bquarks, const vector<TRootMCParticle> invisibleParticles, const vector<TRootMCParticle> neutrinos, const vector<TRootMCParticle> gluinos, const vector<TRootMCParticle> stops)
		{
			isNewPhysics_ = isNewPhysics;
			tops_ = tops;
			leptons_ = leptons;
			quarks_ = quarks;
			bquarks_ = bquarks;
			invisibleParticles_ = invisibleParticles;
			neutrinos_ = neutrinos;
			gluinos_ = gluinos;
			stops_ = stops;
		};
		TRootNPGenEvent(const TRootNPGenEvent& gevt)
		{
			isNewPhysics_ = gevt.isNewPhysics_;
			tops_ = gevt.tops_;
			leptons_ = gevt.leptons_;
			quarks_ = gevt.quarks_;
			bquarks_ = gevt.bquarks_;
			invisibleParticles_ = gevt.invisibleParticles_;
			neutrinos_ = gevt.neutrinos_;
			gluinos_ = gevt.gluinos_;
			stops_ = gevt.stops_;
		};

		virtual ~TRootNPGenEvent(){;};

		virtual TString typeName() const { return "TRootNPGenEvent"; }

		Bool_t isNewPhysics() const {return isNewPhysics_;};
		Bool_t isThereTop() const {return tops_.size()>0? true:false;};

		Int_t numberOfTops() const {return tops_.size();};
		Int_t numberOfLeptons() const {return leptons_.size();};
		Int_t numberOfQuarks() const {return quarks_.size();};
		Int_t numberOfBQuarks() const {return bquarks_.size();};
		Int_t numberOfInvisibleParticles() const {return invisibleParticles_.size();};
		Int_t numberOfNeutrinos() const {return neutrinos_.size();};
		Int_t numberOfGluinos() const{ return gluinos_.size();};
		Int_t numberOfStops() const{ return stops_.size();};

		vector<TRootGenTop> tops() const {return tops_;};
		vector<TRootMCParticle> leptons() const {return leptons_;};
		vector<TRootMCParticle> quarks() const {return quarks_;};
		vector<TRootMCParticle> bquarks() const {return bquarks_;};
		vector<TRootMCParticle> invisibleParticles() const {return invisibleParticles_;};
		vector<TRootMCParticle> neutrinos() const {return neutrinos_;}; 
		vector<TRootMCParticle> gluinos() const {return gluinos_;}; 
		vector<TRootMCParticle> stops() const {return stops_;}; 

		friend std::ostream& operator<< (std::ostream& stream, const TRootNPGenEvent& gevent)
		{
			stream <<"Event ";
			if (gevent.isNewPhysics()) stream << " is NewPhysics ";
			stream <<". ";
			stream << gevent.numberOfTops() <<" tops - "<< gevent.numberOfLeptons()<< " leptons - "<< gevent.numberOfQuarks() <<" quarks - ( "<< gevent.numberOfBQuarks()<<"b ) ";
			stream << gevent.numberOfInvisibleParticles() <<" invisible particles ( "<< gevent.numberOfNeutrinos() <<" neutrinos )";
			return stream;
		}

	private:
  
		Bool_t isNewPhysics_;
		vector<TRootGenTop> tops_;
		vector<TRootMCParticle> leptons_;
		vector<TRootMCParticle> quarks_;
		vector<TRootMCParticle> bquarks_;
		vector<TRootMCParticle> invisibleParticles_;
		vector<TRootMCParticle> neutrinos_;
		vector<TRootMCParticle> gluinos_;
		vector<TRootMCParticle> stops_;
  
		ClassDef (TRootNPGenEvent,2); 
	};
}

#endif
