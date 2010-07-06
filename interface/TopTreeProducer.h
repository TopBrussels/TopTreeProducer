#ifndef TopTreeProducer_h
#define TopTreeProducer_h

// system include files
#include <memory>
#include <string>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Provenance/interface/EventID.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "RecoEgamma/EgammaTools/interface/ConversionLikelihoodCalculator.h"

#include "../interface/HLTAnalyzer.h"
#include "../interface/MCAnalyzer.h"
#include "../interface/MCAssociator.h"
#include "../interface/VertexAnalyzer.h"
#include "../interface/JetAnalyzer.h"
#include "../interface/CaloJetAnalyzer.h"
#include "../interface/GenJetAnalyzer.h"
#include "../interface/PFJetAnalyzer.h"
#include "../interface/MuonAnalyzer.h"
#include "../interface/CosmicMuonAnalyzer.h"
#include "../interface/ElectronAnalyzer.h"
#include "../interface/METAnalyzer.h"
#include "../interface/MHTAnalyzer.h"
#include "../interface/GenEventAnalyzer.h"
#include "../interface/NPGenEventAnalyzer.h"
#include "../interface/SpinCorrGenAnalyzer.h"
#include "../interface/SemiLepEventAnalyzer.h"

#include "../interface/TRootRun.h"
#include "../interface/TRootEvent.h"
#include "../interface/TRootSignalEvent.h"
#include "../interface/TRootParticle.h"
#include "../interface/TRootMCParticle.h"
#include "../interface/TRootJet.h"
#include "../interface/TRootCaloJet.h"
#include "../interface/TRootGenJet.h"
#include "../interface/TRootPFJet.h"
#include "../interface/TRootMuon.h"
#include "../interface/TRootCosmicMuon.h"
#include "../interface/TRootElectron.h"
#include "../interface/TRootMET.h"
#include "../interface/TRootMHT.h"
#include "../interface/TRootGenEvent.h"
#include "../interface/TRootNPGenEvent.h"
#include "../interface/TRootSpinCorrGen.h"
#include "../interface/TRootSemiLepEvent.h"
#include "../interface/TRootTrack.h"
#include "../interface/TRootVertex.h"

#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"

//using namespace TopTree;

class TopTreeProducer : public edm::EDAnalyzer {
public:
	explicit TopTreeProducer(const edm::ParameterSet&);
	~TopTreeProducer();
	
	
private:
	virtual void beginJob() ;
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void endJob() ;

	edm::ParameterSet myConfig_;
	edm::ParameterSet producersNames_;
	
	int verbosity;
	std::string rootFileName_ ;
	TFile* rootFile_ ;
	TTree* eventTree_;
	TTree* runTree_;
	std::string dataType_ ;
	bool doHLT8E29;
	bool doHLT;
	bool doMC;
	bool doPDFInfo;
	bool doSignalMuMuGamma;
	bool doSignalTopTop;
	bool doPrimaryVertex;
	bool runGeneralTracks;
	bool doCaloJet;
	bool doCaloJetStudy;
	bool doGenJet;
	bool doGenJetStudy;
	bool doPFJet;
	bool doPFJetStudy;
	bool doMuon;
	bool doCosmicMuon;
	bool doElectron;
	bool doMET;
	bool doMHT;
	bool doGenEvent;
	bool doNPGenEvent;
	bool doSpinCorrGen;
	bool doSemiLepEvent;
	bool drawMCTree;
	std::vector<std::string> vGenJetProducer;
	std::vector<std::string> vCaloJetProducer;
	std::vector<std::string> vPFJetProducer;
	std::vector<std::string> vCosmicMuonProducer;
	int nTotEvt_;
	HLTAnalyzer* hltAnalyzer_;
	TRootRun* runInfos_;
	TRootEvent* rootEvent;
	TClonesArray* mcParticles;
	TClonesArray* tracks;
	TClonesArray* caloJets;
	std::vector<TClonesArray*> vcaloJets;
	TClonesArray* genJets;
	std::vector<TClonesArray*> vgenJets;
	TClonesArray* pfJets;
	std::vector<TClonesArray*> vpfJets;
	TClonesArray* muons;
	std::vector<TClonesArray*> vcosmicMuons;
	std::vector<std::vector<TClonesArray*> > vcosmicMuonTracks;
	TClonesArray* electrons;
	TClonesArray* met;
	TClonesArray* mht;
	TClonesArray* genEvent;
	TClonesArray* NPgenEvent;
	TClonesArray* spinCorrGen;
	TClonesArray* semiLepEvent;
	TClonesArray* primaryVertex;

};

#endif
