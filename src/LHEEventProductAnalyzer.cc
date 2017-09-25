#include "../interface/LHEEventProductAnalyzer.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
//using namespace std;
using namespace TopTree;
//using namespace reco;
//using namespace edm;

typedef gen::WeightsInfo WGT;

LHEEventProductAnalyzer::LHEEventProductAnalyzer(int verbosity):
verbosity_(verbosity)
{
}


LHEEventProductAnalyzer::~LHEEventProductAnalyzer()
{
}



void LHEEventProductAnalyzer::Process(const edm::Event& iEvent, TRootEvent* rootEvent,edm::EDGetTokenT<LHEEventProduct> lheproductToken,
					edm::EDGetTokenT<std::vector<reco::GenJet> >& genJetsFromPseudoTopToken,
					const edm::EDGetTokenT<edm::ValueMap<float> >& upFragToken,
					const edm::EDGetTokenT<edm::ValueMap<float> >& centralFragToken,
					const edm::EDGetTokenT<edm::ValueMap<float> >& downFragToken,
					const edm::EDGetTokenT<edm::ValueMap<float> >& petersonFragToken,
					const edm::EDGetTokenT<edm::ValueMap<float> >& semilepbrUpToken,
					const edm::EDGetTokenT<edm::ValueMap<float> >& semilepbrDownToken
)
{


	if(verbosity_ > 1) cout << endl << "Analysing LHEEventProduct collection ... = "<<  lheEventProductProducer_.label()  << endl;

	edm::Handle<LHEEventProduct> lheEventProduct;

	if(    iEvent.getByToken( lheproductToken ,lheEventProduct ) ){

		if(verbosity_ > 2) cout << "Analysing LHEEventProduct, collection present "<<endl;

		const std::vector<WGT>& weights  = lheEventProduct->weights();
        if(verbosity_ > 2) cout << "Analysing LHEEventProduct, weights vector assigned"<<endl;
		std::vector<Float_t> weights_d;
		rootEvent->setOriginalXWGTUP(lheEventProduct->originalXWGTUP());

		for (unsigned int w = 0; w < weights.size(); w++)
		{

			int weight_id = std::stoi(weights[w].id);
			if(verbosity_ > 3) cout << "Analysing LHEEventProduct, Weight name extracted"<<endl;
			float weight_val = weights[w].wgt;
			if(verbosity_ > 3) cout << "Analysing LHEEventProduct, Weight value extracted"<<endl;
			rootEvent->setWeight(weight_id, weight_val);

			if(verbosity_ > 3) cout <<"id  "<< weight_id  <<"  weight = " << rootEvent->getWeight(weight_id) << " set successfully" << endl;

		}
	}

	// BFragmentation weights (https://gitlab.cern.ch/CMS-TOPPAG/BFragmentationAnalyzer/tree/master)
	edm::Handle<edm::ValueMap<float> > upFrag;
	edm::Handle<edm::ValueMap<float> > centralFrag;
	edm::Handle<edm::ValueMap<float> > downFrag;
	edm::Handle<edm::ValueMap<float> > petersonFrag;
	edm::Handle<edm::ValueMap<float> > semilepbrUp;
	edm::Handle<edm::ValueMap<float> > semilepbrDown;
	iEvent.getByToken(upFragToken,upFrag); 
	iEvent.getByToken(centralFragToken,centralFrag); 
	iEvent.getByToken(downFragToken,downFrag); 
	iEvent.getByToken(petersonFragToken,petersonFrag); 
	iEvent.getByToken(semilepbrUpToken,semilepbrUp); 
	iEvent.getByToken(semilepbrDownToken,semilepbrDown); 

	edm::Handle<std::vector<reco::GenJet> > genJetsFromPseudoTop;
	iEvent.getByToken(genJetsFromPseudoTopToken,genJetsFromPseudoTop);

	std::map<string,double> bfragwgt;
	double eventupFragWeight = 1.;
	double eventcentralFragWeight= 1.;
	double eventdownFragWeight = 1.;
	double eventpetersonFragWeight = 1.;
	double eventsemilepbrUp= 1.;
	double eventsemilepbrDown= 1.;
	for(auto genJet=genJetsFromPseudoTop->begin(); genJet!=genJetsFromPseudoTop->end(); ++genJet)
	{
		edm::Ref<std::vector<reco::GenJet> > genJetRef(genJetsFromPseudoTop,genJet-genJetsFromPseudoTop->begin());
		//cout << "pt=" << genJet->pt() << " id=" << genJet->pdgId() << " upFragWeight=" << (*upFrag)[genJetRef] << endl;
		//cout << "pt=" << genJet->pt() << " id=" << genJet->pdgId() << " centralFragWeight=" << (*centralFrag)[genJetRef] << endl;
		//cout << "pt=" << genJet->pt() << " id=" << genJet->pdgId() << " downFragWeight=" << (*downFrag)[genJetRef] << endl;
		//cout << "pt=" << genJet->pt() << " id=" << genJet->pdgId() << " petersonFragWeight=" << (*petersonFrag)[genJetRef] << endl;
		//cout << "pt=" << genJet->pt() << " id=" << genJet->pdgId() << " semilepbrUp=" << (*semilepbrUp)[genJetRef] << endl;
		//cout << "pt=" << genJet->pt() << " id=" << genJet->pdgId() << " semilepbrDown=" << (*semilepbrDown)[genJetRef] << endl;
		//std::map<std::string,double> wgts =  {{"upFragWeight", (*upFrag)[genJetRef]}, {"centralFragWeight", (*centralFrag)[genJetRef]}, 
		//				      {"downFragWeight", (*downFrag)[genJetRef]}, {"petersonFragWeight", (*petersonFrag)[genJetRef]},
		//				      {"semilepbrUp", (*semilepbrUp)[genJetRef]}, {"semilepbrDown", (*semilepbrDown)[genJetRef]}};
		//
		eventupFragWeight 		*= (*upFrag)[genJetRef];
		eventcentralFragWeight		*= (*centralFrag)[genJetRef];
		eventdownFragWeight 		*= (*downFrag)[genJetRef];
		eventpetersonFragWeight 	*= (*petersonFrag)[genJetRef];
		eventsemilepbrUp		*= (*semilepbrUp)[genJetRef];
		eventsemilepbrDown		*= (*semilepbrDown)[genJetRef];
	}
	bfragwgt["upFragWeight"]  			= eventupFragWeight;
	bfragwgt["centralFragWeight"] 			= eventcentralFragWeight;
	bfragwgt["downFragWeight"] 			= eventdownFragWeight;
	bfragwgt["petersonFragWeight"] 			= eventpetersonFragWeight;
	bfragwgt["semilepbrUp"] 			= eventsemilepbrUp;
	bfragwgt["semilepbrDown"] 			= eventsemilepbrDown;
	rootEvent->setBFragmentationWeights(bfragwgt);	
}

 void LHEEventProductAnalyzer::PrintWeightNamesList(const edm::Run& iRun,edm::EDGetTokenT<LHERunInfoProduct> lheRunInfoproductToken) //To know which integer XXX corresponds to which weight
 {
 	edm::Handle<LHERunInfoProduct> run;
 	typedef std::vector<LHERunInfoProduct::Header>::const_iterator headers_const_iterator;

 	if(iRun.getByToken( lheRunInfoproductToken, run )){
 	LHERunInfoProduct myLHERunInfoProduct = *(run.product());

 	for (headers_const_iterator iter=myLHERunInfoProduct.headers_begin(); iter!=myLHERunInfoProduct.headers_end(); iter++){
 		std::cout << iter->tag() << std::endl;
 		std::vector<std::string> lines = iter->lines();
 		for (unsigned int iLine = 0; iLine<lines.size(); iLine++) {
 			std::cout << lines.at(iLine);
 		}
 	}
 	}
 }

 void LHEEventProductAnalyzer::CopyWeightNames(const edm::Run& iRun, TRootRun* runInfos,edm::EDGetTokenT<LHERunInfoProduct> lheRunInfoproductToken)
 {
     edm::Handle<LHERunInfoProduct> run;
 	typedef std::vector<LHERunInfoProduct::Header>::const_iterator headers_const_iterator;

 	std::map <std::string,int> weights_d;

 	std::string weightGroup, weightId, weightName, theLine;
 	std::string endTag = "\">";

 	int groupMember = 0;


 	bool openGroup = false;

 	if(iRun.getByToken( lheRunInfoproductToken, run )){
 	LHERunInfoProduct myLHERunInfoProduct = *(run.product());
 	if (verbosity_ > 1) cout << "LHEEventRunInfoProduct retreived." << endl;

 	for (headers_const_iterator iter=myLHERunInfoProduct.headers_begin(); iter!=myLHERunInfoProduct.headers_end(); iter++){
 		if (verbosity_ > 1) std::cout << "LHEEventProductAnalyzer Tag: " << iter->tag() << std::endl;
 		std::vector<std::string> lines = iter->lines();
 		for (unsigned int iLine = 0; iLine<lines.size(); iLine++) {
                theLine = lines.at(iLine);
 			if(theLine.find("<weightgroup") != string::npos ) //This is a Weight Group header line
            {
                openGroup = true;  //signifies that you are inside weightgroup tags
                groupMember = 1; // resets the group member counter to 1
                size_t groupStart = theLine.find("type=")+6;
                size_t eTag = theLine.find(endTag);
                size_t groupLen = eTag - groupStart;
                weightGroup = theLine.substr(groupStart, groupLen) + " ";
                if (verbosity_ > 1) cout << "WeightGroup " << weightGroup << endl;
            }
            else if (theLine.find("</weightgroup") != string::npos)
            {
                openGroup = false; //closing the weightgroup tag
            }
            else if (openGroup) //if you are inside a weightgroup tag
            {
                size_t idStart = theLine.find("\"")+1;
                size_t idEnd = theLine.find("\"", idStart);
                size_t idLen = idEnd - idStart;
                weightId = theLine.substr(idStart, idLen);

                weightName = weightGroup + std::to_string(groupMember);
                if (verbosity_ > 3) cout << "WeightName " << weightName << " ID: " << weightId << endl;

                weights_d[weightName] = std::stoi(weightId);
                if (verbosity_ > 3) cout << "WeightName " << weightName << " set to ID: " << weights_d[weightName] << endl;

                groupMember++;
            }
 		}
 	}

    runInfos->setWeights(weights_d, iRun.run());
 	}
 }
