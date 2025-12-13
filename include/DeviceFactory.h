#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include "Device.h"

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
    Device* createLight() override;
    Device* createCamera() override;
    Device* createDetector() override;
    Device* createTV() override;
    Device* createAlarm() override;
};

#endif