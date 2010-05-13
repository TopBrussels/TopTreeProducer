#ifndef TowerRemover_h
#define TowerRemover_h

#include <memory>
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

class TowerRemover : public edm::EDProducer {

   public:

      explicit TowerRemover(const edm::ParameterSet&);
      ~TowerRemover();

	
   private:
	
        virtual void beginJob() ;
        virtual void produce(edm::Event&, const edm::EventSetup&);
        virtual void endJob() ;

	double DeltaR(double ,double,double ,double);
	double DREleTwr_;
	std::string electronCriteria;
	edm::InputTag src;

};


#endif
