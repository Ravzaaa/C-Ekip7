#include <iostream>
#include "DeviceManager.h"

int main() {
	DeviceManager manager;

	// program acilinca eskilerin yuklenmesi
	manager.loadFromFile();

	// mevcut listeyi gorme
	manager.listDevices();

	manager.uiAddDevice();

	manager.listDevices();

	manager.uiRemoveDevice();

	// program kapanmadan once son halinin kaydedilmesi
	manager.saveToFile();

	std::cout << "\nTest tamamlandi. Cikis yapiliyor...";

	return 0;
	
}