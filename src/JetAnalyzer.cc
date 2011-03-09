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
	isData_ = myConfig.getUntrackedParameter<bool>("isData");
}

JetAnalyzer::~JetAnalyzer()
{
}

bool Rsortrule (std::pair <double,double> p1, std::pair <double,double> p2 )
{
	return p1.second<p2.second; 
}

TRootJet JetAnalyzer::Process(const reco::Jet* jet)
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

		// Some specific methods to pat::Jet
		const pat::Jet *patJet = dynamic_cast<const pat::Jet*>(&*jet);

		localJet.setJetArea(jet->jetArea());
		localJet.setPileupEnergy(jet->pileup());
		localJet.setMaxDistance(jet->maxDistance());

		// Variables from pat::Jet (Basic)
		localJet.setBtag_jetBProbabilityBJetTags(patJet->bDiscriminator("jetBProbabilityBJetTags"));
		localJet.setBtag_jetProbabilityBJetTags(patJet->bDiscriminator("jetProbabilityBJetTags"));
		localJet.setBtag_trackCountingHighPurBJetTags(patJet->bDiscriminator("trackCountingHighPurBJetTags"));
		localJet.setBtag_trackCountingHighEffBJetTags(patJet->bDiscriminator("trackCountingHighEffBJetTags"));
		localJet.setBtag_simpleSecondaryVertexHighEffBJetTags(patJet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags"));
		localJet.setBtag_simpleSecondaryVertexHighPurBJetTags(patJet->bDiscriminator("simpleSecondaryVertexHighPurBJetTags"));
		localJet.setBtag_combinedSecondaryVertexBJetTags(patJet->bDiscriminator("combinedSecondaryVertexBJetTags"));
		localJet.setBtag_combinedSecondaryVertexMVABJetTags(patJet->bDiscriminator("combinedSecondaryVertexMVABJetTags"));
		localJet.setBtag_combinedMVABJetTags(patJet->bDiscriminator("combinedMVABJetTags"));
		localJet.setBtag_softMuonBJetTags(patJet->bDiscriminator("softMuonBJetTags"));
		localJet.setBtag_softMuonByPtBJetTags(patJet->bDiscriminator("softMuonByPtBJetTags"));
		localJet.setBtag_softMuonByIP3dBJetTags(patJet->bDiscriminator("softMuonByIP3dBJetTags"));
		localJet.setBtag_softElectronBJetTags(patJet->bDiscriminator("softElectronBJetTags"));
		localJet.setBtag_softElectronByPtBJetTags(patJet->bDiscriminator("softElectronByPtBJetTags"));
		localJet.setBtag_softElectronByIP3dBJetTags(patJet->bDiscriminator("softElectronByIP3dBJetTags"));
		localJet.setBtag_ghostTrackBJetTags(patJet->bDiscriminator("ghostTrackBJetTags"));
		
		/*cout << "******** BTAGGING INFO *******" << endl;
		cout << "jetBProbabilityBJetTags -> " << patJet->bDiscriminator("jetBProbabilityBJetTags") << endl;
		cout << "jetProbabilityBJetTags -> " << patJet->bDiscriminator("jetProbabilityBJetTags") << endl;
		cout << "simpleSecondaryVertexHighEffBJetTags -> " << patJet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags") << endl;
		cout << "simpleSecondaryVertexHighPurBJetTags -> " << patJet->bDiscriminator("simpleSecondaryVertexHighPurBJetTags") << endl;
		cout << "trackCountingHighEffBJetTags -> " << patJet->bDiscriminator("trackCountingHighEffBJetTags") << endl;
		cout << "trackCountingHighPurBJetTags -> " << patJet->bDiscriminator("trackCountingHighPurBJetTags") << endl;
		cout << "combinedSecondaryVertexBJetTags -> " << patJet->bDiscriminator("combinedSecondaryVertexBJetTags") << endl;	
		cout << "combinedSecondaryVertexMVABJetTags -> " << patJet->bDiscriminator("combinedSecondaryVertexMVABJetTags") << endl;
		cout << "softMuonBJetTags -> " << patJet->bDiscriminator("softMuonBJetTags") << endl;
		cout << "softElectronBJetTags -> " << patJet->bDiscriminator("softElectronBJetTags") << endl;*/

		// jet correction factors

		pat::Jet rawJet = patJet->correctedJet("Uncorrected");
		
		localJet.setJetCorrFactor(0,"L1",rawJet.jecFactor("L1Offset"));
		localJet.setJetCorrFactor(1,"L1L2",rawJet.jecFactor("L2Relative"));
		localJet.setJetCorrFactor(2,"L1L2L3",rawJet.jecFactor("L3Absolute"));
		if(isData_)
		{
			localJet.setJetCorrFactor(3,"L1L2L3L23Residual",rawJet.jecFactor("L2L3Residual"));
		}
		
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


	return localJet;
}
