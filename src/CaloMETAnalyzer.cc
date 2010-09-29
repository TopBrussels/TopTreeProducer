#include "../interface/CaloMETAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

CaloMETAnalyzer::CaloMETAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0), useMC_(false)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	metProducer_ = producersNames.getParameter<edm::InputTag>("CalometProducer");
	myMETAnalyzer = new METAnalyzer(producersNames);
}

CaloMETAnalyzer::CaloMETAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	metProducer_ = producersNames.getParameter<edm::InputTag>("CalometProducer");
	useMC_ = myConfig.getUntrackedParameter<bool>("doMETMC");
	myMETAnalyzer = new METAnalyzer(producersNames,myConfig, verbosity);

}

CaloMETAnalyzer::~CaloMETAnalyzer()
{
}

void CaloMETAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootMET)
{

	unsigned int nMETs=0;

	edm::Handle < std::vector <reco::CaloMET> > recoMETs;
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

		TRootCaloMET localMET = TRootCaloMET(tempMET);

		localMET.setMETType(1); // 1 = CaloMET

		if( dataType_=="RECO" || dataType_=="AOD" || dataType_=="PATAOD")
		{
			// Some specific methods to reco::MET
			/*
			const reco::CaloMET *recoMET = dynamic_cast<const reco::CaloMET*>(&*met);
			localMET.setCaloMETFraction(
				recoMET->maxEtInEmTowers()
				,recoMET->maxEtInHadTowers()
				,recoMET->hadEtInHO()
				,recoMET->hadEtInHB()
				,recoMET->hadEtInHF()
				,recoMET->hadEtInHE()
				,recoMET->emEtInEB()
				,recoMET->emEtInEE()
				,recoMET->emEtInHF()
				,recoMET->etFractionHadronic()
				,recoMET->emEtFraction()
				,recoMET->metSignificance()
				,recoMET->CaloMETInpHF()
				,recoMET->CaloMETInmHF()
				,recoMET->CaloSETInpHF()
				,recoMET->CaloSETInmHF()
				,recoMET->CaloMETPhiInpHF()
				,recoMET->CaloMETPhiInmHF()
			);
			*/

		}

		if( dataType_=="PAT" )
		  {
			// Some specific methods to pat::MET
			const pat::MET *patMET = dynamic_cast<const pat::MET*>(&*met);

			localMET.setCaloMETFraction(
				patMET->maxEtInEmTowers()
				,patMET->maxEtInHadTowers()
				,patMET->hadEtInHO()
				,patMET->hadEtInHB()
				,patMET->hadEtInHF()
				,patMET->hadEtInHE()
				,patMET->emEtInEB()
				,patMET->emEtInEE()
				,patMET->emEtInHF()
				,patMET->etFractionHadronic()
				,patMET->emEtFraction()
				,patMET->metSignificance()
				,patMET->CaloMETInpHF()
				,patMET->CaloMETInmHF()
				,patMET->CaloSETInpHF()
				,patMET->CaloSETInmHF()
				,patMET->CaloMETPhiInpHF()
				,patMET->CaloMETPhiInmHF()
				);
			
		}

		new( (*rootMET)[j] ) TRootCaloMET(localMET);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localMET << endl;
	}

}
