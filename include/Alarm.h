#ifndef ALARM_H
#define ALARM_H

#include "Device.h"
#include <string>

class Alarm : public Device {
public:
    explicit Alarm(const std::string& name);

    void powerOn() override;
    void powerOff() override;      // KAPANMASI REDDEDİLECEK
    void reportStatus() const override;

    Device* clone() const override;
    
};

#endif
