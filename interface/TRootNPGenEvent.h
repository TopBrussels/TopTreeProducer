#ifndef TRootNPGenEvent_h
#define TRootNPGenEvent_h
#include <iostream>
#include <iomanip>
#include <vector>

#include "TObject.h"
#include "Rtypes.h"

#include "../interface/TRootMCParticle.h"
#include "../interface/TRootGenTop.h"

namespace TopTree
{
	class TRootNPGenEvent: public TObject{

	public:
		TRootNPGenEvent(){isNewPhysics_ = false;};
		TRootNPGenEvent(const Bool_t isNewPhysics, const std::vector<TopTree::TRootGenTop> tops, const std::vector<TopTree::TRootMCParticle> leptons, const std::vector<TopTree::TRootMCParticle> quarks,
                    const std::vector<TopTree::TRootMCParticle> bquarks, const std::vector<TopTree::TRootMCParticle> invisibleParticles, const std::vector<TopTree::TRootMCParticle> neutrinos,
                    const std::vector<TopTree::TRootMCParticle> gluinos, const std::vector<TopTree::TRootMCParticle> stops)
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

		std::vector<TRootGenTop> tops() const {return tops_;};
		std::vector<TRootMCParticle> leptons() const {return leptons_;};
		std::vector<TRootMCParticle> quarks() const {return quarks_;};
		std::vector<TRootMCParticle> bquarks() const {return bquarks_;};
		std::vector<TRootMCParticle> invisibleParticles() const {return invisibleParticles_;};
		std::vector<TRootMCParticle> neutrinos() const {return neutrinos_;}; 
		std::vector<TRootMCParticle> gluinos() const {return gluinos_;}; 
		std::vector<TRootMCParticle> stops() const {return stops_;}; 

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
    std::vector<TRootGenTop> tops_;
		std::vector<TRootMCParticle> leptons_;
		std::vector<TRootMCParticle> quarks_;
		std::vector<TRootMCParticle> bquarks_;
		std::vector<TRootMCParticle> invisibleParticles_;
		std::vector<TRootMCParticle> neutrinos_;
		std::vector<TRootMCParticle> gluinos_;
		std::vector<TRootMCParticle> stops_;
  
		ClassDef (TRootNPGenEvent,3); 
	};
}

#endif
