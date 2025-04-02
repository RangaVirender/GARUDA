#ifndef VGLOBAL_HH
#define VGLOBAL_HH

#include "G4AnalysisManager.hh"

extern G4double detDiameter;// = 3.5;//inches
extern G4double detDiameterCm;
extern G4double detLength; //= 6.0;//inches 
extern G4double detHalfLengthZ;
extern G4double detDistance;
extern G4double AlThickness; //= 0.08;//cm
extern G4double AlGap;// = 0.8;//cm //gap between Aliminium and crystal
extern G4double AlPositionZ;// = detDistance + AlThickness/2.0 ;
extern G4double detPositionZ;
extern G4int noOfEvents_int;
extern G4double particleEnergy;
extern G4String particleName;
extern std::chrono::system_clock::time_point startTimeSys;
extern std::chrono::system_clock::time_point endTimeSys;
extern std::time_t startTime;
extern std::time_t endTime;
extern G4String detector_material;
#endif
