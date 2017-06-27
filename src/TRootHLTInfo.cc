#include "../interface/TRootHLTInfo.h"
using namespace TopTree;

TRootHLTInfo::TRootHLTInfo() :
RunID_(0)
,hltNames_()
,hltWasRun_()
,hltErrors_()
,hltAccept_()
{

}

TRootHLTInfo::TRootHLTInfo(UInt_t RunID, vector<std::string> hltNames,  vector<UInt_t> hltWasRun, vector<UInt_t> hltErrors, vector<UInt_t> hltAccept) :
    RunID_(RunID)
    ,hltNames_(hltNames)
    ,hltWasRun_(hltWasRun)
    ,hltErrors_(hltErrors)
    ,hltAccept_(hltAccept)
{

}

UInt_t TRootHLTInfo::hltPath(std::string hltName)
{
    // wildcards at the end of trigger string currently only supported
    size_t wildcardPos = hltName.find("*");
    if (wildcardPos != string::npos)  //if using wildcards
    { 
        //if there is a char after * exit saying it only supports wildcards at end of HLT name with v*
        assert(wildcardPos == hltName.size()-1 && hltName.at(wildcardPos-1) == 'v');

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

void TRootHLTInfo::gethltNameList()
{
    cout<<"Size of hltNames list = "<<hltNames_.size()<<endl; 
    cout<<"*******************************************"<<endl;
    for (UInt_t ipath=0; ipath < hltNames_.size(); ipath++)
    {
        cout << "No. "<<ipath<<" name :"<< hltNames_.at(ipath) << endl;
    }
    cout<<"*******************************************"<<endl;
}

