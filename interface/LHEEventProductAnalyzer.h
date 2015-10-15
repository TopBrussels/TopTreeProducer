#ifndef LheEventAnalyzer_h
#define LheEventAnalyzer_h

// system include files
#include <iostream>
#include <map>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "SimDataFormats/GeneratorProducts/interface/WeightsInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"

//#include "../interface/TRootLHEEventProduct.h"
#include "TClonesArray.h"


#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"

//#include "../interface/TRootGenJet.h"
//#include "../interface/TRootEvent.h"

#include "../interface/TRootRun.h"
#include "../interface/TRootEvent.h"

using namespace TopTree;

class LHEEventProductAnalyzer {

public:
  LHEEventProductAnalyzer(const edm::ParameterSet& producersNames);
  LHEEventProductAnalyzer(const edm::ParameterSet& producersNames, int verbosity);
  LHEEventProductAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
	LHEEventProductAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity);
	~LHEEventProductAnalyzer();
	//	void SetVerbosity(int verbosity) { verbosity_ = verbosity; };
	void Process(const edm::Event& iEvent, TRootEvent* rootEvent);
	void PrintWeightNamesList(const edm::Run& iRun);
	void CopyWeightNames(const edm::Run& iRun, TRootRun* runInfos);
private:
	int verbosity_;
	edm::InputTag lheEventProductProducer_;
	std::vector<std::string> vLHEEventProductProducer;
};

#endif

