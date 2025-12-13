#pragma once
#include <iostream>
#include <string>
#include "Observer.h"
#include "Device.h"

// Sabitler
const std::string EVENT_MOTION = "MOTION_DETECTED";
const std::string EVENT_SMOKE = "SMOKE_DETECTED";
const std::string EVENT_GAS = "GAS_DETECTED";

class Camera : public Device, public Subject {
public:
    Camera(std::string name = "Guvenlik Kamerasi") : Device(name) {}

    void powerOn() override {
        setActive(true);
        std::cout << "[DEVICE]: " << getName() << " (ID: " << getId() << ") sistemi baslatildi." << std::endl;
    }

    void powerOff() override {
        setActive(false);
        std::cout << "[DEVICE]: " << getName() << " kapatildi." << std::endl;
    }

    void reportStatus() const override {
        std::cout << "[STATUS]: " << getName() << " : " << getStatus() << std::endl;
    }

    Device* clone() const override { return new Camera(*this); }

    void detectMotion() {
        if (getActiveStatus()) { 
             notify(EVENT_MOTION);
        }
    }
};

class Detector : public Device, public Subject {
public:
    Detector(std::string name = "Yangin Dedektoru") : Device(name) {}

    void powerOn() override {
        setActive(true);
        std::cout << "[DEVICE]: " << getName() << " (ID: " << getId() << ") aktif edildi." << std::endl;
    }

    void powerOff() override {
        std::cout << "[UYARI]: " << getName() << " kritik cihazdir, kapatilmasi onerilmez!" << std::endl;
        setActive(false);
    }

    void reportStatus() const override {
        std::cout << "[STATUS]: " << getName() << " : " << getStatus() << std::endl;
    }

    Device* clone() const override { return new Detector(*this); }
    bool isCritical() const override { return true; }

    void detectSmoke() {
        if (getActiveStatus()) notify(EVENT_SMOKE);
    }
    void detectGas() {
        if (getActiveStatus()) notify(EVENT_GAS);
    }
};