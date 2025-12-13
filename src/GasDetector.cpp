#include "GasDetector.h"
#include <iostream>

GasDetector::GasDetector(const std::string& name)
    : Device(name), gasDetected_(false)
{
    isPoweredOn = true;
}



void GasDetector::powerOn() {
    std::cout << name << " gaz dedektoru zaten acik.\n";
}

void GasDetector::powerOff() {
    std::cout << name <<  "Kritik cihaz: kapatilamaz\n";
}

void GasDetector::detectGas(bool state) {
    if (!getActiveStatus()) {
        return;
    }

    gasDetected_ = state;

    if (state) {
        std::cout << name << " -> gaz algilandi!\n";
    }
}

void GasDetector::reportStatus() const {
    std::cout << "----------------------\n";
    std::cout << "    GAZ DEDEKTORU\n";
    std::cout << "----------------------\n";
    std::cout << "Ad      : " << name << "\n";
    std::cout << "Durum   : " << (isPoweredOn ? "CALISIYOR" : "KAPALI") << "\n";
    std::cout << "Aktif   : " << (getActiveStatus() ? "EVET" : "HAYIR") << "\n";
    std::cout << "Algilama: "
              << (gasDetected_ ? "GAZ TESPIT EDILDI" : "TEMIZ") << "\n";
    std::cout << "----------------------\n";
}

Device* GasDetector::clone() const {
    return new GasDetector(*this);
}
