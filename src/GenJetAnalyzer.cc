#include "../interface/GenJetAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

GenJetAnalyzer::GenJetAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	genJetProducer_ = producersNames.getParameter<edm::InputTag>("genJetProducer");
}

GenJetAnalyzer::GenJetAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	genJetProducer_ = producersNames.getParameter<edm::InputTag>("genJetProducer");
}

GenJetAnalyzer::GenJetAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	genJetProducer_ = producersNames.getParameter<edm::InputTag>("genJetProducer");
}

GenJetAnalyzer::GenJetAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	vGenJetProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vgenJetProducer");
	genJetProducer_ = edm::InputTag(vGenJetProducer[iter]);
}

GenJetAnalyzer::~GenJetAnalyzer()
{
}

void GenJetAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootGenJets)
{

	unsigned int nJets=0;

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
	try {iEvent.getByLabel(genJetProducer_, recoGenJets);} catch (...) {;}
	
	if(recoGenJets.isValid())
	{
		nJets = recoGenJets->size();

		if(verbosity_>1) std::cout << "   Number of jets = " << nJets << "   Label: " << genJetProducer_.label() << "   Instance: " << genJetProducer_.instance() << std::endl;

		for (unsigned int j=0; j<nJets; j++)
		{
			const reco::GenJet* genJet = 0;	
			if( (dataType_=="RECO" || dataType_=="AOD" || dataType_=="PAT" || dataType_=="PATAOD") && jetType=="CALO" ) genJet = (const reco::GenJet*) ( & ((*recoGenJets)[j]) );
			
			// Call JetAnalyzer to fill the basic Jet Properties
//			TRootJet tempJet = (TRootJet) myJetAnalyzer->Process( &( *(genJet) ), dataType_);

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

}
