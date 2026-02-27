/// \file src/SteppingAction.cc
/// \brief Implementation of the MD::SteppingAction class

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Event.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"

namespace MD
{


SteppingAction::SteppingAction(EventAction* eventAction) : fEventAction(eventAction) {}


void SteppingAction::UserSteppingAction(const G4Step* step)
{

  //Manually Detector for crosscheck


 // if (!fDetVolume) {
  //  const auto detConstruction = static_cast<const DetectorConstruction*>(
  //    G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  //  fDetVolume = detConstruction->GetDetLog();
  //}

  // get volume of the current step
  //G4LogicalVolume* volume =
  //  step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  // check if we are in scoring volume
  //if (volume != fDetVolume) return;

  // collect hit in this step
  //G4cout<<"Hit Detected in step, pos: "<<step->GetPreStepPoint()->GetPosition()<<
  //" ,particle name: "<<step->GetTrack()->GetDefinition()->GetParticleName()<<G4endl;


}


} 
