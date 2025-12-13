#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
protected:
    int id;
    std::string name;
    bool isPoweredOn;
    bool isActive;

public:
    Device(const std::string& name);
    virtual ~Device()= default;

    int getId() const;
    void setId(int newId);
    
    std::string getName() const;
    bool getPowerStatus() const;
    bool getActiveStatus() const;

    virtual void setActive(bool state);

    virtual void powerOn() =0;
    virtual void powerOff() =0;
    virtual void reportStatus() const = 0;

    virtual bool isCritical() const { return false; }

    virtual Device* clone() const = 0;
};

#endif
