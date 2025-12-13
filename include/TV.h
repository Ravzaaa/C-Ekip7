#ifndef TV_H
#define TV_H

#include "Device.h"
#include <string>

class TV : public Device {
private:
    int channel;
    int volume;

public:
    TV(const std::string& name, int channel = 1, int volume = 10);
    Device* clone() const override;

    void powerOn() override;
    void powerOff() override;
    void reportStatus() const override;

    void setChannel(int newChannel);
    void setVolume(int newVolume);
};

#endif
