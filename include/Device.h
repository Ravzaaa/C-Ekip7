#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
protected:
    int id;
    static int idCounter;
    std::string name;
    std::string status;
    bool isPoweredOn;
    bool isActive;

public:
    Device(const std::string& name);
    virtual ~Device()= default;

    int getId() const;
    void setId(int newId);

    void loadId(int savedId);
    
    std::string getName() const;
    std::string getStatus() const;
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
