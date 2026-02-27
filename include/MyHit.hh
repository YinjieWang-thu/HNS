#ifndef MDMyHit_h
#define MDMyHit_h 1



#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4THitsCollection.hh"


namespace MD
{

class MyHit : public G4VHit {
public:
    MyHit() {}
    virtual ~MyHit() {}

    G4ThreeVector fPos;
    G4ThreeVector fMomentum;
    G4String fParticleName;
    G4double fKineticE;
    G4int fOrigin;
    //Origin: -1 as default;
    //for proton, 0 for primary, 1 for Lambda decay, -1 for other;
    //pion-, 1 for Lambda decay, -1 for other;
    //for gamma, 1 for pi0 from Lambda, -1 for other;

    void SetPos(const G4ThreeVector& pos) { fPos = pos; }
    void SetMomentum(const G4ThreeVector& mom) { fMomentum = mom; }
    void SetParticleName(const G4String& name) { fParticleName = name; }
    void SetKineticE(const G4double& ke) { fKineticE = ke; }
    void SetOrigin(const G4int& ori) { fOrigin = ori; }

    const G4ThreeVector& GetPos() const { return fPos; }
    const G4ThreeVector& GetMomentum() const { return fMomentum; }
    const G4String& GetParticleName() const { return fParticleName; }
    const G4double& GetKineticE() const { return fKineticE; }
    const G4int& GetOrigin() const { return fOrigin; }
};

using MyHitsCollection = G4THitsCollection<MyHit>;

}

#endif
