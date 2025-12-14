#include <iostream>
#include "Light.h"
#include "Camera.h"
#include "TV.h"
#include "Alarm.h"
#include "Detector.h"

#include "ModeDirector.h"      // ModeDirector sınıfı burada
#include "ModeTypes.h"
#include "IDeviceController.h"

// Basit test controller'ı
class ConsoleDeviceController : public IDeviceController {
public:
    void setLights(bool on) override {
        std::cout << "[Device] Lights: " << (on ? "ON" : "OFF") << std::endl;
    }

    void setTV(bool on) override {
        std::cout << "[Device] TV: " << (on ? "ON" : "OFF") << std::endl;
    }

    void setMusic(bool on) override {
        std::cout << "[Device] Music: " << (on ? "ON" : "OFF") << std::endl;
    }

    void ensureSecurityDevicesOn() override {
        std::cout << "[Device] Security devices (Camera + Detectors): ALWAYS ON" << std::endl;
    }
};

int main() {
    std::cout << "Akilli Ev Sistemi Baslatiliyor...\n";

    // Light nesnesi olustur
    Light salonIsigi("Salon Isigi", "Sari", 80);

    // Isigi ac
    salonIsigi.powerOn();

    // Durumu yazdir
    salonIsigi.reportStatus();

    // Isigi kapat
    salonIsigi.powerOff();

    // Tekrar durumu yazdir
    salonIsigi.reportStatus();

    // Camera nesnesi olustur
    Camera guvenlikKamerasi("Guvenlik Kamerasi");

    guvenlikKamerasi.powerOn();
    guvenlikKamerasi.startRecording();
    guvenlikKamerasi.reportStatus();

    guvenlikKamerasi.stopRecording();
    guvenlikKamerasi.powerOff();
    guvenlikKamerasi.reportStatus();

    TV salonTV("Salon TV", "Samsung", "QLED", 7, 25);


    salonTV.powerOn();
    salonTV.setChannel(12);
    salonTV.setVolume(40);
    salonTV.reportStatus();
    salonTV.powerOff();
    salonTV.reportStatus();

    Alarm evAlarmi("Alarm Sistemi");

    evAlarmi.powerOn();
    evAlarmi.reportStatus();

    evAlarmi.powerOff();    //  Kapatma denemesi → reddedilmeli
    evAlarmi.reportStatus();

    Detector evDedektoru("Dedektor Sistemi", true, true);

    evDedektoru.powerOn();
    evDedektoru.detectGas(true);
    evDedektoru.detectSmoke(true);
    evDedektoru.reportStatus();
    evDedektoru.powerOff();   // reddedilecek



    ConsoleDeviceController controller;
    ModeDirector director(controller);  // ModeDirector kullanıyoruz

    std::cout << "=== System init (Default Normal Mode) ===" << std::endl;
    director.initDefaultMode();

    int choice = -1;
    while (true) {
        std::cout << "\n--- Mode Menu ---\n";
        std::cout << "1. Normal Mode\n";
        std::cout << "2. Night (Evening) Mode\n";
        std::cout << "3. Party Mode\n";
        std::cout << "4. Cinema Mode\n";
        std::cout << "0. Exit\n";
        std::cout << "Select: ";
        std::cin >> choice;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Exiting...\n";
            break;
        }

        switch (choice) {
            case 1:
                director.changeMode(ModeType::Normal);
                break;
            case 2:
                director.constructEveningMode();  // UML fonksiyonu
                break;
            case 3:
                director.constructPartyMode();    // UML fonksiyonu
                break;
            case 4:
                director.constructCinemaMode();   // UML fonksiyonu
                break;
            default:
                std::cout << "Unknown choice.\n";
                break;
        }
    }

    return 0;
}

