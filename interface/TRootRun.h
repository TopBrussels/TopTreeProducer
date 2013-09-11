#ifndef TRootRun_h
#define TRootRun_h

#include <string>
#include <iostream>
#include <vector>

#include "Rtypes.h"
#include "TObject.h"
#include "TVector3.h"
#include "TRootHLTInfo.h"

using namespace std;

namespace TopTree
{

	class TRootRun : public TObject
	{

	public:
		TRootRun() :
			nHLTEvents_(0)
			,nHLTWasRun_(0)
			,nHLTAccept_(0)
			,nHLTErrors_(0)
			,hltInputTag_("")
			{;}
	
		~TRootRun() {;}
		
		UInt_t  nHLTEvents() const { return nHLTEvents_; }
		UInt_t  nHLTWasRun() const { return nHLTWasRun_; }
		UInt_t  nHLTAccept() const { return nHLTAccept_; }
		UInt_t  nHLTErrors() const { return nHLTErrors_; }

		std::string hltInputTag() const { return hltInputTag_; }

		void setHLTInputTag(std::string hltInputTag) { hltInputTag_ = hltInputTag; }

		void setNHLTEvents(UInt_t nHLTEvents) { nHLTEvents_=nHLTEvents; }
		void setNHLTWasRun(UInt_t nHLTWasRun) { nHLTWasRun_=nHLTWasRun; }
		void setNHLTAccept(UInt_t nHLTAccept) { nHLTAccept_=nHLTAccept; }
		void setNHLTErrors(UInt_t nHLTErrors) { nHLTErrors_=nHLTErrors; }

		// new hlt methods

		void setHLTinfos(vector<TopTree::TRootHLTInfo> hltInfos) { hltInfos_ = hltInfos; }

		TopTree::TRootHLTInfo getHLTinfo(UInt_t RunID) { 

		  for (UInt_t i=0; i<hltInfos_.size(); i++) 

		    if (hltInfos_[i].RunID() == RunID)

		      return hltInfos_[i];
		  
		  return TopTree::TRootHLTInfo();

		}

		vector<TopTree::TRootHLTInfo> copyHLTinfos() const { return hltInfos_; }; // for the skimmer

	private:

		// new HLT method
		vector<TopTree::TRootHLTInfo> hltInfos_;

		UInt_t nHLTEvents_;			// Nb of events
		UInt_t nHLTWasRun_;			// Nb of events where at least one HLT was run
		UInt_t nHLTAccept_;			// Nb of accepted events
		UInt_t nHLTErrors_;			// Nb of events where at least one HLT had error

		std::string hltInputTag_;							// name of the HLT inputtag provided in the TopTreeProducer config

		ClassDef (TRootRun,1);
	};
}

#endif
