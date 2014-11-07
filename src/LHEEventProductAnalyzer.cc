#include "../interface/LHEEventProductAnalyzer.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

//using namespace std;
using namespace TopTree;
//using namespace reco;
//using namespace edm;

typedef gen::WeightsInfo WGT;

LHEEventProductAnalyzer::LHEEventProductAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	lheEventProductProducer_ = producersNames.getParameter<edm::InputTag>("lheEventProductProducer");
}

LHEEventProductAnalyzer::LHEEventProductAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	lheEventProductProducer_ = producersNames.getParameter<edm::InputTag>("lheEventProductProducer");
}

LHEEventProductAnalyzer::LHEEventProductAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	lheEventProductProducer_ = producersNames.getParameter<edm::InputTag>("lheEventProductProducer");
}

LHEEventProductAnalyzer::LHEEventProductAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	vLHEEventProductProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vlheEventProductProducer");
	lheEventProductProducer_ = edm::InputTag(vLHEEventProductProducer[iter]);
}


LHEEventProductAnalyzer::~LHEEventProductAnalyzer()
{
}



void LHEEventProductAnalyzer::Process(const edm::Event& iEvent, TRootEvent* rootEvent)
{

  //  cout << "Analysing LHEEventProduct collection ... = "<<  lheEventProductProducer_.label()  << endl;


  //  if( lheEventProductProducer_.label()) != ""

  //	edm::Handle < edm::View <LHEEventProduct> > lheEventProduct;
        edm::Handle<LHEEventProduct> lheEventProduct;
	//	cout << "Analysing LHEEventProduct collection ..1. = "<<endl;

	iEvent.getByLabel( lheEventProductProducer_ ,lheEventProduct );

	//	cout << "Analysing LHEEventProduct collection ..2. = "<<endl;
	// double muf_down_mur_down_weight = lheEventProduct->originalXWGTUP();



	const std::vector<WGT>& weights  = lheEventProduct->weights();
	//	cout << "Analysing LHEEventProduct collection ..3 = "<< muf_down_mur_down_weight  << endl;

        std:vector<double> weights_d;

		for (int w = 0; w < 9; w++){
	 string weight_id = weights[w].id;
	 double weight_val = weights[w].wgt;
	 weights_d.push_back(weight_val);

	 //		cout <<"id  "<< weight_id  <<"  weight = " << weight_val << endl;

	}

		rootEvent->setWeights(weights_d);



	//        cout << "Analysing LHEEventProduct collection ..3. = " <<muf_down_mur_down_weight<<   endl;




}
