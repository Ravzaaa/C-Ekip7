#include "Device.h"

int Device::idCounter = 0;

Device::Device(const std::string& name)
    :  name(name), status("OFF"), isPoweredOn(false), isActive(true) {
        id = ++idCounter;
    }

    int Device::getId() const {
        return id;
    }

    void Device::setId(int newId) {
        id = newId;
    }


    std ::string Device::getName() const {
        return name;
    }

    std::string Device::getStatus() const {
        return status;
    }

    bool Device::getPowerStatus() const {
        return isPoweredOn;
    }

    bool Device::getActiveStatus() const {
        return isActive;
    }   

    void Device::setActive(bool state) {
        isActive = state;
        status = state ? "ACTIVE" : "INACTIVE";
    }

    void Device::loadId(int savedId) {
    this->id = savedId;
    if (savedId > idCounter) {
        idCounter = savedId;
    }
    }
