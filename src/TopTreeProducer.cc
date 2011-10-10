#include "../interface/TopTreeProducer.h"

#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/Handle.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;


TopTreeProducer::TopTreeProducer(const edm::ParameterSet& iConfig)
{
	myConfig_ = iConfig.getParameter<ParameterSet>("myConfig");
	producersNames_ = iConfig.getParameter<ParameterSet>("producersNames");
}


TopTreeProducer::~TopTreeProducer()
{
}


// ------------ method called once each job just before starting event loop  ------------
void TopTreeProducer::beginJob()
{

	// Load Config parameters	
	verbosity = myConfig_.getUntrackedParameter<int>("verbosity", 0);
	rootFileName_ = myConfig_.getUntrackedParameter<string>("RootFileName","noname.root");
	doHLT = myConfig_.getUntrackedParameter<bool>("doHLT",false);
	doMC = myConfig_.getUntrackedParameter<bool>("doMC",false);
	doPDFInfo = myConfig_.getUntrackedParameter<bool>("doPDFInfo",false);
	doPrimaryVertex = myConfig_.getUntrackedParameter<bool>("doPrimaryVertex",false);
	runGeneralTracks = myConfig_.getUntrackedParameter<bool>("runGeneralTracks",false);
	doCaloJet = myConfig_.getUntrackedParameter<bool>("doCaloJet",false);
	doGenJet = myConfig_.getUntrackedParameter<bool>("doGenJet",false);
	doPFJet = myConfig_.getUntrackedParameter<bool>("doPFJet",false);
	doJPTJet = myConfig_.getUntrackedParameter<bool>("doJPTJet",false);
	doMuon = myConfig_.getUntrackedParameter<bool>("doMuon",false);
	doElectron = myConfig_.getUntrackedParameter<bool>("doElectron",false);	
	doCaloMET = myConfig_.getUntrackedParameter<bool>("doCaloMET",false);
	doPFMET = myConfig_.getUntrackedParameter<bool>("doPFMET",false);
	doTCMET = myConfig_.getUntrackedParameter<bool>("doTCMET",false);
	drawMCTree = myConfig_.getUntrackedParameter<bool>("drawMCTree",false);
	doGenEvent = myConfig_.getUntrackedParameter<bool>("doGenEvent",false);
	doNPGenEvent = myConfig_.getUntrackedParameter<bool>("doNPGenEvent",false);
	doSpinCorrGen = myConfig_.getUntrackedParameter<bool>("doSpinCorrGen",false);
	vector<string> defaultVec;
	vGenJetProducer = producersNames_.getUntrackedParameter<vector<string> >("vgenJetProducer",defaultVec);
	vCaloJetProducer = producersNames_.getUntrackedParameter<vector<string> >("vcaloJetProducer",defaultVec);
	vPFJetProducer = producersNames_.getUntrackedParameter<vector<string> >("vpfJetProducer",defaultVec);
	vJPTJetProducer = producersNames_.getUntrackedParameter<vector<string> >("vJPTJetProducer",defaultVec);
	vMuonProducer = producersNames_.getUntrackedParameter<vector<string> >("vmuonProducer",defaultVec);
	vElectronProducer = producersNames_.getUntrackedParameter<vector<string> >("velectronProducer",defaultVec);
	
	for(unsigned int s=0;s<vGenJetProducer.size();s++){
		TClonesArray* a;
		vgenJets.push_back(a);
	}

	for(unsigned int s=0;s<vCaloJetProducer.size();s++){
		TClonesArray* a;
		vcaloJets.push_back(a);
	}

	for(unsigned int s=0;s<vPFJetProducer.size();s++){
		TClonesArray* a;
		vpfJets.push_back(a);
	}

	for(unsigned int s=0;s<vJPTJetProducer.size();s++){
		TClonesArray* a;
		vjptJets.push_back(a);
	}

	for(unsigned int s=0;s<vMuonProducer.size();s++){
		TClonesArray* a;
		vmuons.push_back(a);
	}

	for(unsigned int s=0;s<vElectronProducer.size();s++){
		TClonesArray* a;
		velectrons.push_back(a);
	}

	nTotEvt_ = 0;
	
	// initialize root output file
	rootFile_ = new TFile(rootFileName_.c_str(), "recreate");
	rootFile_->cd();
	if(verbosity>0) cout << "New RootFile " << rootFileName_.c_str() << " is created" << endl;

	runInfos_ = new TRootRun();
	runTree_ = new TTree("runTree", "Global Run Infos");
	runTree_->Branch ("runInfos", "TopTree::TRootRun", &runInfos_);
	if(verbosity>0) cout << "RunTree is created" << endl;

	rootEvent = 0;
	eventTree_ = new TTree("eventTree", "Event Infos");
	eventTree_->Branch ("Event", "TopTree::TRootEvent", &rootEvent);
	if(verbosity>0) cout << "EventTree is created" << endl;

	if(doHLT)
	{
		if(verbosity>0) cout << "HLT info will be added to rootuple" << endl;
		hltAnalyzer_ = new HLTAnalyzer(producersNames_, myConfig_);
		hltAnalyzer_->setVerbosity(verbosity);
	}

	if(doMC)
	{
		if(verbosity>0) cout << "MC Particles info will be added to rootuple" << endl;
		mcParticles = new TClonesArray("TopTree::TRootMCParticle", 1000);
		eventTree_->Branch ("MCParticles", "TClonesArray", &mcParticles);
	}

	if(doCaloJet)
	{
		if(verbosity>0) cout << "CaloJets info will be added to rootuple" << endl;
		for(unsigned int s=0;s<vCaloJetProducer.size();s++)
		{
			vcaloJets[s] = new TClonesArray("TopTree::TRootCaloJet", 1000);
			char name[100];
			sprintf(name,"CaloJets_%s",vCaloJetProducer[s].c_str());
			eventTree_->Branch (name, "TClonesArray", &vcaloJets[s]);
		}
	}

	if(doGenJet)
	{
		if(verbosity>0) cout << "GenJets info will be added to rootuple (for GenJetStudy)" << endl;
		for(unsigned int s=0; s<vGenJetProducer.size(); s++)
		{
			vgenJets[s] = new TClonesArray("TopTree::TRootGenJet", 1000);
			char name[100];
			sprintf(name,"GenJets_%s",vGenJetProducer[s].c_str());
			eventTree_->Branch (name, "TClonesArray", &vgenJets[s]);
		}
	}
	
	if(doPFJet)
	{
		if(verbosity>0) cout << "PFJets info will be added to rootuple" << endl;
		for(unsigned int s=0;s<vPFJetProducer.size();s++)
		{
			vpfJets[s] = new TClonesArray("TopTree::TRootPFJet", 1000);
			char name[100];
			sprintf(name,"PFJets_%s",vPFJetProducer[s].c_str());
			eventTree_->Branch (name, "TClonesArray", &vpfJets[s]);
		}
	}

	if(doJPTJet)
	{
		if(verbosity>0) cout << "JPT Jets info will be added to rootuple" << endl;
		for(unsigned int s=0;s<vJPTJetProducer.size();s++)
		{
			vjptJets[s] = new TClonesArray("TopTree::TRootJPTJet", 1000);
			char name[100];
			sprintf(name,"JPTJets_%s",vJPTJetProducer[s].c_str());
			eventTree_->Branch (name, "TClonesArray", &vjptJets[s]);
		}
	}
	
	if(doGenEvent)
	{
		if(verbosity>0) cout << "GenEvent info will be added to rootuple" << endl;
		genEvent = new TClonesArray("TopTree::TRootGenEvent", 1000);
		eventTree_->Branch ("GenEvent", "TClonesArray", &genEvent);
	}

	if(doNPGenEvent)
	{
		if(verbosity>0) cout << "NPGenEvent info will be added to rootuple" << endl;
		NPgenEvent = new TClonesArray("TopTree::TRootNPGenEvent", 1000);
		eventTree_->Branch ("NPGenEvent", "TClonesArray", &NPgenEvent);
	}

	if(doSpinCorrGen)
	{
		if(verbosity>0) cout << "SpinCorrelation Gen info will be added to rootuple" << endl;
		spinCorrGen = new TClonesArray("TopTree::TRootSpinCorrGen", 1000);
		eventTree_->Branch ("SpinCorrGen", "TClonesArray", &spinCorrGen);
	}
    
	if(doMuon)
	{
		if(verbosity>0) cout << "Muons info will be added to rootuple" << endl;
		for(unsigned int s=0;s<vMuonProducer.size();s++) {
			vmuons[s] = new TClonesArray("TopTree::TRootMuon", 1000);
			char name[100];
			sprintf(name,"Muons_%s",vMuonProducer[s].c_str());
			eventTree_->Branch (name, "TClonesArray", &vmuons[s]);
		} 
	}
	
	if(doElectron)
	{
		if(verbosity>0) cout << "Electrons info will be added to rootuple" << endl;
		for(unsigned int s=0;s<vElectronProducer.size();s++) {
			velectrons[s] = new TClonesArray("TopTree::TRootElectron", 1000);
			char name[100];
			sprintf(name,"Electrons_%s",vElectronProducer[s].c_str());
			eventTree_->Branch (name, "TClonesArray", &velectrons[s]);
		} 
	}

	if(doCaloMET)
	{
		if(verbosity>0) cout << "CaloMET info will be added to rootuple" << endl;
		CALOmet = new TClonesArray("TopTree::TRootCaloMET", 1000);
		eventTree_->Branch ("CaloMET", "TClonesArray", &CALOmet);
	}

	if(doPFMET)
	{
		if(verbosity>0) cout << "ParticleFlowMET info will be added to rootuple" << endl;
		PFmet = new TClonesArray("TopTree::TRootPFMET", 1000);
		eventTree_->Branch ("PFMET", "TClonesArray", &PFmet);
	}

	if(doTCMET)
	{
		if(verbosity>0) cout << "Track Corrected MET info will be added to rootuple" << endl;
		TCmet = new TClonesArray("TopTree::TRootMET", 1000);
		eventTree_->Branch ("TCMET", "TClonesArray", &TCmet);
	}
	
	if(doPrimaryVertex)
	{
		if(verbosity>0) cout << "Primary Vertex info will be added to rootuple" << endl;
		primaryVertex = new TClonesArray("TopTree::TRootVertex", 1000);
		eventTree_->Branch ("PrimaryVertex", "TClonesArray", &primaryVertex);
	}

}


