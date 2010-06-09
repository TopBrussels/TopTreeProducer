#include "../interface/HLTAnalyzer.h"

using namespace std;
using namespace TopTree;

int getIndexForRun ( const edm::Event& iEvent, vector<TopTree::TRootHLTInfo> infos ) {
  
  for (unsigned int i=0; i<infos.size(); i++) {

    TopTree::TRootHLTInfo hltInfo_ = infos[i];

    if ( iEvent.id().run() == hltInfo_.RunID() )
    
      return i;

  }

  return -1;

}

void HLTAnalyzer::init(const edm::Event& iEvent, TRootEvent* rootEvent)
{
       
  // check if we need to process HLT8E29

   edm::Handle<edm::TriggerResults> trigResults;
   try {iEvent.getByLabel(triggerResultsTag8E29_,trigResults);} catch (...) {;}
   if (!trigResults.isValid())
     doHLT8E29_=false;
   else
     doHLT8E29_=true;     
}

void HLTAnalyzer::process(const edm::Event& iEvent, TRootEvent* rootEvent)
{
	nEvents_++;
	
	if(doHLT_)
	{
	  
	  int index = getIndexForRun(iEvent,hltInfos_);
	  
	  if ( index == -1 || index < (int)hltInfos_.size()-1 ) {// no info for this run yet -> create a new entry
	    
	    edm::Handle<edm::TriggerResults> trigResults, trigResults1st, trigResults2nd;
	    try {iEvent.getByLabel(triggerResultsTag1st_,trigResults1st);} catch (...) {;}
	    try {iEvent.getByLabel(triggerResultsTag2nd_,trigResults2nd);} catch (...) {;}
	    if(trigResults1st.isValid())
	      {
		trigResults = trigResults1st;
		triggerResultsTag_ = triggerResultsTag1st_;
	      }
	    else if(trigResults2nd.isValid())
	      {
		trigResults = trigResults2nd;
		triggerResultsTag_ = triggerResultsTag2nd_;
	      }
	    else
	    {
	      trigResults = trigResults1st;
	      triggerResultsTag_ = triggerResultsTag1st_;
	    }
	    
	    //cout << "triggerResultsTag_: " << triggerResultsTag_ << endl;
	    
	    triggerNames_=iEvent.triggerNames(*trigResults);
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
	    
	    if (index == -1) {
	      hltInfos_.push_back(TopTree::TRootHLTInfo(iEvent.id().run(),hltNames_,hltWasRun_,hltAccept_,hltErrors_));
	      index = getIndexForRun(iEvent,hltInfos_); // reload the index number
	    }

	  }

//	  cout << "hltInfos.size(): " << hltInfos_.size() << endl; 
	
//	  if (hltInfos_.size() > 0 && index != -1)
//	    cout << "hltNames.size(): " << hltInfos_[index].nHLTPaths() << endl;

//	  cout << "Index: " << index << endl;

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
	    {                                                                                                           	      if (trigResults->wasrun(i)) hltInfos_[index].sethltWasRun(i);
	      if (trigResults->error(i) ) hltInfos_[index].sethltErrors(i);
	      if (trigResults->accept(i))
		{
		  hltInfos_[index].sethltAccept(i);
		  hltDecision[i]=true;
		}
	    }
	  
//	  cout << "hltDecision.size(): " << hltDecision.size() << endl;
	  rootEvent->setTrigHLT(hltDecision);
	  
	}

	if(doHLT8E29_)
	{

	  //cout << "hltInfos8E29.size(): " << hltInfos8E29_.size() << endl; 
	
	  //if (hltInfos8E29_.size() > 0)
	  //  cout << "hltNames8E29.size(): " << hltInfos8E29_[hltInfos8E29_.size()-1].nHLTPaths() << endl;

	  int index = getIndexForRun(iEvent,hltInfos8E29_);
	  
	  if ( index == -1 ) {// no info for this run yet -> create a new entry

	    edm::Handle<edm::TriggerResults> trigResults;
	    try {iEvent.getByLabel(triggerResultsTag8E29_,trigResults);} catch (...) {;}
	    if(trigResults.isValid())
	      {
		triggerNames8E29_=iEvent.triggerNames(*trigResults);
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
		
		hltInfos8E29_.push_back(TopTree::TRootHLTInfo(iEvent.id().run(),hltNames8E29_,hltWasRun8E29_,hltAccept8E29_,hltErrors8E29_));	
		index = getIndexForRun(iEvent,hltInfos8E29_); // reload the index number
	      }
	    else doHLT8E29_ = false;

	  }

	  //cout << "Index: " << index << endl;

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
	      if (trigResults->wasrun(i)) hltInfos8E29_[index].sethltWasRun(i);
	      if (trigResults->error(i) ) hltInfos8E29_[index].sethltErrors(i);
	      if (trigResults->accept(i))
		{
		  hltInfos8E29_[index].sethltAccept(i);
		  hltDecision[i]=true;
		}
	    }
	  
	  //cout << "hltDecision.size(): " << hltDecision.size() << endl;
	  rootEvent->setTrigHLT8E29(hltDecision);
	  
	  
	}
	
	return;
}


