#include "../interface/PFJetAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

PFJetAnalyzer::PFJetAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	pfJetProducer_ = producersNames.getParameter<edm::InputTag>("pfJetProducer");
	myJetAnalyzer = new JetAnalyzer();
}

PFJetAnalyzer::PFJetAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	pfJetProducer_ = producersNames.getParameter<edm::InputTag>("pfJetProducer");
	myJetAnalyzer = new JetAnalyzer(verbosity);
}

PFJetAnalyzer::PFJetAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	pfJetProducer_ = producersNames.getParameter<edm::InputTag>("pfJetProducer");
	myJetAnalyzer = new JetAnalyzer(myConfig, verbosity);
}

PFJetAnalyzer::PFJetAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	vPFJetProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vpfJetProducer");
	pfJetProducer_ = edm::InputTag(vPFJetProducer[iter]);
	myJetAnalyzer = new JetAnalyzer(myConfig, verbosity);
}

PFJetAnalyzer::~PFJetAnalyzer()
{
}

void PFJetAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootJets)
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

	edm::Handle < std::vector <reco::PFJet> > recoPFJets;
	if( (dataType_=="RECO" || dataType_=="AOD") && jetType=="PF" )
	{
		iEvent.getByLabel(pfJetProducer_, recoPFJets);
		nJets = recoPFJets->size();
	}

	edm::Handle < std::vector <pat::Jet> > patJets;
	if( dataType_=="PAT" || dataType_=="PATAOD" )
	{
		iEvent.getByLabel(pfJetProducer_, patJets);
		nJets = patJets->size();
	}
		
	if(verbosity_>1) std::cout << "   Number of jets = " << nJets << "   Label: " << pfJetProducer_.label() << "   Instance: " << pfJetProducer_.instance() << std::endl;

	for (unsigned int j=0; j<nJets; j++)
	{
		const reco::Jet* jet = 0;	
		if( (dataType_=="RECO" || dataType_=="AOD") && jetType=="PF" ) jet = (const reco::Jet*) ( & ((*recoPFJets)[j]) );
		if( dataType_=="PAT" || dataType_=="PATAOD" )
		{
			jet = (const reco::Jet*) ( & ((*patJets)[j]) );
			if( (*patJets)[j].isPFJet() ) jetType="PF";
		}
		
		// Call JetAnalyzer to fill the basic Jet Properties
		TRootJet tempJet = myJetAnalyzer->Process( &( *(jet) ), dataType_);
		
		TRootPFJet localJet = TRootPFJet(tempJet);

		localJet.setJetType(2); // 2 = PFJet

		if( dataType_=="RECO" || dataType_=="AOD" )
		{
			//Some specific methods to reco::PFJet
			const reco::PFJet *pfJet = dynamic_cast<const reco::PFJet*>(&*jet);

			localJet.setChargedHadronEnergyFraction(pfJet->chargedHadronEnergyFraction());
			localJet.setNeutralHadronEnergyFraction(pfJet->neutralHadronEnergyFraction());
			localJet.setChargedEmEnergyFraction(pfJet->chargedEmEnergyFraction());
			localJet.setChargedMuEnergyFraction(pfJet->chargedMuEnergyFraction());
			localJet.setNeutralEmEnergyFraction(pfJet->neutralEmEnergyFraction());
			localJet.setChargedMultiplicity(pfJet->chargedMultiplicity());
			localJet.setNeutralMultiplicity(pfJet->neutralMultiplicity());
			localJet.setMuonMultiplicity(pfJet->muonMultiplicity());
		}

		if( dataType_=="PATAOD" || dataType_=="PAT" )
		{
			// Some specific methods to pat::Jet
			const pat::Jet *patJet = dynamic_cast<const pat::Jet*>(&*jet);

			localJet.setChargedHadronEnergyFraction(patJet->chargedHadronEnergyFraction());
			localJet.setNeutralHadronEnergyFraction(patJet->neutralHadronEnergyFraction());
			localJet.setChargedEmEnergyFraction(patJet->chargedEmEnergyFraction());
			localJet.setChargedMuEnergyFraction(patJet->chargedMuEnergyFraction());
			localJet.setNeutralEmEnergyFraction(patJet->neutralEmEnergyFraction());
			localJet.setChargedMultiplicity(patJet->chargedMultiplicity());
			localJet.setNeutralMultiplicity(patJet->neutralMultiplicity());
			localJet.setMuonMultiplicity(patJet->muonMultiplicity());
		}

		new( (*rootJets)[j] ) TRootPFJet(localJet);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localJet << endl;
		
	}

}
