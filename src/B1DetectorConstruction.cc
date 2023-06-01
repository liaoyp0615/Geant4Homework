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
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Orb.hh"
#include "G4EllipticalTube.hh"
#include "G4Box.hh"
#include "G4Ellipsoid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction() : G4VUserDetectorConstruction(), fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
	// Get nist material manager
	G4NistManager* nist = G4NistManager::Instance();

	// Envelope parameters
	G4double env_sizeXY = 300*cm, env_sizeZ = 300*cm; // 4m * 4m * 4m
	G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");

	// Option to switch on/off checking of volumes overlaps
	G4bool checkOverlaps = true;


	//     
	// World
	//
	G4double world_sizeXY = 1.2*env_sizeXY;
	G4double world_sizeZ  = 1.2*env_sizeZ;
	G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

	G4Box* solidWorld =    
				new G4Box("World",			//its name
						0.5*world_sizeXY,	//its x-size
						0.5*world_sizeXY, 	//its y-size
						0.5*world_sizeZ);	//its z-size

	G4LogicalVolume* logicWorld =                         
				new G4LogicalVolume(solidWorld,	//its solid
									world_mat,	//its material
									"World");	//its name

	G4VPhysicalVolume* physWorld = 
				new G4PVPlacement(0,		// no rotation
						G4ThreeVector(),	// at (0,0,0)
						logicWorld,			// its logical volume
						"World",			// its name
						0,					// its mother volume
						false,				// no boolean operation
						0,					// copy number
						checkOverlaps);		// overlaps checking

	//     
	// Envelope
	//  
	G4Box* solidEnv =
				new G4Box("Envelope",	//its name
						0.5*env_sizeXY,
						0.5*env_sizeXY,
						0.5*env_sizeZ); //its size

	G4LogicalVolume* logicEnv =
				new G4LogicalVolume(solidEnv,            //its solid
									env_mat,             //its material
									"Envelope");         //its name
				new G4PVPlacement(0,                     //no rotation
								G4ThreeVector(),         //at (0,0,0)
								logicEnv,                //its logical volume
								"Envelope",              //its name
								logicWorld,              //its mother  volume
								false,                   //no boolean operation
								0,                       //copy number
								checkOverlaps);          //overlaps checking

	//
	// head shape
	// 
	G4Material* shape_head = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
	G4ThreeVector pos_head = G4ThreeVector(0*cm, 0*cm, 42*cm);
	
	G4double headShape_Rmax = 9.*cm;
	G4Orb* solidShape_head = new G4Orb("headShape", headShape_Rmax);
	G4LogicalVolume* logicShape_head =
				new G4LogicalVolume(solidShape_head,      // its solid
									shape_head,           // its material
									"headShape");         // its name
				new G4PVPlacement(0,                      // no rotation
								pos_head,                 // at position
								logicShape_head,          // its logical volume
								"headShape",              // its name
								logicEnv,                 // its mother  volume
								false,                    // no boolean operation
								0,                        // copy number
								checkOverlaps);           // overlaps checking

	//
	// neck
	//
	G4Material* shape_neck = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
	G4ThreeVector pos_neck = G4ThreeVector(0*cm, 0*cm, 29.5*cm);

	G4double neckShape_xSemiAxis = 5*cm; 
	G4double neckShape_ySemiAxis = 5*cm;
	G4double neckShape_Dz = 4.5*cm;
	G4EllipticalTube* solidShape_neck = new G4EllipticalTube("neckShape", neckShape_xSemiAxis, neckShape_ySemiAxis, neckShape_Dz);
	G4LogicalVolume* logicShape_neck =
				new G4LogicalVolume(solidShape_neck,      // its solid
									shape_neck,           // its material
									"neckShape");         // its name
				new G4PVPlacement(0,                      // no rotation
								pos_neck,                 // at position
								logicShape_neck,          // its logical volume
								"neckShape",              // its name
								logicEnv,                 // its mother  volume
								false,                    // no boolean operation
								0,                        // copy number
								checkOverlaps);           // overlaps checking

	//
	// body
	//
	G4Material* shape_body = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
	G4ThreeVector pos_body = G4ThreeVector(0*cm, 0*cm, 0*cm);

	G4double bodyShape_x = 13*cm; 
	G4double bodyShape_y = 6*cm;
	G4double bodyShape_z = 25*cm;
	G4Box* solidShape_body = new G4Box("bodyShape", bodyShape_x, bodyShape_y, bodyShape_z);
	G4LogicalVolume* logicShape_body =
				new G4LogicalVolume(solidShape_body,      // its solid
									shape_body,           // its material
									"bodyShape");         // its name
				new G4PVPlacement(0,                      // no rotation
								pos_body,                 // at position
								logicShape_body,          // its logical volume
								"bodyShape",              // its name
								logicEnv,                 // its mother  volume
								false,                    // no boolean operation
								0,                        // copy number
								checkOverlaps);           // overlaps checking

	//
	// leg1
	//
	G4Material* shape_leg1 = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
	G4ThreeVector pos_leg1 = G4ThreeVector(7*cm, 0*cm, -66*cm);

	G4double leg1Shape_xSemiAxis = 5.5*cm; 
	G4double leg1Shape_ySemiAxis = 5.5*cm;
	G4double leg1Shape_Dz = 41*cm;
	G4EllipticalTube* solidShape_leg1 = new G4EllipticalTube("leg1Shape", leg1Shape_xSemiAxis, leg1Shape_ySemiAxis, leg1Shape_Dz);
	G4LogicalVolume* logicShape_leg1 =
				new G4LogicalVolume(solidShape_leg1,      // its solid
									shape_leg1,           // its material
									"leg1Shape");         // its name
				new G4PVPlacement(0,                      // no rotation
								pos_leg1,                 // at position
								logicShape_leg1,          // its logical volume
								"leg1Shape",              // its name
								logicEnv,                 // its mother  volume
								false,                    // no boolean operation
								0,                        // copy number
								checkOverlaps);           // overlaps checking

	//
	// leg2
	//
	G4Material* shape_leg2 = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
	G4ThreeVector pos_leg2 = G4ThreeVector(-7*cm, 0*cm, -66*cm);

	G4double leg2Shape_xSemiAxis = 5.5*cm; 
	G4double leg2Shape_ySemiAxis = 5.5*cm;
	G4double leg2Shape_Dz = 41*cm;
	G4EllipticalTube* solidShape_leg2 = new G4EllipticalTube("leg2Shape", leg2Shape_xSemiAxis, leg2Shape_ySemiAxis, leg2Shape_Dz);
	G4LogicalVolume* logicShape_leg2 =
				new G4LogicalVolume(solidShape_leg2,      // its solid
									shape_leg2,           // its material
									"leg2Shape");         // its name
				new G4PVPlacement(0,                      // no rotation
								pos_leg2,                 // at position
								logicShape_leg2,          // its logical volume
								"leg2Shape",              // its name
								logicEnv,                 // its mother  volume
								false,                    // no boolean operation
								0,                        // copy number
								checkOverlaps);           // overlaps checking

	//
	// Tumor
	//
	G4Material* shape_tumor = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
	G4ThreeVector pos_tumor = G4ThreeVector(-8*cm, 0*cm, 0*cm);

	G4double tumorShape_xSemiAxis = 2*cm; 
	G4double tumorShape_ySemiAxis = 1*cm;
	G4double tumorShape_zSemiAxis = 3*cm;
	G4double tumorShape_zBottomCut = 0*cm;
	G4double tumorShape_zTopCut = 0*cm;
	G4Ellipsoid* solidShape_tumor = new G4Ellipsoid("tumorShape", 
				tumorShape_xSemiAxis, tumorShape_ySemiAxis, tumorShape_zSemiAxis, tumorShape_zBottomCut, tumorShape_zTopCut);
	G4LogicalVolume* logicShape_tumor =
				new G4LogicalVolume(solidShape_tumor,      // its solid
									shape_tumor,           // its material
									"tumorShape");         // its name
				new G4PVPlacement(0,                      // no rotation
								pos_tumor,                 // at position
								logicShape_tumor,          // its logical volume
								"tumorShape",              // its name
								logicEnv,                 // its mother  volume
								false,                    // no boolean operation
								0,                        // copy number
								checkOverlaps);           // overlaps checking


	// color
	G4VisAttributes* headVis = new G4VisAttributes(G4Colour(1.,1.,0.,0.9));
	logicShape_head->SetVisAttributes(headVis);
	G4VisAttributes* neckVis = new G4VisAttributes(G4Colour(1.,0.,1.,0.9));
	logicShape_neck->SetVisAttributes(neckVis);
	G4VisAttributes* bodyVis = new G4VisAttributes(G4Colour(0.,1.,0.,0.2));
	logicShape_body->SetVisAttributes(bodyVis);
	G4VisAttributes* legVis = new G4VisAttributes(G4Colour(0.,0.,1.,0.9));
	logicShape_leg1->SetVisAttributes(legVis);
	logicShape_leg2->SetVisAttributes(legVis);
	G4VisAttributes* tumorVis = new G4VisAttributes(G4Colour(1.,0.,0.,0.9));
	logicShape_tumor->SetVisAttributes(tumorVis);

	
	// Set logicShape_tumor as scoring volume
	fScoringVolume = logicShape_tumor;

	//
	//always return the physical World
	//
	return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
