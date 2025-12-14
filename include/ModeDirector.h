#pragma once

#include <memory>
#include "ModeTypes.h"
#include "ModeBuilder.h"
#include "IDeviceController.h"

// UML: ModeDirector
// Burada ModeDirector, IModeBuilder kullanarak farklı modları kuruyor.
class ModeDirector {
public:
    explicit ModeDirector(IDeviceController& deviceController);

    // Sistem açılışında NormalMode'a geç (LLR 5.6)
    void initDefaultMode();

    // Genel amaçlı: ModeType ile mod değiştir
    void changeMode(ModeType newMode);

    // UML diyagramındaki fonksiyon isimleri:
    void setBuilder(IModeBuilder* b);   // UML'de var, biz zorunlu kullanmıyoruz
    void constructPartyMode();          // PartyMode
    void constructCinemaMode();         // CinemaMode
    void constructEveningMode();        // Night (Evening) Mode

    ModeType getCurrentMode() const { return currentMode; }
    ModeConfig getCurrentConfig() const { return currentConfig; }

private:
    IDeviceController& deviceController;
    ModeType currentMode;
    ModeConfig currentConfig;

    IModeBuilder* externalBuilder{nullptr}; 

    std::unique_ptr<IModeBuilder> createBuilder(ModeType mode) const;
    void applyConfig(const ModeConfig& config);
};
