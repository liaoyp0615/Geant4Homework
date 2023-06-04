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
/// \file B1RunAction.cc
/// \brief Implementation of the B1RunAction class

#include "B1RunAction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <TMath.h>
using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::B1RunAction(B1Analysis* myAna)
: G4UserRunAction(), fmyAna(myAna),
  fAllEdep(0.), fAllEdep2(0.),
  fTumorEdep(0.), fTumorEdep2(0.),
  fBodyEdep(0.), fBodyEdep2(0.),
  fHeadEdep(0.), fHeadEdep2(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::~B1RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::BeginOfRunAction(const G4Run*)
{
  const G4double milligray = 1.e-3*gray;
  const G4double microgray = 1.e-6*gray;
  const G4double nanogray  = 1.e-9*gray;  
  const G4double picogray  = 1.e-12*gray; 
  new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
  new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
  new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
  new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray); 

  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fAllEdep);
  accumulableManager->RegisterAccumulable(fAllEdep2); 
  accumulableManager->RegisterAccumulable(fTumorEdep);
  accumulableManager->RegisterAccumulable(fTumorEdep2); 
  accumulableManager->RegisterAccumulable(fBodyEdep);
  accumulableManager->RegisterAccumulable(fBodyEdep2); 
  accumulableManager->RegisterAccumulable(fHeadEdep);
  accumulableManager->RegisterAccumulable(fHeadEdep2); 

  // book the histogram to be saved
  fmyAna->Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Compute dose = total energy deposit in a run and its variance
  G4double Alledep  = fAllEdep.GetValue();
  G4double Alledep2 = fAllEdep2.GetValue();
  G4double Allrms = Alledep2 - Alledep*Alledep/nofEvents;
  if (Allrms > 0.) Allrms = TMath::Sqrt(Allrms); else Allrms = 0.;

  G4double Tumoredep  = fTumorEdep.GetValue();
  G4double Tumoredep2 = fTumorEdep2.GetValue();
  G4double Tumorrms = Tumoredep2 - Tumoredep*Tumoredep/nofEvents;
  if (Tumorrms > 0.) Tumorrms = TMath::Sqrt(Tumorrms); else Tumorrms = 0.;

  G4double Bodyedep  = fBodyEdep.GetValue();
  G4double Bodyedep2 = fBodyEdep2.GetValue();
  G4double Bodyrms = Bodyedep2 - Bodyedep*Bodyedep/nofEvents;
  if (Bodyrms > 0.) Bodyrms = TMath::Sqrt(Bodyrms); else Bodyrms = 0.;

  G4double Headedep  = fHeadEdep.GetValue();
  G4double Headedep2 = fHeadEdep2.GetValue();
  G4double Headrms = Headedep2 - Headedep*Headedep/nofEvents;
  if (Headrms > 0.) Headrms = TMath::Sqrt(Headrms); else Headrms = 0.;

  const B1DetectorConstruction* detectorConstruction = static_cast<const B1DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4double Tumor_mass = detectorConstruction->GetTumorLogicVolume()->GetMass();
  G4double Body_mass = detectorConstruction->GetBodyLogicVolume()->GetMass();
  G4double Head_mass = detectorConstruction->GetHeadLogicVolume()->GetMass();
  G4double All_mass = Tumor_mass + Body_mass + Head_mass;

  G4double Alldose = Alledep / All_mass;
  G4double AllrmsDose = Allrms / All_mass;
  G4double Tumordose = Tumoredep / Tumor_mass;
  G4double TumorrmsDose = Tumorrms / Tumor_mass;
  G4double Bodydose = Bodyedep / Body_mass;
  G4double BodyrmsDose = Bodyrms / Body_mass;
  G4double Headdose = Headedep / Head_mass;
  G4double HeadrmsDose = Headrms / Head_mass;


  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const B1PrimaryGeneratorAction* generatorAction
   = static_cast<const B1PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy,"Energy");
  }
        
  // Print
  if (!IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------" << G4endl
     << " The run consists of " << nofEvents << " "<< runCondition << G4endl
     << " Cumulated dose per run, in Tumor volume : " 
     << G4BestUnit(Tumordose,"Dose") << " rms = " << G4BestUnit(TumorrmsDose,"Dose") << G4endl
     << " Cumulated dose per run, in Body volume : " 
     << G4BestUnit(Bodydose,"Dose") << " rms = " << G4BestUnit(BodyrmsDose,"Dose") << G4endl
     << " Cumulated dose per run, in Head volume : " 
     << G4BestUnit(Headdose,"Dose") << " rms = " << G4BestUnit(HeadrmsDose,"Dose") << G4endl
     << " Cumulated dose per run, in All (Tumor+Body+Head) volume : " 
     << G4BestUnit(Alldose,"Dose") << " rms = " << G4BestUnit(AllrmsDose,"Dose") << G4endl
     << "TumorEdep = " << Tumoredep << G4endl
	 << "BodyEdep = " << Bodyedep << G4endl
	 << "AllEdep = " << Alledep << G4endl
	 << "--------------------------------`----------------------------"
     << G4endl << G4endl;
  }
  // else {
  //   G4cout
  //    << G4endl
  //    << "--------------------End of Local Run------------------------";
  // }


  // write & close tree
  fmyAna->Save();


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void B1RunAction::AddAllEdep (G4double edep)
{
  fAllEdep  += edep;
  fAllEdep2 += edep*edep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void B1RunAction::AddTumorEdep (G4double edep)
{
  fTumorEdep  += edep;
  fTumorEdep2 += edep*edep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void B1RunAction::AddBodyEdep (G4double edep)
{
  fBodyEdep  += edep;
  fBodyEdep2 += edep*edep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void B1RunAction::AddHeadEdep (G4double edep)
{
  fHeadEdep  += edep;
  fHeadEdep2 += edep*edep;
}
