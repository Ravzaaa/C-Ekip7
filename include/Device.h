#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <string>

class Device {
protected:
    static int idCounter; 
    int id;
    std::string name;
    std::string status;
    bool isActive;

public:
    Device(std::string n);
    virtual ~Device();

    int getId() const;
    std::string getName() const;

    virtual void setActive(bool state);
    virtual void powerOn();
    virtual void powerOff();

    virtual void reportStatus() const;

    virtual Device* clone() const = 0;
};

#endif

