#include "HistoryStack.h"

void HistoryStack::push(const Snapshot& s) { stack.push_back(s); }

Snapshot HistoryStack::pop() {
    // Not: revertToPreviousState() zaten empty() kontrol ediyor.
    Snapshot top = stack.back();
    stack.pop_back();
    return top;
}

bool HistoryStack::empty() const { return stack.empty(); }
