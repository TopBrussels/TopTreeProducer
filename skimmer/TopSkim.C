#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <time.h>

#include "./tinyxml/tinyxml.h"

#include "../interface/TRootMuon.h"
#include "../interface/TRootCosmicMuon.h"
#include "../interface/TRootElectron.h"
#include "../interface/TRootJet.h"
#include "../interface/TRootPFJet.h"
#include "../interface/TRootCaloJet.h"
#include "../interface/TRootMET.h"
#include "../interface/TRootGenEvent.h"
#include "../interface/TRootNPGenEvent.h"
#include "../interface/TRootSpinCorrGen.h"
#include "../interface/TRootSignalEvent.h"
#include "../interface/TRootEvent.h"
#include "../interface/TRootRun.h"
#include "../interface/TRootParticle.h"
#include "../interface/TRootMCParticle.h"
#include "../interface/TRootSemiLepEvent.h"
#include "../interface/TRootTrack.h"

#include "TFile.h"
#include "TBranch.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TObjString.h"

struct keepObjects
{
	TBranch* inBranch;
	TClonesArray* inArray;
	TClonesArray* outArray;
	string name;
	string type;
	float minPt;
	float maxEta;
	bool skipObjects;
	int minNObjects;
};

vector<keepObjects> parseObjects(TiXmlDocument doc, TTree* inEventTree, TTree* outEventTree)
{
	vector<keepObjects> toKeep;
	TiXmlHandle hdl (&doc);
	TiXmlNode *node = 0;
	TiXmlElement *elem = 0;
	bool nodeFound = false;
	node = hdl.Node ();
	for( node = node->FirstChild(); node; node = node->NextSibling() )
	{
		if(node->Value () == string ("keepbranches"))
		{
			nodeFound = true;
			elem = node->FirstChildElement ();
			if(!elem)
			{
				cerr << "The node doesn't exist" << endl;
				delete node;
				delete elem;
			}
			while(elem)
			{
				keepObjects tempObj;
				tempObj.name = (TString) elem->Attribute("name");
				tempObj.type = (TString) elem->Attribute("type");
				
				tempObj.inBranch = (TBranch *) inEventTree->GetBranch((tempObj.name).c_str());
				tempObj.inArray = new TClonesArray((tempObj.type).c_str(), 0);
				tempObj.inBranch->SetAddress( &(tempObj.inArray) );
				
				tempObj.outArray = new TClonesArray((tempObj.type).c_str(), 1000);
				outEventTree->Branch ((tempObj.name).c_str(), "TClonesArray", &(tempObj.outArray) );
				
				elem->QueryFloatAttribute ("minPt", &(tempObj.minPt));
				elem->QueryFloatAttribute ("maxEta", &(tempObj.maxEta));
				
				int skipObj = 0, minNobj = 0;
				elem->QueryIntAttribute ("minNObjects", &(minNobj));
				tempObj.minNObjects = minNobj;
				elem->QueryIntAttribute ("skipObjects", &(skipObj));
				if(skipObj == 0)
					tempObj.skipObjects = false;
				else if(skipObj == 1)
					tempObj.skipObjects = true;
				else
					cerr << "Wrong skipObjects : " << skipObj << " for " << tempObj.name << endl;
				
				cout << "The skim will keep " << tempObj.name << ", of type " << tempObj.type << endl;
				cout << "With minPt = " << tempObj.minPt << " and maxEta = " << tempObj.maxEta << endl;
				if(tempObj.skipObjects)
					cout << "With skipObjects = true " << endl;
				else
					cout << "With skipObjects = false " << endl;

				toKeep.push_back(tempObj);
				
				if(tempObj.type == "TRootCosmicMuon") // prepare stuff for storage of the CosmicMuonTracks
				{
					keepObjects tempObj1, tempObj2, tempObj3;
					string muonType = "";
					
					if(tempObj.name == "CosmicMuons_muons") muonType = "muons";
					else if(tempObj.name == "CosmicMuons_muons1Leg") muonType = "muons1Leg";
					else if(tempObj.name == "CosmicMuons_muonsBarrelOnly") muonType = "muonsBarrelOnly";
					else if(tempObj.name == "CosmicMuons_muons1LegBarrelOnly") muonType = "muons1LegBarrelOnly";
					
					tempObj1.name = "CosmicMuonGlobalTracks_" + muonType;
					tempObj1.type = "TRootTrack";
					
					tempObj1.inBranch = (TBranch *) inEventTree->GetBranch((tempObj1.name).c_str());
					tempObj1.inArray = new TClonesArray((tempObj1.type).c_str(), 0);
					tempObj1.inBranch->SetAddress( &(tempObj1.inArray) );
					
					tempObj1.outArray = new TClonesArray((tempObj1.type).c_str(), 1000);
					outEventTree->Branch ((tempObj1.name).c_str(), "TClonesArray", &(tempObj1.outArray) );
					toKeep.push_back(tempObj1);
					
					tempObj2.name = "CosmicMuonTrackerTracks_" + muonType;
					tempObj2.type = "TRootTrack";
					
					tempObj2.inBranch = (TBranch *) inEventTree->GetBranch((tempObj2.name).c_str());
					tempObj2.inArray = new TClonesArray((tempObj2.type).c_str(), 0);
					tempObj2.inBranch->SetAddress( &(tempObj2.inArray) );
					
					tempObj2.outArray = new TClonesArray((tempObj2.type).c_str(), 1000);
					outEventTree->Branch ((tempObj2.name).c_str(), "TClonesArray", &(tempObj2.outArray) );
					toKeep.push_back(tempObj2);
					
					tempObj3.name = "CosmicMuonStandAloneTracks_" + muonType;
					tempObj3.type = "TRootTrack";
					
					tempObj3.inBranch = (TBranch *) inEventTree->GetBranch((tempObj3.name).c_str());
					tempObj3.inArray = new TClonesArray((tempObj3.type).c_str(), 0);
					tempObj3.inBranch->SetAddress( &(tempObj3.inArray) );
					
					tempObj3.outArray = new TClonesArray((tempObj3.type).c_str(), 1000);
					outEventTree->Branch ((tempObj3.name).c_str(), "TClonesArray", &(tempObj3.outArray) );
					toKeep.push_back(tempObj3);
					
				}
				
				elem = elem->NextSiblingElement ();	// iteration 
			}
		}
	}

	if(!nodeFound)
	{
		cerr << "The node doesn't exist" << endl;
		delete node;
		delete elem;
	}
	
	return toKeep;
}

