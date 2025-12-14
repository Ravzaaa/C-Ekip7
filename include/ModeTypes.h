#pragma once
#include <string>
#include <iostream>

// Hâlâ LLR 5.1’e uygun 4 mod türümüz var
enum class ModeType {
    Normal,
    Night,
    Party,
    Cinema
};

// UML'deki ModeConfig'e göre tasarlanan sınıf
class ModeConfig {
public:
    std::string modeName;   // UML: modeName
    bool lightState{false}; // UML: lightState
    bool tvState{false};    // UML: tvState
    bool musicState{false}; // UML: musicState

    void setLights(bool state) { lightState = state; }
    void setTV(bool state)     { tvState = state; }
    void setMusic(bool state)  { musicState = state; }

    void showSettings() const {
        std::cout << "Mode: " << modeName << "\n";
        std::cout << "  Lights: " << (lightState ? "ON" : "OFF") << "\n";
        std::cout << "  TV: "     << (tvState    ? "ON" : "OFF") << "\n";
        std::cout << "  Music: "  << (musicState ? "ON" : "OFF") << "\n";
    }
};
