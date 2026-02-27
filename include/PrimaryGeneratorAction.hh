/// \file /include/PrimaryGeneratorAction.hh
/// \brief Definition of the MD::PrimaryGeneratorAction class

#ifndef MDPrimaryGeneratorAction_h
#define MDPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include <vector>

class G4ParticleGun;
class G4Event;

struct ParticleData {
    G4ThreeVector momentum_p, momentum_K, momentum_Ld;
    G4double energy_p, energy_K, energy_Ld, weight;
};


namespace MD
{

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued
/// in front of the phantom across 80% of the (X,Y) phantom size.

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    // method from the base class
    void GeneratePrimaries(G4Event*) override;

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    G4ParticleGun* fParticleGun = nullptr;  
    std::vector<ParticleData> fParticleData;
    size_t fCurrentIndex;
} ;

#endif

}
