#include "../interface/GenEventAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

GenEventAnalyzer::GenEventAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	genEventProducer_ = producersNames.getParameter<edm::InputTag>("genEventProducer");
}

GenEventAnalyzer::GenEventAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	genEventProducer_ = producersNames.getParameter<edm::InputTag>("genEventProducer");
}

GenEventAnalyzer::GenEventAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	genEventProducer_ = producersNames.getParameter<edm::InputTag>("genEventProducer");
}

GenEventAnalyzer::~GenEventAnalyzer()
{
}


TLorentzVector  P4toTLV(reco::Particle::LorentzVector a){ return TLorentzVector(a.px(), a.py(), a.pz(), a.energy());}

void GenEventAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootGenEvent){

        std::cout<<"Process method"<<endl;
	edm::Handle < TtGenEvent > genEvent;
        iEvent.getByLabel(genEventProducer_, genEvent);


	if(verbosity_>1) std::cout << "   GenEvent  "  << "   Label: " << genEventProducer_.label() << "   Instance: " << genEventProducer_.instance() << std::endl;

	TRootGenEvent TRootgenEvt;
        cout<<"toto"<<endl;
	TRootgenEvt.SetBoolean(genEvent->isTtBar(), genEvent->isFullHadronic(), genEvent->isSemiLeptonic(), genEvent->isFullLeptonic());
        cout<<"toto"<<endl;
	TRootgenEvt.SetSemiLeptonicChannel((TRootGenEvent::LeptonType) genEvent->semiLeptonicChannel());
        cout<<"toto"<<endl;
	TLorentzVector neutrino;
	TLorentzVector lepton;
	TLorentzVector leptonicDecayW, leptonicDecayB, leptonicDecayTop;
	TLorentzVector hadronicDecayW, hadronicDecayB, hadronicDecayTop, hadronicDecayQuark, hadronicDecayQuarkBar;
        cout<<"toto"<<endl;
        cout<<"toto"<<endl;
	if( genEvent->isSemiLeptonic()){
	  if(genEvent->singleNeutrino()) neutrino = P4toTLV(genEvent->singleNeutrino()->p4());
  	  if(genEvent->singleLepton()) lepton = P4toTLV(genEvent->singleNeutrino()->p4());
	  if(genEvent->leptonicDecayW()) leptonicDecayW = P4toTLV(genEvent->leptonicDecayW()->p4());
	  if(genEvent->leptonicDecayB()) leptonicDecayB = P4toTLV(genEvent->leptonicDecayB()->p4());
	  if(genEvent->leptonicDecayTop()) leptonicDecayTop = P4toTLV(genEvent->leptonicDecayTop()->p4());
	  if(genEvent->hadronicDecayW()) hadronicDecayW = P4toTLV(genEvent->hadronicDecayW()->p4());
	  if(genEvent->hadronicDecayB()) hadronicDecayB = P4toTLV(genEvent->hadronicDecayB()->p4());
	  if(genEvent->hadronicDecayTop()) hadronicDecayTop = P4toTLV(genEvent->hadronicDecayTop()->p4());
	  if(genEvent->hadronicDecayQuark()) hadronicDecayQuark = P4toTLV(genEvent->hadronicDecayQuark()->p4());
	  if(genEvent->hadronicDecayQuarkBar()) hadronicDecayQuarkBar = P4toTLV(genEvent->hadronicDecayQuarkBar()->p4());
	}
        cout<<"toto"<<endl;
	TRootgenEvt.SetTLorentzVector(lepton, neutrino, leptonicDecayW, leptonicDecayB, leptonicDecayTop, hadronicDecayB, hadronicDecayW, hadronicDecayTop, hadronicDecayQuark, hadronicDecayQuarkBar);
        cout<<"toto"<<endl;
	std::vector<TLorentzVector> ISR, leptonicDecayTopRadiation, hadronicDecayTopRadiation;
	for(unsigned int i=0;i<genEvent->ISR().size();i++) ISR.push_back(P4toTLV(genEvent->ISR()[i]->p4())); 
	for(unsigned int i=0;i<genEvent->leptonicDecayTopRadiation().size();i++) leptonicDecayTopRadiation.push_back(P4toTLV(genEvent->leptonicDecayTopRadiation()[i]->p4())); 
	for(unsigned int i=0;i<genEvent->hadronicDecayTopRadiation().size();i++) hadronicDecayTopRadiation.push_back(P4toTLV(genEvent->hadronicDecayTopRadiation()[i]->p4())); 
        cout<<"toto"<<endl;
	TRootgenEvt.SetRadiation(leptonicDecayTopRadiation, hadronicDecayTopRadiation, ISR);
        cout<<"toto"<<endl;
	new( (*rootGenEvent)[0] ) TRootGenEvent(TRootgenEvt);
}
