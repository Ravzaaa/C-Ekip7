#ifndef MSH_H
#define MSH_H

#include <iostream>
#include <string>

// --- DUMMY SINIFLAR (Test İçin Gerekli) ---
// Diğer arkadaşların henüz kodlarını yazmadığı için,
// senin kodun hata vermesin diye bu boş kutuları kullanıyoruz.
class StateManager { public: void setState(int s){} void revertToPreviousState(){} };
class ModeManager { public: void setMode(int m){} };
class DeviceManager { public: void addDevice(){} void removeDevice(int id){} void listDevices(){} };
class DataManager { public: void saveState(){} void loadState(){} };
class SecurityManager { public: void enableSecurity(){} void disableSecurity(){} };

// --- SENİN GÖREVİN: Singleton MSH Sınıfı ---
class MSH {
private:
    static MSH* instance; // Tekil nesne

    // Alt yöneticiler
    StateManager* stateManager;
    ModeManager* modeManager;
    DeviceManager* deviceManager;
    DataManager* dataManager;
    SecurityManager* securityManager;

    // Private Constructor (Dışarıdan nesne oluşturulamaz)
    MSH();

public:
    // Global erişim noktası
    static MSH* getInstance();

    // Sistemi başlatan fonksiyon
    void initSystem();

    // Menüyü gösteren fonksiyon
    void showMenu();

    // Kullanıcı seçimini işleyen fonksiyon
    void handleInput(int choice);
};

#endif // MSH_H