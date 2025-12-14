#include "ModeDirector.h"
#include <iostream>



ModeDirector::ModeDirector(IDeviceController& deviceController)
    : deviceController(deviceController),
      currentMode(ModeType::Normal),
      currentConfig{} {
}

void ModeDirector::initDefaultMode() {
    changeMode(ModeType::Normal);
}

void ModeDirector::setBuilder(IModeBuilder* b) {
    externalBuilder = b;
}

// UML'deki isimler, içeride changeMode kullanıyoruz
void ModeDirector::constructPartyMode() {
    changeMode(ModeType::Party);
}

void ModeDirector::constructCinemaMode() {
    changeMode(ModeType::Cinema);
}

void ModeDirector::constructEveningMode() {
    changeMode(ModeType::Night);
}

// Asıl iş burada: uygun builder'ı seç, ModeConfig üret, cihazlara uygula
void ModeDirector::changeMode(ModeType newMode) {
    std::unique_ptr<IModeBuilder> localBuilder;

    if (externalBuilder == nullptr) {
        // Kendi builder'ımızı üret
        localBuilder = createBuilder(newMode);
        if (!localBuilder) {
            std::cerr << "[ModeDirector] Uyarı: Desteklenmeyen mod!" << std::endl;
            return;
        }
    }

    IModeBuilder* builderToUse = externalBuilder ? externalBuilder : localBuilder.get();

    builderToUse->reset();
    builderToUse->buildLights();
    builderToUse->buildTV();
    builderToUse->buildMusic();

    ModeConfig config = builderToUse->getResult();

    applyConfig(config);

    currentMode = newMode;
    currentConfig = config;

    // Rapor amaçlı:
    // currentConfig.showSettings();
}

// Mod tipine göre uygun concrete builder'ı üret
std::unique_ptr<IModeBuilder> ModeDirector::createBuilder(ModeType mode) const {
    switch (mode) {
        case ModeType::Normal:
            return std::make_unique<NormalModeBuilder>();
        case ModeType::Night:
            return std::make_unique<NightModeBuilder>();
        case ModeType::Party:
            return std::make_unique<PartyModeBuilder>();
        case ModeType::Cinema:
            return std::make_unique<CinemaModeBuilder>();
        default:
            return nullptr;
    }
}

// ModeConfig'i gerçek cihazlara uygula (LLR 5.2–5.5)
void ModeDirector::applyConfig(const ModeConfig& config) {
    deviceController.setLights(config.lightState);
    deviceController.setTV(config.tvState);
    deviceController.setMusic(config.musicState);

    // LLR 5.5: Kamera ve Dedektörler her zaman açık
    deviceController.ensureSecurityDevicesOn();
}
