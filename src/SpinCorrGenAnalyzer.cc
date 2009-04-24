#include "../interface/SpinCorrGenAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

SpinCorrGenAnalyzer::SpinCorrGenAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	genEventProducer_ = producersNames.getParameter<edm::InputTag>("genEventProducer");
}

SpinCorrGenAnalyzer::SpinCorrGenAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	genEventProducer_ = producersNames.getParameter<edm::InputTag>("genEventProducer");
}

SpinCorrGenAnalyzer::SpinCorrGenAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	genEventProducer_ = producersNames.getParameter<edm::InputTag>("genEventProducer");
}

SpinCorrGenAnalyzer::~SpinCorrGenAnalyzer()
{
}


//TLorentzVector  P4toTLV(reco::Particle::LorentzVector a){ return TLorentzVector(a.px(), a.py(), a.pz(), a.energy());}

void SpinCorrGenAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootSpinCorrGen){

	edm::Handle < TtGenEvent > genEvt;
        iEvent.getByLabel(genEventProducer_, genEvt);


	//	if(verbosity_>1) std::cout << "   SpinCorrGen  "  << "   Label: " << spinCorrGenProducer_.label() << "   Instance: " << spinCorrGenProducer_.instance() << std::endl;
	if(verbosity_>1) std::cout << "   SpinCorrGen  "  << "   Label: " << genEventProducer_.label() << "   Instance: " << genEventProducer_.instance() << std::endl;

	//my code
 
	double cosThetaTLHel= -9999;
	double cosThetaTBHel= -9999;
	double cosThetaTQHel= -9999;
	double topsZMFMass =-9999;

	if(genEvt->isSemiLeptonic(WDecay::kMuon)){
	  //	  reco::Particle::LorentzVector topsZMF(genEvt.top()->p4()+genEvt.topBar()->p4());
	  reco::Particle::LorentzVector topsZMF(genEvt->leptonicDecayTop()->p4()+ genEvt->hadronicDecayTop()->p4());
	  
	  // boost particle 4-vectors to tt ZMF
	  if(genEvt->leptonicDecayTop() && genEvt->hadronicDecayTop() && genEvt->singleLepton() && genEvt->hadronicDecayB() && genEvt->hadronicDecayQuark()&& genEvt->hadronicDecayQuarkBar() ){
	    
	    reco::Particle::LorentzVector tLeptonicZMF(ROOT::Math::VectorUtil::boost(genEvt->leptonicDecayTop()->p4(), topsZMF.BoostToCM()));
	    reco::Particle::LorentzVector tHadronicZMF(ROOT::Math::VectorUtil::boost(genEvt->hadronicDecayTop()->p4(), topsZMF.BoostToCM()));
	    reco::Particle::LorentzVector lLeptonicZMF(ROOT::Math::VectorUtil::boost(genEvt->singleLepton()->p4(), topsZMF.BoostToCM()));
	    reco::Particle::LorentzVector bHadronicZMF(ROOT::Math::VectorUtil::boost(genEvt->hadronicDecayB()->p4(), topsZMF.BoostToCM()));
	    reco::Particle::LorentzVector q1HadronicZMF(ROOT::Math::VectorUtil::boost(genEvt->hadronicDecayQuark()->p4(), topsZMF.BoostToCM()));
	    reco::Particle::LorentzVector q2HadronicZMF(ROOT::Math::VectorUtil::boost(genEvt->hadronicDecayQuarkBar()->p4(), topsZMF.BoostToCM()));
	    
	    //--------------------------------------------------------------------------------
	    // build spin basis unit vectors
	    reco::Particle::Vector leptHelZMF(tLeptonicZMF.Vect().Unit());    
	    reco::Particle::Vector hadrHelZMF(tHadronicZMF.Vect().Unit()); // = -leptHelZMF
	    
	    reco::Particle::Vector q1HadZMF(q1HadronicZMF.Vect().Unit());
	    reco::Particle::Vector q2HadZMF(q2HadronicZMF.Vect().Unit());
	    reco::Particle::Vector qHadZMF(q1HadronicZMF.energy() < q2HadronicZMF.energy() ? // only lower energy quark used
					   q1HadZMF :
					   q2HadZMF);
	    
	    // boost 4-vectors to t(bar) rest frames
	    reco::Particle::LorentzVector lLeptonicTRest(ROOT::Math::VectorUtil::boost(lLeptonicZMF, tLeptonicZMF.BoostToCM()));
	    reco::Particle::LorentzVector bHadronicTRest(ROOT::Math::VectorUtil::boost(bHadronicZMF, tHadronicZMF.BoostToCM()));
	    reco::Particle::LorentzVector q1HadronicTRest(ROOT::Math::VectorUtil::boost(q1HadronicZMF, tHadronicZMF.BoostToCM()));
	    reco::Particle::LorentzVector q2HadronicTRest(ROOT::Math::VectorUtil::boost(q2HadronicZMF, tHadronicZMF.BoostToCM()));
	    reco::Particle::LorentzVector qHadronicTRest(q1HadronicTRest.energy() < q2HadronicTRest.energy() ? // only lower energy quark used
							 q1HadronicTRest :
							 q2HadronicTRest);
	    
	    // extract particle directions in t(bar) rest frames
	    reco::Particle::Vector lDirectionTRest(lLeptonicTRest.Vect().Unit());
	    reco::Particle::Vector bDirectionTRest(bHadronicTRest.Vect().Unit());
	    reco::Particle::Vector q1DirectionTRest(q1HadronicTRest.Vect().Unit());
	    reco::Particle::Vector q2DirectionTRest(q2HadronicTRest.Vect().Unit());
	    reco::Particle::Vector qDirectionTRest(qHadronicTRest.Vect().Unit());
	    
	    
	    cosThetaTLHel = leptHelZMF.Dot(lDirectionTRest);
	    cosThetaTBHel = hadrHelZMF.Dot(bDirectionTRest);
	    cosThetaTQHel = hadrHelZMF.Dot(qDirectionTRest);
	    topsZMFMass = topsZMF.mass();
	    
	    
	
	    //set the variable in the TopTree
	    TRootSpinCorrGen localSSG;
	    localSSG.setcosThetaTLHel(cosThetaTLHel); 
	    localSSG.setcosThetaTBHel(cosThetaTBHel);
	    localSSG.setcosThetaTQHel(cosThetaTQHel);
	    localSSG.settopsZMFMass(topsZMFMass);
	    
	    new( (*rootSpinCorrGen)[0] ) TRootSpinCorrGen(localSSG);
	    
	  }// close if 
	}//close if semilep


}
