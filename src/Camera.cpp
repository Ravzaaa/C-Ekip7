#include "Camera.h"
#include <iostream>

Camera::Camera(const std::string& name)
    : Device(name), recording(false) {}

void Camera::powerOn() {
    if (!isPoweredOn) {
        isPoweredOn = true;
        std::cout << name << " kamerasi acildi.\n";
    } else {
        std::cout << name << " kamerasi zaten acik.\n";
    }
}

void Camera::powerOff() {
    if (isPoweredOn) {
        isPoweredOn = false;
        recording = false;
        std::cout << name << " kamerasi kapatildi.\n";
    } else {
        std::cout << name << " kamerasi zaten kapali.\n";
    }
}

void Camera::startRecording() {
    if (isPoweredOn && !recording) {
        recording = true;
        std::cout << name << " kayit almaya basladi.\n";
    } else if (!isPoweredOn) {
        std::cout << name << " kapali, kayit baslatilamaz.\n";
    } else {
        std::cout << name << " zaten kayit aliyor.\n";
    }
}

void Camera::stopRecording() {
    if (recording) {
        recording = false;
        std::cout << name << " kaydi durdurdu.\n";
    } else {
        std::cout << name << " zaten kayit almiyor.\n";
    }
}

void Camera::reportStatus() const {
    std::cout << "---- CAMERA STATUS ----\n";
    std::cout << "Ad: " << name << "\n";
    std::cout << "Durum: " << (isPoweredOn ? "Acik" : "Kapali") << "\n";
    std::cout << "Kayit: " << (recording ? "Var" : "Yok") << "\n";
    std::cout << "------------------------\n";
}
