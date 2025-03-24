class MyMainFrame : public TGMainFrame {
private:
    TGTextButton *check_geant4_button; // Button for cmake
    TGTextButton *cmakeButton; // Button for cmake
    TGTextButton *makeButton; // Button for make
    TGTextButton *runSimButton; // Button for running simulation
    TGTextButton *exitButton;  // Button for exiting the application
    TGTextButton *loadLogButton;  // Button for exiting the application
    TGTextButton *loadInstrxnButton;  // Button for exiting the application
    TGTextView   *textOutput;    // Text output field
    TGLabel      *labelDisplay;  // Label to display text
    TGGroupFrame *grid_frame_1;
    TGGroupFrame *grid_frame_2;
    TGHorizontal3DLine *h_line_1;
    TGHorizontal3DLine *h_line_2;

public:
    MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h);
    virtual ~MyMainFrame();
    void geant4_button_clicked(); // Action for "Click Me" button
    void cmakeButton_clicked(); // Action for "Click Me" button
    void makeButton_clicked(); // Action for "Click Me" button
    void runSimButton_clicked(); // Action for "Click Me" button
    void exitButton_clicked();  // Action for "Exit" button
    void loadInstrxnButton_clicked();
    void loadLogButton_clicked();
    void LoadFile(const char *filename);  // Function to load file into TGTextView
    void updateOutField();  // Function to update TGTextView in real time
    virtual void CloseWindow();  // Properly handle window close
};

