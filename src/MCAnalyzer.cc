#include "../interface/MCAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;


MCAnalyzer::MCAnalyzer():
    verbosity_(0)
    ,doElectronMC_(false)
    ,electronMC_etaMax_(99999.)
    ,electronMC_ptMin_(99999.)
    ,doMuonMC_(false)
    ,muonMC_etaMax_(99999.)
    ,muonMC_ptMin_(99999.)
    ,doUnstablePartsMC_(false)
{
  
}




MCAnalyzer::MCAnalyzer(const edm::ParameterSet& config, int verbosity)
{
  verbosity_ = verbosity;
  doElectronMC_ = config.getUntrackedParameter<bool>("doElectronMC", false);
  electronMC_etaMax_ = config.getParameter<double>("electronMC_etaMax");
  electronMC_ptMin_ = config.getParameter<double>("electronMC_ptMin");
  doMuonMC_ = config.getUntrackedParameter<bool>("doMuonMC", false);
  muonMC_etaMax_ = config.getParameter<double>("muonMC_etaMax");
  muonMC_ptMin_ = config.getParameter<double>("muonMC_ptMin");
  doJetMC_ = config.getUntrackedParameter<bool>("doJetMC", false);
  jetMC_etaMax_ = config.getParameter<double>("jetMC_etaMax");
  jetMC_ptMin_ = config.getParameter<double>("jetMC_ptMin");
  doMETMC_ = config.getUntrackedParameter<bool>("doMETMC", false);
  doUnstablePartsMC_ = config.getUntrackedParameter<bool>("doUnstablePartsMC", false);
  if(verbosity_>2) cout << "MC Analyzer Instantiated." << endl;
}



MCAnalyzer::~MCAnalyzer()
{
  
}



void MCAnalyzer::DrawMCTree(const edm::Event& iEvent, const edm::EventSetup& iSetup, const edm::ParameterSet& config, const edm::ParameterSet& producersNames)
{
  cout << endl << " ----- ParticleTreeDrawer -----" << endl;
  ParticleTreeDrawer* ptd = new ParticleTreeDrawer(config, producersNames);
  ptd->analyze( iEvent, iSetup );
  delete ptd;
}



void MCAnalyzer::PDFInfo(const edm::Event& iEvent, TRootEvent* rootEvent, edm::EDGetTokenT<GenEventInfoProduct> genEventInfoProductToken)
{
  if(verbosity_>1) cout << endl << "   Process PDF Infos..." << endl;
  edm::Handle<GenEventInfoProduct> genEvtInfo;
  iEvent.getByToken( genEventInfoProductToken, genEvtInfo );
  typedef gen::PdfInfo PDF;
  const PDF *pdfInfo = genEvtInfo->pdf();
  if (genEvtInfo->hasPDF() && verbosity_>1) {
      cout << "   First incoming parton:  flavour=" << pdfInfo->id.first << " x1 = " << pdfInfo->x.first << endl;
      cout << "   Second incoming parton: flavour=" << pdfInfo->id.second << " x2 = " << pdfInfo->x.second << endl;
      cout << "   Factorization Scale Q = " << pdfInfo->scalePDF << endl;
  }
  rootEvent->setIdParton1(pdfInfo->id.first);
  rootEvent->setXParton1(pdfInfo->x.first);
  rootEvent->setIdParton2(pdfInfo->id.second);
  rootEvent->setXParton2(pdfInfo->x.second);
  rootEvent->setFactorizationScale(pdfInfo->scalePDF);
}



