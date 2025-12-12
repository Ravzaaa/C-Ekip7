#pragma once
#include "Observer.h"

// NOT: Dev 3'ten Device.h gelince buraya #include "Device.h" ekleyecegiz
// ve class'lari "public Device, public Subject" yapacagiz.

class Camera : public Subject {
public:
    void detectMotion() {
        // LLR 6.3
        notify("MOTION_DETECTED");
    }
};

class Detector : public Subject {
public:
    void detectSmoke() {
        // LLR 6.4
        notify("SMOKE_DETECTED");
    }
    void detectGas() {
        notify("GAS_DETECTED");
    }
};