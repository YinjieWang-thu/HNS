/// \file src/RunAction.cc
/// \brief Implementation of the MD::RunAction class

#include "RunAction.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4AnalysisManager.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

namespace MD
{


RunAction::RunAction()
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetDefaultFileType("root");      // 选择 ROOT 格式
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(true); 
    analysisManager->SetNtupleRowWise(false);
    analysisManager->SetFileName("myOutput"); 

    analysisManager->CreateNtuple("Hits", "hits");
    analysisManager->CreateNtupleIColumn("proton1");// bool value
    analysisManager->CreateNtupleDColumn("x_p1");
    analysisManager->CreateNtupleDColumn("y_p1");
    analysisManager->CreateNtupleDColumn("z_p1");
    analysisManager->CreateNtupleDColumn("Px_p1");
    analysisManager->CreateNtupleDColumn("Py_p1");
    analysisManager->CreateNtupleDColumn("Pz_p1");
    analysisManager->CreateNtupleDColumn("Ek_p1");
    analysisManager->CreateNtupleIColumn("Kaon");
    analysisManager->CreateNtupleDColumn("x_K");
    analysisManager->CreateNtupleDColumn("y_K");
    analysisManager->CreateNtupleDColumn("z_K");
    analysisManager->CreateNtupleDColumn("Px_K");
    analysisManager->CreateNtupleDColumn("Py_K");
    analysisManager->CreateNtupleDColumn("Pz_K");
    analysisManager->CreateNtupleDColumn("Ek_K");
    analysisManager->CreateNtupleIColumn("Sigma");
    analysisManager->CreateNtupleDColumn("x_Sg");
    analysisManager->CreateNtupleDColumn("y_Sg");
    analysisManager->CreateNtupleDColumn("z_Sg");
    analysisManager->CreateNtupleDColumn("Px_Sg");
    analysisManager->CreateNtupleDColumn("Py_Sg");
    analysisManager->CreateNtupleDColumn("Pz_Sg");
    analysisManager->CreateNtupleDColumn("Ek_Sg");
    analysisManager->CreateNtupleIColumn("Lambda");
    analysisManager->CreateNtupleDColumn("x_Ld");
    analysisManager->CreateNtupleDColumn("y_Ld");
    analysisManager->CreateNtupleDColumn("z_Ld");
    analysisManager->CreateNtupleDColumn("Px_Ld");
    analysisManager->CreateNtupleDColumn("Py_Ld");
    analysisManager->CreateNtupleDColumn("Pz_Ld");
    analysisManager->CreateNtupleDColumn("Ek_Ld");
    analysisManager->CreateNtupleIColumn("proton2");
    analysisManager->CreateNtupleDColumn("x_p2");
    analysisManager->CreateNtupleDColumn("y_p2");
    analysisManager->CreateNtupleDColumn("z_p2");
    analysisManager->CreateNtupleDColumn("Px_p2");
    analysisManager->CreateNtupleDColumn("Py_p2");
    analysisManager->CreateNtupleDColumn("Pz_p2");
    analysisManager->CreateNtupleDColumn("Ek_p2");
    analysisManager->CreateNtupleIColumn("pion");
    analysisManager->CreateNtupleDColumn("x_pi");
    analysisManager->CreateNtupleDColumn("y_pi");
    analysisManager->CreateNtupleDColumn("z_pi");
    analysisManager->CreateNtupleDColumn("Px_pi");
    analysisManager->CreateNtupleDColumn("Py_pi");
    analysisManager->CreateNtupleDColumn("Pz_pi");
    analysisManager->CreateNtupleDColumn("Ek_pi");
    analysisManager->CreateNtupleIColumn("photon1");
    analysisManager->CreateNtupleDColumn("x_gamma1");
    analysisManager->CreateNtupleDColumn("y_gamma1");
    analysisManager->CreateNtupleDColumn("z_gamma1");
    analysisManager->CreateNtupleDColumn("Px_gamma1");
    analysisManager->CreateNtupleDColumn("Py_gamma1");
    analysisManager->CreateNtupleDColumn("Pz_gamma1");
    analysisManager->CreateNtupleDColumn("Ek_gamma1");
    analysisManager->CreateNtupleIColumn("photon2");
    analysisManager->CreateNtupleDColumn("x_gamma2");
    analysisManager->CreateNtupleDColumn("y_gamma2");
    analysisManager->CreateNtupleDColumn("z_gamma2");
    analysisManager->CreateNtupleDColumn("Px_gamma2");
    analysisManager->CreateNtupleDColumn("Py_gamma2");
    analysisManager->CreateNtupleDColumn("Pz_gamma2");
    analysisManager->CreateNtupleDColumn("Ek_gamma2");
    analysisManager->CreateNtupleIColumn("photon3");//from Sigma
    analysisManager->CreateNtupleDColumn("x_gamma3");
    analysisManager->CreateNtupleDColumn("y_gamma3");
    analysisManager->CreateNtupleDColumn("z_gamma3");
    analysisManager->CreateNtupleDColumn("Px_gamma3");
    analysisManager->CreateNtupleDColumn("Py_gamma3");
    analysisManager->CreateNtupleDColumn("Pz_gamma3");
    analysisManager->CreateNtupleDColumn("Ek_gamma3");
    analysisManager->CreateNtupleIColumn("neutron");
    analysisManager->CreateNtupleDColumn("x_n");
    analysisManager->CreateNtupleDColumn("y_n");
    analysisManager->CreateNtupleDColumn("z_n");
    analysisManager->CreateNtupleDColumn("Px_n");
    analysisManager->CreateNtupleDColumn("Py_n");
    analysisManager->CreateNtupleDColumn("Pz_n");
    analysisManager->CreateNtupleDColumn("Ek_n");
    analysisManager->CreateNtupleDColumn("weight");
    //OTHER PARTICLES TO BE FILLED
    analysisManager->FinishNtuple();
    //analysisManager->SetNtupleFileName(0, "HitsNtuple");
}


void RunAction::BeginOfRunAction(const G4Run*)
{
  auto analysisManager = G4AnalysisManager::Instance();
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  analysisManager->OpenFile("MyOutput");

}


void RunAction::EndOfRunAction(const G4Run* run)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile(false);
  

  if (IsMaster()) {
    G4cout << G4endl << "--------------------End of Global Run-----------------------"<< G4endl;
  }
  else {
    G4cout << G4endl << "--------------------End of Local Run------------------------"<< G4endl;
  }

}


}  
