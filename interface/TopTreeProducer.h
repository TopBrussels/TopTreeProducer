#ifndef TopTreeProducer_h
#define TopTreeProducer_h

// system include files
#include <memory>
#include <string>
#include <iostream>

// user include files

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "DataFormats/Provenance/interface/EventID.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/MergeableCounter.h"
#include "DataFormats/METReco/interface/HcalNoiseSummary.h"

//Added for GenHFHadronMatcher
#include "SimDataFormats/JetMatching/interface/JetFlavourMatching.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/Jet.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "../interface/HLTAnalyzer.h"
#include "../interface/MCAnalyzer.h"
#include "../interface/VertexAnalyzer.h"
#include "../interface/JetAnalyzer.h"
#include "../interface/GenJetAnalyzer.h"
#include "../interface/PFJetAnalyzer.h"
#include "../interface/FatJetAnalyzer.h"
#include "../interface/MuonAnalyzer.h"
#include "../interface/ElectronAnalyzer.h"
#include "../interface/PhotonAnalyzer.h"
#include "../interface/METAnalyzer.h"
#include "../interface/PFMETAnalyzer.h"
#include "../interface/NPGenEventAnalyzer.h"
#include "../interface/LHEEventProductAnalyzer.h"



#include "../interface/TRootRun.h"
#include "../interface/TRootEvent.h"
#include "../interface/TRootParticle.h"
#include "../interface/TRootMCParticle.h"
#include "../interface/TRootJet.h"
#include "../interface/TRootGenJet.h"
#include "../interface/TRootPFJet.h"
#include "../interface/TRootSubstructureJet.h"
#include "../interface/TRootLepton.h"
#include "../interface/TRootMuon.h"
#include "../interface/TRootElectron.h"
#include "../interface/TRootMET.h"
#include "../interface/TRootPFMET.h"
#include "../interface/TRootNPGenEvent.h"
#include "../interface/TRootVertex.h"
#include "../interface/GenTTXCategorizer.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TClonesArray.h"

//using namespace TopTree;

class TopTreeProducer : public edm::EDAnalyzer {
public:
	explicit TopTreeProducer(const edm::ParameterSet&);
	~TopTreeProducer();


  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
	virtual void beginJob() override;
	virtual void beginRun(const edm::Run&, const edm::EventSetup&) override;
	virtual void endRun(const edm::Run&, const edm::EventSetup&, const edm::ParameterSet&);
	virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endLuminosityBlock(const edm::LuminosityBlock&, const EventSetup&) override;
	virtual void endJob() override;

	edm::ParameterSet myConfig_;
	edm::ParameterSet producersNames_;
	edm::ParameterSet valuesForConsumeCommand;

	int verbosity;
	std::string rootFileName_ ;
	TFile* rootFile_ ;
	TTree* eventTree_;
	TTree* runTree_;
  TH1F* tmp_;
	bool doHLT;
	bool doMC;
	bool doPDFInfo;
	bool doSignalMuMuGamma;
	bool doSignalTopTop;
	bool doPrimaryVertex;
	bool doGenJet;
	bool doPFJet;
	bool doFatJet;
	bool doMuon;
	bool doElectron;
	bool doPhoton;
	bool doPhotonMC;
	bool doPFMET;
	bool doNPGenEvent;
	bool doGenTTXGenerator;
	bool doLHEEventProd;
	bool drawMCTree;
	bool doEventCleaningInfo;
	std::vector<std::string> vGenJetProducer;
	std::vector<std::string> vPFJetProducer;
	std::vector<std::string> vFatJetProducer;
	std::vector<std::string> vMuonProducer;
	std::vector<std::string> vGsfElectronProducer;
	std::vector<std::string> vElectronProducer_calibrated;
	std::vector<std::string> vElectronProducer_uncalibrated;
	std::vector<std::string> vPhotonProducer;
        std::vector<std::string> vPFmetProducer;
	std::vector<std::string> vPFmetProducerMuEGClean;
	int nTotEvt_;
	HLTAnalyzer* hltAnalyzer_;
    LHEEventProductAnalyzer* lheEventProductAnalyzer_;
    LHEEventProductAnalyzer* RunlheEventProductAnalyzer_;
	TRootRun* runInfos_;
	TRootEvent* rootEvent;
	TClonesArray* mcParticles;
	TClonesArray* tracks;
	std::vector<TClonesArray*> vgenJets;
	std::vector<TClonesArray*> vpfJets;
	std::vector<TClonesArray*> vfatJets;
	std::vector<TClonesArray*> vmuons;
	std::vector<TClonesArray*> velectrons_calibrated;
	std::vector<TClonesArray*> vphotons;
	std::vector<TClonesArray*> vPFmets;
        std::vector<TClonesArray*> vPFmetsMuEGClean;
	//	TClonesArray* lheEventProduct;
	TClonesArray* NPgenEvent;
	TClonesArray* primaryVertex;

    bool useEventCounter_;
    std::vector<std::string> filters_;
    bool isRealData_;


	// handles necessary for accessing objects in 76X or higher:

