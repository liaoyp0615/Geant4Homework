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
/// \file B1EventAction.cc
/// \brief Implementation of the B1EventAction class

#include "B1EventAction.hh"
#include "B1RunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::B1EventAction(B1RunAction* runAction, B1Analysis* myAna)
: G4UserEventAction(),
  fRunAction(runAction), fmyAna(myAna)
{
  fPrintModulo = 2000;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::~B1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::BeginOfEventAction(const G4Event* evt)
{
  G4int evtNb = evt->GetEventID();
  if (evtNb%fPrintModulo == 0) 
    G4cout << "\n---> Begin of event: " << evtNb << G4endl;

  // initialisation per event
  fposi[0] = fposi[1] = fposi[2] = fedep = fw = 0.;
  ftumorposi[0] = ftumorposi[1] = ftumorposi[2] = ftumoredep = ftumorw = 0.;
  fbodyposi[0] = fbodyposi[1] = fbodyposi[2] = fbodyedep = fbodyw = 0.;
  fheadposi[0] = fheadposi[1] = fheadposi[2] = fheadedep = fheadw = 0.;
  fnstep = ftumornstep = fbodynstep = fheadnstep = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event*)
{
  // accumulate statistics in run action
  fRunAction->AddAllEdep(fw);
  fRunAction->AddTumorEdep(ftumorw);
  fRunAction->AddBodyEdep(fbodyw);
  fRunAction->AddHeadEdep(fheadw);

  // average position
  for(int i=0; i<3; i++) {
    fposi[i] /= fnstep;
    ftumorposi[i] /= ftumornstep;
    fbodyposi[i] /= fbodynstep;
    fheadposi[i] /= fheadnstep;
  }

  // fill average position & total deposit energy
  fmyAna->Fill( fposi[0], fposi[1], fposi[2], fedep, fw,
                ftumorposi[0], ftumorposi[1], ftumorposi[2], ftumoredep, ftumorw,
                fbodyposi[0], fbodyposi[1], fbodyposi[2], fbodyedep, fbodyw,
                fheadposi[0], fheadposi[1], fheadposi[2], fheadedep, fheadw);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::AddAll(G4double x, G4double y, G4double z, G4double e, G4double w)
{
  fposi[0]+=x; 
  fposi[1]+=y; 
  fposi[2]+=z; 
  fedep+=e;
  fw+=e*w;
  fnstep+=1;
};

void B1EventAction::AddTumor(G4double x, G4double y, G4double z, G4double e, G4double w)
{
  ftumorposi[0]+=x;
  ftumorposi[1]+=y;
  ftumorposi[2]+=z;
  ftumoredep+=e;
  ftumorw+=e*w;
  ftumornstep+=1;
};

void B1EventAction::AddBody(G4double x, G4double y, G4double z, G4double e, G4double w)
{
  fbodyposi[0]+=x;
  fbodyposi[1]+=y;
  fbodyposi[2]+=z;
  fbodyedep+=e;
  fbodyw+=e*w;
  fbodynstep+=1;
};

void B1EventAction::AddHead(G4double x, G4double y, G4double z, G4double e, G4double w)
{
  fheadposi[0]+=x;
  fheadposi[1]+=y;
  fheadposi[2]+=z;
  fheadedep+=e;
  fheadw+=e*w;
  fheadnstep+=1;
};