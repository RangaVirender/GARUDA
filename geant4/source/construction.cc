
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

#include "construction.hh"
#include "detector.hh"
#include "vGlobalVariables.hh"

//global variables
//G4double detDiameter;
G4double detDiameterCm;
G4double detLength;
G4double detHalfLengthZ;
G4double detPositionZ;
G4double detDistance;

MyDetectorConstruction::MyDetectorConstruction()
{
    DefineMaterials();

    xWorld = 1.0*m;
    yWorld = 1.0*m;
    zWorld = 1.0*m;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    
    Na = nist->FindOrBuildElement("Na");
    I = nist->FindOrBuildElement("I");
    NaI_mat = new G4Material("NaI_mat", 3.67*g/cm3, 2);
    NaI_mat->AddElement(Na, 1);
    NaI_mat->AddElement(I, 1);
    
    La = nist->FindOrBuildElement("La");
    Br = nist->FindOrBuildElement("Br");
    LaBr3_mat = new G4Material("LaBr3_mat", 5.06*g/cm3, 2);
    LaBr3_mat->AddElement(La, 1);
    LaBr3_mat->AddElement(Br, 3);
    
    Ce = nist->FindOrBuildElement("Ce");
    CeBr3_mat = new G4Material("CeBr3_mat", 5.1*g/cm3, 2);
    CeBr3_mat->AddElement(Ce, 1);
    CeBr3_mat->AddElement(Br, 3);
    
    Ge = nist->FindOrBuildElement("Ge");
    HPGe_mat = new G4Material("HPGe_mat", 5.323*g/cm3, 1);
    HPGe_mat->AddElement(Ce, 1);
    
    Al = nist->FindOrBuildElement("Al");
    AlMat = new G4Material("AlMat", 2.7 * g/cm3, 1);
    AlMat->AddElement(Al, 1);


    //------------------------Steel-------------------------------------------
    Fe = nist->FindOrBuildElement("Fe");
    Cr = nist->FindOrBuildElement("Cr");
    Ni = nist->FindOrBuildElement("Ni");
    steel = new G4Material("steel", 7.9*g/cm3, 3);
    // 304SS almost no carbon
    steel->AddElement(Fe, 70.*perCent);
    steel->AddElement(Cr, 20.*perCent);
    steel->AddElement(Ni, 10.*perCent);

}


G4LogicalVolume *MyDetectorConstruction::CreateLogicalVolume(G4VSolid* solid,
                                                             const G4String& materialName,
                                                             const G4String& volumeName)
{
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* material = nullptr;

    // Handle material selection
    if (materialName == "LaBr3") {material = LaBr3_mat;}
    else if (materialName == "NaI")   {material = NaI_mat;}
    else if (materialName == "CeBr3") {material = CeBr3_mat;}
    else if (materialName == "HPGe")  {material = HPGe_mat;}
    // Create and return the logical volume
    return new G4LogicalVolume(solid, material, volumeName);
    
}
G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);

    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    //solidDetector = new G4Box("solidDetector", 2*cm, 2*cm, 2*cm);
    
    //Dimensions  
    
    //detDiameter = 3.5;//inches
    detLength = 6.0;//inches 
    G4double AlThickness = 0.08;//cm
    G4double AlGap = 0.8;//cm //gap between Aliminium and crystal
    detDistance = 20.0;//cm //distance between det surface and source
    G4double AlPositionZ = detDistance + AlThickness/2.0 ;

    // Create a tubular shape (G4Tubs)
    
    G4double detInnerRadius = 0.; // Inner radius
    G4double detOuterRadius =  detDiameter*(0.5*2.54); // cm // Outer radius in inches
    detHalfLengthZ =  detLength*(0.5*2.54); // cm // Half-length along Z-axis
    G4double detStartPhi = 0.; // Starting angle (in radians)
    G4double detDeltaPhi = 2. * M_PI; // Delta angle (full circle)

   // solidDetector = new G4Tubs("solidDetector", detInnerRadius*cm, detOuterRadius*cm, detHalfLengthZ*cm, detStartPhi, detDeltaPhi);



    // Define a box solid
     boxSolid = new G4Box("BoxSolid", 10 * cm, 10 * cm, 10 * cm);
     boxLogic = MyDetectorConstruction::CreateLogicalVolume(boxSolid, detector_material, "BoxVolume");
    //logicDetector = new G4LogicalVolume(solidDetector, LaBr3, "logicDetector");
    

    //fScoringVolume = logicDetector;
    
    detPositionZ =  AlPositionZ + AlThickness/2.0 + AlGap + detHalfLengthZ ;

    physDetector = new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, detPositionZ*cm), boxLogic, "physDetector", logicWorld, false, 0, true);

    //create Aluminium surface
    G4double AlInnerRadius = detInnerRadius; // Inner radius
    G4double AlOuterRadius = detOuterRadius; // Outer radius in inches
    G4double AlHalfLengthZ = AlThickness*0.5; // cm // Half-length along Z-axis
    G4double AlStartPhi = 0.; // Starting angle (in radians)
    G4double AlDeltaPhi = 2. * M_PI; // Delta angle (full circle)

   // solidAl = new G4Tubs("solidAl", AlInnerRadius*cm, AlOuterRadius*cm, AlHalfLengthZ*cm, AlStartPhi, AlDeltaPhi );

   // logicAl = new G4LogicalVolume(solidAl, AlMat, "logicAl");

    //physAl = new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, AlPositionZ*cm ), logicAl, "physAl", logicWorld, false, 0, true);
     
   //Steel chamber wall

    G4double steelChamberInnerRadius = 0.0; // Inner radius
    G4double steelChamberOuterRadius = 10.0; // Outer radius in cm
    G4double steelChamberHalfLengthZ = 0.3/2.0; // cm // Half-length along Z-axis
    G4double steelChamberStartPhi = 0.; // Starting angle (in radians)
    G4double steelChamberDeltaPhi = 2.0*M_PI; // Delta angle (full circle)
    G4double steelChamberPositionZ = 2.5 ; //cm
   // solidSteelChamber = new G4Tubs("solidSteelChamber", steelChamberInnerRadius*cm, steelChamberOuterRadius*cm,
     //                               steelChamberHalfLengthZ*cm, steelChamberStartPhi, steelChamberDeltaPhi );

   // logicSteelChamber = new G4LogicalVolume(solidSteelChamber, steel, "logicSteelChamber");

   // physSteelChamber = new G4PVPlacement(0, G4ThreeVector(0.*m, 0.*m, steelChamberPositionZ*cm ), logicSteelChamber,
              //                            "physSteelChamber", logicWorld, false, 0, true);
     
    detDiameterCm = detDiameter*2.54;
    G4double solidAngle = 2.0*M_PI*( 1.0 - detDistance/sqrt(pow(detDistance,2.0) + pow(detDiameterCm/2.0,2.0))) ;

    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    if(boxLogic != NULL)
        boxLogic->SetSensitiveDetector(sensDet);
}
