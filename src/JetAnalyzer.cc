#include "../interface/JetAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

JetAnalyzer::JetAnalyzer():verbosity_(0),useMC_(false)
{
}

JetAnalyzer::JetAnalyzer(int verbosity):verbosity_(verbosity),useMC_(false)
{
}

JetAnalyzer::JetAnalyzer(const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	useMC_ = myConfig.getUntrackedParameter<bool>("doJetMC");
}

JetAnalyzer::~JetAnalyzer()
{
}

bool Rsortrule (std::pair <double,double> p1, std::pair <double,double> p2 )
{
	return p1.second<p2.second; 
}

TRootJet JetAnalyzer::Process(const reco::Jet* jet, std::string dataType)
{

	TRootJet localJet(
		jet->px()
		,jet->py()
		,jet->pz()
		,jet->energy()
		,jet->vx()
		,jet->vy()
		,jet->vz()
		,jet->pdgId()
		,jet->charge()
	); 

	localJet.setNConstituents(jet->nConstituents());
	localJet.setJetArea(jet->jetArea());
	localJet.setPileupEnergy(jet->pileup());
	localJet.setMaxDistance(jet->maxDistance());

	if( dataType=="PATAOD" || dataType=="PAT" )
	{
		// Some specific methods to pat::Jet
		const pat::Jet *patJet = dynamic_cast<const pat::Jet*>(&*jet);

		localJet.setJetArea(jet->jetArea());
		localJet.setPileupEnergy(jet->pileup());
		localJet.setMaxDistance(jet->maxDistance());

		// Variables from pat::Jet (Basic)
		localJet.setBtag_combinedSecondaryVertexBJetTags(patJet->bDiscriminator("combinedSecondaryVertexBJetTags"));
		localJet.setBtag_combinedSecondaryVertexMVABJetTags(patJet->bDiscriminator("combinedSecondaryVertexMVABJetTags"));
		localJet.setBtag_impactParameterMVABJetTags(patJet->bDiscriminator("impactParameterMVABJetTags"));
		localJet.setBtag_jetBProbabilityBJetTags(patJet->bDiscriminator("jetBProbabilityBJetTags"));
		localJet.setBtag_jetProbabilityBJetTags(patJet->bDiscriminator("jetProbabilityBJetTags"));
		localJet.setBtag_simpleSecondaryVertexBJetTags(patJet->bDiscriminator("simpleSecondaryVertexBJetTags"));
		localJet.setBtag_softElectronBJetTags(patJet->bDiscriminator("softElectronBJetTags"));
		localJet.setBtag_softMuonBJetTags(patJet->bDiscriminator("softMuonBJetTags"));
		localJet.setBtag_softMuonNoIPBJetTags(patJet->bDiscriminator("softMuonNoIPBJetTags"));
		localJet.setBtag_trackCountingHighEffBJetTags(patJet->bDiscriminator("trackCountingHighEffBJetTags"));
		localJet.setBtag_trackCountingHighPurBJetTags(patJet->bDiscriminator("trackCountingHighPurBJetTags"));

		localJet.setBCorrection(patJet->corrFactor(patJet->corrStep(), "b"));
		localJet.setCCorrection(patJet->corrFactor(patJet->corrStep(), "c"));
		localJet.setUDSCorrection(patJet->corrFactor(patJet->corrStep(), "uds"));
		localJet.setGCorrection(patJet->corrFactor(patJet->corrStep(), "glu"));

		// Use  associated tracks to calculate charged broadness of the jet
		// FIXME - Check generalTracks collection is present
		reco::TrackRefVector tracks =  patJet->associatedTracks() ;
		Float_t deltaR = 0.;
		Float_t pTrackerTot = 0.;
		// TODO - Use std::map....
		vector < pair < Float_t , Float_t > > tracksVPair ;
		pair < Float_t , Float_t > tracksPair;

		for(unsigned int iTracks = 0; iTracks< patJet->associatedTracks().size() ; iTracks++)
		{
			deltaR = localJet.DeltaR(TLorentzVector(tracks[iTracks]->px(),tracks[iTracks]->py(),tracks[iTracks]->pz(),0));
			pTrackerTot += tracks[iTracks]->p();
			tracksPair.first = tracks[iTracks]->p();
			tracksPair.second = deltaR;
			tracksVPair.push_back(tracksPair);
		}
	
		sort(tracksVPair.begin(), tracksVPair.end(), Rsortrule);
		Float_t Rmin = 0;
		Float_t pDummy = 0;
		for(std::vector<std::pair< Float_t,Float_t > >::iterator i = tracksVPair.begin(); i!=tracksVPair.end(); i++)
		{
			pDummy+=(*i).first;
			if (pDummy>0.75*(pTrackerTot))
			{
				Rmin = (*i).second;
				break;
			}
		}
		if (Rmin<1e-5) {Rmin=0.;}
		localJet.setChargedBroadness(Rmin);

		// Matched genParticle
		if (useMC_)
		{
			// MC truth associator index
			if ((patJet->genParticleRef()).isNonnull()) {
				localJet.setGenParticleIndex((patJet->genParticleRef()).index());
			} else {
				localJet.setGenParticleIndex(-1);
			}

			// set the parton flavour
			localJet.setPartonFlavour(patJet->partonFlavour());

			// check if jet comes from a top
			// change that ... 
			// look on TtGenEvent
			// keep the TRef ...
			bool IsTopJet =  false;
			if(patJet->genParton())
			{
				const reco::Candidate* gen = patJet->genParton();
				while(gen->mother())
				{
					if(abs((gen->mother())->pdgId()) == 6)
					{
						IsTopJet =  true;
						break;
					}
					else
					{
						gen = (gen->mother() );
					}
				}
			}
			localJet.setIsTopJet(IsTopJet);
		}

	}

	return localJet;
}
