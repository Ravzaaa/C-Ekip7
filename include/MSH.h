#pragma once
#include "State.h"
#include "HistoryStack.h"
#include "Snapshot.h"

class MSH {
private:
    State currentState;
    HistoryStack history;

public:
    MSH(); // default Normal

    void setState(State s);
    void revertToPreviousState();
    State getCurrentState() const;

    void applyRestrictions();
    Snapshot saveSnapshot();
    void restoreSnapshot(Snapshot s);
};
