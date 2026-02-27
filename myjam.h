//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 16 10:55:15 2025 by ROOT version 6.36.04
// from TTree tree/jam
// found on file: ./phase.root
//////////////////////////////////////////////////////////

#ifndef myjam_h
#define myjam_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class myjam {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           mul;
   Float_t         b;
   Int_t           Npart;
   vector<int>     *pid;
   vector<int>     *coll;
   vector<float>   *x;
   vector<float>   *y;
   vector<float>   *z;
   vector<float>   *t;
   vector<float>   *px;
   vector<float>   *py;
   vector<float>   *pz;
   vector<float>   *E;

   // List of branches
   TBranch        *b_mul;   //!
   TBranch        *b_b;   //!
   TBranch        *b_Npart;   //!
   TBranch        *b_pid;   //!
   TBranch        *b_coll;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_z;   //!
   TBranch        *b_t;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_E;   //!

   myjam(TTree *tree=0);
   virtual ~myjam();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual bool     Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef myjam_cxx
myjam::myjam(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("./phase.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("./phase.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

myjam::~myjam()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t myjam::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t myjam::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void myjam::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   pid = 0;
   coll = 0;
   x = 0;
   y = 0;
   z = 0;
   t = 0;
   px = 0;
   py = 0;
   pz = 0;
   E = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mul", &mul, &b_mul);
   fChain->SetBranchAddress("b", &b, &b_b);
   fChain->SetBranchAddress("Npart", &Npart, &b_Npart);
   fChain->SetBranchAddress("pid", &pid, &b_pid);
   fChain->SetBranchAddress("coll", &coll, &b_coll);
   fChain->SetBranchAddress("x", &x, &b_x);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("z", &z, &b_z);
   fChain->SetBranchAddress("t", &t, &b_t);
   fChain->SetBranchAddress("px", &px, &b_px);
   fChain->SetBranchAddress("py", &py, &b_py);
   fChain->SetBranchAddress("pz", &pz, &b_pz);
   fChain->SetBranchAddress("E", &E, &b_E);
   Notify();
}

bool myjam::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return true;
}

void myjam::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t myjam::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef myjam_cxx
