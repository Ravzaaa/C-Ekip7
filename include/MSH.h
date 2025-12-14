#ifndef MSH_H
#define MSH_H

#include <iostream>
#include <string>
#include <memory> // unique_ptr icin gerekebilir

// --- DİĞER GELİŞTİRİCİLERİN DOSYALARI (Include Ediyoruz) ---
#include "DataManager.h"      // Dev 1
#include "DeviceManager.h"    // Dev 2
// Not: Dev 3 (Device hiyerarşisi) zaten DeviceManager icinde var.
#include "ModeManager.h"      // Dev 4 (State / Memento - Durum Yönetimi)
#include "ModeDirector.h"     // Dev 5 (Builder - Mod Yönetimi)
#include "SecurityManager.h"  // Dev 6 (Observer / Chain - Güvenlik)
#include "IDeviceController.h" // Dev 5 entegrasyonu için arayüz

// --- Geliştirici 7: Entegrasyon ve Menü Arayüzü ---
// LLR 7.1: Singleton Pattern
class MSH {
private:
    static MSH* instance;

    // Alt Yöneticiler (Pointer olarak tutuyoruz)
    DataManager* dataManager;         // Dev 1
    DeviceManager* deviceManager;     // Dev 2
    ModeManager* stateManager;        // Dev 4 (İsmi ModeManager ama State yönetiyor)
    ModeDirector* modeDirector;       // Dev 5 (Builder yapısı)
    SecurityManager* securityManager; // Dev 6

    // Dev 5'in Modları cihazlara uygulayabilmesi için bir ara katman
    IDeviceController* deviceControllerBridge; 

    // Private Constructor
    MSH();

public:
    // Global Erişim (LLR 7.1)
    static MSH* getInstance();

    // Sistemi Başlatma (LLR 7.6)
    void initSystem();

    // Menü İşlemleri (LLR 7.2)
    void showMenu();
    void handleInput(int choice); // LLR 7.3

    // Yardımcı Entegrasyon Fonksiyonları
    DeviceManager* getDeviceManager() const { return deviceManager; }
};

#endif // MSH_H