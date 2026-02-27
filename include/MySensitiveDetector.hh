#ifndef MDMySensitiveDetector_h
#define MDMySensitiveDetector_h 1


#include "G4VSensitiveDetector.hh"
#include "MyHit.hh"
#include "G4SDManager.hh"
#include "G4VProcess.hh"
#include "TrackRegistry.hh"

namespace MD
{

class MySensitiveDetector : public G4VSensitiveDetector {
public:
    MySensitiveDetector(const G4String& name)
        : G4VSensitiveDetector(name), fHitsCollection(nullptr) {
            //一定要注册名字
            collectionName.insert("MyHitsCollection");
        }

    ~MySensitiveDetector() {}

    virtual void Initialize(G4HCofThisEvent* hce) override {
        fHitsCollection = new MyHitsCollection(SensitiveDetectorName, collectionName[0]);
        auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
        hce->AddHitsCollection(hcID, fHitsCollection);
    }

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override {
        auto hit = new MyHit();
        auto track = step->GetTrack();
        hit->SetPos(step->GetPreStepPoint()->GetPosition());
        hit->SetMomentum(track->GetMomentum());
        hit->SetParticleName(track->GetDefinition()->GetParticleName());
        hit->SetKineticE(track->GetKineticEnergy());
        auto name = track->GetDefinition()->GetParticleName();
        hit->SetOrigin(-1);
        if(name == "proton")
        {
            G4int parentID = step->GetTrack()->GetParentID();
            if(parentID == 0) hit->SetOrigin(0);
            else
            {
                auto parentInfoOpt = TrackRegistry::Lookup(parentID);
                if(parentInfoOpt)
                {
                    TrackInfo parentInfo = *parentInfoOpt;
                    if(parentInfo.pdgCode == 3122)
                    {
                        hit->SetOrigin(1);
                    }
                }
            }
        }

        if(name == "neutron")
        {
            G4int parentID = step->GetTrack()->GetParentID();
            auto parentInfoOpt = TrackRegistry::Lookup(parentID);
            if(parentInfoOpt)
            {
                TrackInfo parentInfo = *parentInfoOpt;
                if(parentInfo.pdgCode == 3122)
                {
                    hit->SetOrigin(1);
                }
            }
        }

        if(name == "lambda")
        {
            G4int parentID = step->GetTrack()->GetParentID();
            auto parentInfoOpt = TrackRegistry::Lookup(parentID);
            if(parentInfoOpt)
            {
                TrackInfo parentInfo = *parentInfoOpt;
                if(parentInfo.pdgCode == 3212)
                {
                    hit->SetOrigin(1);
                }
            }
        }

        if (name == "pi-")
        {
            G4int parentID = track->GetParentID();
            auto parentInfoOpt = TrackRegistry::Lookup(parentID);

            if(parentInfoOpt)
            {
                TrackInfo parentInfo = *parentInfoOpt;
                if (parentInfo.pdgCode == 3122)
                {
                    hit->SetOrigin(1);
                }
            }
        }
        
        if (name == "gamma")
        {
            G4int parentID = track->GetParentID();
            auto parentInfoOpt = TrackRegistry::Lookup(parentID);

            if(parentInfoOpt)
            {
                TrackInfo parentInfo = *parentInfoOpt;
                if(parentInfo.pdgCode == 111)
                {
                    G4int grandParentID = parentInfo.parentID;
                    auto grandInfoOpt = TrackRegistry::Lookup(grandParentID);
                    if(grandInfoOpt)
                    {
                        TrackInfo grandInfo = *grandInfoOpt;
                        if (grandInfo.pdgCode == 3122)
                        {
                            hit->SetOrigin(1);
                        }
                    }
                }
                if(parentInfo.pdgCode == 3212)
                {
                    hit->SetOrigin(2);
                }
            }
        }

        fHitsCollection->insert(hit);
        return true;
    }

private:
    MyHitsCollection* fHitsCollection;
};

}

#endif