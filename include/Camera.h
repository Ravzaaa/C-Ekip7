#ifndef CAMERA_H
#define CAMERA_H

#include "Device.h"
#include <string>

class Camera : public Device {
private:
    bool recording;

public:
    Camera(const std::string& name);

    void powerOn() override;
    void powerOff() override;
    void reportStatus() const override;

    Device* clone() const override;

    void startRecording();
    void stopRecording();
};

#endif
