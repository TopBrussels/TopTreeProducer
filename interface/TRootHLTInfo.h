#ifndef TRootHLTInfo_h
#define TRootHLTInfo_h

#include <string>
#include <iostream>
#include <vector>

#include "Rtypes.h"
#include "TObject.h"
#include "TVector3.h"
#include <cassert> // for assert()

using namespace std;

namespace TopTree
{

class TRootHLTInfo : public TObject
{

public:

    TRootHLTInfo();
    TRootHLTInfo(UInt_t RunID, vector<std::string> hltNames,  vector<UInt_t> hltWasRun, vector<UInt_t> hltErrors, vector<UInt_t> hltAccept);

    std::string hltNames (UInt_t trigId) const
    {
        return (hltNames_.size()>trigId ?  hltNames_.at(trigId) : "bad_index" );
    };
    UInt_t hltWasRun (UInt_t trigId) const
    {
        return (hltWasRun_.size()>trigId ?  hltWasRun_.at(trigId) : 0 );
    };
    UInt_t hltAccept (UInt_t trigId) const
    {
        return (hltAccept_.size()>trigId ?  hltAccept_.at(trigId) : 0 );
    };
    UInt_t hltErrors (UInt_t trigId) const
    {
        return (hltErrors_.size()>trigId ?  hltErrors_.at(trigId) : 0 );
    };

    UInt_t RunID() const
    {
        return RunID_;
    };

    UInt_t nHLTPaths() const
    {
        return hltNames_.size();
    };

    UInt_t hltPath(std::string hltName);

    void sethltWasRun (UInt_t trigId)
    {
        hltWasRun_[trigId]++;
    };
    void sethltAccept (UInt_t trigId)
    {
        hltAccept_[trigId]++;
    };
    void sethltErrors (UInt_t trigId)
    {
        hltErrors_[trigId]++;
    };

    void gethltNameList();


private:
    UInt_t RunID_;
    vector<std::string> hltNames_;
    vector<UInt_t> hltWasRun_;
    vector<UInt_t> hltErrors_;
    vector<UInt_t> hltAccept_;

    ClassDef (TRootHLTInfo,2);

};

}

#endif
