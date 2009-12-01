#include "../interface/TopTreeProducer.h"

using namespace std;
using namespace reco;
using namespace edm;


TopTreeProducer::TopTreeProducer(const edm::ParameterSet& iConfig)
{
	myConfig_ = iConfig.getParameter<ParameterSet>("myConfig");
	dataType_ = myConfig_.getUntrackedParameter<string>("dataType","unknown");
	cout << "dataType: " << dataType_ << endl;
	if( dataType_=="RECO" )				producersNames_ = iConfig.getParameter<ParameterSet>("producersNamesRECO");
	else if( dataType_=="AOD" )			producersNames_ = iConfig.getParameter<ParameterSet>("producersNamesAOD");
	else if( dataType_=="PATAOD" )	producersNames_ = iConfig.getParameter<ParameterSet>("producersNamesPATAOD");
	else if( dataType_=="PAT" )			producersNames_ = iConfig.getParameter<ParameterSet>("producersNamesPAT");
	else { cout << "TopTreeProducer::TopTreeProducer...   dataType is unknown...  exiting..." << endl; exit(1); }
}


TopTreeProducer::~TopTreeProducer()
{
}



// ------------ method called once each job just before starting event loop  ------------
void TopTreeProducer::beginJob(const edm::EventSetup&)
{

	// Load Config parameters	
	verbosity = myConfig_.getUntrackedParameter<int>("verbosity", 0);
	rootFileName_ = myConfig_.getUntrackedParameter<string>("RootFileName","noname.root");
	isCSA07Soup = myConfig_.getUntrackedParameter<bool>("isCSA07Soup",false);
	doHLT = myConfig_.getUntrackedParameter<bool>("doHLT",false);
	doMC = myConfig_.getUntrackedParameter<bool>("doMC",false);
	doPDFInfo = myConfig_.getUntrackedParameter<bool>("doPDFInfo",false);
	doPrimaryVertex = myConfig_.getUntrackedParameter<bool>("doPrimaryVertex",false);
	doJet = myConfig_.getUntrackedParameter<bool>("doJet",false);
	doJetStudy = myConfig_.getUntrackedParameter<bool>("doJetStudy",false);
	doMuon = myConfig_.getUntrackedParameter<bool>("doMuon",false);
	doCosmicMuon = myConfig_.getUntrackedParameter<bool>("doCosmicMuon",false);
	doElectron = myConfig_.getUntrackedParameter<bool>("doElectron",false);	
	doMET = myConfig_.getUntrackedParameter<bool>("doMET",false);
	drawMCTree = myConfig_.getUntrackedParameter<bool>("drawMCTree",false);
	doGenEvent = myConfig_.getUntrackedParameter<bool>("doGenEvent",false);
	doNPGenEvent = myConfig_.getUntrackedParameter<bool>("doNPGenEvent",false);
	doSpinCorrGen = myConfig_.getUntrackedParameter<bool>("doSpinCorrGen",false);
	doSemiLepEvent = myConfig_.getUntrackedParameter<bool>("doSemiLepEvent",false);
	vector<string> defaultVec;
	vector<string> defaultVecCM;
	
	vJetProducer = producersNames_.getUntrackedParameter<vector<string> >("vjetProducer",defaultVec);
	vCosmicMuonProducer = producersNames_.getUntrackedParameter<vector<string> >("vcosmicMuonProducer",defaultVecCM);

	for(unsigned int s=0;s<vJetProducer.size();s++){
		TClonesArray* a;
		vjets.push_back(a); 
	}

	for(unsigned int s=0;s<vCosmicMuonProducer.size();s++){
		TClonesArray* a;
		vcosmicMuons.push_back(a); 

		vector<TClonesArray*> trackVector;
                for (unsigned int t=0; t<3; t++)
		  trackVector.push_back(a);

		vcosmicMuonTracks.push_back(trackVector);
	}

	nTotEvt_ = 0;
	
	// initialize root output file
	if(verbosity>0) cout << "New RootFile " << rootFileName_.c_str() << " is created" << endl;
	rootFile_ = new TFile(rootFileName_.c_str(), "recreate");
	rootFile_->cd();

	runInfos_ = new TRootRun();
	runTree_ = new TTree("runTree", "Global Run Infos");
	runTree_->Branch ("runInfos", "TRootRun", &runInfos_);

	rootEvent = 0;
	eventTree_ = new TTree("eventTree", "Event Infos");
	eventTree_->Branch ("Event", "TRootEvent", &rootEvent);

	if(doHLT)
	{
		hltAnalyzer_ = new HLTAnalyzer(producersNames_);
		hltAnalyzer_->setVerbosity(verbosity);
	}

	if(doMC)
	{
		if(verbosity>0) cout << "MC Particles info will be added to rootuple" << endl;
		mcParticles = new TClonesArray("TRootMCParticle", 1000);
		eventTree_->Branch ("MCParticles", "TClonesArray", &mcParticles);
	}
	
	

	if(doJet)
	{
		if(verbosity>0) cout << "Jets info will be added to rootuple" << endl;
		jets = new TClonesArray("TRootJet", 1000);
		eventTree_->Branch ("Jets", "TClonesArray", &jets);
	}
	
	if(doJetStudy)
	{
		if(verbosity>0) cout << "Jets info will be added to rootuple (for JetStudy)" << endl;
		for(unsigned int s=0;s<vJetProducer.size();s++){
			vjets[s] = new TClonesArray("TRootJet", 1000);
			char name[100];
			sprintf(name,"Jets_%s",vJetProducer[s].c_str());
			eventTree_->Branch (name, "TClonesArray", &vjets[s]);
		}
	}
	
	if(doGenEvent)
	{
		if(verbosity>0) cout << "GenEvent info will be added to rootuple" << endl;
		genEvent = new TClonesArray("TRootGenEvent", 1000);
		eventTree_->Branch ("GenEvent", "TClonesArray", &genEvent);
	}

	if(doNPGenEvent)
	{
		if(verbosity>0) cout << "NPGenEvent info will be added to rootuple" << endl;
		NPgenEvent = new TClonesArray("TRootNPGenEvent", 1000);
		eventTree_->Branch ("NPGenEvent", "TClonesArray", &NPgenEvent);
	}

	if(doSpinCorrGen)
	{
		if(verbosity>0) cout << "SpinCorrelation Gen info will be added to rootuple" << endl;
		spinCorrGen = new TClonesArray("TRootSpinCorrGen", 1000);
		eventTree_->Branch ("SpinCorrGen", "TClonesArray", &spinCorrGen);
	}
    
	if(doSemiLepEvent)
	{
		if(verbosity>0) cout << "SemiLepEvent info will be added to rootuple" << endl;
		semiLepEvent = new TClonesArray("TRootSemiLepEvent", 1000);
		eventTree_->Branch ("SemiLepEvent", "TClonesArray", &semiLepEvent);
	}

	if(doMuon)
	{
		if(verbosity>0) cout << "Muons info will be added to rootuple" << endl;
		muons = new TClonesArray("TRootMuon", 1000);
		eventTree_->Branch ("Muons", "TClonesArray", &muons);
	}

	if(doCosmicMuon)
	{
		if(verbosity>0) cout << "Cosmic Muons info will be added to rootuple" << endl;
	     
		for(unsigned int s=0;s<vCosmicMuonProducer.size();s++){
			vcosmicMuons[s] = new TClonesArray("TRootCosmicMuon", 1000);
			char name[100];
			sprintf(name,"CosmicMuons_%s",vCosmicMuonProducer[s].c_str());
			eventTree_->Branch (name, "TClonesArray", &vcosmicMuons[s]);

			// put the track(gl,sta,tr) branches for this muoncollection

		        vcosmicMuonTracks[s][0] = new TClonesArray("TRootTrack",1000);
			//char name[100];
			sprintf(name,"CosmicMuonGlobalTracks_%s",vCosmicMuonProducer[s].c_str());
			eventTree_->Branch (name, "TClonesArray", &vcosmicMuonTracks[s][0]);

			vcosmicMuonTracks[s][1] = new TClonesArray("TRootTrack",1000);
			//char name[100];
			sprintf(name,"CosmicMuonTrackerTracks_%s",vCosmicMuonProducer[s].c_str());
			eventTree_->Branch (name, "TClonesArray", &vcosmicMuonTracks[s][1]);

			vcosmicMuonTracks[s][2] = new TClonesArray("TRootTrack",1000);
			//char name[100];
			sprintf(name,"CosmicMuonStandAloneTracks_%s",vCosmicMuonProducer[s].c_str());
			eventTree_->Branch (name, "TClonesArray", &vcosmicMuonTracks[s][2]);

			//}
		} 
	}
	
	if(doElectron)
	{
		if(verbosity>0) cout << "Electrons info will be added to rootuple" << endl;
		electrons = new TClonesArray("TRootElectron", 1000);
		eventTree_->Branch ("Electrons", "TClonesArray", &electrons);
	}



	if(doMET)
	{
		if(verbosity>0) cout << "MET info will be added to rootuple" << endl;
		met = new TClonesArray("TRootMET", 1000);
		eventTree_->Branch ("MET", "TClonesArray", &met);
	}

}


