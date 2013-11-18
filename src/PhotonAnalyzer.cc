#include "../interface/PhotonAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;
using namespace isodeposit;

PhotonAnalyzer::PhotonAnalyzer (const edm::ParameterSet & producersNames):
verbosity_(0),
useMC_(false)
{
  photonProducer_ = producersNames.getParameter < edm::InputTag > ("photonProducer");
}

PhotonAnalyzer::PhotonAnalyzer (const edm::ParameterSet & producersNames, const edm::ParameterSet & myConfig, int verbosity):
verbosity_ (verbosity)
{
  photonProducer_ = producersNames.getParameter < edm::InputTag > ("photonProducer");
  useMC_ = myConfig.getUntrackedParameter < bool > ("doPhotonMC");
}
PhotonAnalyzer::PhotonAnalyzer (const edm::ParameterSet & producersNames, int iter, const edm::ParameterSet & myConfig, int verbosity):
verbosity_ (verbosity)
{
  vPhotonProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vphotonProducer");
  photonProducer_ =	edm::InputTag(vPhotonProducer[iter]);
  useMC_ = myConfig.getUntrackedParameter < bool > ("doPhotonMC");
}

PhotonAnalyzer::~PhotonAnalyzer ()
{
}

void
PhotonAnalyzer::Process (const edm::Event & iEvent, TClonesArray * rootPhotons, const edm::EventSetup& iSetup)
{
  unsigned int nPhotons = 0;

  edm::Handle < std::vector < pat::Photon > >patPhotons;
  iEvent.getByLabel (photonProducer_, patPhotons);
  nPhotons = patPhotons->size ();

  if (verbosity_ > 1)
    std::cout << "   Number of photons = " << nPhotons << "   Label: " << photonProducer_.label () << "   Instance: " << photonProducer_.instance () << std::endl;

    for (unsigned int j = 0; j < nPhotons; j++)
    {
      const pat::Photon*  patPhoton = &((*patPhotons)[j]);//dynamic_cast < const pat::Photon * >(&*photon);
      const reco::Photon* photon = (const reco::Photon *) patPhoton;//(&((*patPhotons)[j]));

      TRootPhoton localPhoton (photon->px (), photon->py (), photon->pz (), photon->energy ());

      if (useMC_)
      {
        // MC truth associator index
        if ((patPhoton->genParticleRef ()).isNonnull ())
        {
          localPhoton.setGenParticleIndex ((patPhoton->genParticleRef ()).index ());
        }
        else
        {
          localPhoton.setGenParticleIndex (-1);
        }
      }
      
      new ((*rootPhotons)[j]) TRootPhoton (localPhoton);
      if (verbosity_ > 2)
        cout << "   [" << setw (3) << j << "] " << localPhoton << endl;
   }
}
