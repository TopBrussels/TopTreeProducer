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

	edm::Handle < TtGenEvent > genEvent;
        iEvent.getByLabel(genEventProducer_, genEvent);


	if(verbosity_>1) std::cout << "   GenEvent  "  << "   Label: " << genEventProducer_.label() << "   Instance: " << genEventProducer_.instance() << std::endl;

	TRootGenEvent TRootgenEvt;
	TRootgenEvt.SetBoolean(genEvent->isTtBar(), genEvent->isFullHadronic(), genEvent->isSemiLeptonic(), genEvent->isFullLeptonic());
	TRootgenEvt.SetSemiLeptonicChannel((TRootGenEvent::LeptonType) genEvent->semiLeptonicChannel());
	TLorentzVector neutrino;
	TLorentzVector lepton;
	TLorentzVector leptonicDecayW, leptonicDecayB, leptonicDecayTop;
	TLorentzVector hadronicDecayW, hadronicDecayB, hadronicDecayTop, hadronicDecayQuark, hadronicDecayQuarkBar;
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
	TRootgenEvt.SetTLorentzVector(lepton, neutrino, leptonicDecayW, leptonicDecayB, leptonicDecayTop, hadronicDecayB, hadronicDecayW, hadronicDecayTop, hadronicDecayQuark, hadronicDecayQuarkBar);
	std::vector<TLorentzVector> ISR, leptonicDecayTopRadiation, hadronicDecayTopRadiation;
	for(unsigned int i=0;i<genEvent->ISR().size();i++) 
	 if(genEvent->ISR()[i]) 
	   ISR.push_back(P4toTLV(genEvent->ISR()[i]->p4())); 
	for(unsigned int i=0;i<genEvent->leptonicDecayTopRadiation().size();i++) 
	 if(genEvent->leptonicDecayTopRadiation()[i]) 
	   leptonicDecayTopRadiation.push_back(P4toTLV(genEvent->leptonicDecayTopRadiation()[i]->p4())); 
	cout<<genEvent->hadronicDecayTopRadiation().size()<<endl;
	for(unsigned int i=0;i<genEvent->hadronicDecayTopRadiation().size();i++) 
	 if(genEvent->hadronicDecayTopRadiation()[i])
	   hadronicDecayTopRadiation.push_back(P4toTLV(genEvent->hadronicDecayTopRadiation()[i]->p4())); 
        TRootgenEvt.SetRadiation(leptonicDecayTopRadiation, hadronicDecayTopRadiation, ISR);
	new( (*rootGenEvent)[0] ) TRootGenEvent(TRootgenEvt);
}
