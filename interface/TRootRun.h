#ifndef TRootRun_h
#define TRootRun_h

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Rtypes.h"
#include "TObject.h"
#include "TVector3.h"
#include "TRootHLTInfo.h"
#include "TRootWeightInfo.h"

using namespace std;

namespace TopTree
{

class TRootRun : public TObject
{

public:
    TRootRun() :
        nHLTEvents_(-9999)
        ,nHLTWasRun_(-9999)
        ,nHLTAccept_(-9999)
        ,nHLTErrors_(-9999)
        ,hltInputTag_("")
    {
        ;
    }

    ~TRootRun()
    {
        ;
    }

    int prePathCounter() const
    {
        return prePathCounter_;
    }
    int postPathCounter() const
    {
        return postPathCounter_;
    }

    UInt_t  nHLTEvents() const
    {
        return nHLTEvents_;
    }
    UInt_t  nHLTWasRun() const
    {
        return nHLTWasRun_;
    }
    UInt_t  nHLTAccept() const
    {
        return nHLTAccept_;
    }
    UInt_t  nHLTErrors() const
    {
        return nHLTErrors_;
    }

    std::string hltInputTag() const
    {
        return hltInputTag_;
    }

    void setPrePathCounter(int nevts)
    {
        prePathCounter_ = nevts;
    }
    void setPostPathCounter(int nevts)
    {
        postPathCounter_ = nevts;
    }

    void setHLTInputTag(std::string hltInputTag)
    {
        hltInputTag_ = hltInputTag;
    }

    void setNHLTEvents(UInt_t nHLTEvents)
    {
        nHLTEvents_=nHLTEvents;
    }
    void setNHLTWasRun(UInt_t nHLTWasRun)
    {
        nHLTWasRun_=nHLTWasRun;
    }
    void setNHLTAccept(UInt_t nHLTAccept)
    {
        nHLTAccept_=nHLTAccept;
    }
    void setNHLTErrors(UInt_t nHLTErrors)
    {
        nHLTErrors_=nHLTErrors;
    }

    // new hlt methods

    void setHLTinfos(vector<TopTree::TRootHLTInfo> hltInfos)
    {
        hltInfos_ = hltInfos;
    }

    TopTree::TRootHLTInfo getHLTinfo(UInt_t RunID)
    {
//        cout << "Number of HLTInfos : " << hltInfos_.size() << endl;
        for (UInt_t i=0; i<hltInfos_.size(); i++)
        {
//            cout << "HLTInfo RunID: " << hltInfos_[i].RunID() << " - RunID passed to function: " << RunID << endl;

            if (hltInfos_[i].RunID() == RunID)
            {
                return hltInfos_[i];
            }
        }

        return TopTree::TRootHLTInfo();

    }

    vector<TopTree::TRootHLTInfo> copyHLTinfos() const
    {
        return hltInfos_;
    }; // for the skimmer

    // Methods for Gen Weights

    void setWeights(std::map<std::string,int> weights_, unsigned int runNumber)
    {
        bool exists = false;
        for (UInt_t i=0; i<weightInfos_.size(); i++)
        {
            if (weightInfos_[i].RunID() == runNumber)
            {
                exists = true;
            }
        }
        if(!exists)
        {
            cout << "Creating new TWeightInfo for run " << runNumber << endl;
            TRootWeightInfo theInfo(runNumber, weights_);
            weightInfos_.push_back(theInfo);
        }
        else
        {
            cout << "Weight Information for run " << runNumber << " already exists." << endl;
        }
    };

    TopTree::TRootWeightInfo getWeightInfo(UInt_t RunID)
    {
        //cout << "Number of HLTInfos : " << hltInfos_.size() << endl;
        for (UInt_t i=0; i<weightInfos_.size(); i++)
        {
            //cout << "HLTInfo RunID: " << hltInfos_[i].RunID() << endl;

            if (weightInfos_[i].RunID() == RunID)
            {
                return weightInfos_[i];
            }
        }

        return TopTree::TRootWeightInfo();

    }

private:

    // new HLT method
    vector<TopTree::TRootHLTInfo> hltInfos_;
    vector<TopTree::TRootWeightInfo> weightInfos_;

    int prePathCounter_;                        // number of events before PAT sequence
    int postPathCounter_;                       // number of events after PAT sequence

    UInt_t nHLTEvents_;			// Nb of events
    UInt_t nHLTWasRun_;			// Nb of events where at least one HLT was run
    UInt_t nHLTAccept_;			// Nb of accepted events
    UInt_t nHLTErrors_;			// Nb of events where at least one HLT had error

    std::string hltInputTag_;							// name of the HLT inputtag provided in the TopTreeProducer config

    ClassDef (TRootRun,2);
};
}

#endif
