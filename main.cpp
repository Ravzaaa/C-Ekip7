#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <memory>    


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



int main() {
	

	return 0;
}
