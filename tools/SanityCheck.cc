// HOW TO COMPILE
//
// g++  -L../src -l Toto -I `root-config --incdir` `root-config --libs` SanityCheck.cc -o SanityCheck
//

#include <iomanip>

#include "../interface/TRootGenEvent.h"
#include "../interface/TRootEvent.h"
#include "../interface/TRootRun.h"

#include "../interface/TRootMuon.h"
#include "../interface/TRootElectron.h"

#include "../interface/TRootJet.h"
#include "../interface/TRootCaloJet.h"
#include "../interface/TRootJPTJet.h"
#include "../interface/TRootPFJet.h"

#include "../interface/TRootMET.h"
#include "../interface/TRootCaloMET.h"
#include "../interface/TRootPFMET.h"

#include "../interface/TRootParticle.h"
#include "../interface/TRootMCParticle.h"
#include "../interface/TRootVertex.h"
#include "../interface/TRootHLTInfo.h"

#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TTree.h>
#include <TChain.h>
#include <TClonesArray.h>

#include <fstream>
#include <sstream>

#include <sys/stat.h>

using namespace TopTree;
using namespace std;

void Tokenize(const string& str,
                      vector<string>& tokens,
                      const string& delimiters = " ")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}


int main(int argc, char *argv[]){

  std::map<std::string, TH1F* > histos;

  std::map<std::string, std::pair<std::string,TClonesArray*> > arrays;

  std::vector<TClonesArray*> objects;
    
  int verbosity                 = 5;
  //0 muet
  //1 Main Info
  //2
  //3 
  //4 Info for each event
  //5 Debug

  bool onlyPU = false;

   // RETRIEVING LIST OF FILENAMES TO CHECK

  if (argc < 3) {

    cout << "Usage: ./SanityCheck --inputfiles file1;file2;fileN (--onlyPU)\n\n" << endl;

    exit(0);

  } else if (argc == 3 && !strstr(argv[1],"--inputfiles")) {

    cout << "Usage: ./SanityCheck --inputfiles file1;file2;fileN (--onlyPU)\n\n" << endl;

    exit(0);

  }

  for (unsigned int i=0;i<argc;i++)
    if (strstr(argv[i],"--onlyPU"))
      onlyPU=true;

  vector<string> fileNames;
  
  Tokenize(argv[2], fileNames, ";");

  if (fileNames.size() == 1) {

    if (!strstr(fileNames[0].c_str(),".root")) {

      cout << "A file containing a file-list was provided" << endl;

      fileNames.clear();

      string line;
      ifstream myfile (argv[2]);
      if (myfile.is_open())
	{
	  while ( myfile.good() )
	    {
	      getline (myfile,line);
	      if (strstr(line.c_str(),".root")) 
		fileNames.push_back((string)line);
	    }
	  myfile.close();
	}
      
      else cout << "Unable to open file"; 


    }

  }

  // CHECKING THE FILECONTENT FOR FILE 0 AND COUNT EVENTS FOR ALL FILES

  unsigned int nEvents = 0; 

  if (verbosity > 0) cout << "Declaring TChains" << endl;
  TChain* eventTree = new TChain("eventTree");
  TChain* runTree = new TChain("runTree");


  for (int fileID=0; fileID < fileNames.size(); fileID++) {
  
    if (verbosity > 0) cout << "Adding file " << fileNames.at(fileID) <<  endl;

    /*TFile* f = TFile::Open(fileNames.at(fileID).c_str());
    
    TTree* runTree = (TTree*) f->Get("runTree");
    TTree* eventTree = (TTree*) f->Get("eventTree");
    
    TBranch* run_br = (TBranch *) runTree->GetBranch("runInfos");
    TRootRun* runInfos = 0;
    run_br->SetAddress(&runInfos);
    
    TBranch* event_br = (TBranch *) eventTree->GetBranch("Event");
    TRootEvent* event = 0;
    event_br->SetAddress(&event);*/

    eventTree->Add(fileNames.at(fileID).c_str());
    runTree->Add(fileNames.at(fileID).c_str());
    
    nEvents += eventTree->GetEntriesFast();
      
  }

  TRootRun* runInfos = new TRootRun();
  runTree->SetBranchStatus("runInfos*",1);
  runTree->SetBranchAddress("runInfos",&runInfos);

  TRootEvent* event = new TRootEvent();
  eventTree->SetBranchStatus("Event*",1);
  eventTree->SetBranchAddress("Event",&event);

  if (verbosity > 0) cout << "Searching the TBranches" << endl;

  int nArrays = 0;
  TClonesArray* myArrays[2000];
  string myArrayClass[2000];
  string myArrayName[2000];

  for (int i=1; i<eventTree->GetListOfBranches()->GetEntriesFast(); i++) {
    
    TBranch * branch = (TBranch *)eventTree->GetListOfBranches()->At(i);
    
    TObject* obj = branch->GetListOfLeaves()->At(0);
    
    std::string ObjName = obj->GetName();

    if (onlyPU && !strstr(ObjName.c_str(),"PrimaryVertex")) continue;
    
    string::size_type position = ObjName.find_last_of("_");
    
    std::string className = "";
    
    if (strstr(ObjName.c_str(),"CaloJet"))
      className="TopTree::TRootCaloJet";
    else if (strstr(ObjName.c_str(),"PFJet"))
      className="TopTree::TRootPFJet";
    else if (strstr(ObjName.c_str(),"JPTJet"))
      className="TopTree::TRootJPTJet";
    else if (strstr(ObjName.c_str(),"GenJet"))
      className="TopTree::TRootGenJet";
    else if (strstr(ObjName.c_str(),"MCParticles"))
      className="TopTree::TRootMCParticle";
    else if (strstr(ObjName.c_str(),"NPGenEvent"))
      className="TopTree::TRootNPGenEvent";
    else if (strstr(ObjName.c_str(),"GenEvent"))
      className="TopTree::TRootGenEvent";
    else if (strstr(ObjName.c_str(),"Muon"))
      className="TopTree::TRootMuon";
    else if (strstr(ObjName.c_str(),"Electron"))
      className="TopTree::TRootElectron";
    else if (strstr(ObjName.c_str(),"TCMET"))
      className="TopTree::TRootMET";
    else if (strstr(ObjName.c_str(),"CaloMET"))
	className="TopTree::TRootCaloMET";
    else if (strstr(ObjName.c_str(),"PFMET"))
      className="TopTree::TRootPFMET";
    else if (strstr(ObjName.c_str(),"MET"))
      className="TopTree::TRootMET";
    else if (strstr(ObjName.c_str(),"MHT"))
      className="TopTree::TRootMHT";
    else if (strstr(ObjName.c_str(),"PrimaryVertex"))
      className="TopTree::TRootVertex";
    
    if (verbosity > 1) cout << "  Found Branch " << className << " " << ObjName.substr(0,position) << endl;
      
    arrays[ObjName.substr(0,position)]=std::pair<std::string,TClonesArray*>(className,new TClonesArray());
    
    char branchStatus[100];
    myArrays[nArrays] = new TClonesArray(className.c_str(), 0);
    myArrayClass[nArrays]=className;
    myArrayName[nArrays]=ObjName.substr(0,position);
    
    string branchName = ObjName.substr(0,position);
    sprintf(branchStatus,"%s*",branchName.c_str());
    
    eventTree->SetBranchStatus(branchStatus,1);
    eventTree->SetBranchAddress(branchName.c_str(),&myArrays[nArrays]);
    
    nArrays++;
    
  } 

  /*char branchStatus[100];
  objects.push_back(new TClonesArray("TopTree::TRootMuon", 0));
  sprintf(branchStatus,"%s*","Muons_selectedPatMuons");
  eventTree->SetBranchStatus(branchStatus,1);
  eventTree->SetBranchAddress("Muons_selectedPatMuons",&objects[0]);*/

  //arrays["Muons_selectedPatMuons"]=std::pair<std::string,TClonesArray*>("TopTree::TRootMuon",objects[0]);

  if (verbosity > 1) cout << "eventTree->GetEntriesFast(): " << eventTree->GetEntries() << endl;
  if (verbosity > 1) cout << "runTree->GetEntriesFast(): " << runTree->GetEntries() << endl;

  if (verbosity > 0) cout << "Looping over " << eventTree->GetEntries() << " events " << endl;
  for(unsigned int ievt=0; ievt<eventTree->GetEntries(); ievt++) {
    //for(unsigned int ievt=0; ievt<1; ievt++) {

    eventTree->GetEntry(ievt);
    runTree->GetEntry(0);
    
    if (verbosity > 0 && ievt % 1000 == 0) std::cout<<"Processing the "<<ievt<<"th event." << flush<<"\r";

    // PileUp plot -> not yet in these toptrees

    string hist="pileup";
    if (histos.find(hist) == histos.end()) histos[hist]=new TH1F((hist).c_str(),(hist+";nPu").c_str(),76,-0.5,75.5);    
    histos[hist]->Fill(event->nPu(0));
    
    hist="kt6PFJetsPF2PAT_rho";
    if (histos.find(hist) == histos.end()) histos[hist]=new TH1F((hist).c_str(),hist.c_str(),80,0,40);
    histos[hist]->Fill(event->kt6PFJetsPF2PAT_rho());    
    
    
    for (unsigned int p=0; p<nArrays; p++) {
      
      //cout << myArrayClass[p] << " " << myArrayName[p] << " " << myArrays[p]->GetEntries() << endl;

      
      //
      // define global plots we want to see
      //
      
      string hist="";
      
      hist="_size";
      if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),100,0,100);
      
      for (unsigned int o=0; o<myArrays[p]->GetEntries(); o++) {
	
	// because c++ it not flexible we need to write the elaborate code below.... Sorry:'(
	
	//
	//
	// Dear object developer:) You can find some sample code here to add plots so all your changes will happen below this comment.....
	//
	//
	
	//
	// HLT
	//
	
	/* NO IMPLEMENTATION YET */
	
	//
	// PRIMARY VERTEX
	//
	
	if (strstr(myArrayClass[p].c_str(),"TopTree::TRootVertex")) {
	  
	  if(o==0) histos[myArrayName[p]+"_size"]->Fill(myArrays[p]->GetEntries());
	  
	}
	
	//
	// GenEvent
	//
	
	else if (strstr(myArrayClass[p].c_str(),"TopTree::TRootGenEvent") || strstr(myArrayClass[p].c_str(),"TopTree::TRootNPGenEvent")) {
	  
	  if(o==0) histos[myArrayName[p]+"_size"]->Fill(myArrays[p]->GetEntries());
	  
	}
	
	//
	// MCParticles
	//
	
	else if (strstr(myArrayClass[p].c_str(),"TopTree::TRootMCParticle")) {
	  
	  if(o==0) histos[myArrayName[p]+"_size"]->Fill(myArrays[p]->GetEntries());
	  
	}
	
	//
	// JETS
	//
	
	// now putting all jet types together, these can be addressed seperately in the future if needed
	else if (strstr(myArrayClass[p].c_str(),"TopTree::TRootGenJet") || strstr(myArrayClass[p].c_str(),"TopTree::TRootCaloJet") || strstr(myArrayClass[p].c_str(),"TopTree::TRootPFJet") || strstr(myArrayClass[p].c_str(),"TopTree::TRootJPTJet") ){
	  
	  if(o==0) histos[myArrayName[p]+"_size"]->Fill(myArrays[p]->GetEntries());
	  
	  // some local plots
	  hist="_pt";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,0,500);
	  hist="_eta";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),300,-6,6);	  
	  hist="_phi";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,-5,5);
	  
	  histos[myArrayName[p]+"_pt"]->Fill(((TRootJet*)myArrays[p]->At(o))->Pt());
	  histos[myArrayName[p]+"_eta"]->Fill(((TRootJet*)myArrays[p]->At(o))->Eta());
	  histos[myArrayName[p]+"_phi"]->Fill(((TRootJet*)myArrays[p]->At(o))->Phi());
	  
	}
	
	// 
	// MET
	//
	
	// now putting all met types together, these can be addressed seperately in the future if needed
	else if (strstr(myArrayClass[p].c_str(),"TopTree::TRootCaloMET") || strstr(myArrayClass[p].c_str(),"TopTree::TRootPFMET") || strstr(myArrayClass[p].c_str(),"TopTree::TRootMET") ){
	  
	  if(o==0) histos[myArrayName[p]+"_size"]->Fill(myArrays[p]->GetEntries());
	  
	  // some local plots
	  hist="_Et";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,0,500);
	  
	  histos[myArrayName[p]+"_Et"]->Fill(((TRootMET*)myArrays[p]->At(o))->Et());
	  
	  
	}
	
	//
	// MUON
	//
	
	else if (strstr(myArrayClass[p].c_str(),"TopTree::TRootMuon")){
	  
	  if(o==0) histos[myArrayName[p]+"_size"]->Fill(myArrays[p]->GetEntries());
	  
	  // some local plots
	  hist="_pt";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,0,500);
	  hist="_eta";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),300,-6,6);	  
	  hist="_phi";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,-5,5);
	  hist="_chargedHadronIso";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,-5,25);
	  hist="_photonIso";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,-5,25);
	  hist="_neutralHadronIso";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,-5,25);
	  hist="_nofValidPixelHits";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),15,0,15);
	  hist="_nofMatchedStations";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),15,0,15);
	  
	  histos[myArrayName[p]+"_pt"]->Fill(((TRootMuon*)myArrays[p]->At(o))->Pt());
	  histos[myArrayName[p]+"_eta"]->Fill(((TRootMuon*)myArrays[p]->At(o))->Eta());
	  histos[myArrayName[p]+"_phi"]->Fill(((TRootMuon*)myArrays[p]->At(o))->Phi());
	  histos[myArrayName[p]+"_chargedHadronIso"]->Fill(((TRootMuon*)myArrays[p]->At(o))->chargedHadronIso());
	  histos[myArrayName[p]+"_photonIso"]->Fill(((TRootMuon*)myArrays[p]->At(o))->photonIso());
	  histos[myArrayName[p]+"_neutralHadronIso"]->Fill(((TRootMuon*)myArrays[p]->At(o))->neutralHadronIso());
	  histos[myArrayName[p]+"_nofValidPixelHits"]->Fill(((TRootMuon*)myArrays[p]->At(o))->nofValidPixelHits());
	  histos[myArrayName[p]+"_nofMatchedStations"]->Fill(((TRootMuon*)myArrays[p]->At(o))->nofMatchedStations());
	  
	}
	
	//
	// ELECTRON
	//
	
	else if (strstr(myArrayClass[p].c_str(),"TopTree::TRootElectron")){
	  
	  if(o==0) histos[myArrayName[p]+"_size"]->Fill(myArrays[p]->GetEntries());
	  
	  // some local plots
	  hist="_pt";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,0,500);
	  hist="_eta";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),300,-6,6);	  
	  hist="_phi";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,-5,5);
	  hist="_chargedHadronIso";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,-5,25);
	  hist="_photonIso";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,-5,25);
	  hist="_neutralHadronIso";
	  if (histos.find(myArrayName[p]+hist) == histos.end()) histos[myArrayName[p]+hist]=new TH1F((myArrayName[p]+hist).c_str(),(myArrayName[p]).c_str(),250,-5,25);	  
	  
	  histos[myArrayName[p]+"_pt"]->Fill(((TRootElectron*)myArrays[p]->At(o))->Pt());
	  histos[myArrayName[p]+"_eta"]->Fill(((TRootElectron*)myArrays[p]->At(o))->Eta());
	  histos[myArrayName[p]+"_phi"]->Fill(((TRootElectron*)myArrays[p]->At(o))->Phi());
	  histos[myArrayName[p]+"_chargedHadronIso"]->Fill(((TRootElectron*)myArrays[p]->At(o))->chargedHadronIso());
	  histos[myArrayName[p]+"_photonIso"]->Fill(((TRootElectron*)myArrays[p]->At(o))->photonIso());
	  histos[myArrayName[p]+"_neutralHadronIso"]->Fill(((TRootElectron*)myArrays[p]->At(o))->neutralHadronIso());
	  
	}
	
      }
      
      //delete myArray;
    }
    
  } cout << endl; // end of event loop

  if(verbosity>1) cout <<"Writing the plots" << endl;

  mkdir("Output",0755);

  std::map<std::string, vector<TH1F*> > new_histos;

  for (std::map<std::string, TH1F* >::const_iterator it=histos.begin(); it != histos.end(); ++it) {

    new_histos[(string)it->second->GetTitle()].push_back(it->second);

  }

  vector<TCanvas*> canvas; // yes another vector but this is the last one, promise!
  vector<TFile*> out; // yes another vector but this is the last one, promise!

  for (std::map<std::string, vector<TH1F*> >::const_iterator it=new_histos.begin(); it != new_histos.end(); ++it) {

    //if (verbosity > 3) cout << myArrayName[p] << " " <<  it->second.size() << endl;

    if (it->second.size() == 0)
      continue;

    int dest = 1;

    int numCanvas = 0;
    
    for (unsigned int j=0; j<it->second.size(); j++) {

      if (j ==0 || dest % 5 == 0) {

	stringstream s; s << canvas.size()+1;

	string cName = "canvas_"+s.str();

	string cTitle = ("Output/"+(string)it->second[j]->GetTitle()).c_str(); // this to know in which dir we need to store it

	canvas.push_back(new TCanvas(cName.c_str(),cTitle.c_str(),800,600));

	mkdir(canvas[canvas.size()-1]->GetTitle(),0755);

	string rootFileName= (string)canvas[canvas.size()-1]->GetTitle()+"/"+(string)canvas[canvas.size()-1]->GetName()+".root";

	out.push_back(new TFile(rootFileName.c_str(),"RECREATE"));
  
	numCanvas = canvas.size()-1;

	if (it->second.size() == 1)
	  canvas[numCanvas]->Divide(1,1);
	else
	  canvas[numCanvas]->Divide(2,2);


	dest=1;

      }

      canvas[numCanvas]->cd(dest);

      gPad->SetGrid();

      if (it->second[j]->Integral() == 0)

	gPad->SetFillColor(kRed);
      
      it->second[j]->SetTitle(it->second[j]->GetName()); // put back title

      it->second[j]->Draw();

      out[out.size()-1]->cd();

      it->second[j]->Write();

      dest++;

    }

  }
  
  for (unsigned int c=0; c<canvas.size(); c++) {

    string saveTitle = (string)canvas[c]->GetTitle()+"/"+(string)canvas[c]->GetName()+".png";

    canvas[c]->SaveAs(saveTitle.c_str());

    out[c]->cd();

    canvas[c]->Write();

    out[c]->Close();

  }

  if(verbosity>1) cout<<"End of the Macro"<<endl;

  return 0;
}
