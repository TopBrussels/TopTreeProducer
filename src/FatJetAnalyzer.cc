#include "../interface/FatJetAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

FatJetAnalyzer::FatJetAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	fatJetProducer_ = producersNames.getParameter<edm::InputTag>("fatJetProducer");
	myJetAnalyzer = new JetAnalyzer();
}

FatJetAnalyzer::FatJetAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	fatJetProducer_ = producersNames.getParameter<edm::InputTag>("fatJetProducer");
	myJetAnalyzer = new JetAnalyzer(verbosity);
}

FatJetAnalyzer::FatJetAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	fatJetProducer_ = producersNames.getParameter<edm::InputTag>("fatJetProducer");
	myJetAnalyzer = new JetAnalyzer(myConfig, verbosity);
}

FatJetAnalyzer::FatJetAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	vFatJetProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vfatJetProducer");
	fatJetProducer_ = edm::InputTag(vFatJetProducer[iter]);
	myJetAnalyzer = new JetAnalyzer(myConfig, verbosity);
}

FatJetAnalyzer::~FatJetAnalyzer()
{
}

void FatJetAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootJets, const edm::EventSetup& iSetup)
{

	unsigned int nJets=0;

	// check if the jet is of the good type
	std::string jetType = "BASIC";
	if( fatJetProducer_.label()=="kt4PFJets"
		|| fatJetProducer_.label()=="kt6Jets"
		|| fatJetProducer_.label()=="iterativeCone5Jets"
		|| fatJetProducer_.label()=="sisCone5Jets"
		|| fatJetProducer_.label()=="sisCone7Jets"
		|| fatJetProducer_.label()=="ak5Jets"
		|| fatJetProducer_.label()=="ak7Jets"
	) jetType="PF";

	edm::Handle < std::vector <pat::Jet> > patJets;
	iEvent.getByLabel(fatJetProducer_, patJets);
	nJets = patJets->size();
	
		
	if(verbosity_>1) std::cout << "   Number of jets = " << nJets << "   Label: " << fatJetProducer_.label() << "   Instance: " << fatJetProducer_.instance() << std::endl;

	for (unsigned int j=0; j<nJets; j++)
	{
		const reco::Jet* jet = 0;	
		jet = (const reco::Jet*) ( & ((*patJets)[j]) );
		if( (*patJets)[j].isPFJet() ) jetType="PF";
			
		// Call JetAnalyzer to fill the basic Jet Properties
		TRootJet tempJet = myJetAnalyzer->Process( &( *(jet) ), iSetup);
		
		TRootPFJet localJet = TRootPFJet(tempJet);

		localJet.setJetType(2); // 2 = PFJet

		// Some specific methods to pat::Jet
		const pat::Jet *patJet = dynamic_cast<const pat::Jet*>(&*jet);
			
		localJet.setChargedHadronEnergyFraction(patJet->chargedHadronEnergyFraction());
		localJet.setNeutralHadronEnergyFraction(patJet->neutralHadronEnergyFraction());
		localJet.setChargedEmEnergyFraction(patJet->chargedEmEnergyFraction());
		localJet.setChargedMuEnergyFraction(patJet->chargedMuEnergyFraction());
		localJet.setNeutralEmEnergyFraction(patJet->neutralEmEnergyFraction());		
		localJet.setHFHadronEnergyFraction(patJet->HFHadronEnergyFraction());
		localJet.setHFEMEnergyFraction(patJet->HFEMEnergyFraction());		
		localJet.setChargedMultiplicity(patJet->chargedMultiplicity());
		localJet.setNeutralMultiplicity(patJet->neutralMultiplicity());
		localJet.setMuonMultiplicity(patJet->muonMultiplicity());		
		localJet.setHFHadronMultiplicity(patJet->HFHadronMultiplicity());
		localJet.setHFEMMultiplicity(patJet->HFEMMultiplicity());

		new( (*rootJets)[j] ) TRootPFJet(localJet);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localJet << endl;
		
	}

}
