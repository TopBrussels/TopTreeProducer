#include "../interface/HLTAnalyzer.h"

using namespace std;
using namespace TopTree;

void HLTAnalyzer::init(const edm::Event& iEvent, TRootEvent* rootEvent)
{
	
	if(doHLT_)
	{
		edm::Handle<edm::TriggerResults> trigResults;
		try {iEvent.getByLabel(triggerResultsTag_,trigResults);} catch (...) {;}
		triggerNames_.init(*trigResults);
		hltNames_=triggerNames_.triggerNames();
		const unsigned int n(hltNames_.size());
		hltWasRun_.resize(n);
		hltAccept_.resize(n);
		hltErrors_.resize(n);
		for (unsigned int i=0; i!=n; ++i)
		{
			hltWasRun_[i]=0;
			hltAccept_[i]=0;
			hltErrors_[i]=0;
		}
	}
	
	if(doHLT8E29_)
	{
		edm::Handle<edm::TriggerResults> trigResults;
		try {iEvent.getByLabel(triggerResultsTag8E29_,trigResults);} catch (...) {;}
		if(trigResults.isValid())
		{
			triggerNames8E29_.init(*trigResults);
			hltNames8E29_=triggerNames8E29_.triggerNames();
			const unsigned int n(hltNames8E29_.size());
			hltWasRun8E29_.resize(n);
			hltAccept8E29_.resize(n);
			hltErrors8E29_.resize(n);
			for (unsigned int i=0; i!=n; ++i)
			{
				hltWasRun8E29_[i]=0;
				hltAccept8E29_[i]=0;
				hltErrors8E29_[i]=0;
			}
		}
		else doHLT8E29_ = false;
	}
	
}

void HLTAnalyzer::process(const edm::Event& iEvent, TRootEvent* rootEvent)
{
	nEvents_++;
	
	if(doHLT_)
	{
		edm::Handle<edm::TriggerResults> trigResults;
		try {iEvent.getByLabel(triggerResultsTag_,trigResults);} catch (...) {;}
		if (trigResults.isValid()) {
			if (trigResults->wasrun()) nWasRun_++;
			const bool accept(trigResults->accept());
			if(verbosity_>0) cout << "   HLT decision: " << accept << endl;
			rootEvent->setGlobalHLT(accept);
			if (accept) ++nAccept_;
			if (trigResults->error() ) nErrors_++;
		}
		else
		{
			cout << "   HLT results not found!" << endl;;
			nErrors_++;
			return;
		}

		// decision for each HLT algorithm
		const unsigned int n(hltNames_.size());
		std::vector<Bool_t> hltDecision(n, false);
		for (unsigned int i=0; i!=n; ++i)
		{
			if (trigResults->wasrun(i)) hltWasRun_[i]++;
			if (trigResults->error(i) ) hltErrors_[i]++;
			if (trigResults->accept(i))
			{
				hltAccept_[i]++;
				hltDecision[i]=true;
			}
		}
	
		rootEvent->setTrigHLT(hltDecision);
	
	}

	if(doHLT8E29_)
	{
		edm::Handle<edm::TriggerResults> trigResults;
		try {iEvent.getByLabel(triggerResultsTag8E29_,trigResults);} catch (...) {;}
		if (trigResults.isValid()) {
			if (trigResults->wasrun()) nWasRun8E29_++;
			const bool accept(trigResults->accept());
			if(verbosity_>0) cout << "   HLT8E29 decision: " << accept << endl;
			rootEvent->setGlobalHLT8E29(accept);
			if (accept) ++nAccept8E29_;
			if (trigResults->error() ) nErrors8E29_++;
		}
		else
		{
			cout << "   HLT8E29 results not found!" << endl;;
			nErrors8E29_++;
			return;
		}

		// decision for each HLT8E29 algorithm
		const unsigned int n(hltNames8E29_.size());
		std::vector<Bool_t> hltDecision(n, false);
		for (unsigned int i=0; i!=n; ++i)
		{
			if (trigResults->wasrun(i)) hltWasRun8E29_[i]++;
			if (trigResults->error(i) ) hltErrors8E29_[i]++;
			if (trigResults->accept(i))
			{
				hltAccept8E29_[i]++;
				hltDecision[i]=true;
			}
		}
	
		rootEvent->setTrigHLT8E29(hltDecision);
	
	}
	
	return;
}


