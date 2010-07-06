#include "../interface/MHTAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

MHTAnalyzer::MHTAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	mhtProducer_ = producersNames.getParameter<edm::InputTag>("mhtProducer");
}

MHTAnalyzer::MHTAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	mhtProducer_ = producersNames.getParameter<edm::InputTag>("mhtProducer");
}

MHTAnalyzer::~MHTAnalyzer()
{
}

void MHTAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootMHT)
{

	unsigned int nMHTs=0;

	edm::Handle < std::vector <pat::MHT> > patMHTs;
	if( dataType_=="PAT" || dataType_=="PATAOD" )
	{
		iEvent.getByLabel(mhtProducer_, patMHTs);
		nMHTs = patMHTs->size();
	}

	if(verbosity_>1) std::cout << "   Number of MHT objects = " << nMHTs << "   Label: " << mhtProducer_.label() << "   Instance: " << mhtProducer_.instance() << std::endl;

	for (unsigned int j=0; j<nMHTs; j++)
	{
//		if( dataType_=="PAT" || dataType_=="PATAOD" ) met = (const reco::Candidate*) ( & ((*patMETs)[j]) );

		TRootMHT localMHT = TRootMHT();

		if( dataType_=="PAT" || dataType_=="PATAOD" )
		{
			// Some specific methods to pat::MHT
			const pat::MHT *patMHT = ( & ((*patMHTs)[j]) );

			localMHT = TRootMHT(
				patMHT->px()
				,patMHT->py()
				,patMHT->pz()
				,patMHT->energy()
				,patMHT->vx()
				,patMHT->vy()
				,patMHT->vz()
			); 

			localMHT.setHT(patMHT->ht());
			localMHT.setSignificance(patMHT->significance());
			localMHT.setNJets(patMHT->getNumberOfJets());
			localMHT.setNElectrons(patMHT->getNumberOfElectrons());
			localMHT.setNMuons(patMHT->getNumberOfMuons());
		}

		new( (*rootMHT)[j] ) TRootMHT(localMHT);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localMHT << endl;
	}

}
