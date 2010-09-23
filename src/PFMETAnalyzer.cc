#include "../interface/PFMETAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

PFMETAnalyzer::PFMETAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0), useMC_(false)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	metProducer_ = producersNames.getParameter<edm::InputTag>("PFmetProducer");
	myMETAnalyzer = new METAnalyzer(producersNames);
}

PFMETAnalyzer::PFMETAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	metProducer_ = producersNames.getParameter<edm::InputTag>("PFmetProducer");
	useMC_ = myConfig.getUntrackedParameter<bool>("doMETMC");
	myMETAnalyzer = new METAnalyzer(producersNames,myConfig, verbosity);

}

PFMETAnalyzer::~PFMETAnalyzer()
{
}

void PFMETAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootMET)
{

	unsigned int nMETs=0;

	edm::Handle < std::vector <reco::PFMET> > recoMETs;
	if( dataType_=="RECO" || dataType_=="AOD" )
	{
		iEvent.getByLabel(metProducer_, recoMETs);
		nMETs = recoMETs->size();
	}

	edm::Handle < std::vector <pat::MET> > patMETs;
	if( dataType_=="PAT" || dataType_=="PATAOD" )
	{
		iEvent.getByLabel(metProducer_, patMETs);
		nMETs = patMETs->size();
	}

	if(verbosity_>1) std::cout << "   Number of MET objects = " << nMETs << "   Label: " << metProducer_.label() << "   Instance: " << metProducer_.instance() << std::endl;

	for (unsigned int j=0; j<nMETs; j++)
	{
		const reco::Candidate* met = 0;	
		if( dataType_=="RECO" || dataType_=="AOD" ) met = (const reco::Candidate*) ( & ((*recoMETs)[j]) );
		if( dataType_=="PAT" || dataType_=="PATAOD" ) met = (const reco::Candidate*) ( & ((*patMETs)[j]) );

		TRootMET tempMET = (TRootMET) myMETAnalyzer->Process( &( *(met) ), dataType_ );

		TRootPFMET localMET = TRootPFMET(tempMET);


		if( dataType_=="RECO" || dataType_=="AOD" || dataType_=="PATAOD")
		{
			// Some specific methods to reco::MET


		}

		if( dataType_=="PAT" )
		  {
			// Some specific methods to pat::MET
		    /*const pat::MET *patMET = dynamic_cast<const pat::MET*>(&*met);	
		   
		    // Not yet available in CMSSW_3_8_X X<=4
		    localMET.setPFMETFraction(
					       patMET->NeutralEMFraction()
					       ,patMET->NeutralHadEtFraction()
					       ,patMET->ChargedEMEtFraction()
					       ,patMET->ChargedHadEtFraction()
					       ,patMET->MuonEtFraction()
					       ,patMET->Type6EtFraction() 
					       ,patMET->Type7EtFraction()
					       );*/
					       
		  }

		new( (*rootMET)[j] ) TRootPFMET(localMET);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localMET << endl;
	}

}
