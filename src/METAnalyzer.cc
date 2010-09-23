#include "../interface/METAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

METAnalyzer::METAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0), useMC_(false)
{
}

METAnalyzer::METAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	useMC_ = myConfig.getUntrackedParameter<bool>("doMETMC");
}

METAnalyzer::~METAnalyzer()
{
}

TopTree::TRootMET METAnalyzer::Process(const reco::Candidate* met, std::string dataType_)
{

  
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

  if( dataType_=="PAT" )
    {
      // Some specific methods to pat::MET
      const pat::MET *patMET = dynamic_cast<const pat::MET*>(&*met);
      
      localMET.setSumEt(patMET->sumEt());
      
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
  
  return localMET;

}
