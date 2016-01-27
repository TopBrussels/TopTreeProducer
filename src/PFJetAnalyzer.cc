#include "../interface/PFJetAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

PFJetAnalyzer::PFJetAnalyzer(const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	myJetAnalyzer = new JetAnalyzer(myConfig, verbosity);
}

PFJetAnalyzer::~PFJetAnalyzer()
{
	delete myJetAnalyzer;
}

void PFJetAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootJets, const edm::EventSetup& iSetup, edm::EDGetTokenT<pat::JetCollection> jetToken)
{

	unsigned int nJets=0;

	edm::Handle < std::vector <pat::Jet> > patJets;
	iEvent.getByToken(jetToken, patJets);
	nJets = patJets->size();


	if(verbosity_>1) std::cout << "   Number of jets = " << nJets << std::endl;

	for (unsigned int j=0; j<nJets; j++)
	{
		const reco::Jet* jet = 0;
		jet = (const reco::Jet*) ( & ((*patJets)[j]) );

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
		localJet.setMuonEnergyFraction(patJet->muonEnergyFraction());
		localJet.setNeutralEmEnergyFraction(patJet->neutralEmEnergyFraction());
		localJet.setHFHadronEnergyFraction(patJet->HFHadronEnergyFraction());
		localJet.setHFEMEnergyFraction(patJet->HFEMEnergyFraction());
		localJet.setChargedMultiplicity(patJet->chargedMultiplicity());
		localJet.setNeutralMultiplicity(patJet->neutralMultiplicity());
		localJet.setMuonMultiplicity(patJet->muonMultiplicity());
		localJet.setHFHadronMultiplicity(patJet->HFHadronMultiplicity());
		localJet.setHFEMMultiplicity(patJet->HFEMMultiplicity());
		localJet.setHadronFlavour(patJet->hadronFlavour());
		localJet.setpuID(patJet->userFloat("pileupJetId:fullDiscriminant")); // This was moved from JetAnalyzer.cc to PFJetAnalyzer.cc/FatJetAnalyzer.cc/JPTJetAnalyzer.cc (By Seth and Kevin on 23 december 2015)
		// DOES NOT WORK FOR FATJETS in 76X --> TO BE FIXED , but seems to be no problem for PFJets...

		new( (*rootJets)[j] ) TRootPFJet(localJet);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localJet << endl;

	}

}
