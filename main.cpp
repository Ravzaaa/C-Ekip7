#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <memory>    

//
//DEV1 TARAFINDAN OLUTURULAN LOG ISLEMI KULLANILACAK
//
//
	
//TEMÝZLEME ISLEMLERI YAPILACAK

class Device {
protected:
	static int idCounter; // ID numarasýný artýrmak için
	int id;
	std::string name;
	std::string status; // active-inactive
	bool isActive;

public:
	Device(std::string n) : name(n), isActive(true), status("OFF") {
		id = ++idCounter;
	}
	virtual ~Device() {}

	int getId() const { return id; }
	std::string getName() const { return name; }


	void setActive(bool state) {
		//dev3 tarafýndan kullanýlacak
	}
	
	virtual void powerOn() {
		//dev3 tarafýndan kullanýlacak
	}

	virtual void powerOff() {
		//dev3 tarafýndan kullanýlacak
	}


	virtual void reportStatus() const {
		std::cout << "ID: " << id << " | Name: " << name << " | Status: " << status
			<< " | Active: " << (isActive ? "Yes" : "No") << std::endl;
	}

	//Prototype Pattern için clone metodu
	virtual Device* clone() const = 0;
};

int Device::idCounter = 0;

//Concrete Devices-Somut Cihazlar
class Light : public Device {
private:
	std::string color;
	int illumination; 
public:
	Light() : Device("Light"), color("White"), illumination(100) {} 

	void setConfig(std::string c, int illum) { color = c; illumination = illum; }

	void reportStatus() const override {
		std::cout << "ID: " << id << " [Light] Color: " << color << ", Illumination: " << illumination << "%" << std::endl;
	}

	// Prototype Pattern
	Device* clone() const override {
		Light* copy = new Light(*this);
		copy->id = ++idCounter; 
		return copy;
	}
};

class Camera : public Device {
private:
	int fps;
	bool nightVision;
public:
	Camera() : Device("Camera"), fps(30), nightVision(false) {} 

	void setConfig(int f, bool nv) { fps = f; nightVision = nv; }

	void reportStatus() const override {
		std::cout << "ID: " << id << " [Camera] FPS: " << fps << ", NightVision: " << (nightVision ? "Yes" : "No") << std::endl;
	}

	Device* clone() const override {
		Camera* copy = new Camera(*this);
		copy->id = ++idCounter;
		return copy;
	}
};

class TV : public Device {
private:
	std::string brand;
	std::string model;
public:
	TV() : Device("TV"), brand("Generic"), model("Standard") {} 

	void setConfig(std::string b, std::string m) { brand = b; model = m; }

	void reportStatus() const override {
		std::cout << "ID: " << id << " [TV] Brand: " << brand << ", Model: " << model << std::endl;
	}

	Device* clone() const override {
		TV* copy = new TV(*this);
		copy->id = ++idCounter;
		return copy;
	}
};


class Detector : public Device {
private:
	bool smokeSensor;
	bool gasSensor;
public:
	Detector() : Device("Detector"), smokeSensor(true), gasSensor(true) {} 

	void reportStatus() const override {
		std::cout << "ID: " << id << " [Detector] Smoke: " << (smokeSensor ? "ON" : "OFF")
			<< ", Gas: " << (gasSensor ? "ON" : "OFF") << std::endl;
	}

	void powerOff() override {
		//dev3 tarafýndan kullanýlacak
	}

	Device* clone() const override {
		Detector* copy = new Detector(*this);
		copy->id = ++idCounter;
		return copy;
	}
};

//abstract factory icin soyut arayuz
class DeviceFactory {
public:
	// factory methodlari
	virtual Device* createLight() = 0;
	virtual Device* createCamera() = 0;
	virtual Device* createDetector() = 0; 
	virtual Device* createTV() = 0;
	virtual ~DeviceFactory() {}
};

class StandardDeviceFactory : public DeviceFactory {
public:
	Device* createLight() override { return new Light(); }
	Device* createCamera() override { return new Camera(); }
	Device* createDetector() override { return new Detector(); }
	Device* createTV() override { return new TV(); }
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

	// istenilen cihaz bilgileri sorgusu
	void uiAddDevice() {
		int choice, quantity;
		std::cout << "\n--- Cihaz Ekle ---\n";
		std::cout << "1. Light\n2. Camera\n3. Detector (Smoke & Gas)\n4. TV\nSecim: ";
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
		default: std::cout << "Gecersiz secim.\n"; return;
		}

		if (!prototype) return;

		
		addDevice(prototype);

		// prototype pattern ile çoðaltma islemi
		for (int i = 1; i < quantity; ++i) {
			addDevice(prototype->clone());
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
		
	}
	void listDevices() {
		std::cout << "\n--- Cihaz Listesi ---\n";
		for (const auto& d : deviceList) {
			d->reportStatus();
		}
		std::cout << "---------------------\n";
	}

	std::vector<Device*>& getDevices() {
		return deviceList;
	}

	// istenilen cihazlarin kaldirilmasi
	void uiRemoveDevice() {
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
					delete d;
					return true;
				}
				return false;
			});

		if (it != deviceList.end()) {
			deviceList.erase(it, deviceList.end());
			std::cout << "Cihaz basariyla silindi.\n";
		}
		else {
			std::cout << "Cihaz bulunamadi.\n";
		}
	} 

};

int main() {
	DeviceManager manager;

	//cihaz ekleme islemi
	manager.uiAddDevice();

	// cihazlari listeleme
	manager.listDevices();

	// cihaz kaldirma islemi
	manager.uiRemoveDevice();

	manager.listDevices();

	std::cout << "\nTest tamamlandi. Cikmak icin Enter'a basin...";

	std::cin.ignore();
	std::cin.get();
	return 0;
}