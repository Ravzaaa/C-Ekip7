#include "Device.h"
#include <iostream>

Device::Device(const std::string& name)
    : name(name), isPoweredOn(false) {}

Device::~Device() {}

void Device::powerOn() {
    if (!isPoweredOn) {
        isPoweredOn = true;
        std::cout << name << " cihazi açildi.\n";
    } else {
        std::cout << name << " cihazi zaten açik.\n";
    }
}

void Device::powerOff() {
    if (isPoweredOn) {
        isPoweredOn = false;
        std::cout << name << " cihazi kapatildi.\n";
    } else {
        std::cout << name << " cihazi zaten kapali.\n";
    }
}
