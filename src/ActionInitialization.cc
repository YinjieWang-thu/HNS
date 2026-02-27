/// \file src/ActionInitialization.cc
/// \brief Implementation of the MD::ActionInitialization class

#include "ActionInitialization.hh"

#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "TrackingAction.hh"

namespace MD
{


void ActionInitialization::BuildForMaster() const
{
  auto runAction = new RunAction;
  SetUserAction(runAction);
}


void ActionInitialization::Build() const
{
  //每写一个新的Action就在这里调用SetUserAction()
  SetUserAction(new PrimaryGeneratorAction);

  auto runAction = new RunAction;
  SetUserAction(runAction);

  auto eventAction = new EventAction(runAction);
  SetUserAction(eventAction);

  SetUserAction(new SteppingAction(eventAction));
  SetUserAction(new TrackingAction());
}


} 
