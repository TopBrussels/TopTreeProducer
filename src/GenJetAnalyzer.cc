#include "../interface/GenJetAnalyzer.h"

using namespace std;
using namespace TopTree;
using namespace reco;
using namespace edm;


GenJetAnalyzer::GenJetAnalyzer(std::string genJetProducerStr, const edm::ParameterSet& myConfig, int verbosity):verbosity_(verbosity)
{
    genJetProducer_ = edm::InputTag(genJetProducerStr);
}

GenJetAnalyzer::~GenJetAnalyzer()
{
}

void GenJetAnalyzer::Process(const edm::Event& iEvent, TClonesArray* rootGenJets, edm::EDGetTokenT<std::vector<reco::GenJet> > genJetToken)
{

    // check if the genJet is of the good type
    std::string jetType = "BASIC";
    if( genJetProducer_.label()=="kt4GenJets" || genJetProducer_.label()=="kt6GenJets" || genJetProducer_.label()=="ak5GenJets"
            || genJetProducer_.label()=="ak7GenJets" || genJetProducer_.label()=="ak5GenJetsNoE" || genJetProducer_.label()=="ak5GenJetsNoNu" || genJetProducer_.label()=="ak5GenJetsNoMuNoNu" || genJetProducer_.label()== "slimmedGenJets") jetType="GOOD";

    edm::Handle < std::vector <reco::GenJet> > recoGenJets;
    iEvent.getByToken(genJetToken, recoGenJets);

    unsigned int nJets = recoGenJets->size();

    if(verbosity_>1) std::cout << "   Number of jets = " << nJets << std::endl;

    for (unsigned int j=0; j<nJets; j++)
    {

        if(verbosity_>4)	cout << "Analysing GenJets collection ...looping = " << j  <<endl;
        const reco::GenJet* genJet = 0;
        if( jetType=="GOOD" ) genJet = (const reco::GenJet*) ( & ((*recoGenJets)[j]) );

        TRootGenJet localGenJet(
            genJet->px()
            ,genJet->py()
            ,genJet->pz()
            ,genJet->energy()
            ,genJet->vx()
            ,genJet->vy()
            ,genJet->vz()
            ,genJet->pdgId()
            ,genJet->charge()
        );

        localGenJet.setNConstituents(genJet->nConstituents());
        localGenJet.setMaxDistance(genJet->maxDistance());
        localGenJet.setN90(genJet->nCarrying(0.9));
        localGenJet.setN60(genJet->nCarrying(0.6));
        localGenJet.setetaetaMoment(genJet->etaetaMoment());
        localGenJet.setphiphiMoment(genJet->phiphiMoment());
        localGenJet.setEMEnergy(genJet->emEnergy());
        localGenJet.setHadEnergy(genJet->hadEnergy());
        localGenJet.setInvisibleEnergy(genJet->invisibleEnergy());

        if(verbosity_>4)	cout << "Analysing GenJets collection ...looping Filled Kinematics= " << j  <<endl;
        bool isBHadron = false;
        bool isCHadron = false;
        TRootMCParticle BHad;
        TRootMCParticle CHad;


        std::vector <const reco::Candidate*> mcparts;
        for(unsigned genidx = 0; genidx < genJet->numberOfDaughters(); genidx++)
        {
            if(!(genJet->sourceCandidatePtr(genidx).isNonnull() && genJet->sourceCandidatePtr(genidx).isAvailable()))
            {
                edm::LogInfo("JetConstituentPointer") << "Bad pointer to jet constituent found.  Check for possible dropped particle.";
                continue;
            }

            mcparts.push_back(genJet->daughter(genidx));
        }

        if(verbosity_>4)	cout << "Analysing GenJets collection ...Constituates Loaded = " << j  <<endl;
        for (unsigned i = 0; i < mcparts.size (); i++)
        {
            const reco::Candidate* mcpart = mcparts[i];
            const reco::Candidate* lastB = lastBHadron(*mcpart);
            if( lastB )
            {
                isBHadron = true;
                TRootMCParticle tmp( lastB->px(), lastB->py(), lastB->pz(), lastB->energy() );
                BHad = tmp;
                break;
            }
        }

        for (unsigned i = 0; i < mcparts.size (); i++)
        {
            if( isBHadron ) break; //no need to loop over again, this is b-jet!
            const reco::Candidate* mcpart = mcparts[i];
            const reco::Candidate* lastC = lastCHadron(*mcpart);
            if( lastC )
            {
                isCHadron = true;
                TRootMCParticle tmp( lastC->px(), lastC->py(), lastC->pz(), lastC->energy() );
                CHad = tmp;
                break;
            }
        }
        if(verbosity_>4)	cout << "B Hadron? : " << isBHadron <<endl;
        if( isBHadron ) localGenJet.setBHadron(BHad); //if B-Hadron matched, always assign B-Hadron
        else localGenJet.setBHadron(TRootMCParticle());
        if(verbosity_>4)	cout << "C Hadron? : " << isCHadron <<endl;
        if( isCHadron ) localGenJet.setCHadron(CHad); //if only no B-Hadron matched, assign C-Hadron
        else localGenJet.setCHadron(TRootMCParticle());

        if(verbosity_>4)	cout << "Analysing GenJets collection ...checked hadrons. " << localGenJet.Px()  <<" "<< localGenJet.Py()  <<"  "  << localGenJet.Pt() <<" size GJ : "<<  (sizeof(rootGenJets))  << endl;
        if(verbosity_>4)
        {
            TRootGenJet testjet(localGenJet);
            cout << "Checking Copy Constructor of TRootGenJet" << endl;
        }
        new ((*rootGenJets)[j]) TRootGenJet(localGenJet);

        if(verbosity_>4)	cout << "Analysing GenJets colloction wrote genjet"  <<endl;

        if(verbosity_>2) cout << "   ["<< setw(3) << j << "] " << localGenJet << endl;
    }
}

