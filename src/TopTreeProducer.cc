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
	doMuon = myConfig_.getUntrackedParameter<bool>("doMuon",false);
	doElectron = myConfig_.getUntrackedParameter<bool>("doElectron",false);	
	doMET = myConfig_.getUntrackedParameter<bool>("doMET",false);
	drawMCTree = myConfig_.getUntrackedParameter<bool>("drawMCTree",false);
	doGenEvent = myConfig_.getUntrackedParameter<bool>("doGenEvent",false);
	doSpinCorrGen = myConfig_.getUntrackedParameter<bool>("doSpinCorrGen",false);

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
	
	if(doGenEvent)
	{
		if(verbosity>0) cout << "GenEvent info will be added to rootuple" << endl;
		genEvent = new TClonesArray("TRootGenEvent", 1000);
		eventTree_->Branch ("GenEvent", "TClonesArray", &genEvent);
	}

	if(doSpinCorrGen)
	{
		if(verbosity>0) cout << "SpinCorrelation Gen info will be added to rootuple" << endl;
		spinCorrGen = new TClonesArray("TRootSpinCorrGen", 1000);
		eventTree_->Branch ("SpinCorrGen", "TClonesArray", &spinCorrGen);
	}
    

	if(doMuon)
	{
		if(verbosity>0) cout << "Muons info will be added to rootuple" << endl;
		muons = new TClonesArray("TRootMuon", 1000);
		eventTree_->Branch ("Muons", "TClonesArray", &muons);
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
	runTree_->Fill();

	std::cout << "Total number of events: " << nTotEvt_ << std::endl;
	std::cout << "Closing rootfile " << rootFile_->GetName() << std::endl;
	rootFile_->Write();
	rootFile_->Close();

	// Trigger Summary Tables
	if(doHLT)
	{	
		cout << "Trigger Summary Tables" << endl;
		hltAnalyzer_ ->copySummary(runInfos_);
		hltAnalyzer_->printStats();
	}

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

	// GenEvent
	if(doGenEvent)
	{
		if(verbosity>1) cout << endl << "Analysing GenEvent collection..." << endl;
		GenEventAnalyzer* myGenEventAnalyzer = new GenEventAnalyzer(producersNames_, myConfig_, verbosity);
		myGenEventAnalyzer->Process(iEvent, genEvent);
		delete myGenEventAnalyzer;
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
		if(verbosity>1) cout << endl << "Analysing muons collection..." << endl;
		MuonAnalyzer* myMuonAnalyzer = new MuonAnalyzer(producersNames_, myConfig_, verbosity);
		myMuonAnalyzer->Process(iEvent, muons);
		delete myMuonAnalyzer;
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
	if(doMuon) (*muons).Delete();
	if(doElectron) (*electrons).Delete();
	if(doMET) (*met).Delete();
	if(doGenEvent) (*genEvent).Delete();
	if(doSpinCorrGen) (*spinCorrGen).Delete();
	if(verbosity>0) cout << endl;
}

