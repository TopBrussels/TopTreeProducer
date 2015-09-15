#include "../interface/LHEEventProductAnalyzer.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

//using namespace std;
using namespace TopTree;
//using namespace reco;
//using namespace edm;

typedef gen::WeightsInfo WGT;

LHEEventProductAnalyzer::LHEEventProductAnalyzer(const edm::ParameterSet& producersNames):
verbosity_(0), lheEventProductProducer_(producersNames.getParameter<edm::InputTag>("lheEventProductProducer"))
{
}

LHEEventProductAnalyzer::LHEEventProductAnalyzer(const edm::ParameterSet& producersNames, int verbosity):
verbosity_(verbosity), 
lheEventProductProducer_(producersNames.getParameter <edm::InputTag>("lheEventProductProducer"))
{
}

LHEEventProductAnalyzer::LHEEventProductAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):
verbosity_(verbosity), 
lheEventProductProducer_(producersNames.getParameter <edm::InputTag>("lheEventProductProducer"))
{
}

LHEEventProductAnalyzer::LHEEventProductAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity):
verbosity_(verbosity), 
vLHEEventProductProducer(producersNames.getUntrackedParameter <std::vector<std::string> >("vlheEventProductProducer")),
lheEventProductProducer_(edm::InputTag(vLHEEventProductProducer[iter]))
{
}


LHEEventProductAnalyzer::~LHEEventProductAnalyzer()
{
}



void LHEEventProductAnalyzer::Process(const edm::Event& iEvent, TRootEvent* rootEvent)
{


	if(verbosity_ > 1) cout << "Analysing LHEEventProduct collection ... = "<<  lheEventProductProducer_.label()  << endl;

	edm::Handle<LHEEventProduct> lheEventProduct;

	if(    iEvent.getByLabel( lheEventProductProducer_ ,lheEventProduct ) ){

		if(verbosity_ > 1) cout << "Analysing LHEEventProduct, collection present "<<endl;

		const std::vector<WGT>& weights  = lheEventProduct->weights();

		std::vector<Float_t> weights_d;

		for (int w = 0; w < 9; w++)
		{
			std::string weight_id = weights[w].id;
			double weight_val = weights[w].wgt;
			weights_d.push_back(weight_val);

			if(verbosity_ > 1) cout <<"id  "<< weight_id  <<"  weight = " << weight_val << endl;

		}

		rootEvent->setWeights(weights_d);

		if(verbosity_ > 1) cout << "Weights succesfully extracted  "<<   endl;

	} 
}

void LHEEventProductAnalyzer::PrintWeightNamesList(const edm::Event& iEvent, TRootEvent* rootEvent) //To know which integer XXX corresponds to which weight
{
	edm::Handle<LHERunInfoProduct> run; 
	typedef std::vector<LHERunInfoProduct::Header>::const_iterator headers_const_iterator;

	iRun.getByLabel( "externalLHEProducer", run );
	LHERunInfoProduct myLHERunInfoProduct = *(run.product());

	for (headers_const_iterator iter=myLHERunInfoProduct.headers_begin(); iter!=myLHERunInfoProduct.headers_end(); iter++){
		std::cout << iter->tag() << std::endl;
		std::vector<std::string> lines = iter->lines();
		for (unsigned int iLine = 0; iLine<lines.size(); iLine++) {
			std::cout << lines.at(iLine);
		}
	}
}
