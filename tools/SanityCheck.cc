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
    
  int verbosity                 = 1;
  //0 muet
  //1 Main Info
  //2
  //3 
  //4 Info for each event
  //5 Debug

   // RETRIEVING LIST OF FILENAMES TO CHECK

  if (argc != 3) {

    cout << "Usage: ./SanityCheck --inputfiles file1;file2;fileN\n\n" << endl;

    exit(0);

  } else if (argc == 3 && !strstr(argv[1],"--inputfiles")) {

    cout << "Usage: ./SanityCheck --inputfiles file1;file2;fileN\n\n" << endl;

    exit(0);

  }

  vector<string> fileNames;
  
  Tokenize(argv[2], fileNames, ";");


  // CHECKING THE FILECONTENT FOR FILE 0 AND COUNT EVENTS FOR ALL FILES

  unsigned int nEvents = 0; 

  for (int fileID=0; fileID < fileNames.size(); fileID++) {
  
    if (verbosity > 0) cout << "Opening file " << fileNames.at(fileID) << endl;

    TFile* f = TFile::Open(fileNames.at(fileID).c_str());
    
    TTree* runTree = (TTree*) f->Get("runTree");
    TTree* eventTree = (TTree*) f->Get("eventTree");
    
    TBranch* run_br = (TBranch *) runTree->GetBranch("runInfos");
    TRootRun* runInfos = 0;
    run_br->SetAddress(&runInfos);
    
    TBranch* event_br = (TBranch *) eventTree->GetBranch("Event");
    TRootEvent* event = 0;
    event_br->SetAddress(&event);
    
    nEvents += eventTree->GetEntriesFast();
      
    //TBranch* br;
    //TClonesArray* objects;

    for (int i=1; i<eventTree->GetListOfBranches()->GetEntriesFast(); i++) {
      
      TBranch * branch = (TBranch *)eventTree->GetListOfBranches()->At(i);
      
      TObject* obj = branch->GetListOfLeaves()->At(0);
      
      std::string ObjName = obj->GetName();
      
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
    
      //runinfos
      
      runTree->GetEvent(0);
      
      //if (fileID == 0 && verbosity > 3 && runInfos->hltInputTag() != "")
      //	cout << "- " << "TopTree::TRootRun" << setw(5) << " -> " << "\"" << runInfos->hltInputTag() << "\""  << endl;
      
      // making some tests with the branch

      //Declartion of Branches and TClonesArray

      TBranch* br = (TBranch *) eventTree->GetBranch((ObjName.substr(0,position)).c_str());
  
      if (br) {
	if (verbosity > 1) cout << "  Loaded Branch " << className << " " << ObjName.substr(0,position) << endl;
	TClonesArray* objects = new TClonesArray(className.c_str(), 0);
	br->SetAddress(&objects);

	arrays[ObjName.substr(0,position)]=std::pair<std::string,TClonesArray*>(className,objects);

      } else if (verbosity > 1) cerr << "  ERROR loading Branch " << className << " " << ObjName.substr(0,position) << endl;
	
    }

    for(unsigned int ievt=0; ievt<eventTree->GetEntriesFast(); ievt++) {
      //for(unsigned int ievt=0; ievt<8000; ievt++) {
      eventTree->GetEvent(ievt);
      runTree->GetEvent(0);

      if (verbosity > 0 && ievt % 1000 == 0) std::cout<<"Processing the "<<ievt<<"th event." << flush<<"\r";


      for (std::map<std::string, std::pair<std::string,TClonesArray*> >::const_iterator it=arrays.begin(); it != arrays.end(); ++it) {

	//cout << it->first << " " << it->second.first << " " << it->second.second->GetEntries() << endl;

	//
	// define global plots we want to see
	//

	string hist="";

	hist="_size";
	if (histos.find(it->first+hist) == histos.end()) histos[it->first+hist]=new TH1F((it->first+hist).c_str(),(it->first).c_str(),100,0,100);

	for (unsigned int o=0; o<it->second.second->GetEntries(); o++) {
	  // because c++ it not flexible we need to write the crappy code below.... Sorry:'(

	  //
	  // JETS
	  //

	  // now putting all jet types together, these can be addressed seperately in the future if needed
	  if (strstr(it->second.first.c_str(),"TopTree::TRootCaloJet") || strstr(it->second.first.c_str(),"TopTree::TRootPFJet") || strstr(it->second.first.c_str(),"TopTree::TRootJPTJet") ){
	    
	    if(o==0) histos[it->first+"_size"]->Fill(it->second.second->GetEntries());

	    // some local plots
	    hist="_pt";
	    if (histos.find(it->first+hist) == histos.end()) histos[it->first+hist]=new TH1F((it->first+hist).c_str(),(it->first).c_str(),250,0,500);
	    hist="_eta";
	    if (histos.find(it->first+hist) == histos.end()) histos[it->first+hist]=new TH1F((it->first+hist).c_str(),(it->first).c_str(),300,-6,6);	  
	    hist="_phi";
	    if (histos.find(it->first+hist) == histos.end()) histos[it->first+hist]=new TH1F((it->first+hist).c_str(),(it->first).c_str(),250,-5,5);
	  
	    histos[it->first+"_pt"]->Fill(((TRootJet*)it->second.second->At(o))->Pt());
	    histos[it->first+"_eta"]->Fill(((TRootJet*)it->second.second->At(o))->Eta());
	    histos[it->first+"_phi"]->Fill(((TRootJet*)it->second.second->At(o))->Phi());
		     
	  }
	  
	  // 
	  // MET
	  //

	  else if (strstr(it->second.first.c_str(),"TopTree::TRootCaloMET") || strstr(it->second.first.c_str(),"TopTree::TRootPFMET") || strstr(it->second.first.c_str(),"TopTree::TRootMET") ){
	    
	    if(o==0) histos[it->first+"_size"]->Fill(it->second.second->GetEntries());

	    // some local plots
	    hist="_Et";
	    if (histos.find(it->first+hist) == histos.end()) histos[it->first+hist]=new TH1F((it->first+hist).c_str(),(it->first).c_str(),250,0,500);
	  
	    histos[it->first+"_Et"]->Fill(((TRootMET*)it->second.second->At(o))->Et());

		     
	  }

	  //
	  // MUON
	  //
	  
	  if (strstr(it->second.first.c_str(),"TopTree::TRootMuon")){
	    
	    if(o==0) histos[it->first+"_size"]->Fill(it->second.second->GetEntries());

	    // some local plots
	    hist="_pt";
	    if (histos.find(it->first+hist) == histos.end()) histos[it->first+hist]=new TH1F((it->first+hist).c_str(),(it->first).c_str(),250,0,500);
	    hist="_eta";
	    if (histos.find(it->first+hist) == histos.end()) histos[it->first+hist]=new TH1F((it->first+hist).c_str(),(it->first).c_str(),300,-6,6);	  
	    hist="_phi";
	    if (histos.find(it->first+hist) == histos.end()) histos[it->first+hist]=new TH1F((it->first+hist).c_str(),(it->first).c_str(),250,-5,5);
	  
	    histos[it->first+"_pt"]->Fill(((TRootMuon*)it->second.second->At(o))->Pt());
	    histos[it->first+"_eta"]->Fill(((TRootMuon*)it->second.second->At(o))->Eta());
	    histos[it->first+"_phi"]->Fill(((TRootMuon*)it->second.second->At(o))->Phi());
	  
	  }

	  //
	  // ELECTRON
	  //
	  
	  if (strstr(it->second.first.c_str(),"TopTree::TRootElectron")){
	    
	    if(o==0) histos[it->first+"_size"]->Fill(it->second.second->GetEntries());

	    // some local plots
	    hist="_pt";
	    if (histos.find(it->first+hist) == histos.end()) histos[it->first+hist]=new TH1F((it->first+hist).c_str(),(it->first).c_str(),250,0,500);
	    hist="_eta";
	    if (histos.find(it->first+hist) == histos.end()) histos[it->first+hist]=new TH1F((it->first+hist).c_str(),(it->first).c_str(),300,-6,6);	  
	    hist="_phi";
	    if (histos.find(it->first+hist) == histos.end()) histos[it->first+hist]=new TH1F((it->first+hist).c_str(),(it->first).c_str(),250,-5,5);
	  
	    histos[it->first+"_pt"]->Fill(((TRootElectron*)it->second.second->At(o))->Pt());
	    histos[it->first+"_eta"]->Fill(((TRootElectron*)it->second.second->At(o))->Eta());
	    histos[it->first+"_phi"]->Fill(((TRootElectron*)it->second.second->At(o))->Phi());
	  
	  }

	}

	//delete it->second.second;
      }

    }

    cout << endl;
   
    for (std::map<std::string, std::pair<std::string,TClonesArray*> >::const_iterator it=arrays.begin(); it != arrays.end(); ++it)
      delete it->second.second;

    //delete obj;
    //delete br;

    delete event_br;
    delete run_br;

    delete eventTree;
    delete runTree;

    //f->Close();

  }

  if(verbosity>1) cout <<"Writing the plots" << endl;

  std::map<std::string, vector<TH1F*> > new_histos;

  for (std::map<std::string, TH1F* >::const_iterator it=histos.begin(); it != histos.end(); ++it) {

    new_histos[(string)it->second->GetTitle()].push_back(it->second);

  }

  vector<TCanvas*> canvas; // yes another vector but this is the last one, promise!

  for (std::map<std::string, vector<TH1F*> >::const_iterator it=new_histos.begin(); it != new_histos.end(); ++it) {

    if (verbosity > 3) cout << it->first << " " <<  it->second.size() << endl;

    if (it->second.size() == 0)
      continue;

    int dest = 1;

    int numCanvas = 0;
    
    for (unsigned int j=0; j<it->second.size(); j++) {

      if (j ==0 || dest == 5) {

	stringstream s; s << canvas.size()+1;

	string cName = "canvas_"+s.str();

	string cTitle = ("Output/"+(string)it->second[0]->GetTitle()).c_str(); // this to know in which dir we need to store it

	canvas.push_back(new TCanvas(cName.c_str(),cTitle.c_str(),800,600));
	
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

      dest++;

    }

  }

  mkdir("Output",0755);
  
  for (unsigned int c=0; c<canvas.size(); c++) {

    mkdir(canvas[c]->GetTitle(),0755);

    string saveTitle = (string)canvas[c]->GetTitle()+"/"+(string)canvas[c]->GetName()+".png";

    canvas[c]->SaveAs(saveTitle.c_str());

  }

  if(verbosity>1) cout<<"End of the Macro"<<endl;
  
}
