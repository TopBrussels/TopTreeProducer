
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

TopTree::TRootMET METAnalyzer::Process(const reco::Candidate* met)
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
  
  const pat::MET *patMET = dynamic_cast<const pat::MET*>(&*met);
      
  localMET.setSumEt(patMET->sumEt());
      
  if(useMC_)
 	{
    // MC truth associator index
	  if ((patMET->genParticleRef()).isNonnull()) localMET.setGenParticleIndex((patMET->genParticleRef()).index());
	  else localMET.setGenParticleIndex(-1);
  }
  
  return localMET;
}
