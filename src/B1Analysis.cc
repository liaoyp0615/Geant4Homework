//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file B1Analysis.cc
/// \brief Implementation of the B1Analysis class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TFile.h"
#include "TTree.h"
#include "CLHEP/Units/SystemOfUnits.h"

#include "B1Analysis.hh"
#include "G4UnitsTable.hh"
using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1Analysis::B1Analysis()
:fRootFile(0), fNtuple1(0)
{  
  // ntuple
  fNtuple1 = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1Analysis::~B1Analysis()
{
  if (fRootFile) delete fRootFile;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1Analysis::Book()
{ 
  // Creating a tree container to handle histograms and ntuples.
  // This tree is associated to an output file.
  //
  G4String fileName = "output.root";
  fRootFile = new TFile(fileName,"RECREATE");
  if (! fRootFile) {
    G4cout << " B1Analysis::Book : problem creating the ROOT TFile " << G4endl;
    return;
  }

  // create 1st ntuple
  fNtuple1 = new TTree("hits", "hits");
  fNtuple1->Branch("x", &fx);
  fNtuple1->Branch("y", &fy);
  fNtuple1->Branch("z", &fz);
  fNtuple1->Branch("e", &fe);
  fNtuple1->Branch("tx", &ftx);
  fNtuple1->Branch("ty", &fty);
  fNtuple1->Branch("tz", &ftz);
  fNtuple1->Branch("te", &fte);
  fNtuple1->Branch("bx", &fbx);
  fNtuple1->Branch("by", &fby);
  fNtuple1->Branch("bz", &fbz);
  fNtuple1->Branch("be", &fbe);
  fNtuple1->Branch("hx", &fhx);
  fNtuple1->Branch("hy", &fhy);
  fNtuple1->Branch("hz", &fhz);
  fNtuple1->Branch("he", &fhe);
 
  G4cout << "\n----> Output file is open in " << fileName << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1Analysis::Save()
{ 
  if (! fRootFile) return;
  fRootFile->Write();       // Writing the histograms to the file
  fRootFile->Close();       // and closing the tree (and the file)
  G4cout << "\n----> ntuples are saved\n" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1Analysis::Fill(G4double x, G4double y, G4double z, G4double e,
                      G4double tx, G4double ty, G4double tz, G4double te,
                      G4double bx, G4double by, G4double bz, G4double be,
                      G4double hx, G4double hy, G4double hz, G4double he)
{
  fx=x; fy=y; fz=z; fe=e;
  ftx=tx; fty=ty; ftz=tz; fte=te;
  fbx=bx; fby=by; fbz=bz; fbe=be;
  fhx=hx; fhy=hy; fhz=hz; fhe=he;

  if (fNtuple1) fNtuple1->Fill();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
