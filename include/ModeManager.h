#pragma once
#include "State.h"
#include "HistoryStack.h"
#include "Snapshot.h"

class ModeManager {
private:
    State currentState;
    HistoryStack history;

public:
    ModeManager(); // default Normal

    void setState(State s);
    void revertToPreviousState();
    State getCurrentState() const;

    void applyRestrictions() const;
    Snapshot saveSnapshot() const;
    void restoreSnapshot(const Snapshot& s);
};