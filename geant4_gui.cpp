class MyMainFrame : public TGMainFrame {
private:
    TGTextButton *cmakeButton; // Button for cmake
    TGTextButton *makeButton; // Button for make
    TGTextButton *runSimButton; // Button for running simulation
    TGTextButton *exitButton;  // Button for exiting the application
    TGTextButton *loadLogButton;  // Button for exiting the application
    TGTextButton *loadInstrxnButton;  // Button for exiting the application
    TGTextView   *textOutput;    // Text output field
    TGLabel      *labelDisplay;  // Label to display text
    
public:
    MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h);
    virtual ~MyMainFrame();
    void cmakeButton_clicked(); // Action for "Click Me" button
    void makeButton_clicked(); // Action for "Click Me" button
    void runSimButton_clicked(); // Action for "Click Me" button
    void exitButton_clicked();  // Action for "Exit" button
    void loadInstrxnButton_clicked();
    void loadLogButton_clicked();
    void LoadFile(const char *filename);  // Function to load file into TGTextView
    virtual void CloseWindow();  // Properly handle window close
};

MyMainFrame::MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h) : TGMainFrame(p, w, h) 
{
    //Create label display
    labelDisplay = new TGLabel(this, "Welcome to CERN-ROOT based Geant4 GUI by V. Ranga (2025)");
    AddFrame(labelDisplay,new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    
    // Create cmake button
    cmakeButton = new TGTextButton(this, "Run CMAKE");
    cmakeButton->Connect("Clicked()", "MyMainFrame", this, "cmakeButton_clicked()"); // Connect to click handler
    //AddFrame(cmakeButton, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    AddFrame(cmakeButton);
    cmakeButton->MoveResize(50, 200, 20, 30);  // (X, Y, Width, Height)
    
    // Create make button
    makeButton = new TGTextButton(this, "Run MAKE");
    makeButton->Connect("Clicked()", "MyMainFrame", this, "makeButton_clicked()"); // Connect to click handler
    AddFrame(makeButton, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));

    // Create run simulation button
    runSimButton = new TGTextButton(this, "Run Simulation");
    runSimButton->Connect("Clicked()", "MyMainFrame", this, "runSimButton_clicked()"); // Connect to click handler
    AddFrame(runSimButton, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    
    // Create "Load Instructions" button
    loadInstrxnButton = new TGTextButton(this, "Load Instructions");
    loadInstrxnButton->Connect("Clicked()", "MyMainFrame", this, "loadInstrxnButton_clicked()"); // Connect to exit handler
    AddFrame(loadInstrxnButton, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
    
    // Create "Load LOG file" button
    loadLogButton = new TGTextButton(this, "Load LOG file");
    loadLogButton->Connect("Clicked()", "MyMainFrame", this, "loadLogButton_clicked()"); // Connect to exit handler
    AddFrame(loadLogButton, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));

    // Create "Exit" button
    exitButton = new TGTextButton(this, "Exit");
    exitButton->Connect("Clicked()", "MyMainFrame", this, "exitButton_clicked()"); // Connect to exit handler
    AddFrame(exitButton, new TGLayoutHints(kLHintsCenterX, 5, 5, 5, 5));
   
    // Create text output field
    textOutput = new TGTextView(this, 200, 100); // 200x100 pixels size
    AddFrame(textOutput, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 10, 10, 10, 10));
    

    // Set up the main frame
    SetWindowName("CERN-ROOT based GUI for Geant4 by V. Ranga (2025)");
    MapSubwindows();
    Resize(w, h);
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

void MyMainFrame::cmakeButton_clicked()
{   
   
    textOutput->AddLine("Running CMAKE...");
    textOutput->Update();  // Force immediate UI refresh
    gSystem->ProcessEvents(); // Process pending UI events
    
    int cmakeStatus = gSystem->Exec("cd geant4/build && rm -r *  && cmake ../source > ../../log.txt 2>&1");// > to rewrite log file
    if(cmakeStatus != 0)
     {
        textOutput->AddLine("Error: CMAKE failed. Check log.txt");
        textOutput->Update();  // Force immediate UI refresh
        gSystem->ProcessEvents(); // Process pending UI events
        return;
     }
     else 
     {
        textOutput->AddLine("CMAKE completed successfully. Click on Run MAKE to proceed.");
        textOutput->Update();  // Force immediate UI refresh
        gSystem->ProcessEvents(); // Process pending UI events    
     }    
}
//2>&1 is a shell redirection operator. It redirects stderr (error output, file descriptor 2) to
//stdout (standard output, file descriptor 1) so that both standard output and error messages appear in the same stream.
        
void MyMainFrame::makeButton_clicked()
{
    textOutput->AddLine("Running MAKE using 4 cores...");
    textOutput->Update();  // Force immediate UI refresh
    gSystem->ProcessEvents(); // Process pending UI events
    
    int makeStatus = gSystem->Exec("cd geant4/build && make -j4 >> ../../log.txt 2>&1");// >> append to log file
    if(makeStatus != 0)
     {
        textOutput->AddLine("Error: MAKE failed. Check log.txt");
        textOutput->Update();  // Force immediate UI refresh
        gSystem->ProcessEvents(); // Process pending UI events
        return;
     }
     else 
     {
        textOutput->AddLine("MAKE completed successfully. Click on Run Simulation to proceed.");
        textOutput->Update();  // Force immediate UI refresh
        gSystem->ProcessEvents(); // Process pending UI events    
     }
}

void MyMainFrame::runSimButton_clicked() {
    textOutput->AddLine("Started...");
    textOutput->Update();  // Force immediate UI refresh
    gSystem->ProcessEvents(); // Process pending UI events
    
   // std::thread([this]() {
         
        textOutput->AddLine("Running simulation...");
        textOutput->Update();  // Force immediate UI refresh
        gSystem->ProcessEvents(); // Process pending UI events
           
        int simStatus = gSystem->Exec("cd geant4/build && ./sim >> ../../log.txt 2>&1");
        if (simStatus != 0) {
            textOutput->AddLine("Error: Simulation failed. Check log.txt");
            textOutput->Update();  // Force immediate UI refresh
            gSystem->ProcessEvents(); // Process pending UI events
            return;
        }

        textOutput->AddLine("Run successful");
        textOutput->Update();  // Force immediate UI refresh
        gSystem->ProcessEvents(); // Process pending UI events
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
    MyMainFrame *mainFrame = new MyMainFrame(gClient->GetRoot(), 300, 300); // Adjusted size for text output
    app.Run();

    // Delete main frame after application ends
    delete mainFrame;
    return 0;
}
