#include "PrimaryGeneratorAction.hh"
#include "PositroniumDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4RandomTools.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    G4ParticleDefinition* oPs = PositroniumDefinition::OrthoPositronium();
    G4ParticleDefinition* pPs = PositroniumDefinition::ParaPositronium();

    double randomValue = G4UniformRand();
    if (randomValue < 0.75) {
        fParticleGun->SetParticleDefinition(oPs);
    } else {
        fParticleGun->SetParticleDefinition(pPs);
    }

    fParticleGun->SetParticleEnergy(1.0 * MeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
