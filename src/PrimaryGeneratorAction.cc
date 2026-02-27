/// \file src/PrimaryGeneratorAction.cc
/// \brief Implementation of the MD::PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Event.hh"
#include <fstream>
#include <sstream>
#include <iostream>

namespace MD
{



PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(nullptr),
  fCurrentIndex(0)
{
  fParticleGun = new G4ParticleGun(1);

  // default particle kinematic
  //初始化Particle gun的粒子种类和能量，PrimaryGeneratorAction中的定义会被macro的/gun/命令覆盖
  //但是如果在下面的GeneratePrimaries中初始化Particle GUn，那么marco的命令会被覆盖
  

  std::ifstream infile("data.txt");
  if(!infile){
    G4Exception("PrimaryGeneratorAction","DataFileNotFound",FatalException,
                    "Cannot open proton_data.txt");
  }

G4double px_p, py_p, pz_p, E_p, px_K, py_K, pz_K, E_K, px_Ld, py_Ld, pz_Ld, E_Ld, w;
    while(infile >> px_p >> py_p >> pz_p >> E_p >> px_K >> py_K >> pz_K >> E_K >> px_Ld >> py_Ld >> pz_Ld >> E_Ld >> w ) {
        ParticleData data;
        G4ThreeVector mom_p(px_p* GeV, py_p* GeV, pz_p* GeV);
        G4ThreeVector mom_K(px_K* GeV, py_K* GeV, pz_K* GeV);
        G4ThreeVector mom_Ld(px_Ld* GeV, py_Ld* GeV, pz_Ld* GeV);
        data.momentum_p = mom_p;
        data.momentum_K = mom_K;
        data.momentum_Ld = mom_Ld;
        data.energy_p = (E_p-0.93827) * GeV;
        data.energy_K = (E_K-0.49368) * GeV;
        data.energy_Ld = (E_Ld-1.11568) * GeV;
        data.weight = w;
        fParticleData.push_back(data);
    }

    infile.close();

    G4cout << "Loaded " << fParticleData.size()
           << " events from file." << G4endl;


  
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle1 = particleTable->FindParticle(particleName = "proton");
  G4ParticleDefinition* particle2 = particleTable->FindParticle(particleName = "kaon+");
  G4ParticleDefinition* particle3 = particleTable->FindParticle(particleName = "lambda");
  


  auto evtID = event->GetEventID();  
    if (evtID >= (G4int)fParticleData.size()) {
        G4cerr << "Warning: event ID " << evtID
               << " beyond proton data size " << fParticleData.size()
               << ", reusing last entry." << G4endl;
        return;
    }

    G4cout << "-------------------------------------------------------------------processing: "<< evtID << G4endl;

  const ParticleData& pd = fParticleData[evtID];

  fParticleGun->SetParticleDefinition(particle1);
  fParticleGun->SetParticleMomentum(pd.momentum_p);
  fParticleGun->SetParticleEnergy(pd.energy_p);//注意是动能
  fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));
  fParticleGun->GeneratePrimaryVertex(event);

  fParticleGun->SetParticleDefinition(particle2);
  fParticleGun->SetParticleMomentum(pd.momentum_K);
  fParticleGun->SetParticleEnergy(pd.energy_K);
  fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));
  fParticleGun->GeneratePrimaryVertex(event);

  fParticleGun->SetParticleDefinition(particle3);
  fParticleGun->SetParticleMomentum(pd.momentum_Ld);
  fParticleGun->SetParticleEnergy(pd.energy_Ld);
  fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));

  fParticleGun->GeneratePrimaryVertex(event);

  G4PrimaryVertex* vertex = event->GetPrimaryVertex(0);
  if(vertex) vertex->SetWeight(pd.weight);

  fCurrentIndex++;
}


}  
