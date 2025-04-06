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


#include "run.hh"
#include "vGlobalVariables.hh"

MyRunAction::MyRunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->CreateNtuple("Scoring", "Scoring");
    man->CreateNtupleDColumn("fEdep");
    man->FinishNtuple(0);

    man->CreateNtuple("simulationInfo", "simulationInfo");
    man->CreateNtupleIColumn("fnoOfEvents");//column 0
    man->CreateNtupleDColumn("fdetDistance");//column 1
    man->CreateNtupleDColumn("fdetHalfLengthZ");//column 2
    man->CreateNtupleDColumn("fdetDiameterCm");//column 3
    man->CreateNtupleDColumn("fparticleEnergy");//column 4
    man->FinishNtuple(1);


}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();

    std::stringstream strRunID, strNoOfEvents, strParticleEnergy, strDetDistance, strRootFileName;
    strRunID << runID;
    strNoOfEvents << noOfEvents_int; 
    strParticleEnergy << particleEnergy;
    strDetDistance << detDistance;
  //  
//    strRootFileName << "output" + strRunID.str() +"_" + strNoOfEvents.str()+"events_"+ strParticleEnergy.str()+"MeV_"
  //                              + strDetDistance.str()+"cm.root";

    //man->OpenFile("output"+strRunID.str()+"_"+strNoOfEvents.str()+"events_"+strParticleEnergy.str()+"MeV_"+strDetDistance.str()+"cm.root");
  //   man->OpenFile(strRootFileName.str());
       man->OpenFile("output.root");
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    man->FillNtupleIColumn(1, 0, noOfEvents_int); // fill no 3 tuple in the 0th column with integer noOfEvents
    man->FillNtupleDColumn(1, 1, detDistance);
    man->FillNtupleDColumn(1, 2, detHalfLengthZ);
    man->FillNtupleDColumn(1, 3, detDiameterCm);
    man->FillNtupleDColumn(1, 4, particleEnergy);
    man->AddNtupleRow(1);
    
    man->Write();
    man->CloseFile();

   // G4cout << "EndOfRunAction" << G4endl;
}
