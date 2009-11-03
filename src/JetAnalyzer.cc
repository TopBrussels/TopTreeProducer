#include "../interface/JetAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

JetAnalyzer::JetAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0),useMC_(false)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	jetProducer_ = producersNames.getParameter<edm::InputTag>("jetProducer");
}

JetAnalyzer::JetAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity),useMC_(false)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	jetProducer_ = producersNames.getParameter<edm::InputTag>("jetProducer");
}

JetAnalyzer::JetAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	jetProducer_ = producersNames.getParameter<edm::InputTag>("jetProducer");
	useMC_ = myConfig.getUntrackedParameter<bool>("doJetMC");
}

JetAnalyzer::JetAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	vJetProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vjetProducer");
	jetProducer_ = edm::InputTag(vJetProducer[iter]);
	useMC_ = myConfig.getUntrackedParameter<bool>("doJetMC");
}

JetAnalyzer::~JetAnalyzer()
{
}

bool Rsortrule (std::pair <double,double> p1, std::pair <double,double> p2 )
{
	return p1.second<p2.second; 
}

void JetAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootJets)
{

	unsigned int nJets=0;

	// reco::CaloJet or reco::PFJet ?
	std::string jetType = "BASIC";
	if( jetProducer_.label()=="kt4CaloJets"
		|| jetProducer_.label()=="kt6CaloJets"
		|| jetProducer_.label()=="iterativeCone5CaloJets"
		|| jetProducer_.label()=="sisCone5CaloJets"
		|| jetProducer_.label()=="sisCone7CaloJets"
	) jetType="CALO";

	if( jetProducer_.label()=="kt4PFJets"
		|| jetProducer_.label()=="kt6PFJets"
		|| jetProducer_.label()=="iterativeCone5PFJets"
		|| jetProducer_.label()=="sisCone5PFJets"
		|| jetProducer_.label()=="sisCone7PFJets"
	) jetType="PF";

	edm::Handle < std::vector <reco::CaloJet> > recoCaloJets;
	if( (dataType_=="RECO" || dataType_=="AOD") && jetType=="CALO" )
	{
		iEvent.getByLabel(jetProducer_, recoCaloJets);
		nJets = recoCaloJets->size();
	}

	edm::Handle < std::vector <reco::PFJet> > recoPFJets;
	if( (dataType_=="RECO" || dataType_=="AOD") && jetType=="PF" )
	{
		iEvent.getByLabel(jetProducer_, recoPFJets);
		nJets = recoPFJets->size();
	}

	edm::Handle < std::vector <pat::Jet> > patJets;
	if( dataType_=="PAT" || dataType_=="PATAOD" )
	{
		iEvent.getByLabel(jetProducer_, patJets);
		nJets = patJets->size();
	}

	if(verbosity_>1) std::cout << "   Number of jets = " << nJets << "   Label: " << jetProducer_.label() << "   Instance: " << jetProducer_.instance() << std::endl;

	for (unsigned int j=0; j<nJets; j++)
	{
		const reco::Jet* jet = 0;	
		if( (dataType_=="RECO" || dataType_=="AOD") && jetType=="CALO" ) jet = (const reco::Jet*) ( & ((*recoCaloJets)[j]) );
		if( (dataType_=="RECO" || dataType_=="AOD") && jetType=="PF" ) jet = (const reco::Jet*) ( & ((*recoPFJets)[j]) );
		if( dataType_=="PAT" || dataType_=="PATAOD" )
		{
			jet = (const reco::Jet*) ( & ((*patJets)[j]) );
			if( (*patJets)[j].isCaloJet() ) jetType="CALO";
			if( (*patJets)[j].isPFJet() ) jetType="PF";
		}

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
		localJet.setN90(jet->nCarrying(0.9));
		localJet.setN60(jet->nCarrying(0.6));
		localJet.setJetArea(jet->jetArea());
		localJet.setPileupEnergy(jet->pileup());
		localJet.setMaxDistance(jet->maxDistance());


		if( dataType_=="RECO" || dataType_=="AOD" )
		{
			// Some specific methods to reco::Jet
			// Do association to genParticle ?

			if( jetType=="CALO" )
			{
				// Variables from reco::CaloJet
				const reco::CaloJet *caloJet = dynamic_cast<const reco::CaloJet*>(&*jet);
				localJet.setJetType(1);
				localJet.setEcalEnergyFraction(caloJet->emEnergyFraction());
				localJet.setHcalEnergyFraction(caloJet->energyFractionHadronic());
		                localJet.setMaxEInEmTowers(caloJet->maxEInEmTowers());
		                localJet.setMaxEInHadTowers(caloJet->maxEInHadTowers());
	                        localJet.setTowersArea(caloJet->towersArea());
				//std::vector<CaloTowerPtr> getCaloConstituents () const;
			}

			if( jetType=="PF" )
			{
				// Variables from reco::PFJet
				const reco::PFJet *pfJet = dynamic_cast<const reco::PFJet*>(&*jet);
				localJet.setJetType(2);
				localJet.setEcalEnergyFraction(pfJet->chargedEmEnergyFraction() + pfJet->neutralEmEnergyFraction());
				localJet.setHcalEnergyFraction(pfJet->chargedHadronEnergyFraction() + pfJet->neutralHadronEnergyFraction());
				if(pfJet->energy() != 0) localJet.setChargedEnergyFraction( (pfJet->chargedEmEnergy() + pfJet->chargedHadronEnergy() + pfJet->chargedMuEnergy() ) / pfJet->energy());
				localJet.setChargedMultiplicity((int)pfJet->chargedMultiplicity()) ;
				//std::vector <const reco::PFCandidate*> getPFConstituents () const;
			}

		}


		if( dataType_=="PATAOD" || dataType_=="PAT" )
		{
			// Some specific methods to pat::Jet
			const pat::Jet *patJet = dynamic_cast<const pat::Jet*>(&*jet);

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

			
			localJet.setBCorrection(patJet->jetCorrFactors().correction(patJet->jetCorrFactors().corrStep("PART", "b"),patJet->jetCorrStep()));
			localJet.setCCorrection(patJet->jetCorrFactors().correction(patJet->jetCorrFactors().corrStep("PART", "c"),patJet->jetCorrStep()));
			localJet.setUDSCorrection(patJet->jetCorrFactors().correction(patJet->jetCorrFactors().corrStep("PART", "uds"),patJet->jetCorrStep()));
			localJet.setGCorrection(patJet->jetCorrFactors().correction(patJet->jetCorrFactors().corrStep("PART", "glu"),patJet->jetCorrStep()));

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


			if ( patJet->isCaloJet() ) {
				// Variables from pat::Jet (CaloSpecific)
				localJet.setJetType(1);
				localJet.setEcalEnergyFraction(patJet->emEnergyFraction());
				localJet.setHcalEnergyFraction(patJet->energyFractionHadronic());
				localJet.setChargedMultiplicity(patJet->associatedTracks().size()) ;
			      	//std::vector<CaloTowerPtr> getCaloConstituents () const;
		                localJet.setMaxEInEmTowers(patJet->maxEInEmTowers());
		                localJet.setMaxEInHadTowers(patJet->maxEInHadTowers());
	                        localJet.setTowersArea(patJet->towersArea());
			
			}

			if(patJet->isPFJet()) {
				// Variables from pat::Jet (PFSpecific)
				localJet.setJetType(2);
				localJet.setEcalEnergyFraction(patJet->chargedEmEnergyFraction() + patJet->neutralEmEnergyFraction());
				localJet.setHcalEnergyFraction(patJet->chargedHadronEnergyFraction() + patJet->neutralHadronEnergyFraction());
				if(patJet->energy() != 0) localJet.setChargedEnergyFraction( (patJet->chargedEmEnergy() + patJet->chargedHadronEnergy() + patJet->chargedMuEnergy() ) / patJet->energy());
				localJet.setChargedMultiplicity((int)patJet->chargedMultiplicity()) ;
				//std::vector <const reco::PFCandidate*> getPFConstituents () const;
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
		}

		new( (*rootJets)[j] ) TRootJet(localJet);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localJet << endl;
	}
}
