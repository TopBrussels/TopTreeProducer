#include "../interface/TowerRemover.h"

TowerRemover::TowerRemover(const edm::ParameterSet& iConfig):DREleTwr_(iConfig.getParameter<double>("DREleTwr")),
	electronCriteria(iConfig.getParameter<std::string>("electronCriteria")),
	src(iConfig.getParameter<edm::InputTag>("src"))
{
 produces<CaloTowerCollection>();
}


TowerRemover::~TowerRemover()
{
}

double TowerRemover::DeltaR(double eta1,double phi1,double eta2,double phi2)
    
        {
	  double dphi=phi1-phi2;
	  double deta=eta1-eta2;
          if(fabs(dphi)>M_PI){dphi=2*M_PI-fabs(dphi);}
	  return sqrt(dphi*dphi+deta*deta);
	}

void
TowerRemover::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

	edm::Handle<std::vector<pat::Electron> > electrons;
	iEvent.getByLabel(src,electrons);
	StringCutObjectSelector<pat::Electron> elecSelector(electronCriteria);
	edm::Handle<CaloTowerCollection>  towers;
	iEvent.getByLabel("towerMaker",towers);
	
	std::vector<pat::Electron> GoodEles;
	CaloTowerCollection mdfTowers;

	for(std::vector<pat::Electron>::const_iterator ele=electrons->begin();ele!=electrons->end();ele++)
		if(elecSelector(*ele))
			GoodEles.push_back(*ele);
	
	for(CaloTowerCollection::const_iterator tower=towers->begin();tower!=towers->end();tower++){

	if(GoodEles.size()==0) mdfTowers.push_back(*tower);

	if(GoodEles.size()==1){
	const reco::SuperCluster *SC=((GoodEles.at(0)).superCluster()).get();
	double SCeta=SC->eta();
	double SCphi=SC->phi();
	double deltaR=DeltaR(SCeta,SCphi,tower->eta(),tower->phi());
	if(deltaR > DREleTwr_) mdfTowers.push_back(*tower);
	}
	
	if(GoodEles.size()==2){
	const reco::SuperCluster *SC1=((GoodEles.at(0)).superCluster()).get();
	const reco::SuperCluster *SC2=((GoodEles.at(1)).superCluster()).get();
	double SC1eta=SC1->eta();
	double SC1phi=SC1->phi();
	double SC2eta=SC2->eta();
	double SC2phi=SC2->phi();
	double deltaR1st=DeltaR(SC1eta,SC1phi,tower->eta(),tower->phi());
	double deltaR2nd=DeltaR(SC2eta,SC2phi,tower->eta(),tower->phi());
	if(deltaR1st>DREleTwr_ && deltaR2nd>DREleTwr_) mdfTowers.push_back(*tower);
	}
	
	if(GoodEles.size()>2) std::cout<<"TowerRemover.cc should be corrected..."<<std::endl;
	}

	std::auto_ptr<CaloTowerCollection> pOut(new CaloTowerCollection(mdfTowers));
	iEvent.put(pOut);

}

void TowerRemover::beginJob()
{
}

void TowerRemover::endJob()
{
}
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_ANOTHER_FWK_MODULE(TowerRemover);
