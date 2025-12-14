#pragma once

// LLR 5.2 - 5.5: Modlar ışık, TV ve müzik üzerinde değişiklik yapar.
// Kamera ve Dedektörler her zaman açık kalmalıdır (ensureSecurityDevicesOn).

class IDeviceController {
public:
    virtual ~IDeviceController() = default;

    // Işıkların güç durumunu ayarla
    virtual void setLights(bool on) = 0;

    // TV'nin güç durumunu ayarla
    virtual void setTV(bool on) = 0;

    // Müzik sisteminin güç durumunu ayarla
    virtual void setMusic(bool on) = 0;

    // Kamera ve Dedektörler HER ZAMAN açık kalmalı
    // ModeManager her mod değişiminde bunu çağırır (LLR 5.5)
    virtual void ensureSecurityDevicesOn() = 0;
};
