#include "Camera.h"
#include <iostream>

Camera::Camera(const std::string& name, int fps, bool nightVision)
    : Device(name),
      fps(fps),
      nightVision(nightVision),
      recording(false)
{}

void Camera::powerOn() {
    if(!getActiveStatus()) {
    std::cout << name << " kamera aktif degil.\n";
    return;
    }
    
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
    if(!getActiveStatus()) {
    std::cout << name << " kamera aktif degil.\n";
    return;
    }
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
    std::cout << "FPS: " << fps << "\n";
    std::cout << "Night Vision: "<< (nightVision ? "Acik" : "Kapali") << "\n";
    std::cout << "------------------------\n";
}

Device* Camera::clone() const {
    return new Camera(*this);
}   
