#include "DataFormats/Common/interface/Wrapper.h"
#include "TopBrussels/TopTreeProducer/interface/TRootRun.h"
#include "TopBrussels/TopTreeProducer/interface/TRootEvent.h"
#include "TopBrussels/TopTreeProducer/interface/TRootVertex.h"
#include "TopBrussels/TopTreeProducer/interface/TRootParticle.h"
#include "TopBrussels/TopTreeProducer/interface/TRootLepton.h"
#include "TopBrussels/TopTreeProducer/interface/TRootMuon.h"
#include "TopBrussels/TopTreeProducer/interface/TRootElectron.h"
#include "TopBrussels/TopTreeProducer/interface/TRootPhoton.h"
#include "TopBrussels/TopTreeProducer/interface/TRootJet.h"
#include "TopBrussels/TopTreeProducer/interface/TRootPFJet.h"
#include "TopBrussels/TopTreeProducer/interface/TRootJPTJet.h"
#include "TopBrussels/TopTreeProducer/interface/TRootCaloJet.h"
#include "TopBrussels/TopTreeProducer/interface/TRootMET.h"
#include "TopBrussels/TopTreeProducer/interface/TRootPFMET.h"
#include "TopBrussels/TopTreeProducer/interface/TRootTrackMET.h"
#include "TopBrussels/TopTreeProducer/interface/TRootCaloMET.h"
#include "TopBrussels/TopTreeProducer/interface/TRootGenEvent.h"
#include "TopBrussels/TopTreeProducer/interface/TRootNPGenEvent.h"
#include "TopBrussels/TopTreeProducer/interface/TRootMCParticle.h"
#include "TopBrussels/TopTreeProducer/interface/TRootGenJet.h"
#include "TopBrussels/TopTreeProducer/interface/TRootGenTop.h"
#include "TopBrussels/TopTreeProducer/interface/TRootSpinCorrGen.h"
#include "TopBrussels/TopTreeProducer/interface/TRootHLTInfo.h"

#include <vector>
#include <map>

namespace {
  struct dictionary {

    TopTree::TRootRun TRootRun_;
    std::vector<TopTree::TRootRun> vTRootRun_;
 
    TopTree::TRootEvent TRootEvent_;
    std::vector<TopTree::TRootEvent> vTRootEvent_;

    TopTree::triggeredObject triggeredObject_;
    std::vector<TopTree::triggeredObject> vtriggeredObject_;

    std::map<std::string,std::vector<TopTree::triggeredObject> > map_;
 
    TopTree::TRootVertex TRootVertex_;
    std::vector<TopTree::TRootVertex> vTRootVertex_;

    TopTree::TRootParticle TRootParticle_;
    std::vector<TopTree::TRootParticle> vTRootParticle_;
 
    TopTree::TRootLepton TRootLepton_;
    std::vector<TopTree::TRootLepton> vTRootLepton_;
 
    TopTree::TRootMuon TRootMuon_;
    std::vector<TopTree::TRootMuon> vTRootMuon_;

    TopTree::TRootElectron TRootElectron_;
    std::vector<TopTree::TRootElectron> vTRootElectron_;

    TopTree::TRootPhoton TRootPhoton_;
    std::vector<TopTree::TRootPhoton> vTRootPhoton_;

    TopTree::TRootJet TRootJet_;
    std::vector<TopTree::TRootJet> vTRootJet_;

    TopTree::TRootPFJet TRootPFJet_;
    std::vector<TopTree::TRootPFJet> vTRootPFJet_;

    TopTree::TRootJPTJet TRootJPTJet_;
    std::vector<TopTree::TRootJPTJet> vTRootJPTJet_;
 
    TopTree::TRootCaloJet TRootCaloJet_;
    std::vector<TopTree::TRootCaloJet> vTRootCaloJet_;

    TopTree::TRootMET TRootMET_;
    std::vector<TopTree::TRootMET> vTRootMET_;

    TopTree::TRootPFMET TRootPFMET_;
    std::vector<TopTree::TRootPFMET> vTRootPFMET_;

    TopTree::TRootTrackMET TRootTrackMET_;
    std::vector<TopTree::TRootTrackMET> vTRootTrackMET_;

    TopTree::TRootCaloMET TRootCaloMET_;
    std::vector<TopTree::TRootCaloMET> vTRootCaloMET_;

    TopTree::TRootGenEvent TRootGenEvent_;
    std::vector<TopTree::TRootGenEvent> vTRootGenEvent_;

    TopTree::TRootNPGenEvent TRootNPGenEvent_;
    std::vector<TopTree::TRootNPGenEvent> vTRootNPGenEvent_;
  
    TopTree::TRootMCParticle TRootMCParticle_;
    std::vector<TopTree::TRootMCParticle> vTRootMCParticle_;

    TopTree::TRootGenJet TRootGenJet_;
    std::vector<TopTree::TRootGenJet> vTRootGenJet_;

    TopTree::TRootGenTop TRootGenTop_;
    std::vector<TopTree::TRootGenTop> vTRootGenTop_;

    TopTree::TRootSpinCorrGen TRootSpinCorrGen_;
    std::vector<TopTree::TRootSpinCorrGen> vTRootSpinCorrGen_;
   
    TopTree::TRootHLTInfo TRootHLTInfo_;
    std::vector<TopTree::TRootHLTInfo> vTRootHLTInfo_;

  };

}
