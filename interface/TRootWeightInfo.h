#ifndef TRootWeightInfo_h
#define TRootWeightInfo_h

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Rtypes.h"
#include "TObject.h"
#include "TVector3.h"

using namespace std;

namespace TopTree
{

class TRootWeightInfo : public TObject
{

public:

    TRootWeightInfo() :
        RunID_(0)
        ,weights_()
    {
        ;
    }

    TRootWeightInfo(UInt_t RunID, std::map<std::string,int> weights) :
        RunID_(RunID)
        ,weights_(weights)
    {
        ;
    }

    ~TRootWeightInfo()
    {
        ;
    }

    int weightIndex (std::string name) const
    {
        return (weights_.find(name)!=weights_.end() ?  weights_.find(name)->second : -9999 );
    };
    UInt_t RunID() const
    {
        return RunID_;
    };

    void getweightNameList()
    {
        cout<<"Size of weights list = "<<weights_.size()<<endl;
        cout<<"*******************************************"<<endl;
        for (std::map<std::string,int>::iterator iter; iter!=weights_.end(); iter++)
        {
            cout << "Weight Name: "<< iter->first <<" Index :"<< iter->second << endl;
        }
        cout<<"*******************************************"<<endl;
    };

    void setWeightIndex(std::string name, int idx)
    {
        if(weights_.find(name)==weights_.end())
        {
            weights_[name] = idx;
        }
        else
        {
            cout << "Weight " << name << "has already been given an index of " << weights_[name] << endl;
        }
    };

private:
    UInt_t RunID_;
    std::map<std::string,int> weights_;

    ClassDef (TRootWeightInfo,2);

};

}

#endif
