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
			nHLT8E29Events_(0)
			,nHLT8E29WasRun_(0)
			,nHLT8E29Accept_(0)
			,nHLT8E29Errors_(0)
			,nHLTEvents_(0)
			,nHLTWasRun_(0)
			,nHLTAccept_(0)
			,nHLTErrors_(0)
			,hlt8E29InputTag_("")
			,hltInputTag_("")
			{;}
	
		~TRootRun() {;}
		
		UInt_t  nHLT8E29Events() const { return nHLT8E29Events_; }
		UInt_t  nHLT8E29WasRun() const { return nHLT8E29WasRun_; }
		UInt_t  nHLT8E29Accept() const { return nHLT8E29Accept_; }
		UInt_t  nHLT8E29Errors() const { return nHLT8E29Errors_; }
		UInt_t  nHLTEvents() const { return nHLTEvents_; }
		UInt_t  nHLTWasRun() const { return nHLTWasRun_; }
		UInt_t  nHLTAccept() const { return nHLTAccept_; }
		UInt_t  nHLTErrors() const { return nHLTErrors_; }

		std::string hlt8E29InputTag() const { return hlt8E29InputTag_; }
		std::string hltInputTag() const { return hltInputTag_; }

		void setHLT8E29InputTag(std::string hlt8E29InputTag) { hlt8E29InputTag_ = hlt8E29InputTag; }
		void setHLTInputTag(std::string hltInputTag) { hltInputTag_ = hltInputTag; }

		void setNHLT8E29Events(UInt_t nHLT8E29Events) { nHLT8E29Events_=nHLT8E29Events; }
		void setNHLT8E29WasRun(UInt_t nHLT8E29WasRun) { nHLT8E29WasRun_=nHLT8E29WasRun; }
		void setNHLT8E29Accept(UInt_t nHLT8E29Accept) { nHLT8E29Accept_=nHLT8E29Accept; }
		void setNHLT8E29Errors(UInt_t nHLT8E29Errors) { nHLT8E29Errors_=nHLT8E29Errors; }
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

		void setHLTinfos8E29(vector<TopTree::TRootHLTInfo> hltInfos) { hltInfos8E29_ = hltInfos; }

		TopTree::TRootHLTInfo getHLTinfo8E29(UInt_t RunID) { 

		  for (UInt_t i=0; i<hltInfos8E29_.size(); i++) 

		    if (hltInfos8E29_[i].RunID() == RunID)

		      return hltInfos8E29_[i];
		  
		  return TopTree::TRootHLTInfo();

		}

		vector<TopTree::TRootHLTInfo> copyHLTinfos8E29() const { return hltInfos8E29_; }; // for the skimmer

	private:

		// new HLT method
		vector<TopTree::TRootHLTInfo> hltInfos_;
		vector<TopTree::TRootHLTInfo> hltInfos8E29_;

		UInt_t nHLT8E29Events_;		// Nb of events
		UInt_t nHLT8E29WasRun_;		// Nb of events where at least one HLT was run
		UInt_t nHLT8E29Accept_;		// Nb of accepted events
		UInt_t nHLT8E29Errors_;		// Nb of events where at least one HLT had error
		UInt_t nHLTEvents_;			// Nb of events
		UInt_t nHLTWasRun_;			// Nb of events where at least one HLT was run
		UInt_t nHLTAccept_;			// Nb of accepted events
		UInt_t nHLTErrors_;			// Nb of events where at least one HLT had error

		std::string hlt8E29InputTag_;						// name of the 8E29HLT inputtag provided in the TopTreeProducer config
		std::string hltInputTag_;							// name of the HLT inputtag provided in the TopTreeProducer config

		ClassDef (TRootRun,1);
	};
}

#endif
