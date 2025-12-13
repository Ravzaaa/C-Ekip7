#include "../include/SecurityManager.h"

SecurityManager::SecurityManager() {
    // Zinciri burada kuruyoruz
    alarmHandler = new AlarmHandler();
    lightHandler = new LightHandler();
    policeHandler = new PoliceHandler();
    fireHandler = new FireDeptHandler();

    alarmHandler->setNext(lightHandler);
    lightHandler->setNext(policeHandler);
    policeHandler->setNext(fireHandler);
}

SecurityManager::~SecurityManager() {
    delete alarmHandler;
    delete lightHandler;
    delete policeHandler;
    delete fireHandler;
}

void SecurityManager::handleEvent(std::string event) {
    // Disaridan gelen olayi zincire ver
    if (alarmHandler) {
        alarmHandler->handle(event);
    }
}