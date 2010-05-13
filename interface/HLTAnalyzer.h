#ifndef HLTAnalyzer_h
#define HLTAnalyzer_h

// system include files
#include <memory>
#include <string>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "../interface/TRootRun.h"
#include "../interface/TRootEvent.h"

#include <iomanip>

using namespace TopTree;

class HLTAnalyzer
{
	
public:
	
	HLTAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig) :
		verbosity_(0)
		,triggerResultsTag1st_(producersNames.getParameter<edm::InputTag> ("hltProducer1st"))
		,triggerResultsTag2nd_(producersNames.getParameter<edm::InputTag> ("hltProducer2nd"))
		,triggerResultsTag8E29_(producersNames.getParameter<edm::InputTag> ("hltProducer8E29"))
  		,triggerNames_()
  		,triggerNames8E29_()
		,doHLT_(myConfig.getUntrackedParameter<bool>("doHLT",false))
		,doHLT8E29_(myConfig.getUntrackedParameter<bool>("doHLT8E29",false))
  		,nEvents_(0)
  		,nWasRun_(0)
  		,nAccept_(0)
  		,nErrors_(0)
  		,nWasRun8E29_(0)
  		,nAccept8E29_(0)
  		,nErrors8E29_(0)
  		,hltWasRun_(0)
  		,hltAccept_(0)
  		,hltErrors_(0)
  		,hltNames_(0)
  		,hltWasRun8E29_(0)
  		,hltAccept8E29_(0)
  		,hltErrors8E29_(0)
  		,hltNames8E29_(0)
		{;}
	
	~HLTAnalyzer() {;}
	
	void setVerbosity(int verbosity) {verbosity_ = verbosity; };
	void init(const edm::Event& iEvent, TRootEvent* rootEvent);
	void process(const edm::Event& iEvent, TRootEvent* rootEvent);
	void printStats();
	void copySummary(TRootRun* runInfos);
	
/*	unsigned int  nHLTPaths() const { return hltNames_.size(); }

	unsigned int  nEvents() const { return nEvents_; }
	unsigned int  nWasRun() const { return nWasRun_; }
	unsigned int  nAccept() const { return nAccept_; }
	unsigned int  nErrors() const { return nErrors_; }

	std::vector<unsigned int> hltWasRun() const { return hltWasRun_; }
	std::vector<unsigned int> hltAccept() const { return hltAccept_; }
	std::vector<unsigned int> hltErrors() const { return hltErrors_; }
	std::vector<std::string>  hltNames() const { return hltNames_; }

	unsigned int hltWasRun(unsigned ipath) const { return (hltWasRun_.size()>ipath ?  hltWasRun_.at(ipath) : 0 ); }
	unsigned int hltAccept(unsigned ipath) const { return (hltAccept_.size()>ipath ?  hltAccept_.at(ipath) : 0 ); }
	unsigned int hltErrors(unsigned ipath) const { return (hltErrors_.size()>ipath ?  hltErrors_.at(ipath) : 0 ); }
	std::string hltNames(unsigned ipath) const { return (hltNames_.size()>ipath ?  hltNames_.at(ipath) : "noname" ); }
*/

private:
	int verbosity_;
	
	edm::InputTag triggerResultsTag_;		// Input tag for TriggerResults, final choice
	edm::InputTag triggerResultsTag1st_;	// Input tag for TriggerResults, 1st choice
	edm::InputTag triggerResultsTag2nd_;	// Input tag for TriggerResults, 2nd choice
	edm::InputTag triggerResultsTag8E29_;	// Input tag for TriggerResults8E29

	edm::TriggerNames triggerNames_;			// TriggerNames class
	edm::TriggerNames triggerNames8E29_;	// TriggerNames8E29 class

	bool doHLT_;
	bool doHLT8E29_;

	unsigned int  nEvents_;								// number of events processed

	unsigned int  nWasRun_;								// # where at least one HLT was run
	unsigned int  nAccept_;								// # of accepted events
	unsigned int  nErrors_;								// # where at least one HLT had error
	unsigned int  nWasRun8E29_;						// # where at least one HLT was run
	unsigned int  nAccept8E29_;						// # of accepted events
	unsigned int  nErrors8E29_;						// # where at least one HLT had error

	std::vector<unsigned int> hltWasRun_;			// # where HLT[i] was run
	std::vector<unsigned int> hltAccept_;			// # of events accepted by HLT[i]
	std::vector<unsigned int> hltErrors_;			// # of events with error in HLT[i]
	std::vector<std::string>  hltNames_;			// name of each HLT algorithm
	std::vector<unsigned int> hltWasRun8E29_;		// # where HLT[i] was run
	std::vector<unsigned int> hltAccept8E29_;		// # of events accepted by HLT[i]
	std::vector<unsigned int> hltErrors8E29_;		// # of events with error in HLT[i]
	std::vector<std::string>  hltNames8E29_;		// name of each HLT algorithm
	
};

#endif