void MCAnalyzer::ProcessMCParticle(const edm::Event& iEvent, TClonesArray* rootMCParticles, edm::EDGetTokenT<std::vector<reco::GenParticle> > genParticlesToken)
{
  // Fill TClonesArray with preselected MC Electrons, Muons  and with the primary decaying particles
  if(verbosity_>1) cout << endl << "   Process MC Particles..." << endl;
  edm::Handle <reco::GenParticleCollection> genParticles;
  
  iEvent.getByToken( genParticlesToken, genParticles );
  
  int iElectron=0;
  int iMuon=0;
  int iUnstableParticle=0;
  int iPartSel=0;
  int iElectronSel=0;
  int iMuonSel=0;
  int iJet=0, iMET=0, iJetSel=0, iMETSel=0;


  for(unsigned int j=0; j<genParticles->size(); ++j )
  {
    bool addedParticle = false;
    
    const reco::GenParticle & p = (*genParticles)[ j ];
    if(verbosity_>4) cout << "in ProcessMCParticle loop on particle " << j << " with PDGid " << p.pdgId() << " and Status " << p.status() <<endl;
    
    //find the mother ID
    Int_t motherID = 0;
    Int_t grannyID = 0;
    if (p.numberOfMothers() > 0 )
    {
      //sanity check
      const Candidate* mom = p.mother();
      const Candidate* tempCand;
      while(p.pdgId() == mom->pdgId() && mom->numberOfMothers() > 0)
      {
        tempCand = mom;
        mom = tempCand->mother();
      }
      motherID = mom->pdgId();
      if((p.status() == 1 || abs(p.pdgId()) < 7) && verbosity_>4 ) cout << "Mother ID " << mom->pdgId() << " Status " << mom->status() << endl;
      if (mom->numberOfMothers() > 0)
      {
        const Candidate* granny = mom->mother();
        while(granny->pdgId() == mom->pdgId() && granny->numberOfMothers() > 0)
        {
          tempCand = granny;
          granny = tempCand->mother();
        }
        grannyID = granny->pdgId();
        if((p.status() == 1 || abs(p.pdgId()) < 7) && verbosity_>4 ) cout << "Granny ID " << granny->pdgId() << " Status " << granny->status() << endl;
      }
    }
    
    //find the daughter IDs
    Int_t daug0Id = 0;
    Int_t daug1Id = 0;
    Int_t daug2Id = 0;
    Int_t daug3Id = 0;
    if ( doUnstablePartsMC_ )
    {
      if (p.numberOfDaughters() > 0) daug0Id = p.daughter( 0 )->pdgId();
      if (p.numberOfDaughters() > 1) daug1Id = p.daughter( 1 )->pdgId();
      if (p.numberOfDaughters() > 2) daug2Id = p.daughter( 2 )->pdgId();
      if (p.numberOfDaughters() > 3) daug3Id = p.daughter( 3 )->pdgId();
    }
    
    //keep all copies that are 'stable particle' or originate from hard-scattering process (before radiation)
    Int_t keepStatus = false;
    if ( p.status() == 1 || (p.status() > 20 && p.status() < 30) ) keepStatus = true;
    
    
    if ( doElectronMC_ && abs(p.pdgId()) == 11 )
    {
      iElectron++;
      
      if ( !keepStatus && (fabs(p.eta())>electronMC_etaMax_ || p.pt()<electronMC_ptMin_) ) continue;
      else if ( fabs(p.eta())>1000 || fabs(p.pt())<0.0001 ) continue;
      iElectronSel++;
      
      TRootMCParticle localMCElectron( p.px(), p.py(), p.pz(), p.energy(), p.vx(), p.vy(), p.vz(), p.pdgId(), p.charge(), p.status(), p.numberOfDaughters(), motherID, grannyID, daug0Id, daug1Id, daug2Id, daug3Id, j );
      localMCElectron.setStateFlags(p.isPromptFinalState(), p.isPromptDecayed(), p.fromHardProcessBeforeFSR(), p.isHardProcess(), p.fromHardProcessFinalState(), p.fromHardProcessDecayed(), p.isLastCopy());
      
      new ((*rootMCParticles)[iPartSel]) TRootMCParticle(localMCElectron);
      
      if(verbosity_>2) cout << "   ["<< setw(3) << iPartSel << "] MC Electron  " << (const TRootMCParticle&)(*rootMCParticles->At(iPartSel)) << endl;
      
      iPartSel++;
      addedParticle = true;
    }
    
    
    if ( doMuonMC_ && abs(p.pdgId()) == 13 )
    {
      iMuon++;
      
      if ( !keepStatus && (fabs(p.eta())>muonMC_etaMax_ || p.pt()<muonMC_ptMin_) ) continue;
      else if ( fabs(p.eta())>1000 || fabs(p.pt())<0.0001 ) continue;
      iMuonSel++;
      
      TRootMCParticle localMCMuon( p.px(), p.py(), p.pz(), p.energy(), p.vx(), p.vy(), p.vz(), p.pdgId(), p.charge(), p.status(), p.numberOfDaughters(), motherID, grannyID, daug0Id, daug1Id, daug2Id, daug3Id, j );
      localMCMuon.setStateFlags(p.isPromptFinalState(), p.isPromptDecayed(), p.fromHardProcessBeforeFSR(), p.isHardProcess(), p.fromHardProcessFinalState(), p.fromHardProcessDecayed(), p.isLastCopy());
      
      new ((*rootMCParticles)[iPartSel]) TRootMCParticle(localMCMuon);
      
      if(verbosity_>2) cout << "   ["<< setw(3) << iPartSel << "] MC Muon  " << (const TRootMCParticle&)(*rootMCParticles->At(iPartSel)) << endl;
      
      iPartSel++;
      addedParticle = true;
    }
    
    
    // FIXME - GenJet collection instead
    if ( doJetMC_ && (abs(p.pdgId()) < 7 || abs(p.pdgId()) == 21 ) )
    {
      iJet++;
      
      //keep all copies of top quark (some of these are needed for systematics)
      if ( !keepStatus && abs(p.pdgId()) != 6 && (fabs(p.eta())>jetMC_etaMax_ || p.pt()<jetMC_ptMin_) ) continue;
      else if ( fabs(p.eta())>1000 || fabs(p.pt())<0.0001 ) continue;
      iJetSel++;
      
      TRootMCParticle localMCParton( p.px(), p.py(), p.pz(), p.energy(), p.vx(), p.vy(), p.vz(), p.pdgId(), p.charge(), p.status(), p.numberOfDaughters(), motherID, grannyID, daug0Id, daug1Id, daug2Id, daug3Id, j );
      localMCParton.setStateFlags(p.isPromptFinalState(), p.isPromptDecayed(), p.fromHardProcessBeforeFSR(), p.isHardProcess(), p.fromHardProcessFinalState(), p.fromHardProcessDecayed(), p.isLastCopy());
      
      new ((*rootMCParticles)[iPartSel] ) TRootMCParticle(localMCParton);
      
      if(verbosity_>2) cout << "   ["<< setw(3) << iPartSel << "] MC Jet  " << (const TRootMCParticle&)(*rootMCParticles->At(iPartSel)) << endl;
      
      iPartSel++;
      addedParticle = true;
    }
//        else if ( doJetMC_ && abs(p.pdgId()) == 5 && p.status() == 2 ) {
//            iJet++;
//            if ( abs(p.eta()>jetMC_etaMax_) || p.pt()<jetMC_ptMin_ ) continue;
//            TRootMCParticle localMCBQuark( p.px(), p.py(), p.pz(), p.energy(), p.vx(), p.vy(), p.vz(), p.pdgId(), p.charge(), p.status(), p.numberOfDaughters(), motherID, grannyID, 0, 0, 0, 0, j );
//
//            new( (*rootMCParticles)[iPartSel] ) TRootMCParticle( localMCBQuark );
//            if(verbosity_>2) cout << "   MC Jet  " << (const TRootParticle&)(*rootMCParticles->At(iPartSel)) << endl;
//            iPartSel++;
//            iJetSel++;
//            }
    
    
    // FIXME - GenMET collection instead
    if ( doMETMC_ && (abs(p.pdgId()) == 12 || abs(p.pdgId()) == 14 ||  abs(p.pdgId()) == 16 || ( abs(p.pdgId()) > 1000000 && abs(p.pdgId()) < 3000000 ) ) )
    {
      iMET++;
      
      if ( fabs(p.eta())>1000 || p.pt()<0.0001 ) continue;
      iMETSel++;
      
      TRootMCParticle  localMCNeutrino( p.px(), p.py(), p.pz(), p.energy(), p.vx(), p.vy(), p.vz(), p.pdgId() , p.charge(), p.status(), p.numberOfDaughters(), motherID, grannyID, daug0Id, daug1Id, daug2Id, daug3Id, j );
      localMCNeutrino.setStateFlags(p.isPromptFinalState(), p.isPromptDecayed(), p.fromHardProcessBeforeFSR(), p.isHardProcess(), p.fromHardProcessFinalState(), p.fromHardProcessDecayed(), p.isLastCopy());
      
      new ((*rootMCParticles)[iPartSel] ) TRootMCParticle( localMCNeutrino );
      
      if(verbosity_>2) cout << "   ["<< setw(3) << iPartSel << "] MC MET  " << (const TRootMCParticle&)(*rootMCParticles->At(iPartSel)) << endl;
      
      iPartSel++;
      addedParticle = true;
    }
    
    
    // add information on primary unstable particles: keep quarks, taus, Z, W, Higgs, susy and vlq particles, with status 3
    if ( doUnstablePartsMC_ && (abs(p.pdgId()) < 38 || (abs(p.pdgId()) > 1000000 && abs(p.pdgId()) < 3000000)  || (abs(p.pdgId()) > 4000000 && abs(p.pdgId()) < 6000000)) )
    {
      // Avoid double counting
      if ( addedParticle)
      {
        if(verbosity_>2) cout << "   ["<< setw(3) << iPartSel-1 << "] unstable particle : already added" << endl;
        iUnstableParticle++;
        continue;
      }
      
      if ( fabs(p.eta())>1000 || p.pt()<0.0001 ) continue;
      iUnstableParticle++;
      
      TRootMCParticle   localMCUnstable( p.px(), p.py(), p.pz(), p.energy(), p.vx(), p.vy(),p.vz(), p.pdgId(), p.charge(), p.status(), p.numberOfDaughters(), motherID, grannyID, daug0Id, daug1Id, daug2Id, daug3Id, j );
      localMCUnstable.setStateFlags(p.isPromptFinalState(), p.isPromptDecayed(), p.fromHardProcessBeforeFSR(), p.isHardProcess(), p.fromHardProcessFinalState(), p.fromHardProcessDecayed(), p.isLastCopy());
      
      new ((*rootMCParticles)[iPartSel] ) TRootMCParticle(localMCUnstable);
      
      if(verbosity_>2) cout << "   ["<< setw(3) << iPartSel << "] unstable particle  " << (const TRootMCParticle&)(*rootMCParticles->At(iPartSel)) << endl;
      
      iPartSel++;
    }
    
  }
  
  if(verbosity_>1)
  {
    cout << endl;
    cout << "   Number of MC electrons = " << iElectron << ", preselected = " << iElectronSel << endl;
    cout << "   Number of MC muons = " << iMuon << ", preselected = " << iMuonSel << endl;
    cout << "   Number of primary unstable particles dumped in the ntuple = " << iUnstableParticle << endl;
    //cout << "   Size rootMCParticles = " << rootMCParticles->GetEntriesFast() << endl;
  }
    
}