void HLTAnalyzer::printStats()
{
	// final printout of accumulated statistics
	
	if(doHLT_)
	{

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
	  
	  for (unsigned int i = 0; i<hltInfos_.size(); i++) {
	    
	    TopTree::TRootHLTInfo hltInfo = hltInfos_[i];
	    
	    const unsigned int n(hltInfo.nHLTPaths());
	    
	    for (unsigned int j=0; j!=n; ++j)
	      {
		stringstream s;
		s << hltInfo.RunID();
		cout << "HLTAnalyzer-Summary-RUN "+s.str()
		     << right << setw(10) << j << " "
		     << right << setw(10) << hltInfo.hltWasRun(j) << " "
		     << right << setw(10) << hltInfo.hltAccept(j) << " "
		     << right << setw(10) << hltInfo.hltErrors(j) << " "
		     << hltInfo.hltNames(j) << "\n";
	      }
	  }
	  
	  cout << endl;
	  cout << "HLT Summary end!" << endl;
	  cout << endl;
	}
	
	if(doHLT8E29_) {
	  
	  cout << dec << endl;
	  cout << "HLT8E29 Summary" << endl;
	  cout << "HLT8E29Analyzer-Summary " << "---------- Event  Summary ------------\n";
	  cout << "HLT8E29Analyzer-Summary"
	       << " Events total = " << nEvents_
	       << " wasrun = " << nWasRun_
	       << " passed = " << nAccept_
	       << " errors = " << nErrors_
	       << "\n";
	  
	  cout << endl;
	  cout << "HLT8E29Analyzer-Summary " << "---------- HLTrig Summary ------------\n";
	  cout << "HLT8E29Analyzer-Summary "
	       << right << setw(10) << "HLT  Bit#" << " "
	       << right << setw(10) << "WasRun" << " "
	       << right << setw(10) << "Passed" << " "
	       << right << setw(10) << "Errors" << " "
	       << "Name" << "\n";
	  
	  for (unsigned int i = 0; i<hltInfos8E29_.size(); i++) {
	    
	    TopTree::TRootHLTInfo hltInfo = hltInfos8E29_[i];
	    
	    const unsigned int n(hltInfo.nHLTPaths());
	    
	    for (unsigned int j=0; j!=n; ++j)
	      {
		stringstream s;
		s << hltInfo.RunID();
		cout << "HLT8E29Analyzer-Summary-RUN "+s.str()
		     << right << setw(10) << j << " "
		     << right << setw(10) << hltInfo.hltWasRun(j) << " "
		     << right << setw(10) << hltInfo.hltAccept(j) << " "
		     << right << setw(10) << hltInfo.hltErrors(j) << " "
		     << hltInfo.hltNames(j) << "\n";
	      }
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
	  
	  runInfos->setHLTInputTag(triggerResultsTag_.label()+"_"+triggerResultsTag_.instance()+"_"+triggerResultsTag_.process());
	  cout << triggerResultsTag_.label()+"_"+triggerResultsTag_.instance()+"_"+triggerResultsTag_.process() << endl;
	  
	  // set new hlt container
	  
	  runInfos->setHLTinfos(hltInfos_);
	}

	if(doHLT8E29_)
	{
	  
	  runInfos->setNHLT8E29Events(nEvents_);
	  runInfos->setNHLT8E29WasRun(nWasRun8E29_);
	  runInfos->setNHLT8E29Accept(nAccept8E29_);
	  runInfos->setNHLT8E29Errors(nErrors8E29_);
	  
	  runInfos->setHLT8E29InputTag(triggerResultsTag8E29_.label()+"_"+triggerResultsTag8E29_.instance()+"_"+triggerResultsTag8E29_.process());
	  cout << triggerResultsTag8E29_.label()+"_"+triggerResultsTag8E29_.instance()+"_"+triggerResultsTag8E29_.process() << endl;
		
	  // set new hlt container
	  runInfos->setHLTinfos8E29(hltInfos8E29_);
	}
}
