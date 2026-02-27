#define myjam_cxx
#include "myjam.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
#include <TLorentzVector.h>

void myjam::Loop()
{
//   In a ROOT session, you can do:
//      root> .L myjam.C
//      root> myjam t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   ofstream Lambda("pKLambda.txt", ios::app|ios::out);
   if (!Lambda.is_open()) {
       std::cerr << "Error opening file for writing" << std::endl;
       return;
   }
   ofstream Sigma("pKSigma.txt", ios::app|ios::out);
   if (!Sigma.is_open()) {
       std::cerr << "Error opening file for writing" << std::endl;
       return;
   }

   TFile *f_out_Lambda = new TFile("pKLambda.root","RECREATE");
  TTree *tLambda = new TTree("pKLambda","p K Lambda four-momenta");
  TFile *f_out_Sigma  = new TFile("pKSigma.root","RECREATE");
  TTree *tSigma  = new TTree("pKSigma","p K Sigma four-momenta");

 // 分支变量（float）
  float L_p1_px=0, L_p1_py=0, L_p1_pz=0, L_p1_E=0;
  float L_p2_px=0, L_p2_py=0, L_p2_pz=0, L_p2_E=0;
  float L_p3_px=0, L_p3_py=0, L_p3_pz=0, L_p3_E=0;
  tLambda->Branch("p1_px",&L_p1_px,"p1_px/F");
  tLambda->Branch("p1_py",&L_p1_py,"p1_py/F");
  tLambda->Branch("p1_pz",&L_p1_pz,"p1_pz/F");
  tLambda->Branch("p1_E",&L_p1_E,"p1_E/F");
  tLambda->Branch("p2_px",&L_p2_px,"p2_px/F");
  tLambda->Branch("p2_py",&L_p2_py,"p2_py/F");
  tLambda->Branch("p2_pz",&L_p2_pz,"p2_pz/F");
  tLambda->Branch("p2_E",&L_p2_E,"p2_E/F");
  tLambda->Branch("p3_px",&L_p3_px,"p3_px/F");
  tLambda->Branch("p3_py",&L_p3_py,"p3_py/F");
  tLambda->Branch("p3_pz",&L_p3_pz,"p3_pz/F");
  tLambda->Branch("p3_E",&L_p3_E,"p3_E/F");

  float S_p1_px=0, S_p1_py=0, S_p1_pz=0, S_p1_E=0;
  float S_p2_px=0, S_p2_py=0, S_p2_pz=0, S_p2_E=0;
  float S_p3_px=0, S_p3_py=0, S_p3_pz=0, S_p3_E=0;
  tSigma->Branch("p1_px",&S_p1_px,"p1_px/F");
  tSigma->Branch("p1_py",&S_p1_py,"p1_py/F");
  tSigma->Branch("p1_pz",&S_p1_pz,"p1_pz/F");
  tSigma->Branch("p1_E",&S_p1_E,"p1_E/F");
  tSigma->Branch("p2_px",&S_p2_px,"p2_px/F");
  tSigma->Branch("p2_py",&S_p2_py,"p2_py/F");
  tSigma->Branch("p2_pz",&S_p2_pz,"p2_pz/F");
  tSigma->Branch("p2_E",&S_p2_E,"p2_E/F");
  tSigma->Branch("p3_px",&S_p3_px,"p3_px/F");
  tSigma->Branch("p3_py",&S_p3_py,"p3_py/F");
  tSigma->Branch("p3_pz",&S_p3_pz,"p3_pz/F");
  tSigma->Branch("p3_E",&S_p3_E,"p3_E/F");

   if (fChain == 0) return;

   double bz = ; // Beta for 10 GeV proton beam

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   Long64_t n_Cascade0 = 0;

   TH1F *h_Cascade0 = new TH1F("h_Cascade0", "Number of Cascade0 per event", 20, 0, 20);

   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      if(jentry% 200000 == 0 && jentry != 0)
      {
         std::cout << jentry << " out of " << nentries << " events processed." << std::endl;
      }
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      if(mul == 3)
      {
         bool has_Lambda = false;
         bool has_Sigma = false;
         bool has_Omega = false;
         bool has_proton = false;
         bool has_kaon = false;
         bool has_Cascade = false;

         TLorentzVector p1, p2, p3;
         for(size_t i = 0; i < pid->size(); i++)
         {
            if(pid->at(i) == 3122) // Lambda
            {
               has_Lambda = true;
            }
            if(pid->at(i) == 3212) // Sigma
            {
               has_Sigma = true;
            }
            if(pid->at(i) == 2114) // Omega
            {
               has_Omega = true;
            }
            if(pid->at(i) == 2212) // Proton
            {
               has_proton = true;
            }
            if(pid->at(i) == 321) // Kaon
            {
               has_kaon = true;
            }
            if(pid->at(i) == 3322) // Cascade
            {
               has_Cascade = true;
            }
         }
         
         if(has_proton && has_kaon && has_Lambda)
         {
            for(int i=0; i<pid->size(); i++)
            {
               if(pid->at(i) == 2212) // Proton
               {
                  p1.SetPxPyPzE(px->at(i), py->at(i), pz->at(i), E->at(i));
                  p1.Boost(0,0,bz);
               }
               if(pid->at(i) == 321) // Kaon
               {
                  p2.SetPxPyPzE(px->at(i), py->at(i), pz->at(i), E->at(i));
                p2.Boost(0,0,bz);
               }
               if(pid->at(i) == 3122) // Lambda
               {
                  p3.SetPxPyPzE(px->at(i), py->at(i), pz->at(i), E->at(i));
                  p3.Boost(0,0,bz);
               }
               
            }
            Lambda << p1.Px() << "\t" << p1.Py() << "\t" << p1.Pz() << "\t" << p1.E() << "\t"
                      << p2.Px() << "\t" << p2.Py() << "\t" << p2.Pz() << "\t" << p2.E() << "\t"
                        << p3.Px() << "\t" << p3.Py() << "\t" << p3.Pz() << "\t" << p3.E() << "\t" << "1" << endl;
            L_p1_px = p1.Px(); L_p1_py = p1.Py(); L_p1_pz = p1.Pz(); L_p1_E = p1.E();
           L_p2_px = p2.Px(); L_p2_py = p2.Py(); L_p2_pz = p2.Pz(); L_p2_E = p2.E();
           L_p3_px = p3.Px(); L_p3_py = p3.Py(); L_p3_pz = p3.Pz(); L_p3_E = p3.E();
           tLambda->Fill();
                     }

         if(has_proton && has_kaon && has_Sigma)
         {
            for(int i=0; i<pid->size(); i++)
            {
               if(pid->at(i) == 2212) // Proton
               {
                  p1.SetPxPyPzE(px->at(i), py->at(i), pz->at(i), E->at(i));
                  p1.Boost(0,0,bz);
               }
               if(pid->at(i) == 321) // Kaon
               {
                  p2.SetPxPyPzE(px->at(i), py->at(i), pz->at(i), E->at(i));
                  p2.Boost(0,0,bz);
               }
               if(pid->at(i) == 3212) // Sigma
               {
                  p3.SetPxPyPzE(px->at(i), py->at(i), pz->at(i), E->at(i));
                  p3.Boost(0,0,bz);
               }
               
            }
            Sigma << p1.Px() << "\t" << p1.Py() << "\t" << p1.Pz() << "\t" << p1.E() << "\t"
                     << p2.Px() << "\t" << p2.Py() << "\t" << p2.Pz() << "\t" << p2.E() << "\t"
                     << p3.Px() << "\t" << p3.Py() << "\t" << p3.Pz() << "\t" << p3.E() << "\t" << "1" << endl;
                     S_p1_px = p1.Px(); S_p1_py = p1.Py(); S_p1_pz = p1.Pz(); S_p1_E = p1.E();
           S_p2_px = p2.Px(); S_p2_py = p2.Py(); S_p2_pz = p2.Pz(); S_p2_E = p2.E();
           S_p3_px = p3.Px(); S_p3_py = p3.Py(); S_p3_pz = p3.Pz(); S_p3_E = p3.E();
           tSigma->Fill();
         }
   }

      /*
         for(size_t i = 0; i < mul; i++)
         {
            if(pid->at(i) == 3322) // Cascade0
            {
               n_Cascade0++;
               h_Cascade0->Fill(mul);
            }
         }
      */
      
   }

   
   Lambda.close();
   Sigma.close();

   f_out_Lambda->cd();
  tLambda->Write();
  f_out_Lambda->Close();
  delete f_out_Lambda;

  f_out_Sigma->cd();
  tSigma->Write();
  f_out_Sigma->Close();
  delete f_out_Sigma;

  /*
  TFile f_cascade("Cascade0_histogram.root","RECREATE");
  f_cascade.cd();
  h_Cascade0->Write();
  f_cascade.Close();
  delete h_Cascade0;

   std::cout << "Total number of events with Cascade0: " << n_Cascade0 << std::endl;*/
}
