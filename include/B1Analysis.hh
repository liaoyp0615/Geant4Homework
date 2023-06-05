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
/// \file B1Analysis.hh
/// \brief Definition of the B1Analysis class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef B1Analysis_h
#define B1Analysis_h 1

#include "globals.hh"
#include "TFile.h"
#include "TTree.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class B1Analysis
{
  public:
    B1Analysis();
   ~B1Analysis();
   
    void Book();
    void Save();
    void Fill(G4double x, G4double y, G4double z, G4double e,
              G4double tx, G4double ty, G4double tz, G4double te,
              G4double bx, G4double by, G4double bz, G4double be,
              G4double hx, G4double hy, G4double hz, G4double he);
        
  private:
    TFile*   fRootFile;
    TTree*   fNtuple1;

    G4double fx, fy, fz, fe;
    G4double ftx, fty, ftz, fte;
    G4double fbx, fby, fbz, fbe;
    G4double fhx, fhy, fhz, fhe;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

