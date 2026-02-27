
/// \file src/DetectorConstruction.cc
/// \brief Implementation of the MD::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trd.hh"
#include "G4SDManager.hh"
#include "MySensitiveDetector.hh"

namespace MD
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_size = 5*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  auto solidWorld =
    new G4Box("World",  // its name
              0.5 * world_size, 0.5 * world_size, 0.5 * world_size);  // its size

  auto logicWorld = new G4LogicalVolume(solidWorld,  // its solid
                                        world_mat,  // its material
                                        "World");  // its name

  auto physWorld = new G4PVPlacement(nullptr,  // no rotation
                                     G4ThreeVector(),  // at (0,0,0)
                                     logicWorld,  // its logical volume
                                     "World",  // its name
                                     nullptr,  // its mother  volume
                                     false,  // no boolean operation
                                     0,  // copy number
                                     checkOverlaps);  // overlaps checking

  //
  // Detector
  //
  G4double Det_size = 2*m;//Radius
  G4double Det_thickness = 2*mm;
  G4Material* Det_mat = nist->FindOrBuildMaterial("G4_Galactic");

  /*
  auto solidDet = new G4Box("Detector",  // its name
                            0.5 * Det_size, 0.5 * Det_size, 0.5 * Det_thickness); */ // its size

  auto solidDet = new G4Tubs("Detector", 0 ,Det_size, 0.5*Det_thickness, 0, 360*deg);

  auto logicDet = new G4LogicalVolume(solidDet,  // its solid
                                      Det_mat,  // its material
                                      "Detector");  // its name

  new G4PVPlacement(nullptr,  // no rotation
                    G4ThreeVector(0,0,1.001*m),  // at (0,0,1001mm)
                    logicDet,  // its logical volume
                    "Detector",  // its name
                    logicWorld,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking


  fDetLog = logicDet;

  //
  // always return the physical World
  //
  return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
  auto sdManager = G4SDManager::GetSDMpointer();


  auto mySD = new MySensitiveDetector("/MyDetectorSD");     // 命名习惯用形如 /collection/ 的路径
  sdManager->AddNewDetector(mySD);

  SetSensitiveDetector(fDetLog, mySD);
}

}  // namespace B1
