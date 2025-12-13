#include "TV.h"
#include <iostream>

TV::TV(const std::string& name,
       const std::string& brand,
       const std::string& model,
       int channel,
       int volume)
    : Device(name),
      brand(brand),
      model(model),
      channel(channel),
      volume(volume)
{}
void TV::powerOn() {
    if (!getActiveStatus()) {
    std::cout << name << " pasif durumda, TV acilamaz.\n";
    return;
}
    if (!isPoweredOn) {
        isPoweredOn = true;
        std::cout << name << " televizyonu acildi.\n";
    } else {
        std::cout << name << " televizyonu zaten acik.\n";
    }
}

void TV::powerOff() {
    if (isPoweredOn) {
        isPoweredOn = false;
        std::cout << name << " televizyonu kapatildi.\n";
    } else {
        std::cout << name << " televizyonu zaten kapali.\n";
    }
}

void TV::setChannel(int newChannel) {
    if (newChannel > 0) {
        channel = newChannel;
        std::cout << "Kanal degistirildi: " << channel << "\n";
    }
}

void TV::setVolume(int newVolume) {
    if (newVolume >= 0 && newVolume <= 100) {
        volume = newVolume;
        std::cout << "Ses seviyesi degisti: " << volume << "\n";
    }
}

void TV::reportStatus() const {
    std::cout << "---- TV STATUS ----\n";
    std::cout << "Ad: " << name << "\n";
    std::cout << "Durum: " << (isPoweredOn ? "Acik" : "Kapali") << "\n";
    std::cout << "Kanal: " << channel << "\n";
    std::cout << "Ses: " << volume << "\n";
    std::cout << "Marka: " << brand << "\n";
    std::cout << "Model: " << model << "\n";

    std::cout << "-------------------\n";
}

Device* TV::clone() const {
    return new TV(*this);
}

