{
#include <iomanip>

	bool isCSA07Soup              = false;
	bool doHLT                    = false;
	bool doMC                     = false;
	bool doSignalMC               = false;
	bool doTrack                  = true;
	bool doJet                    = true;
	bool doMuon                   = true;
	bool doPhoton                 = true;
	bool doElectron               = true;
	bool doCluster                = true;
	bool doPhotonIsolation        = true;
	bool doPhotonConversion       = true;
	bool doPhotonConversionMC     = false;

	TFile* f=new TFile("TotoAna.root");
	TTree* runTree = (TTree*) f->Get("runTree");
	TTree* eventTree = (TTree*) f->Get("eventTree");

	TBranch* run_br = (TBranch *) runTree->GetBranch("runInfos");
	TRootRun* runInfos = 0;
	run_br->SetAddress(&runInfos);
	
	TBranch* event_br = (TBranch *) eventTree->GetBranch("Event");
	TRootEvent* event = 0;
	event_br->SetAddress(&event);
		
	if(doSignalMC)
	{			
		TBranch* mcSignalEvent_br = (TBranch *) eventTree->GetBranch("MuMuGamma");
		TRootSignalEvent* mcSignalEvent = 0;
		mcSignalEvent_br->SetAddress(&mcSignalEvent);
	}
	
	if(doMC)
	{
		TBranch* mcParticles_br = (TBranch *) eventTree->GetBranch("MCParticles");
		TClonesArray* mcParticles = new TClonesArray("TRootParticle", 0);
		mcParticles_br->SetAddress(&mcParticles);
	}
	
	if(doPhotonConversionMC)
	{
		TBranch* mcPhotons_br = (TBranch *) eventTree->GetBranch("MCPhotons");
		TClonesArray* mcPhotons = new TClonesArray("TRootMCPhoton", 0);
		mcPhotons_br->SetAddress(&mcPhotons);
	}
	
	if(doTrack)
	{
		TBranch* tracks_br = (TBranch *) eventTree->GetBranch("Tracks");
		TClonesArray* tracks = new TClonesArray("TRootTrack", 0);
		tracks_br->SetAddress(&tracks);
		
	}

	if(doJet)
	{
		TBranch* jets_br = (TBranch *) eventTree->GetBranch("Jets");
		TClonesArray* jets = new TClonesArray("TRootJet", 0);
		jets_br->SetAddress(&jets);
	}

	
	if(doMuon)
	{
		TBranch* muons_br = (TBranch *) eventTree->GetBranch("Muons");
		TClonesArray* muons = new TClonesArray("TRootMuon", 0);
		muons_br->SetAddress(&muons);
	}
		
	if(doElectron)
	{

		TBranch* electrons_br = (TBranch *) eventTree->GetBranch("Electrons");
		TClonesArray* electrons = new TClonesArray("TRootElectron", 0);
		electrons_br->SetAddress(&electrons);
	}
				
	if(doPhoton)
	{
		TBranch* photons_br = (TBranch *) eventTree->GetBranch("Photons");
		TClonesArray* photons = new TClonesArray("TRootPhoton", 0);
		photons_br->SetAddress(&photons);
	}
		
	if(doCluster)
	{
		TBranch* clusters_br = (TBranch *) eventTree->GetBranch("BasicClusters");
		TClonesArray* clusters = new TClonesArray("TRootCluster", 0);
		clusters_br->SetAddress(&clusters);
	
		TBranch* superClusters_br = (TBranch *) eventTree->GetBranch("SuperClusters");
		TClonesArray* superClusters = new TClonesArray("TRootSuperCluster", 0);
		superClusters_br->SetAddress(&superClusters);
	}
	
	if(doPhotonConversion)
	{
		TBranch* conversions_br = (TBranch *) eventTree->GetBranch("ConversionTracks");
		TClonesArray* conversionTracks = new TClonesArray("TRootTrack", 0);
		conversions_br->SetAddress(&conversionTracks);
	}
	
	
	// HLT Run Summary
	if (doHLT)
	{
		cout << "runTree->GetEntries()="<<runTree->GetEntries()<<endl;
		runTree->GetEvent(0);
		cout << dec << endl;
		cout << "HLT-Report " << "---------- Event  Summary ------------\n";
		cout << "HLT-Report"
				<< " Events total = " << runInfos->nHLTEvents()
				<< "  wasrun = " << runInfos->nHLTWasRun()
				<< "  passed = " << runInfos->nHLTAccept()
				<< "  errors = " << runInfos->nHLTErrors()
				<< "\n";

		cout << endl;
		cout << "HLT-Report " << "---------- HLTrig Summary ------------\n";
		cout << "HLT-Report   HLT Bit#     WasRun     Passed     Errors  Name\n";

		for (unsigned int i=0; i!=runInfos->nHLTPaths(); ++i)
		{
			printf("HLT-Report %10u %10u %10u %10u  ", i, runInfos->hltWasRun(i), runInfos->hltAccept(i), runInfos->hltErrors(i));
			cout << runInfos->hltNames(i) << endl;
		}

		cout << endl;
	}


	TH1F* h1 = new TH1F("Et_all_photons","Et_all_photons", 200, 0, 50);

	unsigned int nEvents = (int)eventTree->GetEntries();
	//unsigned int nEvents = 2;
	
	for(unsigned int ievt=0; ievt<nEvents; ievt++)
	{
		eventTree->GetEvent(ievt);
		cout <<"event "<< ievt <<endl;
		cout<<"event->nb()="<<event->nb()<<endl;
		if (isCSA07Soup) cout << "CSA07 Soup:  pid=" << event->csa07id() << " - " << event->csa07process() << " - weight=" << event->csa07weight() << endl;

		if (doHLT)
		{
			for(unsigned int ipath=36; ipath<40; ipath++) cout << "   " << runInfos->hltNames(ipath) << " decision=" << event->trigHLT(ipath) <<endl;
		}

	/*
	// Z->mumu gamma  infos at generator level
		
		TRootParticle* muplus = mcSignalEvent->muplus();
		TRootParticle* muminus = mcSignalEvent->muminus();
		TRootParticle* mumu = new TRootParticle();
		(*mumu) = (*muplus) + (*muminus);
		cout << "mu+ Et=" << muplus->Et() << endl;
		cout << "mu- Et=" << muminus->Et() << endl;
	
		TRootParticle* mumuifsr = new TRootParticle();
		TRootParticle* mumufsr = new TRootParticle();
		(*mumufsr) += (*mumu);
		(*mumuifsr) += (*mumu);
		for(unsigned int ifsr = 0; ifsr < mcSignalEvent->nFSR(); ++ifsr )
		{
		TRootParticle* fsr = mcSignalEvent->photonFSR(ifsr);
		(*mumufsr) += (*fsr);
		(*mumuifsr) += (*fsr);
		cout << "FSR("<<ifsr<<") Et=" << fsr->Et() << endl;
		delete fsr;
	}
	
		TRootParticle* mumuisr = new TRootParticle();
		(*mumuisr) += (*mumu);
		for(unsigned int iisr = 0; iisr < mcSignalEvent->nISR(); ++iisr )
		{
		TRootParticle* isr = mcSignalEvent->photonISR(iisr);
		(*mumuisr) += (*isr);
		(*mumuifsr) += (*isr);
		cout << "ISR("<<iisr<<") Et=" << isr->Et() << endl;
		delete isr;
	}
	
		cout << "mumu Et=" << mumu->Et() << " m=" << mumu->M() << endl;
		if ( mcSignalEvent->nISR()>0 ) cout << "mumu+ISR Et=" << mumuisr->Et() << " m=" << mumuisr->M()  << endl;
		if ( mcSignalEvent->nFSR()>0 ) cout << "mumu+FSR Et=" << mumufsr->Et() << " m=" << mumufsr->M()  << endl;
		if ( mcSignalEvent->nISR()>0 && mcSignalEvent->nFSR()>0) cout << "mumu+ISR+FSR Et=" << mumuifsr->Et() << " m=" << mumuifsr->M()  << endl;
	*/
	/*
		if (doPhotonConversionMC)
		{
			cout << "Number of MC photons in event: " << mcPhotons->GetEntriesFast() << endl;
			TRootMCPhoton* myMCphoton;
			for (int imcphoton=0; imcphoton< mcPhotons->GetEntriesFast(); imcphoton++)
			{
				myMCphoton = (TRootMCPhoton*) mcPhotons->At(imcphoton);
				cout 
					<< "Converted TRootMCPhoton["<< imcphoton << "] "
					<<	" (Et,eta,phi)=("<< myMCphoton->Et() <<","<< myMCphoton->Eta() <<","<< myMCphoton->Phi() << ")"
					<< " photon-vertex=("<< myMCphoton->vx() <<","<< myMCphoton->vy() <<","<< myMCphoton->vz() << ")"
					<< " conversion-vertex=("<< myMCphoton->conv_vx() <<","<< myMCphoton->conv_vy() <<","<< myMCphoton->conv_vz() << ")"
					<< " nTracks=" << myMCphoton->nTracks()
					<< " convMass=" << myMCphoton->convMass()
					<< " convEoverP=" << myMCphoton->convEoverP()
					<< " convPtOverEt=" << myMCphoton->convPtOverEt()
					<< " convCotanTheta=" << myMCphoton->convDeltaCotanTheta()
					<< endl;
			}
		}
	*/

		cout << endl << "Photon list..." << endl;
		TRootPhoton* myphoton;
		for (int iphoton=0; iphoton< photons->GetEntriesFast(); iphoton++)
		{
			myphoton = (TRootPhoton*) photons->At(iphoton);
			cout << "   [" << iphoton << "]"; myphoton->Print(); cout << " nConvTracks=" << myphoton->convNTracks() << endl;
			if (myphoton->convNTracks()>0)
			{
				TRootTrack* convtrack1 = (TRootTrack*) myphoton->convTrack1();
				cout <<"  convtrack1 pt=" << convtrack1->Pt() << endl;
			}
			if (myphoton->superCluster() != 0 )
			{
				TRootSuperCluster* sc = (TRootSuperCluster*) myphoton->superCluster();
				cout << "      first associated SC has  Et=" << sc->Pt() << endl;
			}
			h1->Fill(myphoton->Et(),1);
		}

		cout << endl << "SuperClusters list..." << endl;
		TRootSuperCluster* mySC;
		for (int isc=0; isc< superClusters->GetEntriesFast(); isc++)
		{
			mySC = (TRootSuperCluster*) superClusters->At(isc);
			cout << "  SC[" << isc << "] of type" << mySC->type() << " with Et="<< mySC->Pt();
			if (mySC->isPhoton() )
			{
				TRootPhoton* phot = (TRootPhoton*) mySC->photon();
				cout << " is associated to photon Et=" << phot->Et() << endl;
			}
			else
			{
				cout << " is not a photon" << endl;
			}
		}


	} // fin boucle sur evts

	

	gStyle->SetOptStat(1110);

	TH1F* dummy = new TH1F();
	dummy->SetStats(true);
	dummy->SetLineWidth(1);
	dummy->SetLineColor(1);
	dummy->GetXaxis()->SetLabelSize(0.05);
	dummy->GetYaxis()->SetLabelSize(0.05);

	TCanvas *c00  = new TCanvas("c00"," ",800,500);
	c00->SetFillColor(0);
	c00->SetBorderMode(2);
	//c00->Divide(2,1);

	c00->cd(1);
	dummy = h1;
	dummy->Draw();
}
