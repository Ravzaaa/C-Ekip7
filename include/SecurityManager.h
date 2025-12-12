#pragma once
#include <string>
#include "SecurityHandlers.h"

class SecurityManager {
private:
    Handler* alarmHandler;
    Handler* lightHandler;
    Handler* policeHandler;
    Handler* fireHandler;
public:
    SecurityManager();  // Kurucu fonksiyon
    ~SecurityManager(); // Yikici fonksiyon
    void handleEvent(std::string event);
};