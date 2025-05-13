#include "EventAction.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

EventAction::EventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event* event) {
    G4int eventID = event->GetEventID();
    G4cout << ">>> Event " << eventID << " starts." << G4endl;
}

void EventAction::EndOfEventAction(const G4Event* event) {
    G4int eventID = event->GetEventID();
    G4cout << ">>> Event " << eventID << " ends." << G4endl;
}
