#include "Light.h"
#include <iostream>

Light::Light(const std::string& name,
             const std::string& color,
             int brightness)
    : Device(name), color(color), brightness(brightness) {}

void Light::powerOn() {
    if (!isPoweredOn) {
        isPoweredOn = true;
        std::cout << name << " ışığı açildi. Renk: "
                  << color << ", Parlaklik: " << brightness << "\n";
    } else {
        std::cout << name << " ışığı zaten açik.\n";
    }
}

void Light::powerOff() {
    if (isPoweredOn) {
        isPoweredOn = false;
        std::cout << name << " ışığı kapatildi.\n";
    } else {
        std::cout << name << " ışığı zaten kapali.\n";
    }
}

void Light::reportStatus() const {
    std::cout << "---- LIGHT STATUS ----\n";
    std::cout << "Ad: " << name << "\n";
    std::cout << "Durum: " << (isPoweredOn ? "Açik" : "Kapali") << "\n";
    std::cout << "Renk: " << color << "\n";
    std::cout << "Parlaklik: " << brightness << "\n";
    std::cout << "-----------------------\n";
}

void Light::setColor(const std::string& newColor) {
    color = newColor;
}

void Light::setBrightness(int newBrightness) {
    if (newBrightness >= 0 && newBrightness <= 100)
        brightness = newBrightness;
    else
        std::cout << "Parlaklik 0-100 arasi olmalidir.\n";
}
