#pragma once

#include "ModeTypes.h"

// UML'deki IModeBuilder arayüzü
class IModeBuilder {
public:
    virtual ~IModeBuilder() = default;

    virtual void reset() = 0;
    virtual void buildLights() = 0;
    virtual void buildTV() = 0;
    virtual void buildMusic() = 0;

    virtual ModeConfig getResult() const = 0;
};

// ---- Normal Mode Builder ----
// Varsayım: Normal modda sadece ışıklar ON, TV ve müzik OFF.
class NormalModeBuilder : public IModeBuilder {
public:
    NormalModeBuilder();

    void reset() override;
    void buildLights() override;
    void buildTV() override;
    void buildMusic() override;
    ModeConfig getResult() const override;

private:
    ModeConfig config;
};

// ---- Night (Evening) Mode Builder ----
// LLR 5.4: Evening (Gece) modunda hepsi kapalı
class NightModeBuilder : public IModeBuilder {
public:
    NightModeBuilder();

    void reset() override;
    void buildLights() override;
    void buildTV() override;
    void buildMusic() override;
    ModeConfig getResult() const override;

private:
    ModeConfig config;
};

// ---- Party Mode Builder ----
// LLR 5.2: ışıklar ON, TV OFF, müzik ON
class PartyModeBuilder : public IModeBuilder {
public:
    PartyModeBuilder();

    void reset() override;
    void buildLights() override;
    void buildTV() override;
    void buildMusic() override;
    ModeConfig getResult() const override;

private:
    ModeConfig config;
};

// ---- Cinema Mode Builder ----
// LLR 5.3: ışıklar OFF, TV ON, müzik OFF
class CinemaModeBuilder : public IModeBuilder {
public:
    CinemaModeBuilder();

    void reset() override;
    void buildLights() override;
    void buildTV() override;
    void buildMusic() override;
    ModeConfig getResult() const override;

private:
    ModeConfig config;
};
