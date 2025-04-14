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

#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

    virtual G4VPhysicalVolume *Construct();
    void ConstructCherenkov();
    void ConstructScintillator();
    void ConstructTOF();
    void ConstructAtmosphere();

private:
    G4Box  *solidWorld, *boxSolid, *box_det_solid;  
    G4Tubs *solidDetector, *solidAl, *solidSteelChamber, *cylinder_det_solid;
    G4LogicalVolume *logicWorld,  *logicDetector, *logicAl, *logicSteelChamber , *boxLogic, *box_det_logic, *cylinder_det_logic;
    G4VPhysicalVolume *physWorld, *physDetector, *physAl, *physSteelChamber, *box_det_phys, *cylinder_det_phys ;

    //G4OpticalSurface *mirrorSurface;

    G4Material  *worldMat, *NaI_mat , *LaBr3_mat, *CeBr3_mat, *AlMat, *steel, *HPGe_mat;
    G4Element  *Na, *I, *Al,*Fe, *Cr, *Ni, *La, *Br, *Ce, *Ge;

    void DefineMaterials();
    virtual G4LogicalVolume *CreateLogicalVolume(G4VSolid* solid, const G4String& materialName, const G4String& volumeName);
    virtual void ConstructSDandField();

    G4GenericMessenger *fMessenger;

    G4LogicalVolume *fScoringVolume;

    G4double xWorld, yWorld, zWorld;

   
};

#endif