      // ---------- tokens to CMSSW member classes to be accessed in analysis ------------------
    // good practice is to use these instead of getbylabel. However getbylabel is still supported...
    edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
    std::vector<edm::EDGetTokenT<pat::MuonCollection> > vmuonToken_;
    std::vector<edm::EDGetTokenT<edm::View<reco::GsfElectron>> > vGsfelectronToken_;
    std::vector<edm::EDGetTokenT<pat::ElectronCollection> > velectronToken_calibrated_;
    std::vector<edm::EDGetTokenT<pat::ElectronCollection> > velectronToken_uncalibrated_;
    std::vector<edm::EDGetTokenT<pat::PhotonCollection> > vphotonToken_;
    std::vector<edm::EDGetTokenT<pat::JetCollection> > vjetToken_;
    std::vector<edm::EDGetTokenT<pat::JetCollection> > vfatjetToken_;
    std::vector<edm::EDGetTokenT<pat::METCollection> > vmetToken_;
    std::vector<edm::EDGetTokenT<pat::METCollection> > vmetTokenMuEGClean_;
    std::vector<edm::EDGetTokenT<std::vector<reco::GenJet> > >vgenjetToken_;
    edm::EDGetTokenT<edm::TriggerResults> triggerToken1_;
    edm::EDGetTokenT<edm::TriggerResults> triggerToken2_;
    edm::EDGetTokenT<edm::TriggerResults> triggerToken3_;
    edm::EDGetTokenT<edm::TriggerResults> triggerToken4_;
    edm::EDGetTokenT<edm::TriggerResults> triggerToken5_;
    edm::EDGetTokenT<edm::TriggerResults> metfilterToken_;
    edm::EDGetTokenT<HcalNoiseSummary> hcalNoiseSummaryToken_;
    edm::EDGetTokenT<std::vector< PileupSummaryInfo > > pileUpProducerToken_;
    edm::EDGetTokenT<double> fixedGridRhoAllToken_;
    edm::EDGetTokenT<double> fixedGridRhoFastjetAllToken_;
    edm::EDGetTokenT<double> fixedGridRhoFastjetAllCaloToken_;
    edm::EDGetTokenT<double> fixedGridRhoFastjetCentralCaloToken_;
    edm::EDGetTokenT<double> fixedGridRhoFastjetCentralChargedPileUpToken_;
    edm::EDGetTokenT<double> fixedGridRhoFastjetCentralNeutralToken_;
	  edm::EDGetTokenT<GenEventInfoProduct> genEventInfoProductToken_;
    edm::EDGetTokenT<std::vector<reco::GenParticle> > genParticlesToken_;
    edm::EDGetTokenT<LHEEventProduct> lheproductToken_;
	  edm::EDGetTokenT<LHERunInfoProduct> lheRunInfoproductToken_;
    
    edm::EDGetTokenT<reco::BeamSpot> offlineBSToken_;
    // ID decisions objects
    edm::EDGetTokenT<edm::ValueMap<bool> > eleVetoCBIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<bool> > eleLooseCBIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<bool> > eleMediumCBIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<bool> > eleTightCBIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<bool> > eleHEEPCBIdMapToken_;
   
    edm::EDGetTokenT<edm::ValueMap<bool> > eleMediumMVAIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<bool> > eleTightMVAIdMapToken_;
    edm::EDGetTokenT<edm::ValueMap<float> > mvaValuesMapToken_;
    edm::EDGetTokenT<edm::ValueMap<int> > mvaCategoriesMapToken_;

    // filters for 80X
    edm::EDGetTokenT<bool> BadChCandFilterToken_;
    edm::EDGetTokenT<bool> BadPFMuonFilterToken_;

    //80X bad (duplicate) global muon filter 
    edm::EDGetTokenT<edm::PtrVector<reco::Muon>> BadGlobalMuonFilterToken_;
    edm::EDGetTokenT<edm::PtrVector<reco::Muon>> CloneGlobalMuonFilterToken_;

    //BFragmentation reweighting (see https://gitlab.cern.ch/CMS-TOPPAG/BFragmentationAnalyzer) 
    edm::EDGetTokenT<std::vector<reco::GenJet> > genJetsFromPseudoTopToken_;
    edm::EDGetTokenT<edm::ValueMap<float> > upFragToken_;
    edm::EDGetTokenT<edm::ValueMap<float> > centralFragToken_;
    edm::EDGetTokenT<edm::ValueMap<float> > downFragToken_;
    edm::EDGetTokenT<edm::ValueMap<float> > petersonFragToken_;
    edm::EDGetTokenT<edm::ValueMap<float> > semilepBRUpToken_;
    edm::EDGetTokenT<edm::ValueMap<float> > semilepBRDownToken_;
    
    //Extra tool for splitting ttbar samples into ttbb,ttcc,ttll: https://twiki.cern.ch/twiki/bin/view/CMSPublic/GenHFHadronMatcher
    edm::EDGetTokenT<reco::GenJetCollection> genTTXJetsToken_;
    
    edm::EDGetTokenT<std::vector<int> > genTTXBHadJetIndexToken_;
    edm::EDGetTokenT<std::vector<int> > genTTXBHadFlavourToken_;
    edm::EDGetTokenT<std::vector<int> > genTTXBHadFromTopWeakDecayToken_;
    edm::EDGetTokenT<std::vector<reco::GenParticle> > genTTXBHadPlusMothersToken_;
    edm::EDGetTokenT<std::vector<std::vector<int> > > genTTXBHadPlusMothersIndicesToken_;
    edm::EDGetTokenT<std::vector<int> > genTTXBHadIndexToken_;
    edm::EDGetTokenT<std::vector<int> > genTTXBHadLeptonHadronIndexToken_;
    edm::EDGetTokenT<std::vector<int> > genTTXBHadLeptonViaTauToken_;
     
    edm::EDGetTokenT<std::vector<int> > genTTXCHadJetIndexToken_;
    edm::EDGetTokenT<std::vector<int> > genTTXCHadFlavourToken_;
    edm::EDGetTokenT<std::vector<int> > genTTXCHadFromTopWeakDecayToken_;
    edm::EDGetTokenT<std::vector<int> > genTTXCHadBHadronIdToken_;

};


#endif
