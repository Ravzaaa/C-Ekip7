#include "SmokeDetector.h"
#include <iostream>

SmokeDetector::SmokeDetector(const std::string& name)
    : Device(name),  smokeDetected_(false)
{
    // Kritik cihazlar sistemle birlikte açık başlar
    isPoweredOn = true;
}


void SmokeDetector::powerOn() {
        std::cout << name << "Duman Dedektoru zaten acik.\n";
    }


void SmokeDetector::powerOff() {
    // Kritik cihaz: kapatma reddedilir
    std::cout << name <<  "Kritik cihaz: KAPATILAMAZ\n";
}


void SmokeDetector::detectSmoke(bool state) {
    if (!getActiveStatus()) return;


    smokeDetected_ = state;

    if (state) {
        std::cout << name <<  "Duman algilandi!\n";
        // Alarm / Observer ileride buradan tetiklenecek
    }
}

void SmokeDetector::reportStatus() const {
    std::cout << "----------------------\n";
    std::cout << "   DUMAN DEDEKTORU\n";
    std::cout << "----------------------\n";
    std::cout << "Ad      : " << name << "\n";
    std::cout << "Durum   : " << (isPoweredOn ? "CALISIYOR" : "KAPALI") << "\n";
    std::cout << "Aktif   : " << (getActiveStatus() ? "EVET" : "HAYIR") << "\n";
    std::cout << "Algilama: "
              << (smokeDetected_ ? "DUMAN TESPIT EDILDI" : "TEMIZ") << "\n";
    std::cout << "----------------------\n";
}

Device* SmokeDetector::clone() const {
    return new SmokeDetector(*this);
}



