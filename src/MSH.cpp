#include "MSH.h"
#include <iostream>

// --- MSH ctor: default Normal (LLR 4.4) ---
MSH::MSH() : currentState(State::Normal) {}

// --- getters ---
State MSH::getCurrentState() const {
    return currentState;
}

// --- snapshot handling (LLR 4.2) ---
Snapshot MSH::saveSnapshot() const {
    return Snapshot(currentState);
}

void MSH::restoreSnapshot(const Snapshot& s) {
    currentState = s.getSavedState();
    applyRestrictions();
}

// --- state change (LLR 4.2 + LLR 4.5) ---
void MSH::setState(State s) {
    // Save BEFORE changing (Memento)
    history.push(saveSnapshot());
    currentState = s;
    applyRestrictions();
}

// --- revert (LLR 4.3) ---
void MSH::revertToPreviousState() {
    if (history.empty()) {
        std::cout << "[MSH] No previous state." << std::endl;
        return;
    }
    Snapshot prev = history.pop();
    restoreSnapshot(prev);
}

// --- restrictions/log (LLR 4.5) ---
void MSH::applyRestrictions() const {
    std::cout << "[MSH] DURUM RAPORU\n";
    switch (currentState) {
        case State::Normal:
            std::cout << "[DURUM] Normal Mod\n";
            std::cout << "[ACIKLAMA] Standart calisma: temel islevler aktif.\n";
            std::cout << "[KISITLAR]\n";
            std::cout << " - Yok (standart mod)\n";
            std::cout << "[ACIK KALANLAR]\n";
            std::cout << " - Tum kullanici islemleri\n";
            std::cout << " - Cihazlar normal calisir\n";
            break;
        case State::HighPerformance:
            std::cout << "[DURUM] Yuksek Performans Modu\n";
            std::cout << "[ACIKLAMA] Performans oncelikli: kaynak kullanimi artar.\n";
            std::cout << "[KISITLAR]\n";
            std::cout << " - Enerji tasarrufu azaltildi / devre disi\n";
            std::cout << " - Arka plan optimizasyonlari kapatildi\n";
            std::cout << "[ACIK KALANLAR]\n";
            std::cout << " - Tum kullanici islemleri\n";
            std::cout << " - Sistem maksimum performansta\n";
            break;
        case State::Sleep:
            std::cout << "[DURUM] Uyku (Sleep) Modu\n";
            std::cout << "[ACIKLAMA] Enerji tasarrufu: kritik olmayan islevler kisitlanir.\n";

            std::cout << "[KISITLAR]\n";
            std::cout << " - Isiklar: KAPAT (simulasyon)\n";
            std::cout << " - TV / Medya: KAPAT (simulasyon)\n";
            std::cout << " - Agir islemler: DURDUR / ertele\n";
            std::cout << " - Kullanici etkilesimi: SINIRLI (durum goruntule + uyandir)\n";

            std::cout << "[ACIK KALANLAR]\n";
            std::cout << " - Kritik servisler (ornek: sensorler)\n";
            std::cout << " - Uyandir (Wake-up) islemleri\n";
            break;
        default:
            std::cout << "[DURUM] Bilinmeyen durum!\n";
            break;
    }
}
