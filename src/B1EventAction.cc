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
  fPrintModulo = 100;
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
  fposi[0] = fposi[1] = fposi[2] = fedep = 0.;
  ftumorposi[0] = ftumorposi[1] = ftumorposi[2] = ftumoredep = 0.;
  fbodyposi[0] = fbodyposi[1] = fbodyposi[2] = fbodyedep = 0.;
  fnstep = ftumornstep = fbodynstep = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event*)
{
  // accumulate statistics in run action
  fRunAction->AddAllEdep(fedep);
  fRunAction->AddTumorEdep(ftumoredep);
  fRunAction->AddBodyEdep(fbodyedep);

  // average position
  for(int i=0; i<3; i++) fposi[i] /= fnstep;
  for(int i=0; i<3; i++) ftumorposi[i] /= ftumornstep;
  for(int i=0; i<3; i++) fbodyposi[i] /= fbodynstep;

  // fill average position & total deposit energy
  fmyAna->Fill( fposi[0], fposi[1], fposi[2], fedep,
                ftumorposi[0], ftumorposi[1], ftumorposi[2], ftumoredep,
                fbodyposi[0], fbodyposi[1], fbodyposi[2], fbodyedep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