std::vector<const reco::Candidate *> GenJetAnalyzer::getAncestors(const reco::Candidate &c)
{
    vector<const reco::Candidate *> moms;
    if( c.numberOfMothers() == 1 )
    {
        const Candidate * dau = &c;
        const Candidate * mom = c.mother();
        while ( dau->numberOfMothers() == 1)
        {
            moms.push_back( dau );
            dau = mom ;
            mom = dau->mother();
        }
    }
    return moms;
}

bool GenJetAnalyzer::hasBottom(const reco::Candidate &c)
{
    int code1;
    int code2;
    bool tmpHasBottom = false;
    code1 = (int)( ( abs(c.pdgId() ) / 100)%10 );
    code2 = (int)( ( abs(c.pdgId() ) /1000)%10 );
    if ( code1 == 5 || code2 == 5) tmpHasBottom = true;
    return tmpHasBottom;
}

bool GenJetAnalyzer::hasCharm(const reco::Candidate &c)
{
    int code1;
    int code2;
    bool tmpHasCharm = false;
    code1 = (int)( ( abs(c.pdgId() ) / 100)%10 );
    code2 = (int)( ( abs(c.pdgId() ) /1000)%10 );
    if ( code1 == 4 || code2 == 4) tmpHasCharm = true;
    return tmpHasCharm;
}

bool GenJetAnalyzer::decayFromBHadron(const Candidate & c)
{
    bool isFromB = false;
    vector<const Candidate *> allParents = getAncestors( c );
    for( vector<const Candidate *>::const_iterator aParent = allParents.begin();
            aParent != allParents.end();
            aParent ++ )
    {
        if( hasBottom(**aParent) ) isFromB = true;
        /*
         cout << " particle Parent is " << (*aParent)->status()
         << " type " << (*aParent)->pdgId()
         << " pt= " << (*aParent)->pt()
         << " isB = " << isFromB
         << endl;
        */
    }
    return isFromB;
}

bool GenJetAnalyzer::decayFromCHadron(const Candidate & c)
{
    bool isFromC = false;
    vector<const Candidate *> allParents = getAncestors( c );
    for( vector<const Candidate *>::const_iterator aParent = allParents.begin();
            aParent != allParents.end();
            aParent ++ )
    {
        if( hasCharm(**aParent) ) isFromC = true;
        /*
        cout << " particle Parent is " << (*aParent)->status()
        << " type " << (*aParent)->pdgId()
        << " pt=" << (*aParent)->pt()
        << " isC = " << isFromC
        << endl;
        */
    }
    return isFromC;
}

const Candidate* GenJetAnalyzer::lastBHadron(const Candidate & c)
{
    const Candidate * out = 0;

    vector<const Candidate *> allParents = getAncestors( c );
    for( vector<const Candidate *>::const_iterator aParent = allParents.begin();
            aParent != allParents.end();
            aParent ++ )
    {
        if( hasBottom(**aParent) ) out = *aParent;

    }
    return out;
}

const Candidate* GenJetAnalyzer::lastCHadron(const Candidate & c)
{
    const Candidate * out = 0;

    vector<const Candidate *> allParents = getAncestors( c );
    for( vector<const Candidate *>::const_iterator aParent = allParents.begin();
            aParent != allParents.end();
            aParent ++ )
    {
        if( hasCharm(**aParent) ) out = *aParent;

    }
    return out;
}
