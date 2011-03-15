##########################################
### TopTreeProducer Development README ###
##########################################

? Version: 0.1
? Date: 24-02-2011
? Branch: CMSSW_38X
? Tag: None

-------------------------------------------------------------------------------------------------------------

Table of contents:
------------------

1. How to get started
2. How to make a new branch
3. Maintaining the TopTreeProducer
  3.1 The TopTreeProducer structure
  3.2 The objects
    3.2.1 Run and Event
    3.2.2 HLT
    3.2.3 Muon
    3.2.4 Electron
    3.2.5 Jets
    3.2.6 MET
  3.4 The TopTreeProducer Class
  3.5 The Config File
  3.6 Adding new TRoot* objects
4. Testing code
5. How to create a tag
6. What not to do (except if you feel lucky;-))
7. Maintenance of the TopSkimmer

-------------------------------------------------------------------------------------------------------------

1. How to get started
---------------------

!!!!!First of all please read!!!!!

  https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookWriteFrameworkModule

This will help you in understanding how a CMSSW EDAnalyzer works. This knowledge is mandatory for all that follows.

Set up your CVS connection (if not yet done):

  export CVS_RSH=/usr/bin/ssh
  export CVSROOT=:ext:<CERNUSERNAME>@cmscvs.cern.ch:/cvs_server/repositories/CMSSW <- replace <CERNUSERNAME> with yours!

Before you start developing you should have a clean environment. This means you have checked out the latest branch you want to develop in e.g. CMSSW_38X. Clean also means that this environment is not yet used for previous development, this to ensure that you will not create code collision or commit undesirable code to break the package.

How to check out the code:

  cvs co -r CMSSW_38X -d TopBrussels/TopTreeProducer UserCode/TopBrussels/TopTreeProducer

Once you have your new environment, please first try to compile it and fix whatever bug is still present before starting development.

Note: we have not used the HEAD branch on cvs for a long time, so always develop from a CMSSW_3XX branch.

2. How to make a new branch
---------------------------

Let's say you want to start development for CMSSW_4_2_X versions, then you need to start with a new branch in the TopTreeProducer package e.g. CMSSW_42X. How do you do this?

Well just check out the latest branch from CVS, in this case CMSSW_38X, inside your CMSSW_4_2_X CMSSW area:

  cvs co -r CMSSW_38X -d TopBrussels/TopTreeProducer UserCode/TopBrussels/TopTreeProducer

Once you have the code checked out, go to  TopBrussels/TopTreeProducer/ and do:

  cvs tag -b CMSSW_42X (-b stands for "branch-tag")
	
Remove your TopBrussels/TopTreeProducer folder and check out the new branch for CMSSW_42X rather than CMSSW_38X. If you don't you'll end up developing in CMSSW_38X and this is not desired.

Go to the TopTreeProducer directory and try to compile it. For sure it will not compile (due to the drastic CMSSW changes) and you will spend some time chasing bugs in the yard. But hey "No Pain No Gain"!

Once you managed to get the thing compiling, you should get your hands on a sample. 

/*
 
  How to get a sample to run on locally: 

    If the sample is not yet at our T2, you have two options of transferring it for testing:
 
      1) Phedex request: https://cmsweb.cern.ch/phedex/. You can transfer a block of the sample or the full sample to the T2. (ask T2 Admins for more info)
 
      2) FileMover: https://cmsweb.cern.ch/filemover/. This tool allows you to download any file of a sample trough your browser. Then you can upload it to the m-machines for testing.

    More information on samples can be found on DBS: https://cmsweb.cern.ch/dbs_discovery/

*/

Create a PATtuple based on it and then try to run the TopTreeProducer on it. If all goes well, you will have your first TopTree.

Congratulations! You built the base of the CMSSW_42X development. Make sure to commit your changes to CVS.

Tag the base version by doing:

cvs tag baseversion_CMSSW_42X

Now you are ready to start working on your physics object.

Note: To not this step only needs to be performed by one unlucky contributor. 

3. Maintaining the TopTreeProducer
----------------------------------

