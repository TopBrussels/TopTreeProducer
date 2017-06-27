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
	
	HLTAnalyzer(edm::EDGetTokenT<edm::TriggerResults> triggerToken1, edm::EDGetTokenT<edm::TriggerResults> triggerToken2,edm::EDGetTokenT<edm::TriggerResults> triggerToken3, edm::EDGetTokenT<edm::TriggerResults> triggerToken4, edm::EDGetTokenT<edm::TriggerResults> triggerToken5, const edm::ParameterSet& myConfig, int verbosity);
	
	~HLTAnalyzer() {;}
	
	void init(const edm::Event& iEvent, TRootEvent* rootEvent);
	void process(const edm::Event& iEvent, TRootEvent* rootEvent, edm::ParameterSet valuesForConsumeCommand);
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
	
	edm::InputTag triggerResultsTag_; // InputTag to store the tag of the final choice
	edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken_;		// Input Token for TriggerResults, final choice
	edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken1st_;	// Input Token for TriggerResults, 1st choice
	edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken2nd_;	// Input Token for TriggerResults, 2nd choice
	edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken3rd_;	// Input Token for TriggerResults, 3rd choice
	edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken4th_;	// Input Token for TriggerResults, 4th choice
	edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken5th_;	// Input Token for TriggerResults, 4th choice

	edm::TriggerNames triggerNames_;			// TriggerNames class

	bool doHLT_;

	unsigned int  nEvents_;								// number of events processed

	unsigned int  nWasRun_;								// # where at least one HLT was run
	unsigned int  nAccept_;								// # of accepted events
	unsigned int  nErrors_;								// # where at least one HLT had error

	std::vector<unsigned int> hltWasRun_;			// # where HLT[i] was run
	std::vector<unsigned int> hltAccept_;			// # of events accepted by HLT[i]
	std::vector<unsigned int> hltErrors_;			// # of events with error in HLT[i]
	std::vector<std::string>  hltNames_;			// name of each HLT algorithm


	// new HLTInfo container

	vector<TopTree::TRootHLTInfo> hltInfos_;
	
};

#endif
