#pragma once
#include "State.h"

class Snapshot {
private:
    State savedState;

public:
    explicit Snapshot(State s);
    State getSavedState() const;
};
