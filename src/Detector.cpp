#include "Detector.h"
#include <iostream>

Detector::Detector(const std::string& name,
                   bool gasSensor,
                   bool smokeSensor)
    : Device(name),
      gasSensor(gasSensor),
      smokeSensor(smokeSensor),
      gasDetected(false),
      smokeDetected(false)
{
    // Kritik cihaz → sistemle birlikte açık başlar
    isPoweredOn = true;
    status = "ACTIVE";
}

void Detector::powerOn() {
    std::cout << name << " dedektoru zaten aktif.\n";
}

void Detector::powerOff() {
    // Kritik cihaz: kapatma reddedilir
    std::cout << name << " kritik cihazdir, kapatilamaz!\n";
}

void Detector::detectGas(bool state) {
    if (!getActiveStatus() || !gasSensor) return;

    gasDetected = state;
    if (state) {
        std::cout << name << " -> GAZ ALGILANDI!\n";
    }
}

void Detector::detectSmoke(bool state) {
    if (!getActiveStatus() || !smokeSensor) return;

    smokeDetected = state;
    if (state) {
        std::cout << name << " -> DUMAN ALGILANDI!\n";
    }
}

void Detector::reportStatus() const {
    std::cout << "-----------------------------\n";
    std::cout << "        DETECTOR STATUS\n";
    std::cout << "-----------------------------\n";
    std::cout << "Ad          : " << name << "\n";
    std::cout << "Durum       : " << status << "\n";
    std::cout << "Gaz Sensor  : " << (gasSensor ? "VAR" : "YOK") << "\n";
    std::cout << "Duman Sensor: " << (smokeSensor ? "VAR" : "YOK") << "\n";

    if (gasSensor)
        std::cout << "Gaz Algilama: "
                  << (gasDetected ? "TESPIT EDILDI" : "TEMIZ") << "\n";

    if (smokeSensor)
        std::cout << "Duman Algilama: "
                  << (smokeDetected ? "TESPIT EDILDI" : "TEMIZ") << "\n";

    std::cout << "-----------------------------\n";
}

Device* Detector::clone() const {
    return new Detector(*this);
}
