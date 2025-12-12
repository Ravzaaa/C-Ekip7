#include "Snapshot.h"

Snapshot::Snapshot(State s) : savedState(s) {}
State Snapshot::getSavedState() const { return savedState; }