TString parseFileName(TiXmlDocument doc, string name)
{
	TString inFileName;
	TiXmlHandle hdl (&doc);
	TiXmlNode *node = 0;
	TiXmlElement *elem = 0;
	bool nodeFound = false;
	node = hdl.Node ();
	for( node = node->FirstChild(); node; node = node->NextSibling() )
	{
		if (node->Value () == string (name))
		{
			nodeFound = true;
			elem = node->FirstChildElement ();
			if(!elem)
			{
				cerr << "The node doesn't exist" << endl;
				delete node;
				delete elem;
				return 3;
			}
			while (elem)
			{
				inFileName = (TString) elem->Attribute("file");
				elem = elem->NextSiblingElement ();	// iteration 
			}
		}
	}

	if(!nodeFound)
	{
		cerr << "The node doesn't exist" << endl;
		delete node;
		delete elem;
		return 2;
	}
	return inFileName;
}

int main()
{
	clock_t start = clock();

	// set verbosity equal to 0 (silent), 1 or 2 (debug)
	unsigned int verbosity = 0;

	// xml file
	char xmlfile[]="skim.xml";
	
	TiXmlDocument doc (xmlfile);
	
	if(!doc.LoadFile())
	{
		cerr << "Error while loading the xml file: " << xmlfile <<endl;
		cerr << " error #" << doc.ErrorId () << " : " << doc.ErrorDesc () << endl;
      return 1;
	}
	
	TString inFileName = parseFileName(doc, "inputdatasets");
	
	TString outFileName = parseFileName(doc, "outputfilename");

	cout << "input file: " << inFileName << endl;

	TFile* inFile = TFile::Open(inFileName);
	
	TTree* inRunTree = (TTree*) inFile->Get("runTree");

	TBranch* inRunBranch = (TBranch *) inRunTree->GetBranch("runInfos");
	TRootRun* inRunInfos = 0;
	inRunBranch->SetAddress(&inRunInfos);

	TTree* inEventTree = (TTree*) inFile->Get("eventTree");
	
	TBranch* inEventBranch = (TBranch *) inEventTree->GetBranch("Event");
	TRootEvent* inEvent = 0;
	inEventBranch->SetAddress(&inEvent);
	
	cout << "output file: " << outFileName << endl;

	TFile* outFile = new TFile(outFileName, "Recreate");
	outFile->cd();

	TRootRun* outRunInfos = 0;
	TTree* outRunTree = new TTree("runTree", "Global Run Infos");
	outRunTree->Branch("runInfos", "TRootRun", &outRunInfos);
	
	if( verbosity > 0 ) cout << "inRunTree->GetEntries()=" << inRunTree->GetEntries()<<endl;
	inRunTree->GetEvent(0);
	outRunInfos = inRunInfos;
	
	TRootEvent* outRootEvent = 0;
	TTree* outEventTree = new TTree("eventTree", "Event Infos");
	outEventTree->Branch ("Event", "TRootEvent", &outRootEvent);
	
	cout << "Parsing objectsToKeep from xml file..." << endl;
	
	//	parse input objects from xml
	vector<keepObjects> objectsToKeep = parseObjects(doc, inEventTree, outEventTree);
	
	if( verbosity > 0 ) cout << "objectsToKeep.size() = " << objectsToKeep.size() << endl;
	
	// Prepare userInfo to be added to the outEventTree
	string info = "This TopTree was skimmed with the following properties:\n";

	for(unsigned int j=0; j !=objectsToKeep.size(); j++)
	{
		stringstream tmpMinPt, tmpMaxEta, tmpMinNObjects;
		tmpMinPt << objectsToKeep[j].minPt;
		tmpMaxEta << objectsToKeep[j].maxEta;
		tmpMinNObjects << objectsToKeep[j].minNObjects;

		info += "name = " + objectsToKeep[j].name + "  type = " + objectsToKeep[j].type;
		info += "  minPt = " + tmpMinPt.str() + "  maxEta = " + tmpMaxEta.str();
		if(objectsToKeep[j].skipObjects) info += "  skipObjects = 1";
		else info += "  skipObjects = 0";
		info += "  minNObjects = " + tmpMinNObjects.str() + "\n";
	}
	
	// Add UserInfo to outEventTree
	TObjString* userInfo = new TObjString();
	userInfo->SetString(info.c_str());
	
	cout << "userInfo that will be added to the outEventTree:\n" << userInfo->GetString() << endl;
	
	outEventTree->GetUserInfo()->Add( userInfo );
	
	//loop over events
	unsigned int nEvents = (int) inEventTree->GetEntries();
	unsigned int nOutEvents = 0;

	for(unsigned int ievt=0; ievt<nEvents; ievt++)
	{
		inEventTree->GetEvent(ievt);
		if((int) ievt/10000 == (double) ievt/10000)  cout << ">>> analyzing event " << ievt << endl;
		
		if( verbosity > 1 ) cout << ">>> analyzing event " << ievt << endl;
		
		outFile->cd();
		
		outRootEvent = inEvent;
		
		bool keepEvent = true;
		
		for(unsigned int j=0; j !=objectsToKeep.size(); j++)
		{
			if(ievt == 0)
			{
				if( verbosity > 0 )
				{
					cout << "objectsToKeep[" << j << "] : " <<endl;
					cout << "name = " << objectsToKeep[j].name << " type = " << objectsToKeep[j].type << endl;
					cout << "minPt = " << objectsToKeep[j].minPt << " maxEta = " << objectsToKeep[j].maxEta << endl;
					if(objectsToKeep[j].skipObjects) cout << "skipObjects = true" << endl;
					else cout << "skipObjects = false" << endl;
				}
			}

			if(objectsToKeep[j].type == "TRootPFJet")
			{
				TRootPFJet* pfJet;
				int pfJetsKeeped=0;
				for(int i=0; i<(objectsToKeep[j].inArray)->GetEntriesFast(); i++)
				{
					pfJet = (TRootPFJet*) (objectsToKeep[j].inArray)->At(i);
					bool keepPFJet = true;
					
					if(pfJet->Pt() < objectsToKeep[j].minPt || fabs(pfJet->Eta()) > objectsToKeep[j].maxEta)
					{
						if(objectsToKeep[j].skipObjects)
						{
							keepPFJet = false;
							if( verbosity > 1 ) cout << "skip jet with pT = " << pfJet->Pt() << " and eta = " << pfJet->Eta() << endl;
						}
					}

					if(keepPFJet)
					{
						new( (*(objectsToKeep[j].outArray))[pfJetsKeeped] ) TRootPFJet(*pfJet);			
						pfJetsKeeped++;
					}
				}
				
				if(pfJetsKeeped < objectsToKeep[j].minNObjects)
				{
					keepEvent = false;
					if( verbosity > 1 ) cout << "Too small number of selected jets: pfJetsKeeped = " << pfJetsKeeped << endl;
				}
				
				if( verbosity > 1 ) cout << "Processed " << objectsToKeep[j].name << endl;
				if( verbosity > 1 ) cout << "input = " << (objectsToKeep[j].inArray)->GetEntriesFast() << " output = " << (objectsToKeep[j].outArray)->GetEntriesFast() << endl;
				
			}

			else if(objectsToKeep[j].type == "TRootCaloJet")
			{
				TRootCaloJet* caloJet;
				int caloJetsKeeped=0;
				for(int i=0; i<(objectsToKeep[j].inArray)->GetEntriesFast(); i++)
				{
					caloJet = (TRootCaloJet*) (objectsToKeep[j].inArray)->At(i);
					bool keepCaloJet = true;
					
					if(caloJet->Pt() < objectsToKeep[j].minPt || fabs(caloJet->Eta()) > objectsToKeep[j].maxEta)
					{
						if(objectsToKeep[j].skipObjects)
						{
							keepCaloJet = false;
							if( verbosity > 1 ) cout << "skip jet with pT = " << caloJet->Pt() << " and eta = " << caloJet->Eta() << endl;
						}
					}

					if(keepCaloJet)
					{
						new( (*(objectsToKeep[j].outArray))[caloJetsKeeped] ) TRootCaloJet(*caloJet);			
						caloJetsKeeped++;
					}
				}
				
				if(caloJetsKeeped < objectsToKeep[j].minNObjects)
				{
					keepEvent = false;
					if( verbosity > 1 ) cout << "Too small number of selected caloJets: caloJetsKeeped = " << caloJetsKeeped << endl;
				}
				
				if( verbosity > 1 ) cout << "Processed " << objectsToKeep[j].name << endl;
				if( verbosity > 1 ) cout << "input = " << (objectsToKeep[j].inArray)->GetEntriesFast() << " output = " << (objectsToKeep[j].outArray)->GetEntriesFast() << endl;
				
			}
			
			else if(objectsToKeep[j].type == "TRootMCParticle")
			{
				TRootMCParticle* mcparticle;
				int mcparticlesKeeped=0;
				for(int i=0; i<(objectsToKeep[j].inArray)->GetEntriesFast(); i++)
				{
					mcparticle = (TRootMCParticle*) (objectsToKeep[j].inArray)->At(i);
					bool keepMCParticle = true;
					
					if(mcparticle->Pt() < objectsToKeep[j].minPt || fabs(mcparticle->Eta()) > objectsToKeep[j].maxEta)
					{
						if(objectsToKeep[j].skipObjects)
						{
							keepMCParticle = false;
							if( verbosity > 1 ) cout << "skip MCparticle with pT = " << mcparticle->Pt() << " and eta = " << mcparticle->Eta() << endl;
						}
					}
					
					if(keepMCParticle)
					{
						new( (*(objectsToKeep[j].outArray))[mcparticlesKeeped] ) TRootMCParticle(*mcparticle);
						mcparticlesKeeped++;
					}
				}

				if(mcparticlesKeeped < objectsToKeep[j].minNObjects)
				{
					keepEvent = false;
					if( verbosity > 1 ) cout << "Too small number of selected MCparticles: mcparticlesKeeped = " << mcparticlesKeeped << endl;
				}

				if( verbosity > 1 ) cout << "Processed " << objectsToKeep[j].name << endl;
				if( verbosity > 1 ) cout << "input = " << (objectsToKeep[j].inArray)->GetEntriesFast() << " output = " << (objectsToKeep[j].outArray)->GetEntriesFast() << endl;
			}
			
			else if(objectsToKeep[j].type == "TRootMET")
			{
				TRootMET* met;
				int METKeeped=0;
				met = (TRootMET*) (objectsToKeep[j].inArray)->At(0);
				bool keepMET = true;
				
				if(met->Pt() < objectsToKeep[j].minPt || fabs(met->Eta()) > objectsToKeep[j].maxEta)
				{
					if(objectsToKeep[j].skipObjects)
					{
						keepMET = false;
						if( verbosity > 1 ) cout << "skip MET with pT = " << met->Pt() << " and eta = " << met->Eta() << endl;
					}
				}
				
				if(keepMET)
				{
					new( (*(objectsToKeep[j].outArray))[0] ) TRootMET(*met);
					METKeeped++;
				}

				if(METKeeped < objectsToKeep[j].minNObjects)
				{
					keepEvent = false;
					if( verbosity > 1 ) cout << "Too small number of selected MET: METKeeped = " << METKeeped << endl;
				}

				if( verbosity > 1 ) cout << "Processed " << objectsToKeep[j].name << endl;
				if( verbosity > 1 ) cout << "input = " << (objectsToKeep[j].inArray)->GetEntriesFast() << " output = " << (objectsToKeep[j].outArray)->GetEntriesFast() << endl;
			}
			
			else if(objectsToKeep[j].type == "TRootElectron")
			{
				TRootElectron* electron;
				int electronsKeeped=0;
				for(int i=0; i<(objectsToKeep[j].inArray)->GetEntriesFast(); i++)
				{
					electron = (TRootElectron*) (objectsToKeep[j].inArray)->At(i);
					bool keepElectron = true;
					
					if(electron->Pt() < objectsToKeep[j].minPt || fabs(electron->Eta()) > objectsToKeep[j].maxEta)
					{
						if(objectsToKeep[j].skipObjects)
						{
							keepElectron = false;
							if( verbosity > 1 ) cout << "skip Electron with pT = " << electron->Pt() << " and eta = " << electron->Eta() << endl;
						}
					}
					
					if(keepElectron)
					{
						new( (*(objectsToKeep[j].outArray))[electronsKeeped] ) TRootElectron(*electron);
						electronsKeeped++;
					}
				}

				if(electronsKeeped < objectsToKeep[j].minNObjects)
				{
					keepEvent = false;
					if( verbosity > 1 ) cout << "Too small number of selected Electrons: electronsKeeped = " << electronsKeeped << endl;
				}

				if( verbosity > 1 ) cout << "Processed " << objectsToKeep[j].name << endl;
				if( verbosity > 1 ) cout << "input = " << (objectsToKeep[j].inArray)->GetEntriesFast() << " output = " << (objectsToKeep[j].outArray)->GetEntriesFast() << endl;
			}
			
			else if(objectsToKeep[j].type == "TRootMuon")
			{
				TRootMuon* muon;
				int muonsKeeped=0;
				for(int i=0; i<(objectsToKeep[j].inArray)->GetEntriesFast(); i++)
				{
					muon = (TRootMuon*) (objectsToKeep[j].inArray)->At(i);
					bool keepMuon = true;
					
					if(muon->Pt() < objectsToKeep[j].minPt || fabs(muon->Eta()) > objectsToKeep[j].maxEta)
					{
						if(objectsToKeep[j].skipObjects)
						{
							keepMuon = false;
							if( verbosity > 1 ) cout << "skip Muon with pT = " << muon->Pt() << " and eta = " << muon->Eta() << endl;
						}
					}
					
					if(keepMuon)
					{
						new( (*(objectsToKeep[j].outArray))[muonsKeeped] ) TRootMuon(*muon);
						muonsKeeped++;
					}
				}

				if(muonsKeeped < objectsToKeep[j].minNObjects)
				{
					keepEvent = false;
					if( verbosity > 1 ) cout << "Too small number of selected Muons: muonsKeeped = " << muonsKeeped << endl;
				}

				if( verbosity > 1 ) cout << "Processed " << objectsToKeep[j].name << endl;
				if( verbosity > 1 ) cout << "input = " << (objectsToKeep[j].inArray)->GetEntriesFast() << " output = " << (objectsToKeep[j].outArray)->GetEntriesFast() << endl;
			}
			
			else if(objectsToKeep[j].type == "TRootCosmicMuon")
			{
				TRootCosmicMuon* muon;
				int cosmicMuonsKeeped=0;
				for(int i=0; i<(objectsToKeep[j].inArray)->GetEntriesFast(); i++)
				{
					muon = (TRootCosmicMuon*) (objectsToKeep[j].inArray)->At(i);
					bool keepCosmicMuon = true;
					
					if(muon->Pt() < objectsToKeep[j].minPt || fabs(muon->Eta()) > objectsToKeep[j].maxEta)
					{
						if(objectsToKeep[j].skipObjects)
						{
							keepCosmicMuon = false;
							if( verbosity > 1 ) cout << "skip CosmicMuon with pT = " << muon->Pt() << " and eta = " << muon->Eta() << endl;
						}
					}
					
					if(keepCosmicMuon)
					{
						int nCosmicMuonGlobalTracks = 0;
						if(muon->globalTrack() != NULL)
						{
							TRootTrack* track = (TRootTrack*) muon->globalTrack();
							new( (*(objectsToKeep[j+1].outArray))[cosmicMuonsKeeped] ) TRootTrack(*track);
					
							muon->SetGlobalTrack( (TObject*) (objectsToKeep[j+1].outArray)->At(nCosmicMuonGlobalTracks));
				
							nCosmicMuonGlobalTracks++;
						}
					
						int nCosmicMuonTrackerTracks = 0;
						if(muon->trackerTrack() != NULL)
						{
							TRootTrack* track = (TRootTrack*) muon->trackerTrack();
							new( (*(objectsToKeep[j+2].outArray))[cosmicMuonsKeeped] ) TRootTrack(*track);
				
							muon->SetGlobalTrack( (TObject*) (objectsToKeep[j+2].outArray)->At(nCosmicMuonTrackerTracks));
				
							nCosmicMuonTrackerTracks++;
						}
					
						int nCosmicMuonStandaloneTracks = 0;
						if(muon->trackerTrack() != NULL)
						{
							TRootTrack* track = (TRootTrack*) muon->trackerTrack();
							new( (*(objectsToKeep[j+3].outArray))[cosmicMuonsKeeped] ) TRootTrack(*track);
				
							muon->SetGlobalTrack( (TObject*) (objectsToKeep[j+3].outArray)->At(nCosmicMuonStandaloneTracks));
				
							nCosmicMuonStandaloneTracks++;
						}
					
						new( (*(objectsToKeep[j].outArray))[cosmicMuonsKeeped] ) TRootCosmicMuon(*muon);
						cosmicMuonsKeeped++;
					}
				}

				if(cosmicMuonsKeeped < objectsToKeep[j].minNObjects)
				{
					keepEvent = false;
					if( verbosity > 1 ) cout << "Too small number of selected CosmicMuons: cosmicMuonsKeeped = " << cosmicMuonsKeeped << endl;
				}

				if( verbosity > 1 ) cout << "Processed " << objectsToKeep[j].name << endl;
				if( verbosity > 1 ) cout << "input = " << (objectsToKeep[j].inArray)->GetEntriesFast() << " output = " << (objectsToKeep[j].outArray)->GetEntriesFast() << endl;
			}
			else
				cerr << "Unknown type: " << objectsToKeep[j].type << endl;
		}
		
		if(keepEvent)
		{
			nOutEvents++; // nr of output events

			if( verbosity > 1 ) cout << "Filling the outEventTree" << endl;
			
			outEventTree->Fill();
		}
		
		for(vector<keepObjects>::const_iterator iter=objectsToKeep.begin(); iter!=objectsToKeep.end(); iter++)
		{
//			if( verbosity > 1 ) cout << "(iter->outArray)->GetEntriesFast() = "  << (iter->outArray)->GetEntriesFast() << endl;
//			if( verbosity > 1 ) cout << "iter->outArray: " << iter->outArray << endl;
			( *(iter->outArray) ).Delete();
		}
		
	}

	cout << "Filling outRunTree" << endl;
	
	outRunTree->Fill();

	cout << "Writing to output file" << endl;

	outFile->Write();
	
	cout << "Closing output file" << endl;
	
	outFile->Close();

//	WARNING! Don't remove or modify the next line!!! The Automatic TopTree Producer depends on it!
	cout << "--> Skimmed " << nOutEvents << " out of a total of " << nEvents << " events" << endl;

	if (((double)clock() - start) / CLOCKS_PER_SEC < 60)
		cout << "--> The skimming took " << ((double)clock() - start) / CLOCKS_PER_SEC << " seconds." << endl;
	
	else
		cout << "--> The skimming took " << (((double)clock() - start) / CLOCKS_PER_SEC)/60 << " minutes." << endl;
	
	cout << "Code running was succesfull!" << endl;
     
	return(0);
}
