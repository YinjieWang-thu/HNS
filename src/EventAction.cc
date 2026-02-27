/// \file src/EventAction.cc
/// \brief Implementation of the MD::EventAction class

#include "MyHit.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "MySensitiveDetector.hh"
#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "TrackRegistry.hh"

namespace MD{


EventAction::EventAction(RunAction* runAction) : fRunAction(runAction) {}


void EventAction::BeginOfEventAction(const G4Event*)
{
    TrackRegistry::ClearForNewEvent();
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    auto analysisManager = G4AnalysisManager::Instance();
    /*
    analysisManager->FillNtupleIColumn(0,0);
    analysisManager->FillNtupleIColumn(8,0);
    analysisManager->FillNtupleIColumn(16,0);
    analysisManager->FillNtupleIColumn(24,0);
    analysisManager->FillNtupleIColumn(32,0);
    for(G4int j = 1; j<=39; ++j)
    {
        if(j%8 == 0) continue;
        analysisManager->FillNtupleDColumn(j,0);
    }*/

    auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID("MyDetectorSD/MyHitsCollection");
    auto hc = static_cast<MyHitsCollection*>(event->GetHCofThisEvent()->GetHC(hcID));
    if (hc) {
        G4bool is_first_photon = true;//is first photon from pi0 from Lambda
        for (size_t i = 0; i < hc->entries(); ++i) {
            auto hit = (*hc)[i];
            if (hit->GetParticleName() == "proton") //consider string::compare()
            {
                G4int ori = hit->GetOrigin();
                if(ori == 0)
                {
                    analysisManager->FillNtupleIColumn(0,1);
                    analysisManager->FillNtupleDColumn(1,hit->GetPos().x());
                    analysisManager->FillNtupleDColumn(2,hit->GetPos().y());
                    analysisManager->FillNtupleDColumn(3,hit->GetPos().z());
                    analysisManager->FillNtupleDColumn(4,hit->GetMomentum().x());
                    analysisManager->FillNtupleDColumn(5,hit->GetMomentum().y());
                    analysisManager->FillNtupleDColumn(6,hit->GetMomentum().z());
                    analysisManager->FillNtupleDColumn(7,hit->GetKineticE());
                }
                else if(ori == 1)
                {
                    analysisManager->FillNtupleIColumn(32,1);
                    analysisManager->FillNtupleDColumn(33,hit->GetPos().x());
                    analysisManager->FillNtupleDColumn(34,hit->GetPos().y());
                    analysisManager->FillNtupleDColumn(35,hit->GetPos().z());
                    analysisManager->FillNtupleDColumn(36,hit->GetMomentum().x());
                    analysisManager->FillNtupleDColumn(37,hit->GetMomentum().y());
                    analysisManager->FillNtupleDColumn(38,hit->GetMomentum().z());
                    analysisManager->FillNtupleDColumn(39,hit->GetKineticE());
                }

            }
            if(hit->GetParticleName() == "kaon+")
            {
                analysisManager->FillNtupleIColumn(8,1);
                analysisManager->FillNtupleDColumn(9,hit->GetPos().x());
                analysisManager->FillNtupleDColumn(10,hit->GetPos().y());
                analysisManager->FillNtupleDColumn(11,hit->GetPos().z());
                analysisManager->FillNtupleDColumn(12,hit->GetMomentum().x());
                analysisManager->FillNtupleDColumn(13,hit->GetMomentum().y());
                analysisManager->FillNtupleDColumn(14,hit->GetMomentum().z());
                analysisManager->FillNtupleDColumn(15,hit->GetKineticE());
            }
            if(hit->GetParticleName() == "sigma0")
            {
                analysisManager->FillNtupleIColumn(16,1);
                analysisManager->FillNtupleDColumn(17,hit->GetPos().x());
                analysisManager->FillNtupleDColumn(18,hit->GetPos().y());
                analysisManager->FillNtupleDColumn(19,hit->GetPos().z());
                analysisManager->FillNtupleDColumn(20,hit->GetMomentum().x());
                analysisManager->FillNtupleDColumn(21,hit->GetMomentum().y());
                analysisManager->FillNtupleDColumn(22,hit->GetMomentum().z());
                analysisManager->FillNtupleDColumn(23,hit->GetKineticE());
            }
            if(hit->GetParticleName() == "lambda" && hit->GetOrigin() == 1)
            {
                analysisManager->FillNtupleIColumn(24,1);
                analysisManager->FillNtupleDColumn(25,hit->GetPos().x());
                analysisManager->FillNtupleDColumn(26,hit->GetPos().y());
                analysisManager->FillNtupleDColumn(27,hit->GetPos().z());
                analysisManager->FillNtupleDColumn(28,hit->GetMomentum().x());
                analysisManager->FillNtupleDColumn(29,hit->GetMomentum().y());
                analysisManager->FillNtupleDColumn(30,hit->GetMomentum().z());
                analysisManager->FillNtupleDColumn(31,hit->GetKineticE());
            }
            if(hit->GetParticleName() == "pi-" && hit->GetOrigin() == 1)
            {
                analysisManager->FillNtupleIColumn(40,1);
                analysisManager->FillNtupleDColumn(41,hit->GetPos().x());
                analysisManager->FillNtupleDColumn(42,hit->GetPos().y());
                analysisManager->FillNtupleDColumn(43,hit->GetPos().z());
                analysisManager->FillNtupleDColumn(44,hit->GetMomentum().x());
                analysisManager->FillNtupleDColumn(45,hit->GetMomentum().y());
                analysisManager->FillNtupleDColumn(46,hit->GetMomentum().z());
                analysisManager->FillNtupleDColumn(47,hit->GetKineticE());
            }

            if (hit->GetParticleName() == "gamma" && hit->GetOrigin() == 1)
            {
                if(is_first_photon)
                {
                    analysisManager->FillNtupleIColumn(48,1);
                    analysisManager->FillNtupleDColumn(49,hit->GetPos().x());
                    analysisManager->FillNtupleDColumn(50,hit->GetPos().y());
                    analysisManager->FillNtupleDColumn(51,hit->GetPos().z());
                    analysisManager->FillNtupleDColumn(52,hit->GetMomentum().x());
                    analysisManager->FillNtupleDColumn(53,hit->GetMomentum().y());
                    analysisManager->FillNtupleDColumn(54,hit->GetMomentum().z());
                    analysisManager->FillNtupleDColumn(55,hit->GetKineticE());
                }
                else
                {
                    analysisManager->FillNtupleIColumn(56,1);
                    analysisManager->FillNtupleDColumn(57,hit->GetPos().x());
                    analysisManager->FillNtupleDColumn(58,hit->GetPos().y());
                    analysisManager->FillNtupleDColumn(59,hit->GetPos().z());
                    analysisManager->FillNtupleDColumn(60,hit->GetMomentum().x());
                    analysisManager->FillNtupleDColumn(61,hit->GetMomentum().y());
                    analysisManager->FillNtupleDColumn(62,hit->GetMomentum().z());
                    analysisManager->FillNtupleDColumn(63,hit->GetKineticE());
                }
                is_first_photon = false;
            }
            if (hit->GetParticleName() == "gamma" && hit->GetOrigin() == 2)
            {
                analysisManager->FillNtupleIColumn(64,1);
                analysisManager->FillNtupleDColumn(65,hit->GetPos().x());
                analysisManager->FillNtupleDColumn(66,hit->GetPos().y());
                analysisManager->FillNtupleDColumn(67,hit->GetPos().z());
                analysisManager->FillNtupleDColumn(68,hit->GetMomentum().x());
                analysisManager->FillNtupleDColumn(69,hit->GetMomentum().y());
                analysisManager->FillNtupleDColumn(70,hit->GetMomentum().z());
                analysisManager->FillNtupleDColumn(71,hit->GetKineticE());
            }

            if(hit->GetParticleName() == "neutron" && hit->GetOrigin() == 1)
            {
                analysisManager->FillNtupleIColumn(72,1);
                analysisManager->FillNtupleDColumn(73,hit->GetPos().x());
                analysisManager->FillNtupleDColumn(74,hit->GetPos().y());
                analysisManager->FillNtupleDColumn(75,hit->GetPos().z());
                analysisManager->FillNtupleDColumn(76,hit->GetMomentum().x());
                analysisManager->FillNtupleDColumn(77,hit->GetMomentum().y());
                analysisManager->FillNtupleDColumn(78,hit->GetMomentum().z());
                analysisManager->FillNtupleDColumn(79,hit->GetKineticE());
            }
        }
    }
    G4PrimaryVertex* vtx = event->GetPrimaryVertex(0);
    if(vtx)
    {
        analysisManager->FillNtupleDColumn(80,vtx->GetWeight());
    }
    analysisManager->AddNtupleRow();
}

}  
