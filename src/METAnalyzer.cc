#include "../interface/METAnalyzer.h"

using namespace std;
using namespace reco;
using namespace edm;

METAnalyzer::METAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0), useMC_(false)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	metProducer_ = producersNames.getParameter<edm::InputTag>("metProducer");
}

METAnalyzer::METAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	metProducer_ = producersNames.getParameter<edm::InputTag>("metProducer");
	useMC_ = myConfig.getUntrackedParameter<bool>("doMETMC");
}

METAnalyzer::~METAnalyzer()
{
}

void METAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootMET)
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

		TRootMET localMET(
			met->px()
			,met->py()
			,met->pz()
			,met->energy()
			,met->vx()
			,met->vy()
			,met->vz()
		); 


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

		if( dataType_=="PATAOD" )
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

			//pat::MET::UncorectionType ix;
			//ix = pat::MET::uncorrALL;
			localMET.setCorExALL(patMET->corEx(pat::MET::uncorrALL));
			localMET.setCorExJES(patMET->corEx(pat::MET::uncorrJES));
			localMET.setCorExMUON(patMET->corEx(pat::MET::uncorrMUON));

			localMET.setCorEyALL(patMET->corEy(pat::MET::uncorrALL));
			localMET.setCorEyJES(patMET->corEy(pat::MET::uncorrJES));
			localMET.setCorEyMUON(patMET->corEy(pat::MET::uncorrMUON));

			localMET.setCorSumEtALL(patMET->corSumEt(pat::MET::uncorrALL));
			localMET.setCorSumEtJES(patMET->corSumEt(pat::MET::uncorrJES));
			localMET.setCorSumEtMUON(patMET->corSumEt(pat::MET::uncorrMUON));

			localMET.setUncorrectedPhiALL(patMET->uncorrectedPhi(pat::MET::uncorrALL));
			localMET.setUncorrectedPhiJES(patMET->uncorrectedPhi(pat::MET::uncorrJES));
			localMET.setUncorrectedPhiMUON(patMET->uncorrectedPhi(pat::MET::uncorrMUON));

			localMET.setUncorrectedPtALL(patMET->uncorrectedPt(pat::MET::uncorrALL));
			localMET.setUncorrectedPtJES(patMET->uncorrectedPt(pat::MET::uncorrJES));
			localMET.setUncorrectedPtMUON(patMET->uncorrectedPt(pat::MET::uncorrMUON));

			if(useMC_)
			{
				// MC truth associator index
				if ((patMET->genParticleRef()).isNonnull()) {
					localMET.setGenParticleIndex((patMET->genParticleRef()).index());
				} else {
					localMET.setGenParticleIndex(-1);
				}
			}
		}

		new( (*rootMET)[j] ) TRootMET(localMET);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localMET << endl;
	}

}
