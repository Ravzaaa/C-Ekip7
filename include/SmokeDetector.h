
#ifndef SMOKE_DETECTOR_H
#define SMOKE_DETECTOR_H

#include "Device.h"
#include <string>

class SmokeDetector : public Device {

private:
    bool smokeDetected_;

public:
    explicit SmokeDetector(const std::string& name);

    virtual void powerOff() override;           // kritik cihaz: kapatma reddi
    virtual void powerOn() override;
    virtual void reportStatus() const override; 

    void detectSmoke(bool state);     

    Device* clone() const override;

};

#endif 

