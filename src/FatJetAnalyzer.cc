#include "../interface/FatJetAnalyzer.h"
#include "DataFormats/JetReco/interface/CATopJetTagInfo.h"

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

		//extract/write CMS TOP-TAGGING info
		reco::CATopJetTagInfo const * tagInfo =  dynamic_cast<reco::CATopJetTagInfo const *>( patJet->tagInfo("caTop"));
		//bool topTagged = false;

		if ( tagInfo != 0 ) {
            double minMass = tagInfo->properties().minMass;
            double topMass = tagInfo->properties().topMass;
            int nSubJets = tagInfo->properties().nSubJets;
            
            double tau1 = patJet->userFloat("NjettinessAK8:tau1");    //
            double tau2 = patJet->userFloat("NjettinessAK8:tau2");    //  Access the n-subjettiness variables
            double tau3 = patJet->userFloat("NjettinessAK8:tau3");    //
            
            double trimmed_mass = patJet->userFloat("ak8PFJetsCHSTrimmedLinks");   // access to trimmed mass
            double pruned_mass = patJet->userFloat("ak8PFJetsCHSPrunedLinks");     // access to pruned mass
            double filtered_mass = patJet->userFloat("ak8PFJetsCHSFilteredLinks"); // access to filtered mass
            
            
            localJet.setCmsTopTagNsubjets(nSubJets);
            localJet.setCmsTopTagMass(topMass);
            localJet.setCmsTopTagMinMass(minMass);
            localJet.setTau1(tau1);
            localJet.setTau2(tau2);
            localJet.setTau3(tau3);
            localJet.setFilteredMass(filtered_mass);
            localJet.setPrunedMass(pruned_mass);
            localJet.setTrimmedMass(trimmed_mass);
            // if ( nSubJets > 2 && minMass > 50.0 && topMass > 150.0 )
            //   topTagged = true;
		  }


		new( (*rootJets)[j] ) TRootSubstructureJet(localJet);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localJet << endl;
		
	}

}
