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
//
/// \file B1EventAction.hh
/// \brief Definition of the B1EventAction class

#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "B1Analysis.hh"

class B1RunAction;
class B1Analysis;

/// Event action class
///

class B1EventAction : public G4UserEventAction
{
  public:
    B1EventAction(B1RunAction* runAction, B1Analysis* myAna);
    virtual ~B1EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddAll(G4double x, G4double y, G4double z, G4double e, G4int n) {fposi[0]+=x; fposi[1]+=y; fposi[2]+=z; fedep+=e; fnstep+=n;};
    void AddBody(G4double x, G4double y, G4double z, G4double e, G4int n) {ftumorposi[0]+=x; ftumorposi[1]+=y; ftumorposi[2]+=z; ftumoredep+=e; ftumornstep+=n;};
    void AddTumor(G4double x, G4double y, G4double z, G4double e, G4int n) {fbodyposi[0]+=x; fbodyposi[1]+=y; fbodyposi[2]+=z; fbodyedep+=e; fbodynstep+=n;};
    void AddHead(G4double x, G4double y, G4double z, G4double e, G4int n) {fheadposi[0]+=x; fheadposi[1]+=y; fheadposi[2]+=z; fheadedep+=e; fheadnstep+=n;};

  private:
    B1RunAction* fRunAction;
    B1Analysis* fmyAna;
    G4int     fPrintModulo;
    
    G4double fposi[3];
    G4double fedep;
    G4int fnstep;

    G4double ftumorposi[3];
    G4double ftumoredep;
    G4int ftumornstep;

    G4double fbodyposi[3];
    G4double fbodyedep;
    G4int fbodynstep;

    G4double fheadposi[3];
    G4double fheadedep;
    G4int fheadnstep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
