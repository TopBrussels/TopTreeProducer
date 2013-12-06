#include "../interface/PFJetAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

PFJetAnalyzer::PFJetAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	pfJetProducer_ = producersNames.getParameter<edm::InputTag>("pfJetProducer");
	myJetAnalyzer = new JetAnalyzer();
}

PFJetAnalyzer::PFJetAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	pfJetProducer_ = producersNames.getParameter<edm::InputTag>("pfJetProducer");
	myJetAnalyzer = new JetAnalyzer(verbosity);
}

PFJetAnalyzer::PFJetAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	pfJetProducer_ = producersNames.getParameter<edm::InputTag>("pfJetProducer");
	myJetAnalyzer = new JetAnalyzer(myConfig, verbosity);
}

PFJetAnalyzer::PFJetAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	vPFJetProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vpfJetProducer");
	pfJetProducer_ = edm::InputTag(vPFJetProducer[iter]);
	myJetAnalyzer = new JetAnalyzer(myConfig, verbosity);
}

PFJetAnalyzer::~PFJetAnalyzer()
{
}

void PFJetAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootJets, const edm::EventSetup& iSetup)
{

	unsigned int nJets=0;

	// check if the jet is of the good type
	std::string jetType = "BASIC";
	if( pfJetProducer_.label()=="kt4PFJets"
		|| pfJetProducer_.label()=="kt6PFJets"
		|| pfJetProducer_.label()=="iterativeCone5PFJets"
		|| pfJetProducer_.label()=="sisCone5PFJets"
		|| pfJetProducer_.label()=="sisCone7PFJets"
		|| pfJetProducer_.label()=="ak5PFJets"
		|| pfJetProducer_.label()=="ak7PFJets"
	) jetType="PF";

//	edm::Handle < std::vector <pat::Jet> > patJets;
	Handle < View<pat::Jet> > patJets;
	iEvent.getByLabel(pfJetProducer_, patJets);
	nJets = patJets->size();

	Handle<ValueMap<StoredPileupJetIdentifier> > vmap;
	iEvent.getByLabel("puJetIdChs",vmap);

	Handle<ValueMap<float> > puJetIdMVA;
	iEvent.getByLabel("puJetMvaChs","fullDiscriminant",puJetIdMVA);	
		
	if(verbosity_>1) std::cout << "   Number of jets = " << nJets << "   Label: " << pfJetProducer_.label() << "   Instance: " << pfJetProducer_.instance() << std::endl;

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

		// Pile-up ID variables
		PileupJetIdentifier puIdentifier;
		puIdentifier = (*vmap)[patJets->refAt(j)];

		localJet.setDZ(puIdentifier.dZ());
		localJet.setDRMean(puIdentifier.dRMean());
		localJet.setFrac01(puIdentifier.frac01());
		localJet.setFrac02(puIdentifier.frac02());
		localJet.setFrac03(puIdentifier.frac03());
		localJet.setFrac04(puIdentifier.frac04());
		localJet.setFrac05(puIdentifier.frac05());
		localJet.setFrac06(puIdentifier.frac06());
		localJet.setFrac07(puIdentifier.frac07());
		localJet.setRMS(puIdentifier.RMS());
		localJet.setBeta(puIdentifier.beta()); 
		localJet.setBetaStar(puIdentifier.betaStar()); 
		localJet.setBetaClassic(puIdentifier.betaClassic()); 
		localJet.setBetaStarClassic(puIdentifier.betaStarClassic()); 
		localJet.setPtD(puIdentifier.ptD());
		// Pile-up ID MVA
		localJet.setMvaID((*puJetIdMVA)[patJets->refAt(j)]);

		new( (*rootJets)[j] ) TRootPFJet(localJet);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localJet << endl;
		
	}

}
