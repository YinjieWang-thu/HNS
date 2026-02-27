/// \file include/SteppingAction.hh
/// \brief Definition of the MD::SteppingAction class

#ifndef MDSteppingAction_h
#define MDSteppingAction_h 1

#include "G4UserSteppingAction.hh"

class G4LogicalVolume;
class G4Step;

namespace MD
{

class EventAction;


class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(EventAction* eventAction);
    ~SteppingAction() override = default;

    // method from the base class
    void UserSteppingAction(const G4Step*) override;

  private:
    EventAction* fEventAction = nullptr;
    G4LogicalVolume* fDetVolume = nullptr;
};

}

#endif
