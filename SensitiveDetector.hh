#ifndef SENSITIVE_DETECTOR_HH
#define SENSITIVE_DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4ThreeVector.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class SensitiveDetector : public G4VSensitiveDetector {
public:
    SensitiveDetector(G4String name);
    virtual ~SensitiveDetector();
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* hist);
};

#endif
