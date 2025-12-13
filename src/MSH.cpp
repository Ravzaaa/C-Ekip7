#include "MSH.h"
#include <iostream>

// --- MSH ctor: default Normal (LLR 4.4) ---
MSH::MSH() : currentState(State::Normal) {}

// --- getters ---
State MSH::getCurrentState() const {
    return currentState;
}

// --- snapshot handling (LLR 4.2) ---
Snapshot MSH::saveSnapshot() const {
    return Snapshot(currentState);
}

void MSH::restoreSnapshot(const Snapshot& s) {
    currentState = s.getSavedState();
    applyRestrictions();
}

// --- state change (LLR 4.2 + LLR 4.5) ---
void MSH::setState(State s) {
    // Save BEFORE changing (Memento)
    history.push(saveSnapshot());
    currentState = s;
    applyRestrictions();
}

// --- revert (LLR 4.3) ---
void MSH::revertToPreviousState() {
    if (history.empty()) {
        std::cout << "[MSH] No previous state." << std::endl;
        return;
    }
    Snapshot prev = history.pop();
    restoreSnapshot(prev);
}

// --- restrictions/log (LLR 4.5) ---
void MSH::applyRestrictions() const {
    switch (currentState) {
        case State::Normal:
            std::cout << "[MSH] State=Normal" << std::endl;
            break;
        case State::HighPerformance:
            std::cout << "[MSH] State=HighPerformance" << std::endl;
            break;
        case State::Sleep:
            std::cout << "[MSH] State=Sleep (some operations disabled)" << std::endl;
            break;
        default:
            std::cout << "[MSH] State=Unknown" << std::endl;
            break;
    }
}
