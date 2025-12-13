#include "DeviceFactory.h" 
#include "Light.h"
#include "Camera.h"
#include "Detector.h"
#include "TV.h"
#include "Alarm.h"

Device* StandardDeviceFactory::createLight() {
    return new Light("Light", "White", 100);
}

Device* StandardDeviceFactory::createCamera() {
    return new Camera("Camera", 30, false);
}

Device* StandardDeviceFactory::createDetector() {
    return new Detector("Detector", true, true);
}

Device* StandardDeviceFactory::createTV() {
    return new TV("TV", "Generic", "Standard", 1, 10);
}

Device* StandardDeviceFactory::createAlarm() {
    return new Alarm("Alarm");
}