MyMainFrame::MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h) : TGMainFrame(p, w, h) 
{
    //Create label display
   // labelDisplay = new TGLabel(this, "Welcome to CERN-ROOT based Geant4 GUI by V. Ranga (2025)");
    //AddFrame(labelDisplay,new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    
    // Add a horizontal line
    //h_line_1 = new TGHorizontal3DLine(this, 400);
    //AddFrame(h_line_1, new TGLayoutHints(kLHintsExpandX | kLHintsCenterX, 10, 10, 5, 5));
    // kLHintsCenterX: Aligns the widget horizontally to the center of its parent frame.
    //5, 5, 5, 5: Margins around the button in the order—left, right, top, bottom (in pixels).

    // Layout 3: Grid-like arrangement of buttons
    grid_frame_1 = new TGGroupFrame(this, "Useful Checks", kHorizontalFrame);
    //'this' Refers to the parent frame or window that the composite frame belongs to. 
    //It likely represents the current instance of the main frame or another GUI container.
    //70, 10: These are the width and height of the composite frame, in pixels.
    //kHorizontalFrame: A flag indicating how the frame organizes its child components. In this case, it arranges them horizontally.

    // Create "Check Geant4" button
    check_geant4_button = new TGTextButton(grid_frame_1, "Check Geant4");
    check_geant4_button->Connect("Clicked()", "MyMainFrame", this, "geant4_button_clicked()"); // Connect to click handler
    
     // Create "Load Instructions" button
    loadInstrxnButton = new TGTextButton(grid_frame_1, "Load Instructions");
    loadInstrxnButton->Connect("Clicked()", "MyMainFrame", this, "loadInstrxnButton_clicked()"); // Connect to exit handler
    
    // Create "Load LOG file" button
    loadLogButton = new TGTextButton(grid_frame_1, "Load LOG file");
    loadLogButton->Connect("Clicked()", "MyMainFrame", this, "loadLogButton_clicked()"); // Connect to exit handler
 
    grid_frame_1->AddFrame(check_geant4_button, new TGLayoutHints(kLHintsCenterX));
    grid_frame_1->AddFrame(loadInstrxnButton, new TGLayoutHints(kLHintsCenterX));
    grid_frame_1->AddFrame(loadLogButton, new TGLayoutHints(kLHintsCenterX));
    AddFrame(grid_frame_1, new TGLayoutHints(kLHintsExpandX));

    // Add a horizontal line
    //h_line_2 = new TGHorizontal3DLine(this, 400);
    //AddFrame(h_line_2, new TGLayoutHints(kLHintsExpandX | kLHintsCenterX, 10, 10, 5, 5));
    

    grid_frame_2 = new TGGroupFrame(this, "Primary functions", kHorizontalFrame);

    // Create cmake button
    cmakeButton = new TGTextButton(grid_frame_2, "Run CMAKE");
    cmakeButton->Connect("Clicked()", "MyMainFrame", this, "cmakeButton_clicked()"); // Connect to click handler
    
    // Create make button
    makeButton = new TGTextButton(grid_frame_2, "Run MAKE");
    makeButton->Connect("Clicked()", "MyMainFrame", this, "makeButton_clicked()"); // Connect to click handler
 
    // Create run simulation button
    runSimButton = new TGTextButton(grid_frame_2, "Run Simulation");
    runSimButton->Connect("Clicked()", "MyMainFrame", this, "runSimButton_clicked()"); // Connect to click handler
    
    grid_frame_2->AddFrame(cmakeButton, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    grid_frame_2->AddFrame(makeButton, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    grid_frame_2->AddFrame(runSimButton, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    AddFrame(grid_frame_2, new TGLayoutHints(kLHintsExpandX));

    // Create "Exit" button
    exitButton = new TGTextButton(this, "Exit");
    exitButton->Connect("Clicked()", "MyMainFrame", this, "exitButton_clicked()"); // Connect to exit handler
    AddFrame(exitButton, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
   
    // Create text output field
    textOutput = new TGTextView(this, 400, 200); // 200x100 pixels size
    AddFrame(textOutput, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 10, 10, 0, 10));
    

    // Set up the main frame
    SetWindowName("CERN-ROOT based GUI for Geant4 by V. Ranga (2025)");
    MapSubwindows();
    Resize(GetDefaultSize());  // Automatically fit all widgets
    MapWindow();
}

MyMainFrame::~MyMainFrame() {
    // Cleanup dynamically allocated objects
    RemoveFrame(cmakeButton);
    delete cmakeButton;
    
    RemoveFrame(makeButton);
    delete makeButton;

    RemoveFrame(runSimButton);
    delete runSimButton;

    RemoveFrame(exitButton);
    delete exitButton;
    
    RemoveFrame(loadInstrxnButton);
    delete loadInstrxnButton;
    
    RemoveFrame(loadLogButton);
    delete loadLogButton;

    RemoveFrame(textOutput);
    delete textOutput;
    
    RemoveFrame(labelDisplay);
    delete labelDisplay;

    Cleanup();
}

// Function to update TGTextView in real time
void MyMainFrame::updateOutField()
{
    textOutput->Update();  // Force immediate UI refresh
    gSystem->ProcessEvents(); // Process pending UI events
}


// Function to load a file into TGTextView
void MyMainFrame::LoadFile(const char *filename)
{
    textOutput->Clear();
    std::ifstream file(filename);
    if (!file) {
        textOutput->AddLine("Error: Unable to open file!");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        textOutput->AddLine(line.c_str());
    }
    file.close();
}

void MyMainFrame::loadInstrxnButton_clicked()
{
    LoadFile("instructions.txt");
}

void MyMainFrame:: loadLogButton_clicked()
{
    LoadFile("log.txt");
}

void MyMainFrame::geant4_button_clicked()
{   
   
    textOutput->AddLine("Finding Geant4..."); updateOutField();
    
    int geant4_status = gSystem->Exec("geant4-config --version  > log.txt 2>&1");
    
    if(geant4_status != 0)
     {
        textOutput->AddLine("Cannot find Geant4. Please source geant4.sh"); updateOutField();
        return;
     }
     else 
     {
        TString geant4_version = gSystem->GetFromPipe("geant4-config --version");
        TString print_geant4_version_command = "Found Geant4 version " + geant4_version + " Click on Run CMAKE to proceed.";
        textOutput->AddLine(print_geant4_version_command); updateOutField();
     }    
}


void MyMainFrame::cmakeButton_clicked()
{   
   
    textOutput->AddLine("Running CMAKE..."); updateOutField();
    
    int cmakeStatus = gSystem->Exec("cd geant4/build && rm -r *  && cmake ../source >> ../../log.txt 2>&1");// > to rewrite log file
    if(cmakeStatus != 0)
     {
        textOutput->AddLine("Error: CMAKE failed. Check log.txt"); updateOutField();
        return;
     }
     else 
     {
        textOutput->AddLine("CMAKE completed successfully. Click on Run MAKE to proceed."); updateOutField();
     }    
}
//2>&1 is a shell redirection operator. It redirects stderr (error output, file descriptor 2) to
//stdout (standard output, file descriptor 1) so that both standard output and error messages appear in the same stream.
        
void MyMainFrame::makeButton_clicked()
{
    textOutput->AddLine("Running MAKE using 4 cores..."); updateOutField();
    
    int makeStatus = gSystem->Exec("cd geant4/build && make -j4 >> ../../log.txt 2>&1");// >> append to log file
    if(makeStatus != 0)
     {
        textOutput->AddLine("Error: MAKE failed. Check log.txt"); updateOutField();
        return;
     }
     else 
     {
        textOutput->AddLine("MAKE completed successfully. Click on Run Simulation to proceed."); updateOutField();
     }
}

void MyMainFrame::runSimButton_clicked() {
    textOutput->AddLine("Started..."); updateOutField();
    
   // std::thread([this]() {
 
        textOutput->AddLine("Grabbing executable file name..."); updateOutField();
        // Execute the shell command and store output
        TString exec_name = gSystem->GetFromPipe("grep 'Built target' log.txt | awk '{print $4}'");

        // Print the extracted executable name
        // Construct a shell command using the extracted executable name
        TString print_exe_name_command = "Ecexutable file name is: " + exec_name;

        textOutput->AddLine(print_exe_name_command); updateOutField();
        
        textOutput->AddLine("Running simulation..."); updateOutField();
        
        // Construct a shell command using the extracted executable name
        TString exe_command = "cd geant4/build && ./" + exec_name + " >> ../../log.txt 2>&1";

        // Execute the command
        int simStatus = gSystem->Exec(exe_command);

        // Check execution result
        cout << "Execution returned: " << simStatus << endl;

        //int simStatus = gSystem->Exec("cd geant4/build && ./sim >> ../../log.txt 2>&1");
        if (simStatus != 0) {
            textOutput->AddLine("Error: Simulation failed. Check log.txt"); updateOutField();
            return;
        }

        textOutput->AddLine("Run successful"); updateOutField();
    //}).detach();  // Detach to avoid blocking UI
}


void MyMainFrame::exitButton_clicked()
{
    textOutput->AddLine("Exiting application..."); // Add exit message
    gApplication->Terminate(0); // Gracefully exit the application
}

// Properly handle window close
void MyMainFrame::CloseWindow() {
    std::cout << "Closing application...\n";
    gApplication->Terminate(0);  // Stops the ROOT event loop
}

int geant4_gui() {
    TApplication app("ROOT Application", 0, nullptr);
    //0: Represents the argc parameter (argument count). Since no command-line arguments are being passed, this value is set to 0.
    //nullptr: Represents the argv parameter (argument vector). Since there are no command-line arguments, it is set to nullptr (null pointer).
    MyMainFrame *mainFrame = new MyMainFrame(gClient->GetRoot(), 600, 600); // Specifies the width and height of the MyMainFrame window in pixels.
    app.Run();

    // Delete main frame after application ends
    delete mainFrame;
    return 0;
}
