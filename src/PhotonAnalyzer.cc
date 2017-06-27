#include "../interface/PhotonAnalyzer.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "../interface/ElectronAnalyzer.h"


using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;
using namespace isodeposit;

PhotonAnalyzer::PhotonAnalyzer (const edm::ParameterSet & myConfig, int verbosity):
verbosity_ (verbosity)
{
  useMC_ = myConfig.getUntrackedParameter < bool > ("doPhotonMC");
}

PhotonAnalyzer::~PhotonAnalyzer ()
{
}

void
PhotonAnalyzer::Process (const edm::Event & iEvent, TClonesArray * rootPhotons, const edm::EventSetup& iSetup, edm::EDGetTokenT<pat::PhotonCollection> photonToken)
{
  unsigned int nPhotons = 0;

  ///following three collections are only needed for electron veto
  ///currently these are hardcoded
  ///we need to create corresponding member function in PAT photon object
  ///otherwise, we need to keep these collections in our PAT output collections in order to produce TOPTREE from PAT (Taejeong)  

  edm::Handle<reco::ConversionCollection> hConversions;
  iEvent.getByLabel("allConversions", hConversions);


  // ****  As the GSF electrons are not available in the 7_0_X miniAOD
  //I will not try to access them, and the conversion info will not
  // be available in the TOPTREE. This should be fixable with an offical
  // recommendation in 7_1_X

  
  // get the iso deposits. 4 (charged hadrons, pileup charged hadrons, photons, neutral hadrons)
  // currently it is hardcoded ---> need to make it configurable for the future
  inputTagIsoDepPhotons_.push_back( edm::InputTag("phPFIsoDepositChargedPFIso") );
  inputTagIsoDepPhotons_.push_back( edm::InputTag("phPFIsoDepositGammaPFIso") );
  inputTagIsoDepPhotons_.push_back( edm::InputTag("phPFIsoDepositNeutralPFIso") );
  inputTagIsoDepPhotons_.push_back( edm::InputTag("phPFIsoDepositPUPFIso") );
  // there is no difference between PFId and NoPFId so just take PFId iso-value
  // inputTagIsoValPhotons_.push_back( edm::InputTag("phPFIsoValueCharged03PFIdPFIso") );
  //inputTagIsoValPhotons_.push_back( edm::InputTag("phPFIsoValueGamma03PFIdPFIso") );
  //inputTagIsoValPhotons_.push_back( edm::InputTag("phPFIsoValueNeutral03PFIdPFIso") );
  //inputTagIsoValPhotons_.push_back( edm::InputTag("phPFIsoValuePU03PFIdPFIso") );
  
  //These "phPFIsoValueCharged03PFIdPFIso" objects are not present in miniAOD 
  //so commented, TODO: write the standard ISO variables the TRootPhoton in the TOPTREE



  unsigned nTypes=4;
  IsoDepositMaps photonIsoDep(nTypes);
  for (size_t j = 0; j<inputTagIsoDepPhotons_.size(); ++j) {
    iEvent.getByLabel(inputTagIsoDepPhotons_[j], photonIsoDep[j]);
  }
  IsoDepositVals photonIsoValPFId(nTypes);
  for (size_t j = 0; j<inputTagIsoValPhotons_.size(); ++j) {
    iEvent.getByLabel(inputTagIsoValPhotons_[j], photonIsoValPFId[j]);
  }


  //  const IsoDepositVals * photonIsoVals = &photonIsoValPFId;

  edm::Handle < std::vector < pat::Photon > >patPhotons;
  iEvent.getByToken (photonToken, patPhotons);
  nPhotons = patPhotons->size ();

  if (verbosity_ > 1)
    std::cout << "   Number of photons = " << nPhotons << "   Label: " << photonProducer_.label () << "   Instance: " << photonProducer_.instance () << std::endl;

    for (unsigned int j = 0; j < nPhotons; j++)
    {
      const pat::Photon*  patPhoton = &((*patPhotons)[j]);//dynamic_cast < const pat::Photon * >(&*photon);
      const reco::Photon* photon = (const reco::Photon *) patPhoton;//(&((*patPhotons)[j]));

      TRootPhoton localPhoton (photon->px (), photon->py (), photon->pz (), photon->energy ());

      //      cout <<"PHOTON kinematics :  "<< photon->px ()<<"  "<< photon->py ()<<"  "<< photon->pz ()<<"  "<< photon->energy ()<<endl;

      //      cout <<"PHOTON kinematics 1 :"<< endl; 
      localPhoton.setSigmaIetaIeta( photon->sigmaIetaIeta() );
      //cout <<"PHOTON kinematics 2 :"<< endl; 
      localPhoton.setHadronicOverEm( photon->hadronicOverEm() );
      //cout <<"PHOTON kinematics 3 :"<< endl; 
      localPhoton.setHasPixelSeed( photon->hasPixelSeed() );

      //prompt electron veto, commenting out for now, see **** above
      //      bool passelectronveto = !ConversionTools::hasMatchedPromptElectron(photon->superCluster(), hElectrons, hConversions, beamspot.position());
      //localPhoton.setPasselectronveto(passelectronveto);

      //currently PF isolation is directly from RECO, which is empty. need to change it (Taejeong) 
      pat::PhotonRef myPhotonRef(patPhotons,j);
      
      //    double chIso =  (*(*photonIsoVals)[0])[myPhotonRef];
      //double phIso = (*(*photonIsoVals)[1])[myPhotonRef];
      //double nhIso = (*(*photonIsoVals)[2])[myPhotonRef];
      //double puChIso = (*(*photonIsoVals)[3])[myPhotonRef];

      //      localPhoton.setIsoR03_ChargedHadronIso( chIso );
      //localPhoton.setIsoR03_PhotonIso( phIso );
      //localPhoton.setIsoR03_NeutralHadronIso( nhIso );
      //localPhoton.setIsoR03_PuChargedHadronIso( puChIso );

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
