#ifndef POSITRONIUM_DEFINITION_HH
#define POSITRONIUM_DEFINITION_HH

#include "G4ParticleDefinition.hh"

class PositroniumDefinition {
public:
    static G4ParticleDefinition* OrthoPositronium();
    static G4ParticleDefinition* ParaPositronium();
};

#endif
