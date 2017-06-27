#include "../interface/GenTTXCategorizer.h"

////////////////// Tool for splitting ttbar+jets into separate flavour contributions: https://twiki.cern.ch/twiki/bin/view/CMSPublic/GenHFHadronMatcher
GenTTXCategorizer::GenTTXCategorizer()
{
   genJetPtMin_ = 20.;
   genJetAbsEtaMax_ = 666.;
}

Int_t GenTTXCategorizer::Run(
	    edm::Handle<reco::GenJetCollection> genTTXJets,
	    edm::Handle<std::vector<int> >genTTXBHadFlavour,
	    edm::Handle<std::vector<int> > genTTXBHadJetIndex,
	    edm::Handle<std::vector<int> > genTTXBHadFromTopWeakDecay,
	    edm::Handle<std::vector<reco::GenParticle> > genTTXBHadPlusMothers,
	    edm::Handle<std::vector<std::vector<int> > > genTTXBHadPlusMothersIndices,
	    edm::Handle<std::vector<int> > genTTXBHadIndex,
	    edm::Handle<std::vector<int> > genTTXBHadLeptonHadronIndex,
	    edm::Handle<std::vector<int> > genTTXBHadLeptonViaTau,
	    edm::Handle<std::vector<int> > genTTXCHadFlavour,
	    edm::Handle<std::vector<int> > genTTXCHadJetIndex,
	    edm::Handle<std::vector<int> > genTTXCHadFromTopWeakDecay,
	    edm::Handle<std::vector<int> > genTTXCHadBHadronId)
{
   std::map<int, int> bJetFromTopIds;
   std::map<int, int> bJetIds;
   std::map<int, int> cJetIds;



   
   // Count number of specific b hadrons in each jet
   for(size_t hadronId = 0; hadronId < genTTXBHadIndex->size(); ++hadronId) 
     {
        // Flavour of the hadron's origin
        const int flavour = genTTXBHadFlavour->at(hadronId);
	
        // Skip b hadrons coming for W decays (rare case due to CKM, in some generated samples not present at all)
        if(std::abs(flavour) == 24) continue;
	
        // Index of jet associated to the hadron
        const int jetIndex = genTTXBHadJetIndex->at(hadronId);
	
        // Skip hadrons which have no associated jet
        if(jetIndex < 0) continue;
	
        // Skip if jet is not in acceptance
        if(genTTXJets->at(jetIndex).pt() < genJetPtMin_) continue;
	
        if(std::fabs(genTTXJets->at(jetIndex).eta()) > genJetAbsEtaMax_) continue;
	
        // Jet from direct top quark decay [pdgId(top)=6]
        if(std::abs(flavour) == 6) 
	  {
	     if(bJetFromTopIds.count(jetIndex) < 1) bJetFromTopIds[jetIndex] = 1;
	     else bJetFromTopIds[jetIndex]++;
	     continue;
	  }
	
        // Identify jets with b hadrons not from top quark decay
        if(bJetIds.count(jetIndex) < 1) bJetIds[jetIndex] = 1;
        else bJetIds[jetIndex]++;
     }
    
   // Count number of specific c hadrons in each c jet
   for(size_t hadronId = 0; hadronId < genTTXCHadJetIndex->size(); ++hadronId) 
     {
        // Skip c hadrons that are coming from b hadrons
        if(genTTXCHadBHadronId->at(hadronId) >= 0) continue;
	
        // Skip c hadrons coming from W decays
        if(std::abs(genTTXCHadFlavour->at(hadronId)) == 24) continue;
	
        // Index of jet associated to the hadron
        const int jetIndex = genTTXCHadJetIndex->at(hadronId);
	
        // Skip hadrons which have no associated jet
        if(jetIndex < 0) continue;
	
        // Skip if jet is not in acceptance
        if(genTTXJets->at(jetIndex).pt() < genJetPtMin_) continue;
        if(std::fabs(genTTXJets->at(jetIndex).eta()) > genJetAbsEtaMax_) continue;
	
        // Identify jets with b hadrons
        if(cJetIds.count(jetIndex) < 1) cJetIds[jetIndex] = 1;
        else cJetIds[jetIndex]++;
     }
    
   // Find additional b jets
   std::vector<int> additionalBJetIds;
   for(std::map<int, int>::iterator it = bJetIds.begin(); it != bJetIds.end(); ++it) 
     {
        const int jetId = it->first;
	
        // Skip jet if it contains a b hadron directly from top quark decay
        if(bJetFromTopIds.count(jetId) > 0) continue;
        additionalBJetIds.push_back(jetId);
     }
    
   // Find additional c jets
   std::vector<int> additionalCJetIds;
   for(std::map<int, int>::iterator it = cJetIds.begin(); it != cJetIds.end(); ++it) 
     {
        const int jetId = it->first;
	
        // Skip jet if it contains a b hadron, thus being a b jet
        if(bJetFromTopIds.count(jetId) > 0) continue;
        additionalCJetIds.push_back(jetId);
     }
        
   // Categorize event based on number of additional b/c jets
   // and number of corresponding hadrons in each of them
   int additionalJetEventId = bJetFromTopIds.size()*100;
   
   // tt + 1 additional b jet
   if(additionalBJetIds.size() == 1)
     {
        int nHadronsInJet = bJetIds[additionalBJetIds.at(0)];
	
        // tt + 1 additional b jet from 1 additional b hadron
        if(nHadronsInJet == 1) additionalJetEventId += 51;
        // tt + 1 additional b jet from >=2 additional b hadrons
        else additionalJetEventId += 52;
     }
   // tt + >=2 additional b jets
   else if(additionalBJetIds.size() > 1)
     {
        // Check first two additional b jets (rare cases could have more)
        int nHadronsInJet1 = bJetIds[additionalBJetIds.at(0)];
        int nHadronsInJet2 = bJetIds[additionalBJetIds.at(1)];
	
        // tt + >=2 additional b jets each from 1 additional b hadron
        if(std::max(nHadronsInJet1, nHadronsInJet2) == 1) additionalJetEventId += 53;
        // tt + >=2 additional b jets one of which from >=2 additional b hadrons
        else if(std::min(nHadronsInJet1, nHadronsInJet2) == 1 && std::max(nHadronsInJet1, nHadronsInJet2) > 1) additionalJetEventId += 54;
        // tt + >=2 additional b jets each from >=2 additional b hadrons
        else if(std::min(nHadronsInJet1, nHadronsInJet2) > 1) additionalJetEventId += 55;
     }
   // tt + no additional b jets
   else
     {
        // tt + 1 additional c jet
        if(additionalCJetIds.size() == 1)
	  {
	     int nHadronsInJet = cJetIds[additionalCJetIds.at(0)];
	     // tt + 1 additional c jet from 1 additional c hadron
	     if(nHadronsInJet == 1) additionalJetEventId += 41;
	     // tt + 1 additional c jet from >=2 additional c hadrons
	     else additionalJetEventId += 42;
	  }
        // tt + >=2 additional c jets
        else if(additionalCJetIds.size() > 1)
	  {
	     // Check first two additional c jets (rare cases could have more)
	     int nHadronsInJet1 = cJetIds[additionalCJetIds.at(0)];
	     int nHadronsInJet2 = cJetIds[additionalCJetIds.at(1)];
	     // tt + >=2 additional c jets each from 1 additional c hadron
	     if(std::max(nHadronsInJet1, nHadronsInJet2) == 1) additionalJetEventId += 43;
	     // tt + >=2 additional c jets one of which from >=2 additional c hadrons
	     else if(std::min(nHadronsInJet1, nHadronsInJet2) == 1 && std::max(nHadronsInJet1, nHadronsInJet2) > 1) additionalJetEventId += 44;
	     // tt + >=2 additional c jets each from >=2 additional c hadrons
	     else if(std::min(nHadronsInJet1, nHadronsInJet2) > 1) additionalJetEventId += 45;
	  }
        // tt + no additional c jets
        else
	  {
	     // tt + light jets
	     additionalJetEventId += 0;
	  }
     }

   return additionalJetEventId;
}

