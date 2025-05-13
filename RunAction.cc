#include "RunAction.hh"
#include "G4AnalysisManager.hh"

RunAction::RunAction() {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->CreateNtuple("SiDetector", "Pixel Hits");
    analysisManager->CreateNtupleDColumn("EnergyDep"); // Column 0
    analysisManager->CreateNtupleDColumn("TimeOfFlight"); // Column 1
    analysisManager->CreateNtupleDColumn("Xpos"); // Column 2
    analysisManager->CreateNtupleDColumn("Ypos"); // Column 3
    analysisManager->CreateNtupleDColumn("Zpos"); // Column 4
    analysisManager->CreateNtupleIColumn("PixelID"); // Column 5
    analysisManager->FinishNtuple();
}

void RunAction::EndOfRunAction(const G4Run*) {
    G4AnalysisManager::Instance()->Write();
    G4AnalysisManager::Instance()->CloseFile();
}
