#include "../interface/GenJetAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

GenJetAnalyzer::GenJetAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	genJetProducer_ = producersNames.getParameter<edm::InputTag>("genJetProducer");
}

GenJetAnalyzer::GenJetAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	genJetProducer_ = producersNames.getParameter<edm::InputTag>("genJetProducer");
}

GenJetAnalyzer::GenJetAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	genJetProducer_ = producersNames.getParameter<edm::InputTag>("genJetProducer");
}

GenJetAnalyzer::GenJetAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	vGenJetProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vgenJetProducer");
	genJetProducer_ = edm::InputTag(vGenJetProducer[iter]);
}

GenJetAnalyzer::~GenJetAnalyzer()
{
}

void GenJetAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootGenJets)
{
	// check if the genJet is of the good type
	std::string jetType = "BASIC";
	if( genJetProducer_.label()=="kt4GenJets"
		|| genJetProducer_.label()=="kt6GenJets"
		|| genJetProducer_.label()=="iterativeCone5GenJets"
		|| genJetProducer_.label()=="sisCone5GenJets"
		|| genJetProducer_.label()=="sisCone7GenJets"
      || genJetProducer_.label()=="ak5GenJets"
      || genJetProducer_.label()=="ak7GenJets"
      || genJetProducer_.label()=="ak5GenJetsNoE"
	) jetType="CALO";

	edm::Handle < edm::View <reco::GenJet> > recoGenJets;
	iEvent.getByLabel(genJetProducer_, recoGenJets);
	
	unsigned int nJets = recoGenJets->size();

	if(verbosity_>1) std::cout << "   Number of jets = " << nJets << "   Label: " << genJetProducer_.label() << "   Instance: " << genJetProducer_.instance() << std::endl;

	for (unsigned int j=0; j<nJets; j++)
	{
		const reco::GenJet* genJet = 0;	
		if( jetType=="CALO" ) genJet = (const reco::GenJet*) ( & ((*recoGenJets)[j]) );
			
		// Call JetAnalyzer to fill the basic Jet Properties
//		TRootJet tempJet = (TRootJet) myJetAnalyzer->Process( &( *(genJet) ));

		TRootGenJet localGenJet(
			genJet->px()
			,genJet->py()
			,genJet->pz()
			,genJet->energy()
			,genJet->vx()
			,genJet->vy()
			,genJet->vz()
			,genJet->pdgId()
			,genJet->charge()
		);

		localGenJet.setNConstituents(genJet->nConstituents());
		localGenJet.setMaxDistance(genJet->maxDistance());
		localGenJet.setN90(genJet->nCarrying(0.9));
		localGenJet.setN60(genJet->nCarrying(0.6));
		localGenJet.setetaetaMoment(genJet->etaetaMoment());
		localGenJet.setphiphiMoment(genJet->phiphiMoment());
		localGenJet.setEMEnergy(genJet->emEnergy());
		localGenJet.setHadEnergy(genJet->hadEnergy());
		localGenJet.setInvisibleEnergy(genJet->invisibleEnergy());
				
		new( (*rootGenJets)[j] ) TRootGenJet(localGenJet);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localGenJet << endl;
	}
}
