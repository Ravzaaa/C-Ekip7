#ifndef CAMERA_H
#define CAMERA_H

#include "Device.h"
#include <string>

class Camera : public Device {
private:
    int fps;
    bool nightVision;
    bool recording;

public:
    Camera(const std::string& name, int fps=30, bool nightVision=false);

    void powerOn() override;
    void powerOff() override;
    void reportStatus() const override;

    Device* clone() const override;

    void startRecording();
    void stopRecording();
};

#endif
