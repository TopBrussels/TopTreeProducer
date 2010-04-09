#include "../interface/SemiLepEventAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;

SemiLepEventAnalyzer::SemiLepEventAnalyzer(const edm::ParameterSet& producersNames):verbosity_(0)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	semiLepEventProducer_ = producersNames.getParameter<edm::InputTag>("semiLepEventProducer");
}

SemiLepEventAnalyzer::SemiLepEventAnalyzer(const edm::ParameterSet& producersNames, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	semiLepEventProducer_ = producersNames.getParameter<edm::InputTag>("semiLepEventProducer");
}

SemiLepEventAnalyzer::SemiLepEventAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
	dataType_ = producersNames.getUntrackedParameter<string>("dataType","unknown");
	semiLepEventProducer_ = producersNames.getParameter<edm::InputTag>("semiLepEventProducer");
}

SemiLepEventAnalyzer::~SemiLepEventAnalyzer()
{
}


TLorentzVector  P4toTLV(const reco::Candidate* a){ return TLorentzVector(a->px(), a->py(), a->pz(), a->energy());}

void SemiLepEventAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootSemiLepEvent, TClonesArray* rootJets, TClonesArray* rootMuons){

	edm::Handle < TtSemiLeptonicEvent > semiLepEventHandle;
        iEvent.getByLabel(semiLepEventProducer_, semiLepEventHandle);
        TtSemiLeptonicEvent semiLepEvent = * semiLepEventHandle;

	if(verbosity_>1) std::cout << "   GenEvent  "  << "   Label: " << semiLepEventProducer_.label() << "   Instance: " << semiLepEventProducer_.instance() << std::endl;

        TRootSemiLepEvent semiLepEvt;
	vector<double> genMatchSumPt;
	vector<double> genMatchSumDR;
	vector<double> mvaDisc;
	vector<double> fitChi2;
	vector<double> fitProb;
	
	unsigned int size = 0;
	for(TtEvent::HypoClassKey i=TtEvent::kGeom; i<=TtEvent::kKinFit;i=TtEvent::HypoClassKey(i+1))
		for(unsigned int j=0;j<semiLepEvent.numberOfAvailableHypos(i);j++)
	 		if(semiLepEvent.isHypoValid(i,j)){
				size = semiLepEvent.numberOfAvailableHypos(i);
				break;
			}
	for(unsigned int i=0;i<size;i++){
	  genMatchSumPt.push_back(semiLepEvent.genMatchSumPt(i));
	  genMatchSumDR.push_back(semiLepEvent.genMatchSumDR(i));
	  mvaDisc.push_back(semiLepEvent.mvaDisc(i));
	  fitChi2.push_back(semiLepEvent.fitChi2(i));
	  fitProb.push_back(semiLepEvent.fitProb(i));
	}
        semiLepEvt.setGenMatchSumPt(genMatchSumPt); 
	semiLepEvt.setGenMatchSumDR(genMatchSumDR); 
	semiLepEvt.setMvaMethod(semiLepEvent.mvaMethod());
	semiLepEvt.setMvaDiscriminators(mvaDisc);
	semiLepEvt.setFitChi2(fitChi2);
	semiLepEvt.setFitProb(fitProb);

	for(TtEvent::HypoClassKey i=TtEvent::kGeom; i<=TtEvent::kKinFit;i=TtEvent::HypoClassKey(i+1)){
		for(unsigned int j=0;j<semiLepEvent.numberOfAvailableHypos(i);j++){
	 		if(semiLepEvent.isHypoValid(i,j)){
			   if(semiLepEvent.hadronicDecayQuarkBar(i,j) && semiLepEvent.hadronicDecayQuarkBar(i,j) && semiLepEvent.hadronicDecayB(i,j)
		    	   && semiLepEvent.singleNeutrino(i,j) && semiLepEvent.singleLepton(i,j) && semiLepEvent.leptonicDecayB(i,j)){
				TRootJet* quarkP;
				TRootJet* quarkQ;
				TRootJet* hadronicB;
				TRootJet* leptonicB;
				TRootMuon* muon;
				//TLorentzVector
				TLorentzVector TLquarkP;
				TLorentzVector TLquarkQ;
				TLorentzVector TLhadronicB;
				TLorentzVector TLleptonicB;
				TLorentzVector TLmuon;

				TLorentzVector neutrino;
			        bool TLFormat = false;	
				//search in TRooJet Collection
				for(int ij=0;ij<rootJets->GetEntriesFast();ij++){
				        TRootJet* jet = (TRootJet*) rootJets->At(ij);
					TLorentzVector tljet = TLorentzVector(jet->Px(),jet->Py(),jet->Pz(),jet->Energy());
					if(P4toTLV(semiLepEvent.hadronicDecayQuarkBar(i,j))==tljet) quarkP = jet;
					if(P4toTLV(semiLepEvent.hadronicDecayQuarkBar(i,j))==tljet) quarkQ = jet;
					if(P4toTLV(semiLepEvent.hadronicDecayB(i,j))==tljet)   hadronicB = jet;
					if(P4toTLV(semiLepEvent.leptonicDecayB(i,j))==tljet)   leptonicB = jet;
				        delete jet;
				}
				//search in TRootMuon Collection
				for(int ij=0;ij<rootMuons->GetEntriesFast();ij++){
				        TRootMuon* trmuon = (TRootMuon*) rootMuons->At(ij);
					TLorentzVector tlmuon = TLorentzVector(trmuon->Px(),trmuon->Py(),trmuon->Pz(),trmuon->Energy());
					if(P4toTLV(semiLepEvent.singleLepton(i,j))==tlmuon) muon = trmuon;
				        delete trmuon;
				}
				if(!quarkP || !quarkQ || !hadronicB || !leptonicB || !muon){
				   TLFormat = true;
				   TLquarkP = P4toTLV(semiLepEvent.hadronicDecayQuarkBar(i,j));
				   TLquarkQ = P4toTLV(semiLepEvent.hadronicDecayQuarkBar(i,j));
				   TLhadronicB = P4toTLV(semiLepEvent.hadronicDecayB(i,j));
				   TLleptonicB = P4toTLV(semiLepEvent.leptonicDecayB(i,j));
				   TLmuon = P4toTLV(semiLepEvent.singleLepton(i,j));
				}
				if(semiLepEvent.singleNeutrino(i,j)) neutrino = P4toTLV(semiLepEvent.singleNeutrino(i,j));
				
				if(!TLFormat){
					TRootWCandidate hadW(quarkP,quarkQ);
					TRootTopCandidate hadTop(hadW,hadronicB);
					TRootWCandidate lepW(muon,neutrino);
					TRootTopCandidate lepTop(lepW,leptonicB);
					std::vector <std::pair<TRootTopCandidate,std::string> > vecTop;
					vecTop.push_back(std::pair<TRootTopCandidate,std::string>(hadTop,string("HadTop")));
					vecTop.push_back(std::pair<TRootTopCandidate,std::string>(lepTop,string("LepTop")));
					TRootCompositeCandidate compo(vecTop);
					std::vector<int> vecInt = semiLepEvent.jetLeptonCombination(i,j);
			        	TRootSemiLepEvent::HypoCombPair	hypcomb(compo,vecInt);
			        	TRootSemiLepEvent::HypoClassKey	key = (TRootSemiLepEvent::HypoClassKey)i;
					semiLepEvt.addEventHypo(key,hypcomb);
				}
				else{
					TRootWCandidate hadW(TLquarkP,TLquarkQ,false);
					TRootTopCandidate hadTop(hadW,TLhadronicB);
					TRootWCandidate lepW(TLmuon,neutrino,true);
					TRootTopCandidate lepTop(lepW,leptonicB);
					std::vector <std::pair<TRootTopCandidate,std::string> > vecTop;
					vecTop.push_back(std::pair<TRootTopCandidate,std::string>(hadTop,string("HadTop")));
					vecTop.push_back(std::pair<TRootTopCandidate,std::string>(lepTop,string("LepTop")));
					TRootCompositeCandidate compo(vecTop);
					std::vector<int> vecInt = semiLepEvent.jetLeptonCombination(i,j);
			        	TRootSemiLepEvent::HypoCombPair	hypcomb(compo,vecInt);
			        	TRootSemiLepEvent::HypoClassKey	key = (TRootSemiLepEvent::HypoClassKey)i;
					semiLepEvt.addEventHypo(key,hypcomb);
				}
				delete quarkP;
				delete quarkQ;
				delete hadronicB;
				delete leptonicB;
				delete muon;
			    }
			}
        	}
	}

	new( (*rootSemiLepEvent)[0] ) TRootSemiLepEvent(semiLepEvt);
}
