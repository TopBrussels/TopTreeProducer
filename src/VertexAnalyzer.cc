#include "../interface/VertexAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;


VertexAnalyzer::VertexAnalyzer(int verbosity):verbosity_(verbosity)
{
}

VertexAnalyzer::~VertexAnalyzer()
{
}

void VertexAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootVertex, edm::EDGetTokenT<reco::VertexCollection> vtxToken)
{

	edm::Handle< reco::VertexCollection > recoVertex;
	iEvent.getByToken(vtxToken, recoVertex);
	if(verbosity_>1) std::cout  << "   Number of primary vertices = " << recoVertex->size() << std::endl;

	for (unsigned int j=0; j<recoVertex->size(); j++)
	{
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] Vertex  -  (vx,vy,vz)=(" << setw(12) << (*recoVertex)[j].x() << ", " << setw(12) <<  (*recoVertex)[j].y() << ", " << setw(12) << (*recoVertex)[j].z() << ")" << endl;

		const reco::Vertex * vertex = 0;
		vertex = &((*recoVertex)[j]);
		
		TRootVertex localVertex(vertex->x(), vertex->y(), vertex->z());

		localVertex.setIsValid(vertex->isValid());
		localVertex.setIsFake(vertex->isFake());
		localVertex.setChi2(vertex->chi2());
		localVertex.setNdof(vertex->ndof());
		localVertex.setTracksSize(vertex->tracksSize());
		
		localVertex.setXError(vertex->xError());
		localVertex.setYError(vertex->yError());
		localVertex.setZError(vertex->zError());

		new ((*rootVertex)[j]) TRootVertex (localVertex);
	}

}
