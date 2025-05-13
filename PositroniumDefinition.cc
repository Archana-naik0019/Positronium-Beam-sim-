#include "PositroniumDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4DecayTable.hh"
#include "G4PhaseSpaceDecayChannel.hh"

G4ParticleDefinition* PositroniumDefinition::OrthoPositronium() {
    G4String name = "orthoPositronium";
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* existingParticle = particleTable->FindParticle(name);
    
    if (!existingParticle) {
        G4ParticleDefinition* oPs = new G4ParticleDefinition(
            name,  
            1.022 * MeV,   // Mass (e⁺ + e⁻)
            0.0 * MeV,     // Width (ignored)
            0.0 * eplus,   // Charge
            1,             // Spin 1 (triplet)
            0,             // Parity
            0,             // C-Parity
            0,             // Isospin
            0,             // Isospin3
            0,             // G-Parity
            "exotic",      // Particle type
            0,             // Lepton number
            0,             // Baryon number
            9900015,       // PDG code (custom)
            false,         // Stable
            142 * ns,      // Lifetime in vacuum (~142 ns)
            nullptr,       // Some parameter I am unsure of!
            false          // it is Short-lived
        );

        // Add three-photon decay channel
        G4DecayTable* decayTable = new G4DecayTable();
        decayTable->Insert(new G4PhaseSpaceDecayChannel("orthoPositronium", 1.0, 3, "gamma", "gamma", "gamma"));
        oPs->SetDecayTable(decayTable);

        return oPs;
    }
    return existingParticle;
}

G4ParticleDefinition* PositroniumDefinition::ParaPositronium() {
    G4String name = "paraPositronium";
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* existingParticle = particleTable->FindParticle(name);

    if (!existingParticle) {
        G4ParticleDefinition* pPs = new G4ParticleDefinition(
            name,  
            1.022 * MeV,   
            0.0 * MeV,     
            0.0 * eplus,   
            0,             // Spin 0 (singlet)
            0,             
            0,             
            0,             
            0,             
            0,             
            "exotic",      
            0,             
            0,             
            9900016,       // PDG code (custom)
            false,         
            125 * ps,      // Lifetime in vacuum (~125 ps)
            nullptr,       
            false          
        );

        // Add two-photon decay channel
        G4DecayTable* decayTable = new G4DecayTable();
        decayTable->Insert(new G4PhaseSpaceDecayChannel("paraPositronium", 1.0, 2, "gamma", "gamma"));
        pPs->SetDecayTable(decayTable);

        return pPs;
    }
    return existingParticle;
}
