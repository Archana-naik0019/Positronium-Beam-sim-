#include "SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name) {}

SensitiveDetector::~SensitiveDetector() {}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4double energyDep = step->GetTotalEnergyDeposit();
    if (energyDep == 0) return false; // Ignore if no energy is deposited

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    G4ThreeVector pos = step->GetPostStepPoint()->GetPosition();
    G4double time = step->GetPostStepPoint()->GetGlobalTime();
    G4int pixelID = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

    // Store data in ROOT file
    analysisManager->FillNtupleDColumn(0, energyDep / MeV);
    analysisManager->FillNtupleDColumn(1, time / ns);
    analysisManager->FillNtupleDColumn(2, pos.x() / cm);
    analysisManager->FillNtupleDColumn(3, pos.y() / cm);
    analysisManager->FillNtupleDColumn(4, pos.z() / cm);
    analysisManager->FillNtupleIColumn(5, pixelID);
    analysisManager->AddNtupleRow();

    return true;
}
