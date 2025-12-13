#ifndef TV_H
#define TV_H

#include "Device.h"
#include <string>

class TV : public Device {
private:
    int channel;
    int volume;
    std::string brand;
    std::string model;

public:
    TV(const std::string& name, const std::string &brand, const std::string &model,  int channel = 1, int volume = 10);
    Device* clone() const override;

    void powerOn() override;
    void powerOff() override;
    void reportStatus() const override;

    void setChannel(int newChannel);
    void setVolume(int newVolume);
};

#endif