// ------------ method called once each job just after ending the event loop  ------------
void TopTreeProducer::endJob()
{


	// Trigger Summary Tables
	if(doHLT)
	{	
		cout << "Trigger Summary Tables" << endl;
		hltAnalyzer_ ->copySummary(runInfos_);
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

	/*
	// CSA07 Process Id and Event Weight
	if(isCSA07Soup)
	{
		edm::Handle< double> weightHandle;
		iEvent.getByLabel ("csaweightproducer","weight", weightHandle);
		double weight = * weightHandle;
		int processId = csa07::csa07ProcessId(iEvent, 1000., "csaweightproducer");
		char * pname= csa07::csa07ProcessName(processId);
		if(verbosity>1) cout << "CSA07 Soup - id=" << processId << " - "<< pname << " - weight=" << weight << endl;
		rootEvent->setCsa07id(processId);
		rootEvent->setCsa07weight(weight);
		rootEvent->setCsa07process(pname);	
	}
	*/
        
	
	// Trigger
	rootEvent->setGlobalHLT(true);
	if(doHLT)
	{	
		cout << endl << "Get TriggerResults..." << endl;
		if (nTotEvt_==1) hltAnalyzer_->init(iEvent, rootEvent);
		hltAnalyzer_->process(iEvent, rootEvent);
	}
	//if ( ! rootEvent->passGlobalHLT() ) return;

	// MC Info
	if(doMC)
	{
		if(verbosity>1) cout << endl << "Analysing MC info..." << endl;
		MCAnalyzer* myMCAnalyzer = new MCAnalyzer(myConfig_, producersNames_);
		myMCAnalyzer->SetVerbosity(verbosity);
		if (drawMCTree) myMCAnalyzer->DrawMCTree(iEvent, iSetup, myConfig_, producersNames_);
		if ( dataType_=="RECO" && doPDFInfo ) myMCAnalyzer->PDFInfo(iEvent, rootEvent);
		myMCAnalyzer->ProcessMCParticle(iEvent, mcParticles);
		delete myMCAnalyzer;
	}

	
	// Get Primary Vertices
	if(doPrimaryVertex)
	{
		if(verbosity>1) cout << endl << "Analysing primary vertices collection..." << endl;
		VertexAnalyzer* myVertexAnalyzer = new VertexAnalyzer(producersNames_, verbosity);
		myVertexAnalyzer->Process(iEvent, rootEvent);
		delete myVertexAnalyzer;
	}
	
	

	// Calo Jet
	if(doJet)
	{
		if(verbosity>1) cout << endl << "Analysing jets collection..." << endl;
		JetAnalyzer* myJetAnalyzer = new JetAnalyzer(producersNames_, myConfig_, verbosity);
		myJetAnalyzer->Process(iEvent, jets);
		delete myJetAnalyzer;
	}

	if(doJetStudy)
	{
		if(verbosity>1) cout << endl << "Analysing jets collection (for JetStudy)..." << endl;
		for(unsigned int s=0;s<vJetProducer.size();s++){
			JetAnalyzer* myJetAnalyzer = new JetAnalyzer(producersNames_, s,  myConfig_, verbosity);
			myJetAnalyzer->Process(iEvent, vjets[s]);
			delete myJetAnalyzer;
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

        //SemiLepEvent
	if(doSemiLepEvent)
	{
		if(verbosity>1) cout << endl << "Analysing SemiLepEvent collection..." << endl;
		SemiLepEventAnalyzer* mySemiLepEventAnalyzer = new SemiLepEventAnalyzer(producersNames_, myConfig_, verbosity);
		mySemiLepEventAnalyzer->Process(iEvent, semiLepEvent, jets, muons);
		delete mySemiLepEventAnalyzer;
	}
	
	// Muons
	if(doMuon)
	{
		if(verbosity>1) cout << endl << "Analysing muons collection..." << endl;
		MuonAnalyzer* myMuonAnalyzer = new MuonAnalyzer(producersNames_, myConfig_, verbosity);
		myMuonAnalyzer->Process(iEvent, muons);
		delete myMuonAnalyzer;
	}

	// Cosmic Muons
	if(doCosmicMuon)
	{
	  if(verbosity>1) cout << endl << "Analysing muons collection (for cosmics)..." << endl;
     	  
	  for(unsigned int s=0;s<vCosmicMuonProducer.size();s++){
	    CosmicMuonAnalyzer *myCosmicMuonAnalyzer = new CosmicMuonAnalyzer(producersNames_, s,  myConfig_, verbosity);
	    myCosmicMuonAnalyzer->Process(iEvent, vcosmicMuons[s],vcosmicMuonTracks[s]);
	    delete myCosmicMuonAnalyzer;
	  }

	}
	

        // Lazy Tools to calculate Cluster shape variables
	EcalClusterLazyTools* lazyTools = 0;
	if( (dataType_=="RECO" || dataType_=="AOD" || dataType_=="PATAOD") && ( doElectron )  )
	{
		if(verbosity>1) cout << endl << "Loading egamma LazyTools..." << endl;
		edm::InputTag reducedBarrelEcalRecHitCollection_ = producersNames_.getParameter<edm::InputTag>("reducedBarrelEcalRecHitCollection");
		edm::InputTag reducedEndcapEcalRecHitCollection_ = producersNames_.getParameter<edm::InputTag>("reducedEndcapEcalRecHitCollection");
		// FIXME - Test availability of reducedEcalRecHits...
		lazyTools = new EcalClusterLazyTools( iEvent, iSetup, reducedBarrelEcalRecHitCollection_, reducedEndcapEcalRecHitCollection_ );
	}
																

	// Electrons
	if(doElectron)
	{
		if(verbosity>1) cout << endl << "Analysing electrons collection..." << endl;
		ElectronAnalyzer* myElectronAnalyzer = new ElectronAnalyzer(producersNames_, myConfig_, verbosity);
		myElectronAnalyzer->Process(iEvent, electrons, *lazyTools);
		delete myElectronAnalyzer;
	}
			


	// MET 
	if(doMET)
	{
		if(verbosity>1) cout << endl << "Analysing Missing Et..." << endl;
		METAnalyzer* myMETAnalyzer = new METAnalyzer(producersNames_, myConfig_, verbosity);
		myMETAnalyzer->Process(iEvent, met);
		delete myMETAnalyzer;
	}
	
	// Associate recoParticles to mcParticles
	if(doMC)
	{
		MCAssociator* myMCAssociator = new MCAssociator(producersNames_, verbosity);
		myMCAssociator->init(iEvent, mcParticles);
		if(doJet) myMCAssociator->process(jets);
		if(doMuon) myMCAssociator->process(muons);
		if(doElectron) myMCAssociator->process(electrons);
		if(doMET) myMCAssociator->process(met);
		//if(verbosity>2 && doJet) myMCAssociator->printParticleAssociation(jets);
		//if(verbosity>2 && doMuon) myMCAssociator->printParticleAssociation(muons);
		//if(verbosity>2 && doElectron) myMCAssociator->printParticleAssociation(electrons);
		//if(verbosity>2 && doPhoton) myMCAssociator->printParticleAssociation(photons);
		//if(verbosity>2 && doMET) myMCAssociator->printParticleAssociation(met);
		delete myMCAssociator;
	}


	if(verbosity>1) cout << endl << "Filling rootuple..." << endl;
	eventTree_->Fill();
	if(verbosity>1) cout << endl << "Deleting objects..." << endl;
	delete rootEvent;
	if(doMC) (*mcParticles).Delete();
	if(doJet) (*jets).Delete();
	if(doJetStudy){
		for(unsigned int s=0;s<vJetProducer.size();s++){
			(*vjets[s]).Delete();
		}
	}
	if(doMuon) (*muons).Delete();
       	if(doCosmicMuon) {
	
	  for(unsigned int s=0;s<vCosmicMuonProducer.size();s++){
	    (*vcosmicMuons[s]).Delete();
	  }

	}

	if(doElectron) (*electrons).Delete();
	if(doMET) (*met).Delete();
	if(doGenEvent) (*genEvent).Delete();
	if(doNPGenEvent) (*NPgenEvent).Delete();
	if(doSpinCorrGen) (*spinCorrGen).Delete();
	if(doSemiLepEvent) (*semiLepEvent).Delete();
	if(verbosity>0) cout << endl;

}

