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

    TRootHLTInfo() :
        RunID_(0)
        ,hltNames_()
        ,hltWasRun_()
        ,hltErrors_()
        ,hltAccept_()
    {
        ;
    }

    TRootHLTInfo(UInt_t RunID, vector<std::string> hltNames,  vector<UInt_t> hltWasRun, vector<UInt_t> hltErrors, vector<UInt_t> hltAccept) :
        RunID_(RunID)
        ,hltNames_(hltNames)
        ,hltWasRun_(hltWasRun)
        ,hltErrors_(hltErrors)
        ,hltAccept_(hltAccept)
    {
        ;
    }

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

    UInt_t hltPath(std::string hltName)
    {
        // wildcards at the end of trigger string currently only supported
        size_t wildcardPos = hltName.find("*");
        if (wildcardPos != string::npos)  //if using wildcards
        { 
            //if there is a char after * exit saying it only supports wildcards at end of HLT name with v*
            cout<<"Checking trigger string 2"<<endl;
            cout<<"-1 at:"<<hltName.at(wildcardPos-1)<<endl;
            cout<<"wildcard pos: "<<wildcardPos<<"  hltname size: "<<hltName.size()<<endl;
            assert(wildcardPos != hltName.size() || hltName.at(wildcardPos-1) != 'v');

            // cout<<"using wildcards!!!"<<endl;
            string subHLTname = hltName.substr(0,wildcardPos);        
            for (UInt_t ipath=0; ipath < hltNames_.size(); ipath++)
            {
                if (hltNames_.at(ipath).find(subHLTname) != string::npos){
                    return ipath;
                }
            }   
            return 9999;
        }

        else
        {
            for (UInt_t ipath=0; ipath < hltNames_.size(); ipath++)
            {
                // cout << hltNames_.at(ipath)<< " <-> " <<  hltName << endl;
                if (hltNames_.at(ipath) == hltName)
                {
                    return ipath;
                }
            }
            return 9999;
        }
    }    

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

    void gethltNameList()
    {
        cout<<"Size of hltNames list = "<<hltNames_.size()<<endl; 
        cout<<"*******************************************"<<endl;
        for (UInt_t ipath=0; ipath < hltNames_.size(); ipath++)
        {
            cout << "No. "<<ipath<<" name :"<< hltNames_.at(ipath) << endl;
        }
        cout<<"*******************************************"<<endl;
    };

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
