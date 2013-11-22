#include "../interface/PhotonAnalyzer.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

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

  ///following three collections are only needed for electron veto
  ///currently these are hardcoded
  ///we need to create corresponding member function in PAT photon object
  ///otherwise, we need to keep these collections in our PAT output collections in order to produce TOPTREE from PAT (Taejeong)  
  edm::Handle<reco::BeamSpot> bsHandle;
  iEvent.getByLabel("offlineBeamSpot", bsHandle);
  const reco::BeamSpot &beamspot = *bsHandle.product();

  edm::Handle<reco::ConversionCollection> hConversions;
  iEvent.getByLabel("allConversions", hConversions);

  edm::Handle<reco::GsfElectronCollection> hElectrons;
  iEvent.getByLabel("gsfElectrons", hElectrons);

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

      localPhoton.setSigmaIetaIeta( photon->sigmaIetaIeta() );
      localPhoton.setHadronicOverEm( photon->hadronicOverEm() );
      localPhoton.setHasPixelSeed( photon->hasPixelSeed() );

      //prompt electron veto
      bool passelectronveto = !ConversionTools::hasMatchedPromptElectron(photon->superCluster(), hElectrons, hConversions, beamspot.position());
      localPhoton.setPasselectronveto(passelectronveto);

      //currently PF isolation is directly from RECO, which is empty. need to change it (Taejeong) 
      localPhoton.setIsoR03_ChargedHadronIso( photon->chargedHadronIso() );
      localPhoton.setIsoR03_PhotonIso( photon->photonIso() );
      localPhoton.setIsoR03_NeutralHadronIso( photon->neutralHadronIso() );

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
