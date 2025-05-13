#ifndef ACTION_INITIALIZATION_HH
#define ACTION_INITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization();
    virtual ~ActionInitialization() override;

    virtual void Build() const override;
    virtual void BuildForMaster() const override;
};

#endif
