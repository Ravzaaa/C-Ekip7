#pragma once
#include <vector>
#include "Snapshot.h"

class HistoryStack {
private:
    std::vector<Snapshot> stack;

public:
    void push(const Snapshot& s);
    Snapshot pop();
    bool empty() const;
};
