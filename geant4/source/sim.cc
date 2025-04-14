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


#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "vGlobalVariables.hh"
//Global variables
G4int noOfEvents_int;
G4String noOfEvents_string;
G4String visualisation_flag;
G4double particleEnergy;
G4double detDiameter;
G4String detector_material;
G4String det_shape;
G4String solid_volume;
G4String no_of_threads_string;
G4String rad_source_string;
G4String det_length_string;
G4String al_thickness_string;
G4String al_gap_string;

G4String det_inner_radius_string;
G4String det_outer_radius_string;
G4String det_source_dis_string;

G4double det_inner_radius_double;
G4double det_outer_radius_double;
G4double det_length_double;
G4double det_source_dis_double;
G4double al_thickness_double;
G4double al_gap_double;


int main(int argc, char** argv) //number of arguments including ./sim, argument array
{    
    
    //    ./sim vis    1    10000 shape LaBr3  
    //argv  0    1     2     3     4      5
    
      visualisation_flag = argv[1];  // vis for visualisation no_vis for no visualisation
    no_of_threads_string = argv[2];
       noOfEvents_string = argv[3];  //convert string to integer
          noOfEvents_int = stoi(noOfEvents_string);  //convert string to integer
       rad_source_string = argv[4];
               det_shape = argv[5];
 det_inner_radius_string = argv[6];
 det_outer_radius_string = argv[7];
   det_source_dis_string = argv[8];
       det_length_string = argv[9];
     al_thickness_string = argv[10];  
           al_gap_string = argv[11];  
       detector_material = argv[12];
     
     //converts every number to mm
      det_inner_radius_double = std::stod(det_inner_radius_string)*cm ; // cm means the number is entered in cm, it is *10 to convert to mm
      det_outer_radius_double = std::stod(det_outer_radius_string)*cm ;
            det_length_double = std::stod(det_length_string)*cm ;
          al_thickness_double = std::stod(al_thickness_string)*mm ; // mm means number is laready in mm, so no conversion mm=1
                al_gap_double = std::stod(al_gap_string)*mm ;
        det_source_dis_double = std::stod(det_source_dis_string)*cm ;
      


    G4UIExecutive* ui = 0;

    #ifdef G4MULTITHREADED
      G4MTRunManager* runManager = new G4MTRunManager;
    #else
      G4RunManager* runManager = new G4RunManager;
    #endif
    
    runManager->SetVerboseLevel(0);
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());

   
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize(); // to show the actual visualisation graphics
    
    G4UImanager *UImanager = G4UImanager::GetUIpointer(); //to apply commands   
    //universal commands
        
    #ifdef G4MULTITHREADED
        G4String set_no_of_threads_command = "/run/numberOfThreads ";
        UImanager->ApplyCommand(set_no_of_threads_command+no_of_threads_string);
      //  UImanager->ApplyCommand("/run/numberOfThreads 1");//before initialisation
    #endif
        
    if (visualisation_flag == "vis_mode_on")
    {   
        
        ui = new G4UIExecutive(argc, argv);//for extra UI with visualisation graphics
        //UImanager->ApplyCommand("/control/execute vis.mac");
        UImanager->ApplyCommand("/run/initialize");
        UImanager->ApplyCommand("/vis/open OGL");
        UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
        UImanager->ApplyCommand("/vis/drawVolume");
        UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
        UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByCharge");
        UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
        UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
        UImanager->ApplyCommand("/vis/scene/add/scale 10 cm");
        UImanager->ApplyCommand("/vis/scene/add/axes");
        //UImanager->ApplyCommand("/vis/viewer/set/style surface");//sets globally for all volumes
        UImanager->ApplyCommand("/vis/geometry/set/forceWireframe logicWorld 1");//set mother volume to wireframe
        UImanager->ApplyCommand("/vis/geometry/set/forceSolid cylinder_det_logic 1");//set mother volume to wireframe
        UImanager->ApplyCommand("/vis/geometry/set/forceSolid box_det_logic 1");//set mother volume to wireframe
        UImanager->ApplyCommand("/vis/geometry/set/colour cylinder_det_logic 0 1 0 0");// 0 R G B
        UImanager->ApplyCommand("/vis/geometry/set/colour box_det_logic 0 1 0 0");// 0 R G B
        UImanager->ApplyCommand("/vis/viewer/zoom 5");
        UImanager->ApplyCommand("/vis/scene/add/eventID");        
    }
    else if(visualisation_flag == "vis_mode_off")
    {
        UImanager->ApplyCommand("/run/initialize");
    }

        UImanager->ApplyCommand("/gps/particle ion");
        UImanager->ApplyCommand("/process/had/rdm/thresholdForVeryLongDecayTime 100 year");
      
      if(rad_source_string == "Cs137") { UImanager->ApplyCommand("/gps/ion 55 137");}// #for Cs137 662
      if(rad_source_string == "Co60") { UImanager->ApplyCommand("/gps/ion 27 60");}// #for Co60 1173 1332 2505
      if(rad_source_string == "Na22") { UImanager->ApplyCommand("/gps/ion 11 22");}// #for Na22 511 1274 1785
      if(rad_source_string == "Ba133") { UImanager->ApplyCommand("/gps/ion 56 133");}// 
        
        UImanager->ApplyCommand("#/gps/ion 41 94");// #for Nb94 703 871 1574
        UImanager->ApplyCommand("#/gps/ion 11 24");// #for Na24 1368 2754 4122
        UImanager->ApplyCommand("#/gps/ion 21 46");// #for Sc46 889 1120 2009
        UImanager->ApplyCommand("/gps/energy 0 keV");// #kinetic energy of ion
        UImanager->ApplyCommand("/gps/pos/type Point");
        G4String det_source_dis_command = "/gps/pos/centre 0. 0. " + to_string(-1.0*det_source_dis_double) + " mm";
        //UImanager->ApplyCommand("/gps/pos/centre 0. 0. 0. mm"); 
        UImanager->ApplyCommand(det_source_dis_command); 
        UImanager->ApplyCommand("/gps/ang/type iso");
        
     /*   
        if(noOfEvents_int > 50)
        {
        G4double print_prog_no_double = noOfEvents_int/50;
        int print_prog_no_int = std::round(print_prog_no_double); // Rounds to the nearest integer
        G4String print_prog_no_string = to_string(print_prog_no_int);
        G4String print_prog_no_command = "/run/printProgress ";
        UImanager->ApplyCommand(print_prog_no_command+print_prog_no_string);    
        }
       */ 
        G4String run_beam_on_command = "/run/beamOn ";
  G4cout << "Now beam on with total events: " << noOfEvents_int << G4endl;
    
        UImanager->ApplyCommand(run_beam_on_command + noOfEvents_string );

if (visualisation_flag == "vis_mode_on")
{   
        ui->SessionStart();
        delete ui;
}

  G4cout << "Now deleting: vismanager" << G4endl;
  delete visManager;
  delete runManager;
    return 0;
}
