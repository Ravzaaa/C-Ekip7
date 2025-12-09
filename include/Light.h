#ifndef LIGHT_H
#define LIGHT_H

#include "Device.h"
#include <string>

class Light : public Device {
private:
    std::string color;
    int brightness;

public:
    Light(const std::string& name,
          const std::string& color = "Beyaz",
          int brightness = 100);

    void powerOn() override;
    void powerOff() override;
    void reportStatus() const override;

    void setColor(const std::string& newColor);
    void setBrightness(int newBrightness);
};

#endif
