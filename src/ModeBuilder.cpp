#include "ModeBuilder.h"

// -------- NormalModeBuilder --------
NormalModeBuilder::NormalModeBuilder() {
    reset();
}

void NormalModeBuilder::reset() {
    config = ModeConfig{};
    config.modeName = "Normal";
}

void NormalModeBuilder::buildLights() {
    config.setLights(true);   // Normal: ışıklar açık
}

void NormalModeBuilder::buildTV() {
    config.setTV(false);      // TV kapalı
}

void NormalModeBuilder::buildMusic() {
    config.setMusic(false);   // Müzik kapalı
}

ModeConfig NormalModeBuilder::getResult() const {
    return config;
}

// -------- NightModeBuilder --------
NightModeBuilder::NightModeBuilder() {
    reset();
}

void NightModeBuilder::reset() {
    config = ModeConfig{};
    config.modeName = "Night";
}

void NightModeBuilder::buildLights() {
    config.setLights(false);
}

void NightModeBuilder::buildTV() {
    config.setTV(false);
}

void NightModeBuilder::buildMusic() {
    config.setMusic(false);
}

ModeConfig NightModeBuilder::getResult() const {
    return config;
}

// -------- PartyModeBuilder --------
PartyModeBuilder::PartyModeBuilder() {
    reset();
}

void PartyModeBuilder::reset() {
    config = ModeConfig{};
    config.modeName = "Party";
}

void PartyModeBuilder::buildLights() {
    config.setLights(true);
}

void PartyModeBuilder::buildTV() {
    config.setTV(false);
}

void PartyModeBuilder::buildMusic() {
    config.setMusic(true);
}

ModeConfig PartyModeBuilder::getResult() const {
    return config;
}

// -------- CinemaModeBuilder --------
CinemaModeBuilder::CinemaModeBuilder() {
    reset();
}

void CinemaModeBuilder::reset() {
    config = ModeConfig{};
    config.modeName = "Cinema";
}

void CinemaModeBuilder::buildLights() {
    config.setLights(false);
}

void CinemaModeBuilder::buildTV() {
    config.setTV(true);
}

void CinemaModeBuilder::buildMusic() {
    config.setMusic(false);
}

ModeConfig CinemaModeBuilder::getResult() const {
    return config;
}
