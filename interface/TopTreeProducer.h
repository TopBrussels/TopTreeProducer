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

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h" 

#include "../interface/HLTAnalyzer.h"
#include "../interface/MCAnalyzer.h"
#include "../interface/MCAssociator.h"
#include "../interface/VertexAnalyzer.h"
#include "../interface/JetAnalyzer.h"
#include "../interface/JPTJetAnalyzer.h"
#include "../interface/CaloJetAnalyzer.h"
#include "../interface/GenJetAnalyzer.h"
#include "../interface/PFJetAnalyzer.h"
#include "../interface/MuonAnalyzer.h"
#include "../interface/ElectronAnalyzer.h"
#include "../interface/METAnalyzer.h"
#include "../interface/CaloMETAnalyzer.h"
#include "../interface/PFMETAnalyzer.h"
#include "../interface/TCMETAnalyzer.h"
#include "../interface/GenEventAnalyzer.h"
#include "../interface/NPGenEventAnalyzer.h"
#include "../interface/SpinCorrGenAnalyzer.h"

#include "../interface/TRootRun.h"
#include "../interface/TRootEvent.h"
#include "../interface/TRootParticle.h"
#include "../interface/TRootMCParticle.h"
#include "../interface/TRootJet.h"
#include "../interface/TRootCaloJet.h"
#include "../interface/TRootGenJet.h"
#include "../interface/TRootPFJet.h"
#include "../interface/TRootMuon.h"
#include "../interface/TRootElectron.h"
#include "../interface/TRootMET.h"
#include "../interface/TRootCaloMET.h"
#include "../interface/TRootPFMET.h"
#include "../interface/TRootGenEvent.h"
#include "../interface/TRootNPGenEvent.h"
#include "../interface/TRootSpinCorrGen.h"
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
	bool doHLT;
	bool doMC;
	bool doPDFInfo;
	bool doSignalMuMuGamma;
	bool doSignalTopTop;
	bool doPrimaryVertex;
	bool runGeneralTracks;
	bool doCaloJet;
	bool doGenJet;
	bool doPFJet;
	bool doJPTJet;
	bool doMuon;
	bool doElectron;
	bool doCaloMET;
	bool doPFMET;
	bool doTCMET;
	bool doGenEvent;
	bool doNPGenEvent;
	bool doSpinCorrGen;
	bool drawMCTree;
	std::vector<std::string> vGenJetProducer;
	std::vector<std::string> vCaloJetProducer;
	std::vector<std::string> vPFJetProducer;
	std::vector<std::string> vJPTJetProducer;
	std::vector<std::string> vMuonProducer;
	std::vector<std::string> vElectronProducer;
	int nTotEvt_;
	HLTAnalyzer* hltAnalyzer_;
	TRootRun* runInfos_;
	TRootEvent* rootEvent;
	TClonesArray* mcParticles;
	TClonesArray* tracks;
	std::vector<TClonesArray*> vcaloJets;
	std::vector<TClonesArray*> vgenJets;
	std::vector<TClonesArray*> vpfJets;
	std::vector<TClonesArray*> vjptJets;
	std::vector<TClonesArray*> vmuons;
	std::vector<TClonesArray*> velectrons;
	TClonesArray* CALOmet;
	TClonesArray* PFmet;
	TClonesArray* TCmet;
	TClonesArray* genEvent;
	TClonesArray* NPgenEvent;
	TClonesArray* spinCorrGen;
	TClonesArray* primaryVertex;

};

#endif
