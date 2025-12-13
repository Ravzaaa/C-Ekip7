#include "Device.h"

Device::Device(const std::string& name)
    : id(-1), name(name), isPoweredOn(false), isActive(true) {}

    int Device::getId() const {
        return id;
    }

    void Device::setId(int newId) {
        id = newId;
    }


    std ::string Device::getName() const {
        return name;
    }

    bool Device::getPowerStatus() const {
        return isPoweredOn;
    }

    bool Device::getActiveStatus() const {
        return isActive;
    }   

    void Device::setActive(bool state) {
        isActive = state;
    }

