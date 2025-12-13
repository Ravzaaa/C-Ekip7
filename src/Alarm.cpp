#include "Alarm.h"
#include <iostream>

Alarm::Alarm(const std::string& name)
    : Device(name) {
        isPoweredOn = true;
    }

void Alarm::powerOn() {
        std::cout << name << " alarm sistemi zaten aktif edildi!\n";

}

void Alarm::powerOff() {
    std::cout << name << " alarm sistemi kapatilamaz (Kritik Cihaz)\n";
}

void Alarm::reportStatus() const {
    std::cout << "---- ALARM STATUS ----\n";
    std::cout << "Ad: " << name << "\n";
    std::cout << "Durum: " << (isPoweredOn ? "CALISIYOR" : "KAPALI") << "\n";
    std::cout << "----------------------\n";
}

Device* Alarm::clone() const {
    return new Alarm(*this);
}
