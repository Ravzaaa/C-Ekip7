#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <memory>    
#include <cstdlib> // system("cls") komutu için gerekli
#include <fstream> // Dosya okuma/yazma için þart
#include "Logger.h"
#include "Device.h"
#include "Light.h"
#include "Camera.h"
#include "Detector.h"
#include "TV.h"
#include "Alarm.h"

//abstract factory icin soyut arayuz
class DeviceFactory {
public:
	// factory methodlari
	virtual Device* createLight() = 0;
	virtual Device* createCamera() = 0;
	virtual Device* createDetector() = 0; 
	virtual Device* createTV() = 0;
	virtual Device* createAlarm() = 0;
	virtual ~DeviceFactory() {}
};

class StandardDeviceFactory : public DeviceFactory {
public:
	Device* createLight() override { return new Light("Light", "White", 100); }
	Device* createCamera() override { return new Camera("Camera", 30, false); }
	Device* createDetector() override { return new Detector("Detector", true, true); }
	Device* createTV() override { return new TV("TV", "Generic", "Standard", 1, 10); }
	Device* createAlarm() override { return new Alarm("Alarm"); }
};


//yonetici sinif
class DeviceManager {
private:
	std::vector<Device*> deviceList; // dinamik liste olusturma
	DeviceFactory* factory;

public:
	DeviceManager() {
		factory = new StandardDeviceFactory();
	}

	~DeviceManager() {
		// temizlik
		for (Device* d : deviceList) delete d;
		delete factory;
	}

	void clearScreen() {
		system("cls");
	}
	// istenilen cihaz bilgileri sorgusu
	void uiAddDevice() {
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
		addDevice(prototype);
		int baslangicId = prototype->getId();

		// Kalan adet kadar kopyalýyoruz
		for (int i = 1; i < quantity; ++i) {
			// 1. Kopyasýný oluþtur (Þu an ID'si hala 10)
			Device* kopya = prototype->clone();

			// 2. ID'sini manuel olarak deðiþtiriyoruz
			// Baþlangýç ID + Döngü Sayýsý (10+1=11, 10+2=12...)
			kopya->setId(baslangicId + i);

			// 3. Yeni ID'li kopyayý listeye ekle
			addDevice(kopya);
		}

		std::cout << quantity << " adet cihaz eklendi.\n";
	}

	// cihazlarin listeye eklenmesi
	void addDevice(Device* d) {
		deviceList.push_back(d);
		//
		// LOGLAMA ÝSLEMÝ YAPÝLACAK
		//Logger::getInstance()->log("Cihaz eklendi: " + d->getName() + " ID:" + std::to_string(d->getId()));
		//	
		if (Logger::getInstance()) {
			Logger::getInstance()->log("Cihaz eklendi: " + d->getName() + " ID:" + std::to_string(d->getId()));
		}
		
	}
	void listDevices() {
		std::cout << "\n--- Cihaz Listesi ---\n";
		for (const auto& d : deviceList) {
			std::cout << ">> [ID: " << d->getId() << "] \n";
			d->reportStatus();
			std::cout << "\n";
		}
		std::cout << "---------------------\n";
	}

	std::vector<Device*>& getDevices() {
		return deviceList;
	}

	// istenilen cihazlarin kaldirilmasi
	void uiRemoveDevice() {
		clearScreen();
		listDevices(); 
		if (deviceList.empty()) return;

		int idToRemove;
		std::cout << "Silinecek Cihaz ID: ";
		std::cin >> idToRemove;

		removeDevice(idToRemove);
	}

	void removeDevice(int id) {
		auto it = std::remove_if(deviceList.begin(), deviceList.end(),
			[id](Device* d) {
				if (d->getId() == id) {
					//
					// LOGLAMA ISLEMI YAPILACAK
					// 
					//Logger::getInstance()->log("Cihaz silindi ID:" + std::to_string(id));
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
	
	void saveToFile() {
		std::ofstream file("devices.txt"); // Dosyayý yazmak için aç
		if (!file.is_open()) return;

		// Format: ID Tip Isim
		for (Device* d : deviceList) {
			// Basitlik olsun diye ismini tip gibi kullanýyoruz burada
			file << d->getId() << " " << d->getName() << "\n";
		}
		file.close();
		std::cout << "[Sistem] Veriler 'devices.txt' dosyasina kaydedildi.\n";
	}

	
	void loadFromFile() {
		std::ifstream file("devices.txt"); // Dosyayý okumak için aç
		if (!file.is_open()) return; // Dosya yoksa (ilk açýlýþsa) hiçbir þey yapma

		int id;
		std::string name;

		// Dosyayý satýr satýr oku: ID ve Ýsim
		while (file >> id >> name) {
			Device* newDevice = nullptr;

			// Ýsme göre doðru nesneyi oluþtur
			if (name == "Light") newDevice = factory->createLight();
			else if (name == "Camera") newDevice = factory->createCamera();
			else if (name == "Detector") newDevice = factory->createDetector();
			else if (name == "TV") newDevice = factory->createTV();
			else if (name == "Alarm") newDevice = factory->createAlarm();

			if (newDevice) {
				newDevice->loadId(id); // ID'yi ayarla ve sayacý güncelle!
				deviceList.push_back(newDevice);
			}
		}
		file.close();
		std::cout << "[Sistem] Eski cihazlar geri yuklendi.\n";
	}

};

int main() {
	DeviceManager manager;

	// 1. Program açýlýnca ESKÝLERÝ YÜKLE
	manager.loadFromFile();

	// Mevcut listeyi görelim
	manager.listDevices();

	// Kullanýcý iþlem yapsýn
	manager.uiAddDevice();

	// Bir daha görelim
	manager.listDevices();

	manager.uiRemoveDevice();

	// 2. Program kapanmadan önce SON HALÝNÝ KAYDET
	manager.saveToFile();

	std::cout << "\nTest tamamlandi. Cikis yapiliyor...";
	// ...
	return 0;
	
}