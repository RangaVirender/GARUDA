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

#include "event.hh"
#include "vGlobalVariables.hh"
std::chrono::system_clock::time_point startTimeSys, endTimeSys;
std::time_t startTime,endTime;

MyEventAction::MyEventAction(MyRunAction*)
{
    fEdep = 0.;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event* anEvent)
{
    fEdep = 0.;
    G4int  eventID = anEvent->GetEventID();
    if(eventID == 0 )
    {
        startTimeSys = std::chrono::system_clock::now(); // Capture start time
        startTime = std::chrono::system_clock::to_time_t(startTimeSys);
       // G4cout<< "Event Start Time: " <<std::ctime(&startTime) << G4endl;
    }
    
    
}

void MyEventAction::EndOfEventAction(const G4Event* anEvent)
{
    //G4cout << "Energy deposition: " << fEdep << G4endl;

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleDColumn(0, 0, fEdep);
    man->AddNtupleRow(0);

    G4int  eventID = anEvent->GetEventID();
    
    G4int update_after_events = std::round(noOfEvents_int/100.0);
    
    if(noOfEvents_int >=51 && eventID % update_after_events == 0 )
    {
        //G4cout<< "--- End of event --- : " << eventID <<" \r";
        endTimeSys = std::chrono::system_clock::now(); // Capture end time
        std::chrono::duration<double> elapsed_seconds = endTimeSys - startTimeSys;
       // G4cout<< "Time taken: " << elapsed_seconds.count() << G4endl;
        G4double timePerEvent = elapsed_seconds.count()/eventID;
        G4cout<< "EventID: "<<eventID<<
                 " Elapsed: "<< elapsed_seconds.count()<< 
                 "sec Remaining: " << (noOfEvents_int - eventID)*timePerEvent <<
                 "sec Events/sec: "<< eventID/elapsed_seconds.count() <<" \r";
        G4cout.flush();
    }

 

}
