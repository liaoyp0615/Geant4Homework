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
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fBodyVolume(0),
  fTumorVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  bool debug = true;

  if (!fBodyVolume || !fTumorVolume) { 
    const B1DetectorConstruction* detectorConstruction = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fBodyVolume = detectorConstruction->GetBodyVolume();
    fTumorVolume = detectorConstruction->GetTumorVolume();   
  }

  // get volume of the current step
  G4VPhysicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  G4double stepLength=aStep->GetStepLength();
  if(stepLength==0) G4cout<<"step length equal 0!!"<<G4endl;

  // track and edep
  G4Track* gTrack = aStep->GetTrack();
  G4int pdg_code = gTrack->GetDefinition()->GetPDGEncoding();
  G4int charge = gTrack->GetDefinition()->GetPDGCharge();
  G4double edep = aStep->GetTotalEnergyDeposit();

  // pre point
  G4StepPoint* prePoint  = aStep->GetPreStepPoint();
  G4ThreeVector p3_pre  = prePoint->GetMomentum();
  G4ThreeVector pointIn = prePoint->GetPosition();

  // post point
  G4StepPoint* postPoint = aStep->GetPostStepPoint();
  G4ThreeVector p3_post = postPoint->GetMomentum();
  G4ThreeVector pointOut = postPoint->GetPosition();

  //======================= Test ===========================
  if(debug) {
    G4cout << "PDGid:" << pdg_code << " , charge:" << charge << " , edep: " << edep*MeV << " MeV" << G4endl;
    G4cout << " prepoint->  pos(cm): (" <<pointIn.x()*cm<<","<<pointIn.y()*cm<<","<<pointIn.z()*cm
                   <<")  mom(MeV): (" <<p3_pre.x()*MeV<<","<<p3_pre.y()*MeV<<","<<p3_pre.z()*MeV << G4endl;
    G4cout << " postpoint->  pos(cm): (" <<pointOut.x()*cm<<","<<pointOut.y()*cm<<","<<pointOut.z()*cm
                   <<")  mom(MeV): (" <<p3_post.x()*MeV<<","<<p3_post.y()*MeV<<","<<p3_post.z()*MeV << G4endl;
  }
  
  G4double x = pointIn.x()*cm;
  G4double y = pointIn.y()*cm;
  G4double z = pointIn.z()*cm;
  G4double e = edep*MeV;

  if (volume == fBodyVolume)  fEventAction->AddBody(x,y,z,e,1);
  if (volume == fTumorVolume) fEventAction->AddTumor(x,y,z,e,1);
  if (volume == fBodyVolume || volume == fTumorVolume) fEventAction->AddAll(x,y,z,e,1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