void HLTAnalyzer::printStats()
{
	// final printout of accumulated statistics
	
	if(doHLT_)
	{
		const unsigned int n(hltNames_.size());

		cout << dec << endl;
		cout << "HLT Summary" << endl;
		cout << "HLTAnalyzer-Summary " << "---------- Event  Summary ------------\n";
		cout << "HLTAnalyzer-Summary"
			<< " Events total = " << nEvents_
			<< " wasrun = " << nWasRun_
			<< " passed = " << nAccept_
			<< " errors = " << nErrors_
			<< "\n";

		cout << endl;
		cout << "HLTAnalyzer-Summary " << "---------- HLTrig Summary ------------\n";
		cout << "HLTAnalyzer-Summary "
			<< right << setw(10) << "HLT  Bit#" << " "
			<< right << setw(10) << "WasRun" << " "
			<< right << setw(10) << "Passed" << " "
			<< right << setw(10) << "Errors" << " "
			<< "Name" << "\n";

		for (unsigned int i=0; i!=n; ++i)
		{
			cout << "HLTAnalyzer-Summary "
				<< right << setw(10) << i << " "
				<< right << setw(10) << hltWasRun_[i] << " "
				<< right << setw(10) << hltAccept_[i] << " "
				<< right << setw(10) << hltErrors_[i] << " "
				<< hltNames_[i] << "\n";
		}

		cout << endl;
		cout << "HLT Summary end!" << endl;
		cout << endl;
	}

	if(doHLT8E29_)
	{
		const unsigned int n(hltNames8E29_.size());

		cout << dec << endl;
		cout << "HLT8E29 Summary" << endl;
		cout << "HLTAnalyzer-Summary " << "---------- Event  Summary ------------\n";
		cout << "HLTAnalyzer-Summary"
			<< " Events total = " << nEvents_
			<< " wasrun = " << nWasRun8E29_
			<< " passed = " << nAccept8E29_
			<< " errors = " << nErrors8E29_
			<< "\n";

		cout << endl;
		cout << "HLTAnalyzer-Summary " << "---------- HLTrig Summary ------------\n";
		cout << "HLTAnalyzer-Summary "
			<< right << setw(10) << "HLT  Bit#" << " "
			<< right << setw(10) << "WasRun" << " "
			<< right << setw(10) << "Passed" << " "
			<< right << setw(10) << "Errors" << " "
			<< "Name" << "\n";

		for (unsigned int i=0; i!=n; ++i)
		{
			cout << "HLTAnalyzer-Summary "
				<< right << setw(10) << i << " "
				<< right << setw(10) << hltWasRun8E29_[i] << " "
				<< right << setw(10) << hltAccept8E29_[i] << " "
				<< right << setw(10) << hltErrors8E29_[i] << " "
				<< hltNames8E29_[i] << "\n";
		}

		cout << endl;
		cout << "HLT8E29 Summary end!" << endl;
		cout << endl;
	}

	return;
}

void HLTAnalyzer::copySummary(TRootRun* runInfos)
{
	if(doHLT_)
	{
		runInfos->setNHLTEvents(nEvents_);
		runInfos->setNHLTWasRun(nWasRun_);
		runInfos->setNHLTAccept(nAccept_);
		runInfos->setNHLTErrors(nErrors_);

		runInfos->setHLTWasRun(hltWasRun_);
		runInfos->setHLTAccept(hltAccept_);
		runInfos->setHLTErrors(hltErrors_);
		runInfos->setHLTNames(hltNames_);
		
		runInfos->setHLTInputTag(triggerResultsTag_.label()+"_"+triggerResultsTag_.instance()+"_"+triggerResultsTag_.process());
		cout << triggerResultsTag_.label()+"_"+triggerResultsTag_.instance()+"_"+triggerResultsTag_.process() << endl;
	}

	if(doHLT8E29_)
	{
		runInfos->setNHLT8E29Events(nEvents_);
		runInfos->setNHLT8E29WasRun(nWasRun8E29_);
		runInfos->setNHLT8E29Accept(nAccept8E29_);
		runInfos->setNHLT8E29Errors(nErrors8E29_);

		runInfos->setHLT8E29WasRun(hltWasRun8E29_);
		runInfos->setHLT8E29Accept(hltAccept8E29_);
		runInfos->setHLT8E29Errors(hltErrors8E29_);
		runInfos->setHLT8E29Names(hltNames8E29_);

		runInfos->setHLT8E29InputTag(triggerResultsTag8E29_.label()+"_"+triggerResultsTag8E29_.instance()+"_"+triggerResultsTag8E29_.process());
		cout << triggerResultsTag8E29_.label()+"_"+triggerResultsTag8E29_.instance()+"_"+triggerResultsTag8E29_.process() << endl;
	}
}
