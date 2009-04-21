#ifndef ElectronAnalyzer_h
#define ElectronAnalyzer_h

// system include files
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EgammaReco/interface/BasicCluster.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"

#include "../interface/TRootElectron.h"

#include "TClonesArray.h"


class ElectronAnalyzer{
	
public:
	ElectronAnalyzer(const edm::ParameterSet& producersNames);
	ElectronAnalyzer(const edm::ParameterSet& producersNames, const edm::ParameterSet& myConfig, int verbosity);
	~ElectronAnalyzer();
	void SetVerbosity(int verbosity) {verbosity_ = verbosity; };
	void Process(const edm::Event& iEvent, TClonesArray* rootElectrons, EcalClusterLazyTools& lazyTools);

private:
	int verbosity_;
	std::string dataType_ ;
	edm::InputTag electronProducer_;
	bool useMC_;
        bool runSuperCluster_;

};

#endif
