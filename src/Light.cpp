#include "Light.h"
#include <iostream>

Light::Light(const std::string& name,
             const std::string& color,
             int brightness)
    : Device(name), color(color), brightness(brightness) {}

void Light::powerOn() {
    if (!isPoweredOn) {
        isPoweredOn = true;
        std::cout << name << " ISIK ACILDI Renk: "
                  << color << ", Parlaklik: " << brightness << "\n";
    } else {
        std::cout << name << " ISIK ACIK DURUMDA.\n";
    }
}

void Light::powerOff() {
    if (isPoweredOn) {
        isPoweredOn = false;
        std::cout << name << " ISIK KAPANDI.\n";
    } else {
        std::cout << name << " ISIK KAPALI DURUMDA.\n";
    }
}

void Light::reportStatus() const {
    std::cout << "----------------------------\n";
    std::cout << "        LIGHT STATUS\n";
    std::cout << "----------------------------\n";
    std::cout << "Ad: " << name << "\n";
    std::cout << "Durum: " << (isPoweredOn ? "Açik" : "Kapali") << "\n";
    std::cout << "Renk: " << color << "\n";
    std::cout << "Parlaklik: " << brightness << "\n";
    std::cout << "-----------------------\n";
}

Device* Light::clone() const {
    return new Light(*this);
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
