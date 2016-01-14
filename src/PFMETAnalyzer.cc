#include "../interface/PFMETAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

PFMETAnalyzer::PFMETAnalyzer(const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	myMETAnalyzer = new METAnalyzer(myConfig, verbosity);
}

PFMETAnalyzer::~PFMETAnalyzer()
{
}

void PFMETAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootMET, edm::EDGetTokenT<pat::METCollection> metToken)
{

	unsigned int nMETs=0;

	edm::Handle < std::vector <pat::MET> > patMETs;
	iEvent.getByToken(metToken, patMETs);
	nMETs = patMETs->size();

	if(verbosity_>1) std::cout << "   Number of MET objects = " << nMETs << std::endl;

	for (unsigned int j=0; j<nMETs; j++)
	{
		const reco::Candidate* met = 0;	
		met = (const reco::Candidate*) ( & ((*patMETs)[j]) );

		TRootMET tempMET = (TRootMET) myMETAnalyzer->Process( &( *(met) ) );

		TRootPFMET localMET = TRootPFMET(tempMET);

		localMET.setMETType(2); // 2 = PFMET
    
        const pat::MET *patMET = dynamic_cast<const pat::MET*>(&*met);

    	localMET.setPFMETFraction(patMET->NeutralEMFraction(), patMET->NeutralHadEtFraction(), patMET->ChargedEMEtFraction(), patMET->ChargedHadEtFraction(), patMET->MuonEtFraction(), patMET->Type6EtFraction(), patMET->Type7EtFraction());

		new( (*rootMET)[j] ) TRootPFMET(localMET);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localMET << endl;
	}

}
