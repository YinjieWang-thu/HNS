/// \file include/EventAction.hh
/// \brief Definition of the MD::EventAction class

#ifndef MDEventAction_h
#define MDEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"


class G4Event;

namespace MD
{

class RunAction;


class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* runAction);
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;


  private:
    RunAction* fRunAction = nullptr;

};

}  

#endif