// ------------ method called once each job just after ending the event loop  ------------
void TopTreeProducer::endJob()
{

	// Trigger Summary Tables
	if(doHLT)
	{	
		cout << "Trigger Summary Tables" << endl;
		hltAnalyzer_->copySummary(runInfos_);
		hltAnalyzer_->printStats();
	}

	runTree_->Fill();
	
	std::cout << "Total number of events: " << nTotEvt_ << std::endl;
	std::cout << "Closing rootfile " << rootFile_->GetName() << std::endl;
	rootFile_->Write();
	rootFile_->Close();

}


// ------------ method called to for each event  ------------
void TopTreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	rootFile_->cd();
	nTotEvt_++;
	if( (verbosity>1) || (verbosity>0 && nTotEvt_%10==0 && nTotEvt_<=100)  || (verbosity>0 && nTotEvt_%100==0 && nTotEvt_>100) )
		cout << endl << endl 
			<< "####### TopTreeProducer - Cumulated Events " << nTotEvt_
			<< " - Run " << iEvent.id().run() 
			<< " - Event " << iEvent.id().event() 
			<< " #######" << endl;

	// Global Event Infos
	rootEvent = new TRootEvent();
	rootEvent->setNb(nTotEvt_);
	rootEvent->setEventId(iEvent.id().event());
	rootEvent->setRunId(iEvent.id().run());
	rootEvent->setLumiBlockId(iEvent.luminosityBlock());

	// do PileUp info

	edm::InputTag PileupSrc_(producersNames_.getParameter<edm::InputTag>("pileUpProducer"));
	Handle<std::vector< PileupSummaryInfo > >  PupInfo;
	iEvent.getByLabel(PileupSrc_, PupInfo);
  
	if (PupInfo.isValid()) {
	  std::vector<PileupSummaryInfo>::const_iterator PVI;
	  
	  // (then, for example, you can do)
	  for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
	  
	    //std::cout << " Pileup Information: bunchXing, nvtx: " << PVI->getBunchCrossing() << " " << PVI->getPU_NumInteractions() << std::endl;

	    rootEvent->setNPu(PVI->getBunchCrossing(),PVI->getPU_NumInteractions());
	  
	  }

	  //cout << rootEvent->nPu(0) << endl;
	  //cout << rootEvent->nPu(1) << endl;

	}

	// we need to store some triggerFilter info to be able to emulate triggers on older data
	if (doHLT) {
	  if (verbosity > 1) cout << "should do HLT now..." << endl;
		
	  // get Trigger summary from Event
	  edm::Handle<trigger::TriggerEvent> summary, summary1st, summary2nd, summary3rd, summary4th;
	  edm::InputTag summaryTag1st_("hltTriggerSummaryAOD","",(producersNames_.getParameter < edm::InputTag > ("hltProducer1st")).process());
	  edm::InputTag summaryTag2nd_("hltTriggerSummaryAOD","",(producersNames_.getParameter < edm::InputTag > ("hltProducer2nd")).process());
	  edm::InputTag summaryTag3rd_("hltTriggerSummaryAOD","",(producersNames_.getParameter < edm::InputTag > ("hltProducer3rd")).process());
	  edm::InputTag summaryTag4th_("hltTriggerSummaryAOD","",(producersNames_.getParameter < edm::InputTag > ("hltProducer4th")).process());
	  
	  try { iEvent.getByLabel(summaryTag1st_,summary1st);} catch (...) {;}
	  try { iEvent.getByLabel(summaryTag2nd_,summary2nd);} catch (...) {;}
	  try { iEvent.getByLabel(summaryTag3rd_,summary3rd);} catch (...) {;}
	  try { iEvent.getByLabel(summaryTag4th_,summary4th);} catch (...) {;}

	  //cout << summaryTag1st_ << " " << summaryTag2nd_  << " " << summaryTag3rd_  << " " << summaryTag4th_ << endl;
	  //cout << summaryTag1st_.process() << " " << summaryTag2nd_.process()<< " " << summaryTag3rd_.process()<< " " << summaryTag4th_.process() << endl;
	  //cout << summary1st.isValid() << " " << summary2nd.isValid() << " " << summary3rd.isValid() << " " << summary4th.isValid()<< endl;

	  if (summary1st.isValid()) 
	    summary = summary1st;
	  else if (summary2nd.isValid())
	    summary = summary2nd;
	  else if (summary3rd.isValid())
	    summary = summary3rd;
	  else if (summary4th.isValid())
	    summary = summary4th;
	  else
	    cout << "TopTreeProducer::Analyze ERROR: Could not store info for trigger emulation: provided HLTproducerNames are null" << endl;
	    
	  //cout << "summary " << summary << endl;
	  
		if (summary.isValid()) {
	    for (unsigned int i=0; i<summary->sizeFilters(); i++) {
	       if (verbosity > 1) cout << i << " -> " << summary->filterTag(i).label() << endl;
	      
	      // get all trigger objects corresponding to this module.
	      // loop through them and see how many objects match the selection
	      const trigger::Keys& KEYS (summary->filterKeys(i));
	      const int n1(KEYS.size());
	      
	      for (int j=0; j!=n1; ++j) {
					const trigger::TriggerObject& triggerObject( summary-> getObjects().at(KEYS[j]) );
					//cout << "j: " << j << " -> id " << triggerObject.id() << endl;
					//cout << "j: " << j << " -> pt " << triggerObject.pt() << endl;
					//cout << "j: " << j << " -> eta " << triggerObject.eta() << endl;
					//cout << "j: " << j << " -> phi " << triggerObject.phi() << endl;
	      	rootEvent->AddTriggerObject(string(summary->filterTag(i).label()), triggerObject.id(),triggerObject.pt(),triggerObject.eta(),triggerObject.phi());
				}
	    }
	  }
	}
	
	//fastjet density rho
	edm::Handle<double> rho;
	iEvent.getByLabel("kt6PFJetsPF2PAT","rho",rho);
	rootEvent->setKt6PFJetsPF2PAT_rho(*rho);
	
	if(doMC)
	{
		//flavorHistory path
		edm::Handle<unsigned int> flavHist;
		iEvent.getByLabel("flavorHistoryFilter","",flavHist);
		rootEvent->setflavorHistoryPath(*flavHist);
	}
	
	if(runGeneralTracks) // Calculate and fill number of tracks and number of high purity tracks
	{
		// get GeneralTracks collection
		edm::Handle<reco::TrackCollection> tkRef;
		iEvent.getByLabel("generalTracks",tkRef);    
		const reco::TrackCollection* tkColl = tkRef.product();

		if(verbosity>1) std::cout << "Total Number of Tracks " << tkColl->size() << endl;
		rootEvent->setNTracks(tkColl->size());

		int numhighpurity=0;
		reco::TrackBase::TrackQuality _trackQuality = reco::TrackBase::qualityByName("highPurity");

		reco::TrackCollection::const_iterator itk = tkColl->begin();
		reco::TrackCollection::const_iterator itk_e = tkColl->end();
		for(;itk!=itk_e;++itk)
		{
			if(verbosity>1) std::cout << "HighPurity?  " << itk->quality(_trackQuality) << std::endl;
			if(itk->quality(_trackQuality)) numhighpurity++;
		}

		if(verbosity>1) std::cout << "Total Number of HighPurityTracks " << numhighpurity << endl;
		rootEvent->setNHighPurityTracks(numhighpurity);
	}

	// Trigger
	rootEvent->setGlobalHLT(true);
	if(doHLT)
	{
		if(verbosity>1) std::cout << endl << "Get TriggerResults..." << std::endl;
		//if (nTotEvt_==1) hltAnalyzer_->init(iEvent, rootEvent);
		hltAnalyzer_->process(iEvent, rootEvent);
	}

	// MC Info
	if(doMC)
	{
		if(verbosity>1) cout << endl << "Analysing MC info..." << endl;
		MCAnalyzer* myMCAnalyzer = new MCAnalyzer(myConfig_, producersNames_);
		myMCAnalyzer->SetVerbosity(verbosity);
		if (drawMCTree) myMCAnalyzer->DrawMCTree(iEvent, iSetup, myConfig_, producersNames_);
		if (doPDFInfo ) myMCAnalyzer->PDFInfo(iEvent, rootEvent);
		myMCAnalyzer->ProcessMCParticle(iEvent, mcParticles);
		delete myMCAnalyzer;
	}

	// Get Primary Vertices
	if(doPrimaryVertex)
	{
		if(verbosity>1) cout << endl << "Analysing primary vertices collection..." << endl;
		VertexAnalyzer* myVertexAnalyzer = new VertexAnalyzer(producersNames_, verbosity);
		myVertexAnalyzer->Process(iEvent, primaryVertex);
		delete myVertexAnalyzer;
	}

	// CaloJet
	if(doCaloJet)
	{
		if(verbosity>1) cout << endl << "Analysing Calojets collection (for JetStudy)..." << endl;
		for(unsigned int s=0;s<vCaloJetProducer.size();s++){
			CaloJetAnalyzer* myCaloJetAnalyzer = new CaloJetAnalyzer(producersNames_, s, myConfig_, verbosity);
			myCaloJetAnalyzer->Process(iEvent, vcaloJets[s]);
			delete myCaloJetAnalyzer;
		}
	}

	// GenJet
	if(doGenJet)
	{
		if(verbosity>1) cout << endl << "Analysing GenJets collection ..." << endl;
		for(unsigned int s=0; s<vGenJetProducer.size(); s++)
		{
			GenJetAnalyzer* myGenJetAnalyzer = new GenJetAnalyzer(producersNames_, s, myConfig_, verbosity);
			myGenJetAnalyzer->Process(iEvent, vgenJets[s]);
			delete myGenJetAnalyzer;
		}
	}

	// PFJet
	if(doPFJet)
	{
		if(verbosity>1) cout << endl << "Analysing PFjets collection..." << endl;
		for(unsigned int s=0;s<vPFJetProducer.size();s++){
			PFJetAnalyzer* myPFJetAnalyzer = new PFJetAnalyzer(producersNames_, s,  myConfig_, verbosity);
			myPFJetAnalyzer->Process(iEvent, vpfJets[s]);
			delete myPFJetAnalyzer;
		}
	}

	// JPT Jets
	if(doJPTJet)
	{
		if(verbosity>1) cout << endl << "Analysing JPT jets collection..." << endl;
		for(unsigned int s=0;s<vJPTJetProducer.size();s++){
			JPTJetAnalyzer* myJPTJetAnalyzer = new JPTJetAnalyzer(producersNames_, s,  myConfig_, verbosity);
			myJPTJetAnalyzer->Process(iEvent, vjptJets[s]);
			delete myJPTJetAnalyzer;
		}
	}

	// GenEvent
	if(doGenEvent)
	{
		if(verbosity>1) cout << endl << "Analysing GenEvent collection..." << endl;
		GenEventAnalyzer* myGenEventAnalyzer = new GenEventAnalyzer(producersNames_, myConfig_, verbosity);
		myGenEventAnalyzer->Process(iEvent, genEvent);
		delete myGenEventAnalyzer;
	}

	// NPGenEvent
	if(doNPGenEvent)
	{
		if(verbosity>1) cout << endl << "Analysing NPGenEvent collection..." << endl;
		NPGenEventAnalyzer* myNPGenEventAnalyzer = new NPGenEventAnalyzer(producersNames_, myConfig_, verbosity);
		if(verbosity>1) cout << endl << "Analysing NPGenEvent collection..." << endl;
		myNPGenEventAnalyzer->Process(iEvent, NPgenEvent);
		if(verbosity>1) cout << endl << "Analysing NPGenEvent collection..." << endl;
		delete myNPGenEventAnalyzer;
	}

	// SpinCorrelation Gen
	if(doSpinCorrGen)
	{
		if(verbosity>1) cout << endl << "Analysing SpinCorrGen collection..." << endl;
		SpinCorrGenAnalyzer* mySpinCorrGenAnalyzer = new SpinCorrGenAnalyzer(producersNames_, myConfig_, verbosity);
		mySpinCorrGenAnalyzer->Process(iEvent, spinCorrGen);
		delete mySpinCorrGenAnalyzer;
	}

	// Muons
	if(doMuon)
	{
		if(verbosity>1) cout << endl << "Analysing muon collection..." << endl;
		for(unsigned int s=0;s<vMuonProducer.size();s++){
		  MuonAnalyzer* myMuonAnalyzer = new MuonAnalyzer(producersNames_, s, myConfig_, verbosity);
		  myMuonAnalyzer->Process(iEvent, vmuons[s]);
		  delete myMuonAnalyzer;
		}
	}	

	// Lazy Tools to calculate Cluster shape variables
	EcalClusterLazyTools* lazyTools = 0; //obsolete!!!
	
	// Electrons
	if(doElectron)
	{
		if(verbosity>1) cout << endl << "Analysing electrons collection..." << endl;
		for(unsigned int s=0;s<vElectronProducer.size();s++){
		  ElectronAnalyzer* myElectronAnalyzer = new ElectronAnalyzer(producersNames_, s, myConfig_, verbosity);
		  myElectronAnalyzer->Process(iEvent, velectrons[s], *lazyTools, iSetup);
		  delete myElectronAnalyzer;
		}
	}	

	// MET 
	if(doCaloMET)
	{
		if(verbosity>1) cout << endl << "Analysing Calorimeter Missing Et..." << endl;
		CaloMETAnalyzer* myMETAnalyzer = new CaloMETAnalyzer(producersNames_, myConfig_, verbosity);
		myMETAnalyzer->Process(iEvent, CALOmet);
		delete myMETAnalyzer;
	}

	if(doPFMET)
	{
		if(verbosity>1) cout << endl << "Analysing ParticleFlow Missing Et..." << endl;
		PFMETAnalyzer* myMETAnalyzer = new PFMETAnalyzer(producersNames_, myConfig_, verbosity);
		myMETAnalyzer->Process(iEvent, PFmet);
		delete myMETAnalyzer;
	}

	if(doTCMET)
	{
		if(verbosity>1) cout << endl << "Analysing Track Corrected Missing Et..." << endl;
		TCMETAnalyzer* myMETAnalyzer = new TCMETAnalyzer(producersNames_, myConfig_, verbosity);
		myMETAnalyzer->Process(iEvent, TCmet);
		delete myMETAnalyzer;
	}
	
	// Associate recoParticles to mcParticles
	if(doMC)
	{
		MCAssociator* myMCAssociator = new MCAssociator(producersNames_, verbosity);
		myMCAssociator->init(iEvent, mcParticles);
		if(doCaloJet && vcaloJets.size() > 0) myMCAssociator->process(vcaloJets[0]);
		if(doPFJet && vpfJets.size() > 0) myMCAssociator->process(vpfJets[0]);
		if(doMuon && vmuons.size() > 0) myMCAssociator->process(vmuons[0]);
		if(doElectron && velectrons.size() > 0) myMCAssociator->process(velectrons[0]);
		if(doCaloMET) myMCAssociator->process(CALOmet);
		//if(verbosity>2 && doCaloJet && vcaloJets.size() > 0) myMCAssociator->printParticleAssociation(vcaloJets[0]);
		//if(verbosity>2 && doMuon && vmuons.size() > 0) myMCAssociator->printParticleAssociation(vmuons[0]);
		//if(verbosity>2 && doElectron && velectrons.size() > 0) myMCAssociator->printParticleAssociation(velectrons[0]);
		//if(verbosity>2 && doPhoton) myMCAssociator->printParticleAssociation(photons);
		//if(verbosity>2 && doCaloMET) myMCAssociator->printParticleAssociation(CALOmet);
		delete myMCAssociator;
	}


	if(verbosity>1) cout << endl << "Filling rootuple..." << endl;
	eventTree_->Fill();
	if(verbosity>1) cout << endl << "Deleting objects..." << endl;
	delete rootEvent;
	if(doMC) (*mcParticles).Delete();
	if(doCaloJet)
	{
		for(unsigned int s=0;s<vCaloJetProducer.size();s++)
		{
			(*vcaloJets[s]).Delete();
		}
	}
	if(doGenJet)
	{
		for(unsigned int s=0;s<vGenJetProducer.size();s++)
		{
			(*vgenJets[s]).Delete();
		}		
	}
	if(doPFJet){
		for(unsigned int s=0;s<vPFJetProducer.size();s++){
			(*vpfJets[s]).Delete();
		}
	}
	if(doJPTJet){
		for(unsigned int s=0;s<vJPTJetProducer.size();s++){
			(*vjptJets[s]).Delete();
		}
	}
	if(doMuon){
		for(unsigned int s=0;s<vMuonProducer.size();s++){
			(*vmuons[s]).Delete();
		}
	}
	if(doElectron){
		for(unsigned int s=0;s<vElectronProducer.size();s++){
			(*velectrons[s]).Delete();
		}
	}
	if(doCaloMET) (*CALOmet).Delete();
	if(doPFMET) (*PFmet).Delete();
	if(doTCMET) (*TCmet).Delete();
	if(doGenEvent) (*genEvent).Delete();
	if(doNPGenEvent) (*NPgenEvent).Delete();
	if(doSpinCorrGen) (*spinCorrGen).Delete();
	if(doPrimaryVertex) (*primaryVertex).Delete();
	if(verbosity>0) cout << endl;
}
