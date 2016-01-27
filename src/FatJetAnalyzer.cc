#include "../interface/FatJetAnalyzer.h"
#include "DataFormats/BTauReco/interface/CATopJetTagInfo.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

FatJetAnalyzer::FatJetAnalyzer(const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	myJetAnalyzer = new JetAnalyzer(myConfig, verbosity);
}

FatJetAnalyzer::~FatJetAnalyzer()
{
	delete myJetAnalyzer;
}

void FatJetAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootJets, const edm::EventSetup& iSetup, edm::EDGetTokenT<pat::JetCollection> fatjetToken)
{

	unsigned int nJets=0;

	edm::Handle < std::vector <pat::Jet> > patJets;
	iEvent.getByToken(fatjetToken, patJets);
	nJets = patJets->size();


	if(verbosity_>1) std::cout << "   Number of jets = " << nJets << std::endl;

	for (unsigned int j=0; j<nJets; j++)
	{
		const reco::Jet* jet = 0;
		jet = (const reco::Jet*) ( & ((*patJets)[j]) );
		
		TRootJet tempJet = myJetAnalyzer->Process( &( *(jet) ), iSetup);
		
		TRootSubstructureJet localJet = TRootSubstructureJet(tempJet);

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
		localJet.setpuID(-9999); // This was moved from JetAnalyzer.cc to PFJetAnalyzer.cc/FatJetAnalyzer.cc/JPTJetAnalyzer.cc (By Seth and Kevin on 23 december 2015)
		// DOES NOT WORK FOR FATJETS in 76X --> TO BE FIXED 

		//extract/write CMS TOP-TAGGING info
		reco::CATopJetTagInfo const * tagInfo =  dynamic_cast<reco::CATopJetTagInfo const *>( patJet->tagInfo("caTop"));

		if ( tagInfo != 0 ) {


            double minMass = tagInfo->properties().minMass;
            double topMass = tagInfo->properties().topMass;
            int nSubJets = tagInfo->properties().nSubJets;

            double tau1 = patJet->userFloat("NjettinessAK8:tau1");    //
            double tau2 = patJet->userFloat("NjettinessAK8:tau2");    //  Access the n-subjettiness variables
            double tau3 = patJet->userFloat("NjettinessAK8:tau3");    //

			//These Links Not available for FATJETS in 76X (By Seth and Kevin on 23 december 2015)
            double trimmed_mass = -9999; //patJet->userFloat("ak8PFJetsCHSTrimmedLinks");   // access to trimmed mass
            double pruned_mass = -9999; //patJet->userFloat("ak8PFJetsCHSPrunedLinks");     // access to pruned mass
            double filtered_mass = -9999; //patJet->userFloat("ak8PFJetsCHSFilteredLinks"); // access to filtered mass


            localJet.setCmsTopTagNsubjets(nSubJets);
            localJet.setCmsTopTagMass(topMass);
            localJet.setCmsTopTagMinMass(minMass);
            localJet.setTau1(tau1);
            localJet.setTau2(tau2);
            localJet.setTau3(tau3);
            localJet.setFilteredMass(filtered_mass);
            localJet.setPrunedMass(pruned_mass);
            localJet.setTrimmedMass(trimmed_mass);

		  }


		new( (*rootJets)[j] ) TRootSubstructureJet(localJet);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localJet << endl;

	}

}
