
#ifndef GAS_DETECTOR_H
#define GAS_DETECTOR_H

#include "Device.h"
#include <string>

class GasDetector : public Device {

private:
    bool gasDetected_;
public:
    explicit GasDetector(const std::string& name);

    virtual void powerOff() override;           // kritik cihaz: kapatma reddi
    virtual void powerOn() override;
    virtual void reportStatus() const override;

    void detectGas(bool state);    
    
    Device* clone() const override; 
};

#endif
