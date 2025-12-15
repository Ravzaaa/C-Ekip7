#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <vector>
#include <string>
#include "Device.h"
#include "DeviceFactory.h"

//yonetici sinif
class DeviceManager {
private:
    std::vector<Device*> deviceList;
    DeviceFactory* factory;

public:
    DeviceManager();
    ~DeviceManager();

    void clearScreen();
    void uiAddDevice();
    void addDevice(Device* d);
    void listDevices();
    void uiPowerOnDevice();  // Menü 4 için
    void uiPowerOffDevice(); // Menü 5 için

    std::vector<Device*>& getDevices();

    void uiRemoveDevice();
    void removeDevice(int id);

    void saveToFile();
    void loadFromFile();
};

#endif