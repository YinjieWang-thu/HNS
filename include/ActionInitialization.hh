/// \file include/ActionInitialization.hh
/// \brief Definition of the MD::ActionInitialization class

#ifndef MDActionInitialization_h
#define MDActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

namespace MD
{


class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization() = default;
    ~ActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build() const override;
};

}  

#endif
