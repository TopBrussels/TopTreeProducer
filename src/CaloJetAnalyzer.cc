#include "../interface/CaloJetAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

CaloJetAnalyzer::CaloJetAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	caloJetProducer_ = producersNames.getParameter<edm::InputTag>("caloJetProducer");
	myJetAnalyzer = new JetAnalyzer();
}

CaloJetAnalyzer::CaloJetAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	caloJetProducer_ = producersNames.getParameter<edm::InputTag>("caloJetProducer");
	myJetAnalyzer = new JetAnalyzer(verbosity);
}

CaloJetAnalyzer::CaloJetAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	caloJetProducer_ = producersNames.getParameter<edm::InputTag>("caloJetProducer");
	doCaloJetId_ = myConfig.getUntrackedParameter<bool>("doCaloJetId");
	myJetAnalyzer = new JetAnalyzer(myConfig, verbosity);
}

CaloJetAnalyzer::CaloJetAnalyzer(const edm::ParameterSet& producersNames, int iter, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	vCaloJetProducer = producersNames.getUntrackedParameter<std::vector<std::string> >("vcaloJetProducer");
	caloJetProducer_ = edm::InputTag(vCaloJetProducer[iter]);
	doCaloJetId_ = myConfig.getUntrackedParameter<bool>("doCaloJetId");
	myJetAnalyzer = new JetAnalyzer(myConfig, verbosity);
}

CaloJetAnalyzer::~CaloJetAnalyzer()
{
}

void CaloJetAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootJets)
{

	unsigned int nJets=0;

	// check if the jet is of the good type
	std::string jetType = "BASIC";
	if( caloJetProducer_.label()=="kt4CaloJets"
		|| caloJetProducer_.label()=="kt6CaloJets"
		|| caloJetProducer_.label()=="iterativeCone5CaloJets"
		|| caloJetProducer_.label()=="sisCone5CaloJets"
		|| caloJetProducer_.label()=="sisCone7CaloJets"
      || caloJetProducer_.label()=="ak5CaloJets"
      || caloJetProducer_.label()=="ak7CaloJets"
	) jetType="CALO";

	edm::Handle < edm::View <reco::CaloJet> > recoCaloJets;
	if( (dataType_=="RECO" || dataType_=="AOD") && jetType=="CALO" )
	{
		iEvent.getByLabel(caloJetProducer_, recoCaloJets);
		nJets = recoCaloJets->size();
	}

	edm::Handle < std::vector <pat::Jet> > patJets;
	if( dataType_=="PAT" || dataType_=="PATAOD" )
	{
		iEvent.getByLabel(caloJetProducer_, patJets);
		nJets = patJets->size();
	}
		
	if(verbosity_>1) std::cout << "   Number of jets = " << nJets << "   Label: " << caloJetProducer_.label() << "   Instance: " << caloJetProducer_.instance() << std::endl;

	for (unsigned int j=0; j<nJets; j++)
	{
		const reco::Jet* jet = 0;	
		if( (dataType_=="RECO" || dataType_=="AOD") && jetType=="CALO" ) jet = (const reco::Jet*) ( & ((*recoCaloJets)[j]) );
		if( dataType_=="PAT" || dataType_=="PATAOD" )
		{
			jet = (const reco::Jet*) ( & ((*patJets)[j]) );
			if( (*patJets)[j].isCaloJet() ) jetType="CALO";
		}
		
		// Call JetAnalyzer to fill the basic Jet Properties
		TRootJet tempJet = (TRootJet) myJetAnalyzer->Process( &( *(jet) ), dataType_);

		TRootCaloJet localJet = TRootCaloJet(tempJet);

		localJet.setJetType(1); // 1 = CaloJet
		localJet.setN90(jet->nCarrying(0.9));
		localJet.setN60(jet->nCarrying(0.6));
		localJet.setetaetaMoment(jet->etaetaMoment());
		localJet.setphiphiMoment(jet->phiphiMoment());

		if( dataType_=="RECO" || dataType_=="AOD" )
		{
			//Some specific methods to reco::CaloJet
			const reco::CaloJet *caloJet = dynamic_cast<const reco::CaloJet*>(&*jet);
			localJet.setEcalEnergyFraction(caloJet->emEnergyFraction());
			localJet.setHcalEnergyFraction(caloJet->energyFractionHadronic());
			localJet.setMaxEInEmTowers(caloJet->maxEInEmTowers());
			localJet.setMaxEInHadTowers(caloJet->maxEInHadTowers());
			localJet.setTowersArea(caloJet->towersArea());

			if(doCaloJetId_)
			{
				//JetId handle
				edm::Handle<reco::JetIDValueMap> hJetIDMap;
				if(caloJetProducer_.label() == "ak5CaloJets")
					iEvent.getByLabel( "ak5JetID", hJetIDMap );
				else if(caloJetProducer_.label() == "ak7CaloJets")
					iEvent.getByLabel( "ak7JetID", hJetIDMap );
				else if(caloJetProducer_.label() == "sisCone5CaloJets")
					iEvent.getByLabel( "sisCone5JetID", hJetIDMap );
				else if(caloJetProducer_.label() == "sisCone7CaloJets")
					iEvent.getByLabel( "sisCone7JetID", hJetIDMap );
				else if(caloJetProducer_.label() == "iterativeCone5CaloJets")
					iEvent.getByLabel( "iterativeCone5JetID", hJetIDMap );
				else if(caloJetProducer_.label() == "kt4CaloJets")
					iEvent.getByLabel( "kt4JetID", hJetIDMap );
				else if(caloJetProducer_.label() == "kt6CaloJets")
					iEvent.getByLabel( "kt6JetID", hJetIDMap );
				
				edm::RefToBase<reco::CaloJet> jetRef = recoCaloJets->refAt(j);
				reco::JetID jetId = (*hJetIDMap)[ jetRef ];
				
				localJet.setfHPD(jetId.fHPD);
				localJet.setfRBX(jetId.fRBX);
				localJet.setn90Hits(jetId.n90Hits);
				localJet.setnHCALTowers(jetId.nHCALTowers);
				localJet.setnECALTowers(jetId.nECALTowers);
				// todo?
				// for AOD use tower based approximations / inferior options?
				// approximatefHPD, approximatefRBX, hitsInN90        

			} //end of if(doCaloJetId_)

		} // end of if( dataType_=="RECO" || dataType_=="AOD" )

		if( dataType_=="PATAOD" || dataType_=="PAT" )
		{
			// Some specific methods to pat::Jet
			const pat::Jet *patJet = dynamic_cast<const pat::Jet*>(&*jet);
			
			localJet.setChargedMultiplicity(patJet->associatedTracks().size()) ;
			localJet.setEcalEnergyFraction(patJet->emEnergyFraction());
			localJet.setHcalEnergyFraction(patJet->energyFractionHadronic());
			localJet.setMaxEInEmTowers(patJet->maxEInEmTowers());
			localJet.setMaxEInHadTowers(patJet->maxEInHadTowers());
			localJet.setTowersArea(patJet->towersArea());

			if(doCaloJetId_)
			{
				localJet.setfHPD(patJet->jetID().fHPD);
				localJet.setfRBX(patJet->jetID().fRBX);
				localJet.setn90Hits(patJet->jetID().n90Hits);
				localJet.setnHCALTowers(patJet->jetID().nHCALTowers);
				localJet.setnECALTowers(patJet->jetID().nECALTowers);

			} //end of if(doCaloJetId_)

		} //end of if( dataType_=="PATAOD" || dataType_=="PAT" )
		
		new( (*rootJets)[j] ) TRootCaloJet(localJet);
		if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localJet << endl;
		
	}

}