Here we will try to summarize how the TopTreeProducer is built and how you can add/edit/remove things.

  3.1 The TopTreeProducer structure
  ---------------------------------

  Here you can find a visual on the TopTreeProducer for CMSSW_38X: http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/TopBrussels/TopTreeProducer/?pathrev=CMSSW_38X

  Directory Structure:

  TopBrussels/TopTreeProducer/interface------------Location of the C++ header files
                             /src------------------Location of the C++ source files
                             /python---------------Location of the python CMSSW config files which serve as includes to the main config
                             /test-----------------Location of the main config file and test macros (for analyzing TopTrees)
                             /tools----------------Location for various TopTree tools (not necessary linked to TopTree production e.g. TopTree branch dumper, event counter etc)
                             /skimmer--------------Location of the TopSkim.C package
                             /BuildFile------------CMSSW BuildFile which is used in the compiler linking step (only important when adding special CMSSW tags)

  Class Structure example: 

  TopTreeProducer class --> the main EDAnalyzer which runs all the Physics Objects Modules and creates the final TopTree
                        |-> interface/TopTreeProducer.h: defines all containers to store jets, muons etcÉ
                            |-> src/TopTreeProducer.cc: main event loop where all modules are run and the corresponding output is stored.
                        |-> test/TopTreeProducer.py: cmsRun configuration file to run this class.
   
  Example Module: Jets

                  |-> interface/TRootJet.h: Defines what a Jet will look like in the TopTree. Contains variables and getters,setters to fill and read these variables. 
                                            Various constructors to accommodate different ways of defining a new jet
                                |-> interface/TRootCaloJet.h: inherits from TRootJet and adds CaloJet specific variables.
                                |-> interface/TRootPFJet.h: inherits from TRootJet and adds PFJet specific variables.
                                |-> interface/TRootJPTJet.h: inherits from TRootJet and adds JPTJet specific variables.

		    |-> src/TRootJet.cc: implements this TRootJet class. (dummy .cc file for the root dict in our case)
                                  |-> src/TRootCaloJet.cc: idem.
                                  |-> src/TRootPFJet.cc: idem.
                                  |-> src/TRootJPTJet.cc: idem.

                  |-> interface/JetAnalyzer.h: CMSSW module to build TopTree::TRootJet from pat::Jet and fill all the variables. Returns the jet to the TopTreeProducer class.
                                |-> interface/CaloJetAnalyzer.h: same as JetAnalyzer but adds the specific CaloJet properties to the jet.
                                |-> interface/PFJetAnalyzer.h: same as JetAnalyzer but adds the specific PFJet properties to the jet.
                                |-> interface/JPTJetAnalyzer.h: same as JetAnalyzer but adds the specific JPTJet properties to the jet.

                    |-> src/JetAnalyzer.cc: c++ implementation of the module.
                                  |-> src/CaloJetAnalyzer.cc: c++ implementation of the module.
                                  |-> src/PFJetAnalyzer.cc: c++ implementation of the module.
                                  |-> src/JPTJetAnalyzer.cc: c++ implementation of the module.

  The TopTreeProducer class puts the objects in a TClonesArray object (or in a vector<TClonesArray> object for example when you want both AK5 and KT4 CaloJets - Explained below) for writing in the TopTree.

  3.2 The Objects
  ---------------

    This section will give you a short overview on where to find the object you are responsible for. Always in the format of the 

      - TopTree definition: TRoot class which defines how the object looks like in the TopTree
      - CMSSW implementation: The module that runs in the TopTreeProducer and creates the TRootObject

    The content of the files is always the same as the Jet-case described above. The best way to proceed is to start reading the TRoot* Class and understand what the object is. Then check out the analyzer module that creates these objects. In a last stage you can have a look at the TopTreeProducer class to see how your object is embedded in the big picture.

    General method of adding variables to a TRoot Object:
  
      For example, we'll add the number of pixel hits for a muon (dummy example)

      1) open interface/TRootMuon.h
      2) Add a variable in the "private" section of the class (bottom of the file) e.g. Int_t nPixelHits_;
      3) Add this variable with a standard value (e.g. -9999) to all the TRootMuon constructors
      4) Create a set function to put in the value (you'll see a block in the file where all set functions are)
            void setNPixelHits ( int nPixelHits ) { nPixelHits_ = nPixelHits; }
      5) Create a get function to retrieve this value in your analysis
            Int_t getNPixelHits ( ) const { return nPixelHits_; }
      6) Call the TRootMuon::setNPixelHits function from src/MuonAnalyzer.cc using the proper value as argument.

    Note: For Jets and MET where you have different types, it is a little more complicated:

      1) Your variable is just a JET observable: use TRootJet.h and JetAnalyzer.cc
      2) Your variable is for example CALO specific: use TRootCaloJet.h and CaloJetAnalyzer.cc (same for PF and JPT)

      -> Same goes for MET and all objects with multiple types.
 
    3.2.1 Run and Event
    -------------------

    Typical Run and Event variables: eventID, lumiBlockID, runID, generalTrack info, HLT decision, ...

    TopTree Definition: Run -> interface/TRootRun.h
                                |_> src/TRootRun.cc: Class Implementation for Root
                        Event -> interface/TRootEvent.h
                                |_> src/TRootEvent.cc: Class Implementation for Root

    Implementation: Both objects are produced inside src/TopTreeProducer.cc. No separate modules are run for these objecs.
 
    3.2.2 HLT
    ---------

    TopTree Definition: interface/TRootHLTInfo.h: HLTInfo container which provides mapping between triggerPath and triggerBit e.g. HLT_Mu9 -> trigger bit 41 (dummy value!)
                         |_> src/TRootHLTInfo.cc: Class Implementation for Root
                        interface/TRootRun.h: Holds a vector of HLTInfo objects (one for each run)
                         |_> src/TRootRun.cc: Class Implementation for Root

    Implementation: --> interface/HLTAnalyzer.h
                         |_> src/HLTAnalyzer.cc

    3.2.3 Muon
    ----------

    TopTree Definition: interface/TRootMuon.h
                         |_> src/TRootMuon.cc: Class Implementation for Root

    Implementation: --> interface/MuonAnalyzer.h
                         |_> src/MuonAnalyzer.cc

    3.2.4 Electron
    --------------

    TopTree Definition: interface/TRootElectron.h
                         |_> src/TRootElectron.cc: Class Implementation for Root

    Implementation: --> interface/ElectronAnalyzer.h
                         |_> src/ElectronAnalyzer.cc

    3.2.5 Jets
    ----------
    See section 3.1.

    3.2.6 MET
    ---------

    MET also comes in different flavors, it's completely analogue to the JETS case (Section 3.1)

    TopTree Definition: interface/TRootMET.h
                           |_> interface/TRootCaloMET.h
                           |_> interface/TRootPFMET.h
                           |_> interface/TRootTCMET.h
                         |_> src/TRootMET.cc: Class Implementation for Root
                            |_> src/TRootCaloMET.cc
                            |_> src/TRootPFMET.cc
                            |_> src/TRootTCMET.cc

    Implementation: --> interface/METAnalyzer.h
                           |_> interface/CaloMETAnalyzer.h
                           |_> interface/PFMETAnalyzer.h
                           |_> interface/TCMETAnalyzer.h
                         |_> src/METAnalyzer.cc
                            |_> src/CaloMETAnalyzer.cc
                            |_> src/PFMETAnalyzer.cc
                            |_> src/TCMETAnalyzer.cc

  3.4 The TopTreeProducer Class
  -----------------------------

  If you have not read the CMS Workbook on EDAnalyzers, go back and do it!

  Here we will review in some detail how the TopTreeProducer class handles the particular case of PFJets. The other modules are completely analogous.

  src/TopTreeProducer.cc (definitions in interface/TopTreeProducer.h - it is a CMSSW EDAnalyzer)
        |_> TopTreeProducer::TopTreeProducer() (constructor)
                     |_> Define the names of the collections to use (e.g the muon,jets,.. collection names in the source CMSSW Pat or RECO file)

        |_> TopTreeProducer::~TopTreeProducer() (destructor) EMPTY for now

        |_> TopTreeProducer::beginJob()
                     |_> General items:
                         |_> Reading more parameters from the config file (see next section)
                         |_> rootFileName_ = myConfig_.getUntrackedParameter<string>("RootFileName","noname.root"); ==> the output filename for the TopTree
                         |_> verbosity = myConfig_.getUntrackedParameter<int>("verbosity", 0); => verbosity level should be included in all cout, cerr commands;
 
                               e.g. in the code :  if (verbosity > 0) {
                                                      cout << "You should not read this unless you have set verbosity > 0" << endl;
                                                   }

                               Note: When verbosity = 0 we don't want to see ANY cout! Verbosity levels can be found in test/TopTreeProducer.py                         
 
                     |_> Specific items for each module:
                         |_> On/off switch
                              e.g.: doPFJet = myConfig_.getUntrackedParameter<bool>("doPFJet",false); -> Switch for the PFJets module for only one type of PFJets
                                    doPFJetStudy = myConfig_.getUntrackedParameter<bool>("doPFJetStudy",false); -> Switch for the PFJets module for multiple PFJet types e.g.: AK5PFJets, KT4PFJets,.. (hence the "Study" suffix)

                         |_> If you are working with a "Study" collection (e.g. PFJetStudy or METStudy,..) a few extra things should be coded:
				
				vector<string> defaultVec;
                              	vPFJetProducer = producersNames_.getUntrackedParameter<vector<string> >("vpfJetProducer",defaultVec);
				for(unsigned int s=0;s<vPFJetProducer.size();s++){
					TClonesArray* a;
					vpfJets.push_back(a);
				}

                             This code initializes a vector of TClonesArrays to store the different PFJet types.

			 |_> Add the corresponding branches to the TopTree. Both for the Single and Multiple PFJet type case:
	
                               Single: 

			        if(doPFJet) {
                                  if(verbosity>0) cout << "PFJets info will be added to rootuple" << endl;
                                  pfJets = new TClonesArray("TopTree::TRootPFJet", 1000);
                                  eventTree_->Branch ("PFJets", "TClonesArray", &pfJets);
                                }
	
                               Multiple:

                                if(doPFJetStudy) {
                                  if(verbosity>0) cout << "PFJets info will be added to rootuple (for PFJetStudy)" << endl;
                                  for(unsigned int s=0;s<vPFJetProducer.size();s++) {
                                    vpfJets[s] = new TClonesArray("TopTree::TRootPFJet", 1000);
                                    char name[100];
                                    sprintf(name,"PFJets_%s",vPFJetProducer[s].c_str());
                                    eventTree_->Branch (name, "TClonesArray", &vpfJets[s]);
                                  }
                                }

        |_> TopTreeProducer::endJob() 
                     |_> Fill the RunTree
                     |_> Save the output TopTree
                     |_> Print HLT summary

        |_> TopTreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
                     |_> Here the magic happens!!!
                     |_> All the object modules are run and the objects put in their containers 
                     |_> Example of the PFJet implementation:

                         // PFJet
                         if(doPFJet) {
                           if(verbosity>1) cout << endl << "Analysing PFJets collection..." << endl;
                           PFJetAnalyzer* myPFJetAnalyzer = new PFJetAnalyzer(producersNames_, myConfig_, verbosity);
                           myPFJetAnalyzer->Process(iEvent, pfJets);
                           delete myPFJetAnalyzer;
                         }

                         This block of code is common to most modules. It runs the PFJetAnalyzer module and provides it the configuration options e.g. which collection names (producerNames_) and the verbosity level.
                         The process function gets as input pfJets, which is the TClonesArray where the TRootPFJet objects will be stored.                        

                         if(doPFJetStudy) {
                         if(verbosity>1) cout << endl << "Analysing PFjets collection (for JetStudy)..." << endl;
                           for(unsigned int s=0;s<vPFJetProducer.size();s++){
                             PFJetAnalyzer* myPFJetAnalyzer = new PFJetAnalyzer(producersNames_, s,  myConfig_, verbosity);
                             myPFJetAnalyzer->Process(iEvent, vpfJets[s]);
                             delete myPFJetAnalyzer;
                           }
                         }

                         Same as the above code but for the "PFJetStudy" we loop over all types of PFJets we want to have in our TopTree.


                     |_> At the end of the analyze function we have to free up some memory by deleting the TClonesArray containers after the eventTree->Fill(); ofcourse:-)
		
                         if (doPFJet) (*pfJets).Delete();
                         
                         if(doPFJetStudy){
                           for(unsigned int s=0;s<vPFJetProducer.size();s++){
                           (*vpfJets[s]).Delete();
                           }
                         }



  3.5 The Config File
  -------------------

  Location : test/TopTreeProducer.py - Generic TopTreeProducer configuration file

  It is a standard CMSSW EDAnalyzer configuration file in python so you should recognize some standard things as 
   
    import FWCore.ParameterSet.Config as cms
    process = cms.Process("NewProcess")
    process.source = cms.Source("PoolSource",

    etcetc

  So we will not give another introduction to CMSSW:)

  What you should know about this file is that it set's the options we have been using in the TopTreeProducer class:

      doPFJet = cms.untracked.bool(False),
      doPFJetStudy = cms.untracked.bool(True),

  and it also defines the producernames for the different cases of RECO AOD etc

    |_> NOTE about producerNames: to know what collection names are in your PAT/RECO file you can use edmDumpEventContent or open the file in a root browser.

  In this file you also define the output filename of the TopTree.

  You can also define more options than just switching on/off a branch e.g.: doMC or doMuonMC among others.
  If you do so, make sure that you define this parameter in the config as well as in the TopTreeProducer.h/cc file.

  3.6 Adding new TRoot* objects
  -----------------------------

  Before you start implementing a TRoot class, make sure it is necessary!

  For example: when adding also PFMuon in the game. Do we need a TRootPFMuon or can the PFMuon be described by a TRootMuon. Are there extra functionalities?

  Let's say that you indeed need a TRootPFMuon Class. Then probably you will use TRootMuon as a base-class and extend this with PF specific options. (look at TRootJet.h and TRootCaloJet.h for example)

  If you do so, please do not forget to put your newly created TRootPFMuon Class in src/LinkDef.h. This is of utmost importance! Otherwise root will get angry at you;-)

  To do that just look for example for all lines containing TRootMuon.h, copy the line and substitute Muon with PFMuon.

  Then add the analyzer module PFMuonAnalyzer.h/.cc and make the corresponding code in TopTreeProducer.h/.cc as we described above.

  That's about it..

