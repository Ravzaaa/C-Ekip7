#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
protected:
    std::string name;
    bool isPoweredOn;

public:
    Device(const std::string& name);
    virtual ~Device();

    virtual void powerOn();
    virtual void powerOff();
    virtual void reportStatus() const = 0;
};

#endif
