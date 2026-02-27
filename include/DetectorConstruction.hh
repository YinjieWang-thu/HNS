/// \file include/DetectorConstruction.hh
/// \brief Definition of the MD::DetectorConstruction class

#ifndef MDDetectorConstruction_h
#define MDDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

namespace MD
{

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction() = default;
    ~DetectorConstruction() override = default;

    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;
    G4LogicalVolume* GetDetLog() const { return fDetLog; }

  protected:
    G4LogicalVolume* fDetLog = nullptr;
};

}  

#endif