4. Testing code
---------------

To test the code, you just have to run TopTreeProducer.py from the test directory.

First of all you can check if the config file is valid python

  python TopTreeProducer.py (make sure you have done cmsenv before)

If it gives no errors, your in the clear.

Secondly just do

  cmsRun TopTreeProducer.py

And this should, in the ideal case, provide you a nice TopTree as output.

During testing, you can switch on/off as many objects as you like but in the end this is the minimal set of objects that should be able to run together

  - Muons
  - Electrons
  - All kind of jet options
  - All kind of met options
  - HLT
  - MC/GenEvent/NPGenEvent

Make sure your development on one object doesn't make the other ones break.

Test cases (this is the minimal set that should succeed!):

  - Test the TopTreeProducer on PAT MC input (created from the RECO/AOD input)
  - Test the TopTreeProducer on PAT DATA input (created from the RECO/AOD input)

Finally try to write a simple macro to read out the variables you changed in your object and validate them. An example standalone root macro can be found in test/Macro.C and compilation info in the README in the same dir.

If you write an awesome Macro to validate your object please do commit it to CVS;-)

5. How to create a tag
----------------------

When you are really - and I mean REALY - confident that your code works and the output is sane, you should commit all your changes to the CVS branch you are working in.

All means:

  - Changes to TRoot classes
  - Changes to Analyzers
  - Changes to TopTreeProducer.py
  - Changed to Macro.C whenever changes in the TopTreeFormat require that.
  - Changes in src/LinkDef.h
  - Changes in src/MakeFile
  - Changed in BuildFile

When you have committed everything, set up a new environment like you did before (eg the CMSSW_42X branch) and with that clean environment try to produce once again a TopTree and validate it.

This will ensure that there is nothing you forgot to commit:)

Once all of that is done you should create a sticky tag which can be used for production e.g.: CMSSW_42X_v1

    cd path/to/TopBrussels/TopTreeProducer
    cvs tag CMSSW_42X_v1

Then you should announce your new tag to the top-brussels mailing list and also write a changelog for this tag on https://mon.iihe.ac.be/trac/t2b/wiki/TopTreeProducer_Changelog

6. What not to do (except if you feel lucky;-))
-----------------------------------------------

This is very short:

 - Do not commit any code that is broken except when you know that this won't cripple the development of others.

 - Do NOT forget to use the verbosity switch on all your cout and cerr statements. This can be a major problem when submitting production jobs as the log files of the job then become really big!

     -> Verbosity 0 in the config means that it's really on MUTE.

 - Please try not to produce code with millions of compiler warnings.

7. Maintenance of the TopSkimmer
--------------------------------
**SOON**
