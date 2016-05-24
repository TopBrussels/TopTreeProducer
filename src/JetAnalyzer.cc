#include "../interface/JetAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

JetAnalyzer::JetAnalyzer():verbosity_(0),useMC_(false)
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

TRootJet JetAnalyzer::Process(const reco::Jet* jet, const edm::EventSetup& iSetup)
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

	// Some specific methods to pat::Jet
	const pat::Jet *patJet = dynamic_cast<const pat::Jet*>(&*jet);

	localJet.setNConstituents(jet->nConstituents());
	localJet.setJetArea(jet->jetArea()); // needs to be calculated with fastjet, not yet done in the standard cfg's
	localJet.setMaxDistance(jet->maxDistance());

	// Variables from pat::Jet (Basic)
	localJet.setBtag_combinedInclusiveSecondaryVertexV2BJetTags(patJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
  localJet.setBtag_PFCombinedMVAV2BJetTags(patJet->bDiscriminator("pfCombinedMVAV2BJetTags"));
	localJet.setBtag_softPFElectronBJetsTags(patJet->bDiscriminator("softPFElectronBJetTags"));
	localJet.setBtag_softPFMuonBJetsTags(patJet->bDiscriminator("softPFMuonBJetTags"));
	localJet.setCtag_pfCombinedCvsLJetTags(patJet->bDiscriminator("pfCombinedCvsLJetTags"));
	localJet.setCtag_pfCombinedCvsBJetTags(patJet->bDiscriminator("pfCombinedCvsBJetTags"));
	localJet.setpuID(-9999);
    //localJet.setpuID(patJet->userFloat("pileupJetId:fullDiscriminant")); 
	// in 76X the FatJets don't have the 'fullDiscriminator' --> setpuID is initialized in
	//PFJetAnalyzer.cc/FatJetAnalyzer.cc/JPTJetAnalyzer.cc and set to a default value here!! (By Seth and Kevin on 23 december 2015)
	// TO BO FIXED IN THE FUTURE????????!!!!!!!??????!!!!
	if(verbosity_ > 2) cout << "CSV old, new: " << patJet->bDiscriminator("combinedSecondaryVertexBJetTags") << ", " << patJet->bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags") << endl;


	// jet correction factors
	std::vector< std::string > jecLevels = patJet->availableJECLevels();

	pat::Jet rawJet = patJet->correctedJet("Uncorrected");

	localJet.setJetCorrFactor(0,jecLevels[1],rawJet.jecFactor(jecLevels[1]));
	localJet.setJetCorrFactor(1,jecLevels[1]+"L2",rawJet.jecFactor("L2Relative"));
	localJet.setJetCorrFactor(2,jecLevels[1]+"L2L3",rawJet.jecFactor("L3Absolute"));
	if(jecLevels.size() > 4 && jecLevels[4] == "L2L3Residual" )
		localJet.setJetCorrFactor(3,jecLevels[1]+"L2L3L23Residual",rawJet.jecFactor("L2L3Residual"));

	// Matched genParticle
	if (useMC_)
	{
		// MC truth associator index
		if ((patJet->genParticleRef()).isNonnull())
			localJet.setGenParticleIndex((patJet->genParticleRef()).index());
		else
			localJet.setGenParticleIndex(-1);

		// set the parton flavour
		localJet.setPartonFlavour(patJet->partonFlavour());

		// check if jet comes from a top
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
