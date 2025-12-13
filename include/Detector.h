#ifndef DETECTOR_H
#define DETECTOR_H

#include "Device.h"
#include <string>

class Detector : public Device {
private:
    bool gasSensor;        
    bool smokeSensor;     

    bool gasDetected;     
    bool smokeDetected;    

public:
    Detector(const std::string& name,
             bool gasSensor = true,
             bool smokeSensor = true);

    // Kritik cihaz davranışı
    void powerOn() override;
    void powerOff() override;        // KAPANMASI REDDEDİLECEK
    void reportStatus() const override;


    void detectGas(bool state);
    void detectSmoke(bool state);

    Device* clone() const override;
};

#endif
