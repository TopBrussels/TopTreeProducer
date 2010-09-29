#include "../interface/JPTJetAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

JPTJetAnalyzer::JPTJetAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	JPTJetProducer_ = producersNames.getParameter<edm::InputTag>("JPTJetProducer");
	myJetAnalyzer = new JetAnalyzer();
}

JPTJetAnalyzer::JPTJetAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	JPTJetProducer_ = producersNames.getParameter<edm::InputTag>("JPTJetProducer");
	myJetAnalyzer = new JetAnalyzer(verbosity);
}

JPTJetAnalyzer::JPTJetAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	JPTJetProducer_ = producersNames.getParameter<edm::InputTag>("JPTJetProducer");
	//doJPTJetId_ = myConfig.getUntrackedParameter<bool>("doJPTJetId");
	myJetAnalyzer = new JetAnalyzer(myConfig, verbosity);
}

JPTJetAnalyzer::JPTJetAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	vJPTJetProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vJPTJetProducer");
	JPTJetProducer_ = edm::InputTag(vJPTJetProducer[iter]);
	//doJPTJetId_ = myConfig.getUntrackedParameter<bool>("doJPTJetId");
	myJetAnalyzer = new JetAnalyzer(myConfig, verbosity);
}

JPTJetAnalyzer::~JPTJetAnalyzer()
{
}

void JPTJetAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootJets)
{

	unsigned int nJets=0;

	// check if the jet is of the good type
	std::string jetType = "BASIC";
	
	edm::Handle < std::vector <pat::Jet> > patJets;
	if( dataType_=="PAT" || dataType_=="PATAOD" )
	{
		iEvent.getByLabel(JPTJetProducer_, patJets);
		nJets = patJets->size();
	}
		
	if(verbosity_>1) std::cout << "   Number of jets = " << nJets << "   Label: " << JPTJetProducer_.label() << "   Instance: " << JPTJetProducer_.instance() << std::endl;

	for (unsigned int j=0; j<nJets; j++)
	{
		const reco::Jet* jet = 0;	
	
		if( dataType_=="PAT" || dataType_=="PATAOD" )
		{
			jet = (const reco::Jet*) ( & ((*patJets)[j]) );
			if( (*patJets)[j].isJPTJet() ) jetType="JPT";
		}
		
		// Call JetAnalyzer to fill the basic Jet Properties
		TRootJet tempJet = (TRootJet) myJetAnalyzer->Process( &( *(jet) ), dataType_);

		TRootJPTJet localJet = TRootJPTJet(tempJet);

		localJet.setJetType(3); // 3 = JPTJet
		localJet.setN90(jet->nCarrying(0.9));
		localJet.setN60(jet->nCarrying(0.6));

		if( dataType_=="PATAOD" || dataType_=="PAT" )
		{
			// Some specific methods to pat::Jet
			const pat::Jet *patJet = dynamic_cast<const pat::Jet*>(&*jet);
			localJet.setChargedMultiplicity(patJet->chargedMultiplicity()) ;
			localJet.chargedHadronEnergy(patJet->chargedHadronEnergy());
			localJet.chargedHadronEnergyFraction(patJet->chargedHadronEnergyFraction());
			localJet.neutralHadronEnergy(patJet->neutralHadronEnergy());
			localJet.neutralHadronEnergyFraction(patJet->neutralHadronEnergyFraction());
			localJet.chargedEmEnergy(patJet->chargedEmEnergy());
			localJet.chargedEmEnergyFraction(patJet->chargedEmEnergyFraction());
			localJet.neutralEmEnergy(patJet->neutralEmEnergy());
			localJet.neutralEmEnergyFraction(patJet->neutralEmEnergyFraction());
			

		
		} //end of if( dataType_=="PATAOD" || dataType_=="PAT" )
		
		new( (*rootJets)[j] ) TRootJPTJet(localJet);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localJet << endl;
		
	}

}
