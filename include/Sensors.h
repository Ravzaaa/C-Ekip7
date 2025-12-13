#pragma once
#include <iostream>
#include "Observer.h"
// YENİ: Device sınıfını dahil ettim
#include "Device.h"

using namespace std;

// ---------------------------------------------------------
//  CAMERA SINIFI (Hem Device hem Subject)
// ---------------------------------------------------------
class Camera : public Device, public Subject {
public:
    // Device sınıfı "isim" istiyor, biz de kurucuda (constructor) bunu istiyoruz
    // Varsayılan olarak "Guvenlik Kamerasi" ismini verdik.
    Camera(string deviceName = "Guvenlik Kamerasi") : Device(deviceName) {}

    // --- Device'dan Gelen Zorunlu Fonksiyonlar ---
    void powerOn() override {
        setActive(true);
        cout << "[DEVICE]: " << getName() << " (ID: " << getId() << ") ACILDI." << endl;
    }

    void powerOff() override {
        setActive(false);
        cout << "[DEVICE]: " << getName() << " (ID: " << getId() << ") KAPATILDI." << endl;
    }

    void reportStatus() const override {
        cout << "[STATUS]: " << getName() << " durumu: " << getStatus() << endl;
    }

    // Prototype Pattern (Kopyalama için gerekli)
    Device* clone() const override {
        return new Camera(*this);
    }

    // --- Dev 6 (Senin) Fonksiyonun ---
    void detectMotion() {
        // ARTIK AKILLI: Sadece cihaz aktifse (fişi takılıysa) algılar!
        if (getActiveStatus()) {
            notify("MOTION_DETECTED");
        } else {
            cout << "[UYARI]: " << getName() << " kapali oldugu icin hareket algilanamadi." << endl;
        }
    }
};

// ---------------------------------------------------------
//  DETECTOR SINIFI (Hem Device hem Subject)
// ---------------------------------------------------------
class Detector : public Device, public Subject {
public:
    // Varsayılan isim: "Yangin Dedektoru"
    Detector(string deviceName = "Yangin Dedektoru") : Device(deviceName) {}

    // --- Device'dan Gelen Zorunlu Fonksiyonlar ---
    void powerOn() override {
        setActive(true);
        cout << "[DEVICE]: " << getName() << " (ID: " << getId() << ") ACILDI." << endl;
    }

    void powerOff() override {
        // Dedektörler kritik cihazdır, normalde kapanmaz ama fonksiyonu yazmak zorundayız.
        setActive(false);
        cout << "[DEVICE]: " << getName() << " KAPATILDI." << endl;
    }

    void reportStatus() const override {
        cout << "[STATUS]: " << getName() << " sensor durumu: " << getStatus() << endl;
    }

    Device* clone() const override {
        return new Detector(*this);
    }
    
    // Dedektör kritiktir (Device.h'deki sanal fonksiyonu eziyoruz)
    bool isCritical() const override { return true; }

    // --- Dev 6 (Senin) Fonksiyonların ---
    void detectSmoke() {
        if (getActiveStatus()) {
            notify("SMOKE_DETECTED");
        }
    }

    void detectGas() {
        if (getActiveStatus()) {
            notify("GAS_DETECTED");
        }
    }
};