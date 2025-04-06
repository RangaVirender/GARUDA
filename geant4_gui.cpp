class MyMainFrame : public TGMainFrame
{
    private:
    TGTextButton  *source_sh_file_button; // Button for sourcing geant4.sh file to terminal
    TGTextButton  *check_geant4_button; // Button for checking geant4 installation
    TGButtonGroup *vis_mode_button_group;
    TGRadioButton *vis_mode_ON_button;
    TGRadioButton *vis_mode_OFF_button;
    TGComboBox    *select_det_mat_cbox; // List for selecting detector material
    TGComboBox    *select_det_shape_cbox; // List for selecting detector material
    TGNumberEntry *no_of_events_entry;
    TGNumberEntry *no_of_threads_entry;
    TGTextButton  *clear_build_button; // Button for cmake
    TGTextButton  *cmake_button; // Button for cmake
    TGTextButton  *make_button; // Button for make
    TGTextButton  *run_sim_button; // Button for running simulation
    TGTextButton  *stop_sim_button; // Button for running simulation
    TGTextButton  *plot_spec_button; // Button for running simulation
    TGTextButton  *exit_button;  // Button for exiting the application
    TGTextButton  *load_log_button;  // Button for loading log.txt
    TGTextButton  *load_instrxn_button;  // Button for loading instruction.txt
    TGTextView    *text_output;    // Text output field
    TGGroupFrame  *grid_frame_1; //grid 1 
    TGGroupFrame  *grid_frame_2; //grid 2 
    TGGroupFrame  *grid_frame_3; //grid 3 
    TGGroupFrame  *grid_frame_4; //grid 3 
    TString        source_file_path;
    TString        vis_mode_string;
    TString        det_mat_string;
    TString        det_shape_string;
    int            det_mat_int;
    int            det_shape_int;
    TGLabel       *label;
    int            no_of_events_int;
    TString        no_of_events_string;
    TString        no_of_threads_string;
    int            no_of_threads_int;
    int            no_of_cores_int;
    TString        no_of_cores_string;
    int            frame;

    public:
    MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h);
    virtual ~MyMainFrame();
    void source_sh_file_button_clicked(); // Action for "Click Me" button
    void geant4_button_clicked(); // Action for "Click Me" button
    void clear_build_button_clicked(); // Action for "Click Me" button
    void cmake_button_clicked(); // Action for "Click Me" button
    void make_button_clicked(); // Action for "Click Me" button
    void run_sim_button_clicked(); // Action for "Click Me" button
    void stop_sim_button_clicked(); // Action for "Click Me" button
    void plot_spec_button_clicked(); // Action for "Click Me" button
    void exit_button_clicked();  // Action for "Exit" button
    void load_instrxn_button_clicked();
    void load_log_button_clicked();
    void LoadFile(const char *filename);  // Function to load file into TGTextView
    void update_text_output();  // Function to update TGTextView in real time
    void UpdateAnimation();
    virtual void CloseWindow();  // Properly handle window close
    TString       pwd_path;
    
};


