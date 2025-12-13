#include "DeviceManager.h"
#include "Logger.h"
#include <iostream>
#include <algorithm>
#include <fstream>  //dosya okuma/yazma icin gerekli
#include <cstdlib> // system("cls") komutu için gerekli

DeviceManager::DeviceManager() {
    factory = new StandardDeviceFactory();
}

DeviceManager::~DeviceManager() {
    // temizlik
    for (Device* d : deviceList) delete d;
    delete factory;
}

void DeviceManager::clearScreen() {
    system("cls");

}

// istenilen cihaz bilgileri sorgusu
void DeviceManager::uiAddDevice() {
    clearScreen();
    int choice, quantity;
    std::cout << "\n--- Cihaz Ekle ---\n";
    std::cout << "1. Light\n2. Camera\n3. Detector (Smoke & Gas)\n4. TV\n5. Alarm\nSecim: ";
    std::cin >> choice;
    std::cout << "Adet: ";
    std::cin >> quantity;

    Device* prototype = nullptr;

    //ilk cihazin factory ile olusturulmasi
    switch (choice) {
    case 1: prototype = factory->createLight(); break;
    case 2: prototype = factory->createCamera(); break;
    case 3: prototype = factory->createDetector(); break;
    case 4: prototype = factory->createTV(); break;
    case 5: prototype = factory->createAlarm(); break;
    default: std::cout << "Gecersiz secim.\n"; return;
    }

    if (!prototype) return;

    // ilk (Prototip) cihazi ekleme
    addDevice(prototype);

    int baslangicId = prototype->getId();

    for (int i = 1; i < quantity; ++i) {
        Device* kopya = prototype->clone();
        kopya->setId(baslangicId + i);
        addDevice(kopya);  // yeni ID'li kopyayý listeye ekleme
    }

    std::cout << quantity << " adet cihaz eklendi.\n";
}

// cihazlarin listeye eklenmesi
void DeviceManager::addDevice(Device* d) {
    deviceList.push_back(d);

    if (Logger::getInstance()) {
        Logger::getInstance()->log("Cihaz eklendi: " + d->getName() + " ID:" + std::to_string(d->getId()));
    }
}

void DeviceManager::listDevices() {
    std::cout << "\n--- Cihaz Listesi ---\n";
    for (const auto& d : deviceList) {
        std::cout << ">> [ID: " << d->getId() << "] \n";
        d->reportStatus();
        std::cout << "\n";
    }
    std::cout << "---------------------\n";
}

std::vector<Device*>& DeviceManager::getDevices() {
    return deviceList;
}

// istenilen cihazlarin kaldirilmasi
void DeviceManager::uiRemoveDevice() {
    clearScreen();
    listDevices();
    if (deviceList.empty()) return;

    int idToRemove;
    std::cout << "Silinecek Cihaz ID: ";
    std::cin >> idToRemove;

    removeDevice(idToRemove);
}

void DeviceManager::removeDevice(int id) {
    auto it = std::remove_if(deviceList.begin(), deviceList.end(),
        [id](Device* d) {
            if (d->getId() == id) {
                if (Logger::getInstance()) {
                    Logger::getInstance()->log("Cihaz silindi ID:" + std::to_string(id));
                }
                delete d;
                return true;
            }
            return false;
        });

    clearScreen();
    if (it != deviceList.end()) {
        deviceList.erase(it, deviceList.end());
        std::cout << "Cihaz basariyla silindi.\n";
    }
    else {
        std::cout << "Cihaz bulunamadi.\n";
    }
}

void DeviceManager::saveToFile() {
    std::ofstream file("devices.txt");  //dosyayi yazmak icin acma islemi
    if (!file.is_open()) return;

    for (Device* d : deviceList) {
        file << d->getId() << " " << d->getName() << "\n";
    }
    file.close();
    std::cout << "[Sistem] Veriler 'devices.txt' dosyasina kaydedildi.\n";
}

void DeviceManager::loadFromFile() {
    std::ifstream file("devices.txt");  //dosyayi okumak icin acma islemi
    if (!file.is_open()) return;

    int id;
    std::string name;

    //dosyayi satir satir okuma
    while (file >> id >> name) {
        Device* newDevice = nullptr;

        //isme gore dogru nesneyi olusturma
        if (name == "Light") newDevice = factory->createLight();
        else if (name == "Camera") newDevice = factory->createCamera();
        else if (name == "Detector") newDevice = factory->createDetector();
        else if (name == "TV") newDevice = factory->createTV();
        else if (name == "Alarm") newDevice = factory->createAlarm();

        if (newDevice) {
            newDevice->loadId(id);
            deviceList.push_back(newDevice);
        }
    }
    file.close();
    std::cout << "[Sistem] Eski cihazlar geri yuklendi.\n";
}