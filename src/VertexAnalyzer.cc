#include "../interface/VertexAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

VertexAnalyzer::VertexAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
}

VertexAnalyzer::VertexAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	primaryVertexProducer_ = producersNames.getParameter<edm::InputTag>("primaryVertexProducer");
}

VertexAnalyzer::~VertexAnalyzer()
{
}

void VertexAnalyzer::Process(const edm::Event& iEvent, TRootEvent* rootEvent)
{

	edm::Handle< reco::VertexCollection > recoVertex;
	iEvent.getByLabel(primaryVertexProducer_, recoVertex);
	if(verbosity_>1) std::cout  << "   Number of primary vertices = " << recoVertex->size() << "   Label: " << primaryVertexProducer_.label() << "   Instance: " << primaryVertexProducer_.instance() << std::endl;
	for (unsigned int j=0; j<recoVertex->size(); j++)
	{
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] Vertex  -  (vx,vy,vz)=(" << setw(12) << (*recoVertex)[j].x() << ", " << setw(12) <<  (*recoVertex)[j].y() << ", " << setw(12) << (*recoVertex)[j].z() << ")" << endl;
		rootEvent->addPrimaryVertex( TVector3( (*recoVertex)[j].x(), (*recoVertex)[j].y(), (*recoVertex)[j].z() ) );
	}

}