MyMainFrame::MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h) : TGMainFrame(p, w, h) 
{
    // kLHintsCenterX: Aligns the widget horizontally to the center of its parent frame.
    //5, 5, 5, 5: Margins around the button in the order—left, right, top, bottom (in pixels).

    
    //'this' Refers to the parent frame or window that the composite frame belongs to. 
    //It likely represents the current instance of the main frame or another GUI container.
    //70, 10: These are the width and height of the composite frame, in pixels.
    //kHorizontalFrame: A flag indicating how the frame organizes its child components. In this case, it arranges them horizontally.

    // Layout 3: Grid-like arrangement of buttons
    grid_frame_1 = new TGGroupFrame(this, "Useful Checks", kHorizontalFrame);
 
    // Create "source .sh file" button
    source_sh_file_button = new TGTextButton(grid_frame_1, "Source geant4.sh file");
    source_sh_file_button->Connect("Clicked()", "MyMainFrame", this, "source_sh_file_button_clicked()"); // Connect to click handler
    
    // Create "Check Geant4" button
    check_geant4_button = new TGTextButton(grid_frame_1, "Check Geant4");
    check_geant4_button->Connect("Clicked()", "MyMainFrame", this, "geant4_button_clicked()"); // Connect to click handler
    
     // Create "Load Instructions" button
    load_instrxn_button = new TGTextButton(grid_frame_1, "Load Instructions");
    load_instrxn_button->Connect("Clicked()", "MyMainFrame", this, "load_instrxn_button_clicked()"); // Connect to exit handler
    
    // Create "Load LOG file" button
    load_log_button = new TGTextButton(grid_frame_1, "Load LOG file");
    load_log_button->Connect("Clicked()", "MyMainFrame", this, "load_log_button_clicked()"); // Connect to exit handler
 
    grid_frame_1->AddFrame(source_sh_file_button, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 0));
    grid_frame_1->AddFrame(check_geant4_button, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 0));
    grid_frame_1->AddFrame(load_instrxn_button, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 0));
    grid_frame_1->AddFrame(load_log_button, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 0));
    AddFrame(grid_frame_1, new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));

    grid_frame_2 = new TGGroupFrame(this, "Simulation Parameters", kHorizontalFrame);
    
    // Create a button group
    vis_mode_button_group = new TGButtonGroup(grid_frame_2, "Visualisation Mode");
    // Add radio buttons to the group
    vis_mode_ON_button  = new TGRadioButton(vis_mode_button_group, "ON");
    vis_mode_OFF_button = new TGRadioButton(vis_mode_button_group, "OFF");
    vis_mode_ON_button->SetState(kButtonDown); // Marks it as selected

    // Create a combobox
    select_det_shape_cbox = new TGComboBox(grid_frame_2, -1);
    select_det_shape_cbox->AddEntry("Cylinder", 1);
    select_det_shape_cbox->AddEntry("Box", 2);
    select_det_shape_cbox->Select(1);
    select_det_shape_cbox->Resize(100, 25); // Resize the text entry field


    // Create a combobox
    select_det_mat_cbox = new TGComboBox(grid_frame_2, -1);//"Select Detector Material");
    select_det_mat_cbox->AddEntry("NaI:Tl", 1);
    select_det_mat_cbox->AddEntry("LaBr3:Ce", 2);
    select_det_mat_cbox->AddEntry("CeBr3", 3);
    select_det_mat_cbox->AddEntry("HPGe", 4);
    // Set default entry (e.g., "Option 2" with ID = 2)
    select_det_mat_cbox->Select(2);
    select_det_mat_cbox->Resize(100, 25); // Resize the text entry field

    // Create a text entry field
    no_of_threads_entry = new TGNumberEntry(grid_frame_2, 4, 2, -1, TGNumberFormat::kNESInteger);//default value, max digits, ID 
    // no_of_events_entry->SetText("10"); // Set default text
    
    no_of_cores_string = gSystem->GetFromPipe("grep '^core id' /proc/cpuinfo | sort -u | wc -l");
    cout << "No of cores in CPU: " << no_of_cores_string << endl;
    no_of_cores_int = no_of_cores_string.Atoi();
    no_of_threads_entry->SetLimits(TGNumberFormat::kNELLimitMinMax, 1, no_of_cores_int);
   
    no_of_events_entry = new TGNumberEntry(grid_frame_2, 1, 9, -1, TGNumberFormat::kNESInteger);//default value, max digits, ID 
    // no_of_events_entry->SetText("10"); // Set default text
    no_of_events_entry->SetLimits(TGNumberFormat::kNELLimitMinMax, 1, 1e8);
   
    grid_frame_2->AddFrame(vis_mode_button_group, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 0));
    grid_frame_2->AddFrame(no_of_threads_entry, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 0));
    grid_frame_2->AddFrame(no_of_events_entry, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 0));
    grid_frame_2->AddFrame(select_det_shape_cbox, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 0));
    grid_frame_2->AddFrame(select_det_mat_cbox, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 0));
    AddFrame(grid_frame_2, new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
    
    grid_frame_3 = new TGGroupFrame(this, "Primary functions", kHorizontalFrame);
    // Create clear build button
    clear_build_button = new TGTextButton(grid_frame_3, "Clear build folder");
    clear_build_button->Connect("Clicked()", "MyMainFrame", this, "clear_build_button_clicked()"); // Connect to click handler
    
    // Create cmake button
    cmake_button = new TGTextButton(grid_frame_3, "Run CMAKE");
    cmake_button->Connect("Clicked()", "MyMainFrame", this, "cmake_button_clicked()"); // Connect to click handler
    
    // Create make button
    make_button = new TGTextButton(grid_frame_3, "Run MAKE");
    make_button->Connect("Clicked()", "MyMainFrame", this, "make_button_clicked()"); // Connect to click handler
    
    // Create run simulation button
    run_sim_button = new TGTextButton(grid_frame_3, "Run Simulation");
    run_sim_button->Connect("Clicked()", "MyMainFrame", this, "run_sim_button_clicked()"); // Connect to click handler
    
    // Create stop simulation button
    stop_sim_button = new TGTextButton(grid_frame_3, "Stop Simulation");
    stop_sim_button->Connect("Clicked()", "MyMainFrame", this, "stop_sim_button_clicked()"); // Connect to click handler

    grid_frame_3->AddFrame(clear_build_button, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    grid_frame_3->AddFrame(cmake_button, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    grid_frame_3->AddFrame(make_button, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    grid_frame_3->AddFrame(run_sim_button, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    grid_frame_3->AddFrame(stop_sim_button, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    AddFrame(grid_frame_3, new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
 
    grid_frame_4 = new TGGroupFrame(this, "Primary functions", kHorizontalFrame);
    label = new TGLabel(grid_frame_4, "........................");
    // Set the text color to red
    label->SetTextColor(TColor::RGB2Pixel(255, 0, 0));

    // Create "Exit" button
    exit_button = new TGTextButton(grid_frame_4, "Exit");
    exit_button->Connect("Clicked()", "MyMainFrame", this, "exit_button_clicked()"); // Connect to exit handler
    
    plot_spec_button = new TGTextButton(grid_frame_4, "Plot spectrum");
    plot_spec_button->Connect("Clicked()", "MyMainFrame", this, "plot_spec_button_clicked()"); // Connect to exit handler
    

    grid_frame_4->AddFrame(label, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    grid_frame_4->AddFrame(plot_spec_button, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    grid_frame_4->AddFrame(exit_button, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    AddFrame(grid_frame_4, new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
    
       
    // Create text output field
    text_output = new TGTextView(this, 600, 300); // 200x100 pixels size
    AddFrame(text_output, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 10, 10, 0, 10));

    // Set up the main frame
    SetWindowName("CERN-ROOT based GUI for Geant4 by V. Ranga (2025)");
    MapSubwindows();
    Resize(GetDefaultSize());  // Automatically fit all widgets
    MapWindow();
}

MyMainFrame::~MyMainFrame() {
    // Cleanup dynamically allocated objects
    RemoveFrame(clear_build_button);    delete clear_build_button;
    RemoveFrame(cmake_button);          delete cmake_button;
    RemoveFrame(make_button);           delete make_button;
    RemoveFrame(run_sim_button);        delete run_sim_button;
    RemoveFrame(stop_sim_button);       delete stop_sim_button;
    RemoveFrame(exit_button);           delete exit_button;
    RemoveFrame(load_instrxn_button);   delete load_instrxn_button;
    RemoveFrame(load_log_button);       delete load_log_button;
    RemoveFrame(text_output);           delete text_output;
    
    Cleanup();
}

// Function to update TGTextView in real time
void MyMainFrame::update_text_output()
{
    text_output->Update();  // Force immediate UI refresh
    gSystem->ProcessEvents(); // Process pending UI events
}


// Function to load a file into TGTextView
void MyMainFrame::LoadFile(const char *filename)
{
    text_output->Clear();
    std::ifstream file(filename);
    if (!file) 
    {
       text_output->AddLine("Error: Unable to open file!");
       return;
    }

    std::string line;
    while (std::getline(file, line)) 
    {
       text_output->AddLine(line.c_str());
    }
    file.close();
}


void MyMainFrame::load_instrxn_button_clicked()
{   
    TString instrxn_file_path = pwd_path+"/instructions.txt"; 
    LoadFile(instrxn_file_path);
}

void MyMainFrame:: load_log_button_clicked()
{
    TString log_file_path = pwd_path+"/log.txt"; 
    LoadFile(log_file_path);
    text_output->ShowBottom(); // Scroll to the last line
}

void MyMainFrame:: source_sh_file_button_clicked()
{
    text_output->AddLine("Select .sh file from /geant4_install_folder/bin/ directory"); // Add exit message
    // File types for filtering (e.g., All files or specific types like .txt)
   const char *fileTypes[] = {".sh files", "*.sh",
                               0, 0};

   // Create a file info object
   TGFileInfo fileInfo;
   fileInfo.fFileTypes = fileTypes;

   // Open file dialog
   new TGFileDialog(gClient->GetRoot(), gClient->GetRoot(), kFDOpen, &fileInfo);

   // Print selected file path
   if (fileInfo.fFilename)
    {
      source_file_path = string(fileInfo.fFilename);
      TString print_source_file_path = "Selected file: "+ source_file_path; 
      text_output->AddLine(print_source_file_path); update_text_output();
      TString source_file_command = "bash -c 'source "+source_file_path+"; env > temp_env.txt'";
      gSystem->Exec(source_file_command);
    } 
    else
    {
      cout<<"No file selected." << endl;
    }

// steps to make persistent geant4 env in root
// source geant4.sh
//dump env to a file
//read file and set root env
// now the env is set in the terminal itself. it will be set even if you quit root. need to restart terminal to unset the env

ifstream envFile("temp_env.txt");
std::string line;

while (getline(envFile, line)) 
{
    auto pos = line.find('=');
    if (pos != std::string::npos)
    {
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
       // Check if the key or value concerns Geant4
       // if (key.find("LD_LIBRARY_PATH") != std::string::npos || value.find("geant4") != std::string::npos)
        {
            gSystem->Setenv(key.c_str(), value.c_str());
        }
    }
}
envFile.close();


}
void MyMainFrame::geant4_button_clicked()
{   
   
    text_output->AddLine("Finding Geant4..."); update_text_output();
    TString geant4_config_command_1 = "geant4-config --version  > log.txt 2>&1";
    int geant4_status = gSystem->Exec(geant4_config_command_1);
    
    if(geant4_status != 0)
     {
       text_output->AddLine("Cannot find Geant4. Please source geant4.sh"); update_text_output();
        return;
     }
     else 
     {
        TString geant4_config_command_2 = "geant4-config --version";   
        TString geant4_version = gSystem->GetFromPipe(geant4_config_command_2);
        TString print_geant4_version_command = "Found Geant4 version " + geant4_version + " Click on Run CMAKE to proceed.";
        text_output->AddLine(print_geant4_version_command); update_text_output();
     }    
}

void MyMainFrame::clear_build_button_clicked()
{             
    text_output->AddLine("Clearing contents of the build folder for a clean start."); update_text_output();
    
    TString clear_build_command = "bash -c 'cd "+pwd_path+"/geant4/build && rm -rf * >> ../../log.txt 2>&1'";   
    
    int clear_build_status = gSystem->Exec(clear_build_command);// > to rewrite log file
    if(clear_build_status != 0)
     {
       text_output->AddLine("Error: Clear failed. Build folder may be already empty. Check log.txt. Run CMAKE"); update_text_output();
       return;
     }
     else 
     {
       text_output->AddLine("Build folder cleared successfully. Click on Run CMAKE to proceed."); update_text_output();
     }     
}

void MyMainFrame::cmake_button_clicked()
{             
    label->SetText("Working...");

    text_output->AddLine("Running CMAKE..."); update_text_output();
    
    TString cmake_command = "bash -c 'cd "+pwd_path+"/geant4/build && cmake ../source'";   
    
    int cmake_status = gSystem->Exec(cmake_command);// > to rewrite log file
    if(cmake_status != 0)
     {
       text_output->AddLine("Error: CMAKE failed. Check log.txt"); update_text_output();
       label->SetText("");
        return;
     }
     else 
     {
       text_output->AddLine("CMAKE completed successfully. Click on Run MAKE to proceed."); update_text_output();
     }
    label->SetText("");
    
     
}


//2>&1 is a shell redirection operator. It redirects stderr (error output, file descriptor 2) to
//stdout (standard output, file descriptor 1) so that both standard output and error messages appear in the same stream.
        
void MyMainFrame::make_button_clicked()
{  
    label->SetText("Working...");
   text_output->AddLine("Running MAKE using 4 cores..."); update_text_output();
    
    TString make_command = "bash -c 'cd "+pwd_path+"/geant4/build && make -j4'";   
    
    int make_status = gSystem->Exec(make_command);// >> append to log file
    if(make_status != 0)
     {
        text_output->AddLine("Error: MAKE failed. Check log.txt"); update_text_output();
        label->SetText("");
        return;
     }
     else 
     {
       text_output->AddLine("MAKE completed successfully. Click on Run Simulation to proceed."); update_text_output();
     }
     label->SetText("");
}


void MyMainFrame::run_sim_button_clicked()
{  
  //  make_button->SetEnabled(kFALSE);
  // cmake_button->SetEnabled(kFALSE);
   
   gSystem->Exec("bash -c 'cd "+pwd_path+"/geant4/build && rm -rf *.root '");

   label->SetText("Working...");
   text_output->AddLine("Started..."); update_text_output();
   //text_output->AddLine("Grabbing executable file..."); update_text_output();
   
   // Execute the shell command and store output
   //TString get_exe_name_command = "grep -m 1 'Built target' " + pwd_path + "/log.txt  | awk '{print $4}'";
   
   //TString exec_name = gSystem->GetFromPipe("grep 'Built target' log.txt | awk '{print $4}'");
   //TString exec_name = gSystem->GetFromPipe(get_exe_name_command);
   //if(exec_name == "")
  // {
  //   text_output->AddLine("Couldnt find executable. Run MAKE."); update_text_output();
  //   label->SetText("");        
  //   return;
  // }
   // Print the extracted executable name
   // Construct a shell command using the extracted executable name
  // TString print_exe_name_command = "Ecexutable file name is: " + exec_name;
  // text_output->AddLine(print_exe_name_command); update_text_output();
   
   //TString exec_name = "sim";

   no_of_events_int = no_of_events_entry->GetNumber();
   no_of_events_string = to_string(no_of_events_int);
   TString print_no_of_events_command = "No of events: " + no_of_events_string;
   text_output->AddLine(print_no_of_events_command); update_text_output();
   
   if(no_of_events_int > 100)
   {
        std::cout << "No of events " << no_of_events_int << " is more than 100" <<std::endl;
        std::cout << "Turning visualisation OFF..." <<std::endl;
        vis_mode_OFF_button->SetState(kButtonDown); // Marks it as selected
        vis_mode_ON_button->SetState(kButtonUp); // Marks it as unselected
   }
   
    if(vis_mode_ON_button->GetState() == kButtonDown) //kButtonDown means button is pressed
       {
           std::cout << "vis_mode_on" << std::endl;
           vis_mode_string = " vis_mode_on ";
       }
    else if(vis_mode_OFF_button->GetState() == kButtonDown)
            {
                std::cout << "vis_mode_off" << std::endl;
                vis_mode_string = " vis_mode_off ";
            }

   det_shape_int = select_det_shape_cbox->GetSelected();
   
   switch(det_shape_int)
   {
   case 1: std::cout<<"case 1:"<<std::endl; det_shape_string = " cylinder ";      break;
   case 2: std::cout<<"case 2:"<<std::endl; det_shape_string = " box "; break;
   }

   std::cout << "Det mat int: " << det_mat_int << std::endl;
   
   det_mat_int = select_det_mat_cbox->GetSelected();
   
   switch(det_mat_int)
   {
   case 1: std::cout<<"case 1:"<<std::endl; det_mat_string = " NaI"; break;
   case 2: std::cout<<"case 2:"<<std::endl; det_mat_string = " LaBr3"; break;
   case 3: std::cout<<"case 3:"<<std::endl; det_mat_string = " CeBr3"; break;
   case 4: std::cout<<"case 4:"<<std::endl; det_mat_string = " HPGe"; break;
   }

   std::cout << "Det mat int: " << det_mat_int << std::endl;


   no_of_threads_int = no_of_threads_entry->GetNumber();
   no_of_threads_string = to_string(no_of_threads_int);
   cout << "\033[1;31m No of threads used of simulations: \033[0m" << no_of_threads_int << endl;
   text_output->AddLine("Running simulation..."); update_text_output();     
   
   // Construct a shell command using the extracted executable name
   TString exe_command = "bash -c 'cd "+pwd_path+"/geant4/build && ./sim " + vis_mode_string
                                                                           + no_of_threads_string + " "
                                                                           + no_of_events_string
                                                                           + det_shape_string
                                                                           + det_mat_string
                                                                           //+ " 2>&1 >> ../../log.txt
                                                                           + " ' ";
                                                                           //+ " ' & ";
   
   cout << "exe_command: " << exe_command << endl;
   
   // Execute the command
   int sim_status = gSystem->Exec(exe_command);
   
   // Check execution result
   cout << "Execution returned: " << sim_status << endl;
   
  // cout << "Merging ROOT files " << endl;
  // gSystem->Exec("bash -c 'cd "+pwd_path+"/geant4/build && hadd -f output.root output_t*.root' ");
   // -f flag to overwrite the merged output file
  // cout << "ROOT files merged to output.root" << endl;

   if (sim_status != 0)
    {
       text_output->AddLine("Error: Simulation failed. Check log.txt"); update_text_output();
       TString exe_command_2 = "bash -c 'cd "+pwd_path+"/geant4/build && ./sim 2>&1'";
       
       TString sim_output = gSystem->GetFromPipe(exe_command_2);
       // Convert TString to std::string
          std::string sim_output_cpp = std::string(sim_output.Data());

       cout << "Execution error returned: " << sim_output << endl;
        // String to search for
        std::string search_string = "error while loading shared libraries:";

    // Check if the string exists in the output
    if (sim_output_cpp.find(search_string) != std::string::npos) {
        std::cout << "Source geant4.sh" << std::endl;
        text_output->AddLine("Couldnt find GEANT4. Source geant4.sh"); update_text_output();
        
        label->SetText("");
        return;
        
    } else {
        std::cout << "Check log.txt" << std::endl;
    }
       label->SetText("");
       return;
    }
    text_output->AddLine("Run successful"); update_text_output();
    label->SetText("");

  //  make_button->SetEnabled(kTRUE);
  // cmake_button->SetEnabled(kTRUE);
   return;
}

void MyMainFrame::plot_spec_button_clicked()
{
    cout << "Merging ROOT files " << endl;
   gSystem->Exec("bash -c 'cd "+pwd_path+"/geant4/build && hadd -f output.root output_t*.root' ");
   // -f flag to overwrite the merged output file
   cout << "ROOT files merged to output.root" << endl;

   TFile* f1 = new TFile("geant4/build/output.root","READ");
   TCanvas* c1 = new TCanvas("c1");    
   TTree* t1 = (TTree*)f1->Get("Scoring");
   TH1D* h1 = new TH1D("h1", "", 3000, 0.01, 3.01);
   t1->Draw("fEdep>>h1","","");
   gPad->SetLogy(); 
   return;
}

void MyMainFrame::stop_sim_button_clicked()
{
   gSystem->Exec("pkill -f ./sim");
   std::cout << "Simulation stopped...\n";
   return;
}

void MyMainFrame::exit_button_clicked()
{
    text_output->AddLine("Exiting application..."); // Add exit message
    gApplication->Terminate(0); // Gracefully exit the application
}

// Properly handle window close
void MyMainFrame::CloseWindow() {
    std::cout << "Closing application...\n";
    gApplication->Terminate(0);  // Stops the ROOT event loop
}

int geant4_gui() 
{
    TApplication app("ROOT Application", 0, nullptr);
    //0: Represents the argc parameter (argument count). Since no command-line arguments are being passed, this value is set to 0.
    //nullptr: Represents the argv parameter (argument vector). Since there are no command-line arguments, it is set to nullptr (null pointer).
    MyMainFrame *mainFrame = new MyMainFrame(gClient->GetRoot(), 700, 700); // Specifies the width and height of the MyMainFrame window in pixels.
    mainFrame->pwd_path = gSystem->pwd();
    gSystem->Exec(" > log.txt");
    app.Run();

    // Delete main frame after application ends
    delete mainFrame;
    return 0;
}
