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

HLTAnalyzer::HLTAnalyzer(edm::EDGetTokenT<edm::TriggerResults> triggerToken1, edm::EDGetTokenT<edm::TriggerResults> triggerToken2,edm::EDGetTokenT<edm::TriggerResults> triggerToken3, edm::EDGetTokenT<edm::TriggerResults> triggerToken4, edm::EDGetTokenT<edm::TriggerResults> triggerToken5, const edm::ParameterSet& myConfig, int verbosity) :
		verbosity_(verbosity)
  		,triggerNames_()
		,doHLT_(myConfig.getUntrackedParameter<bool>("doHLT",false))
  		,nEvents_(0)
  		,nWasRun_(0)
  		,nAccept_(0)
  		,nErrors_(0)
  		,hltWasRun_(0)
  		,hltAccept_(0)
  		,hltErrors_(0)
  		,hltNames_(0)
		{
		triggerResultsToken1st_=triggerToken1;
		triggerResultsToken2nd_=triggerToken2;
		triggerResultsToken3rd_=triggerToken3;
		triggerResultsToken4th_=triggerToken4;
		triggerResultsToken5th_=triggerToken5;
		}

void HLTAnalyzer::process(const edm::Event& iEvent, TRootEvent* rootEvent, edm::ParameterSet valuesForConsumeCommand)
{
	nEvents_++;

	if(doHLT_)
	{

	  int index = getIndexForRun(iEvent,hltInfos_);

//		cout << "index " << index << " and hltInfos_ " << hltInfos_.size() << endl;


	  if ( index == -1 || index < (int)hltInfos_.size()-1 ) {// no info for this run yet -> create a new entry

	    edm::Handle<edm::TriggerResults> trigResults, trigResults1st, trigResults2nd, trigResults3rd, trigResults4th, trigResults5th;
	    try {iEvent.getByToken(triggerResultsToken1st_,trigResults1st);} catch (...) {;}
	    try {iEvent.getByToken(triggerResultsToken2nd_,trigResults2nd);} catch (...) {;}
	    try {iEvent.getByToken(triggerResultsToken3rd_,trigResults3rd);} catch (...) {;}
	    try {iEvent.getByToken(triggerResultsToken4th_,trigResults4th);} catch (...) {;}
	    try {iEvent.getByToken(triggerResultsToken5th_,trigResults5th);} catch (...) {;}
	    if(trigResults1st.isValid())
	      {
				trigResults = trigResults1st;
				triggerResultsToken_ = triggerResultsToken1st_;
				triggerResultsTag_ = valuesForConsumeCommand.getParameter<edm::InputTag>("hltProducer1st");
	      }
	    else if(trigResults2nd.isValid())
	      {
				trigResults = trigResults2nd;
				triggerResultsToken_ = triggerResultsToken2nd_;
				triggerResultsTag_ = valuesForConsumeCommand.getParameter<edm::InputTag>("hltProducer2nd");
	      }
	    else if(trigResults3rd.isValid())
	      {
				trigResults = trigResults3rd;
				triggerResultsToken_ = triggerResultsToken3rd_;
				triggerResultsTag_ = valuesForConsumeCommand.getParameter<edm::InputTag>("hltProducer3rd");
	      }
	    else if(trigResults4th.isValid())
	    {
	      trigResults = trigResults4th;
	      triggerResultsToken_ = triggerResultsToken4th_;
		    triggerResultsTag_ = valuesForConsumeCommand.getParameter<edm::InputTag>("hltProducer4th");
			}
	    else if(trigResults5th.isValid())
	    {
	      trigResults = trigResults5th;
	      triggerResultsToken_ = triggerResultsToken5th_;
		    triggerResultsTag_ = valuesForConsumeCommand.getParameter<edm::InputTag>("hltProducer5th");
			}

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

	  edm::Handle<edm::TriggerResults> trigResults;
	  try {iEvent.getByToken(triggerResultsToken_,trigResults);} catch (...) {;}
	  if (trigResults.isValid()) {
	    if (trigResults->wasrun()) nWasRun_++;
	    const bool accept(trigResults->accept());
	    if(verbosity_>1) cout << "   HLT decision: " << accept << endl;
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
    edm::TriggerNames triggerNames_test=iEvent.triggerNames(*trigResults);
    std::vector<std::string> hltNames_test=triggerNames_test.triggerNames();
	  unsigned int n(hltNames_.size());
    if(n != hltNames_test.size())
    {
        cout << " BUG found in HLTAnalyzer. HLTNames.size() is different for this run"  << endl;
        cout << "                                            Applying brute-force fix..."  << endl;
        n = hltNames_test.size();
    }
	  std::vector<Bool_t> hltDecision(n, false);
	  for (unsigned int i=0; i!=n; ++i)
	    {
			  if (trigResults->wasrun(i)) hltInfos_[index].sethltWasRun(i);
	      if (trigResults->error(i) ) hltInfos_[index].sethltErrors(i);
	      if (trigResults->accept(i))
					{
		  			hltInfos_[index].sethltAccept(i);
		  			hltDecision[i]=true;
					}
	    }

	  //cout << "hltDecision.size(): " << hltDecision.size() << endl;
	  rootEvent->setTrigHLT(hltDecision);

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

}

