#include "../include/MSH.h"
#include "../include/Logger.h" // Dev 1 Logger
#include <limits> // cin.ignore icin

// --- BRIDGE CLASS (Dev 5 ve Dev 2 Entegrasyonu) ---
// ModeDirector (Dev 5), ışıkları açıp kapatmak için bir kontrolcü ister.
// Biz bu emirleri alıp DeviceManager'daki (Dev 2) cihazlara ileteceğiz.
class SystemDeviceController : public IDeviceController {
private:
    DeviceManager* manager;
public:
    SystemDeviceController(DeviceManager* m) : manager(m) {}

    void setLights(bool on) override {
        // DeviceManager listesindeki tüm Light objelerini bul ve durumu ayarla
        auto& devices = manager->getDevices();
        for (auto* d : devices) {
            if (d->getName() == "Light") { // İsim kontrolü veya dynamic_cast yapılabilir
                if (on) d->powerOn(); else d->powerOff();
            }
        }
    }

    void setTV(bool on) override {
        auto& devices = manager->getDevices();
        for (auto* d : devices) {
            if (d->getName() == "TV") {
                if (on) d->powerOn(); else d->powerOff();
            }
        }
    }

    void setMusic(bool on) override {
        // Müzik sistemi henüz cihaz listesinde olmayabilir ama altyapı bu şekildedir.
        std::cout << "[SystemController] Muzik sistemi durumu: " << (on ? "ACIK" : "KAPALI") << "\n";
    }

    void ensureSecurityDevicesOn() override {
        // LLR 5.5: Kamera ve Dedektörler her zaman açık kalmalı
        auto& devices = manager->getDevices();
        for (auto* d : devices) {
            if (d->getName() == "Camera" || d->getName() == "Detector" || d->getName() == "Alarm") {
                if (!d->getPowerStatus()) {
                    d->powerOn(); 
                }
            }
        }
    }
};

// --- SINGLETON IMPLEMENTATION ---
MSH* MSH::instance = nullptr;

MSH::MSH() {
    // 1. Önce Veri Yöneticisi ve Logger (Dev 1)
    dataManager = new DataManager();
    // Logger zaten Singleton, burada çağırmaya gerek yok ama log atabiliriz.
    
    // 2. Cihaz Yöneticisi (Dev 2)
    deviceManager = new DeviceManager();

    // 3. Durum (State) Yöneticisi (Dev 4)
    stateManager = new ModeManager(); // Dosya adı ModeManager ama işlevi StateManager

    // 4. Mod (Builder) Yöneticisi (Dev 5)
    // Önce köprüyü kuruyoruz
    deviceControllerBridge = new SystemDeviceController(deviceManager);
    modeDirector = new ModeDirector(*deviceControllerBridge);

    // 5. Güvenlik Yöneticisi (Dev 6)
    securityManager = new SecurityManager();
}

MSH* MSH::getInstance() {
    if (instance == nullptr) {
        instance = new MSH();
    }
    return instance;
}

// LLR 7.6: initSystem - Tüm modüllerin birleştiği ana akış
void MSH::initSystem() {
    if (Logger::getInstance()) Logger::getInstance()->log("Sistem baslatiliyor (initSystem)...");

    // LLR 1.4: Başlangıçta eski verileri yükle
    std::string savedMode = "Normal";
    int savedDeviceCount = 0;
    dataManager->loadState(savedMode, savedDeviceCount);
    
    // Eski cihazları dosyadan yükle (Dev 2 özelliği)
    deviceManager->loadFromFile();

    // Varsayılan Modu Başlat (LLR 5.6)
    modeDirector->initDefaultMode();

    std::cout << "\n=== MSH AKILLI EV SISTEMINE HOS GELDINIZ ===" << std::endl;
    
    bool isRunning = true;
    int choice;

    while (isRunning) {
        showMenu(); // LLR 7.2
        std::cout << "Seciminiz: ";
        
        // LLR 7.3: Hatalı girdi kontrolü
        if (!(std::cin >> choice)) {
            std::cout << "HATA: Lutfen gecerli bir sayi giriniz!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // LLR 7.5: Çıkış ve Kayıt
        if (choice == 10) {
            std::cout << "Sistem kapaniyor ve son durum kaydediliyor..." << std::endl;
            
            // Şu anki aktif modu al (Builder veya State tarafından)
            // Basitlik adına StateManager'dan durumu alıyoruz
            std::string currentS = "Normal"; // Enum to string dönüşümü gerekebilir
            
            // Verileri kaydet
            dataManager->saveState(currentS, deviceManager->getDevices().size());
            deviceManager->saveToFile(); // Cihaz listesini de kaydet

            if (Logger::getInstance()) Logger::getInstance()->closeLog();
            isRunning = false;
        } else {
            handleInput(choice);
        }
    }
}

void MSH::showMenu() {
    std::cout << "\n--- MY SWEET HOME (MSH) ANA MENU ---" << std::endl;
    std::cout << "[1] Get Home Status (Durum Goster)" << std::endl;
    std::cout << "[2] Add Device (Cihaz Ekle)" << std::endl;
    std::cout << "[3] Remove Device (Cihaz Kaldir)" << std::endl;
    std::cout << "[4] Power ON Device (Cihaz Ac - Manuel)" << std::endl; // YENİ
    std::cout << "[5] Power OFF Device (Cihaz Kapat - Manuel)" << std::endl; // YENİ
    std::cout << "[6] Change Mode (Mod Degistir)" << std::endl;
    std::cout << "[7] Change State (Durum Degistir / Undo)" << std::endl;
    std::cout << "[8] Manual (Kullanim Kilavuzu)" << std::endl;
    std::cout << "[9] About (Hakkinda)" << std::endl;
    std::cout << "[10] Shutdown (Kapat)" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    // Not: Güvenlik Testi (Senaryo 25-27) için gizli seçenek: 11
}

// Girdi İşleme
void MSH::handleInput(int choice) {
    switch (choice) {
        case 1: 
            // PDF Step 4, 12, 16...
            stateManager->applyRestrictions(); // Durum ve kısıtlar
            deviceManager->listDevices();      // Cihaz listesi
            break;
        case 2: 
            // PDF Step 5, 8, 9, 10
            deviceManager->uiAddDevice(); 
            break;
        case 3: 
            // PDF Step 13, 15
            deviceManager->uiRemoveDevice(); 
            break;
        case 4: 
            // PDF Step 31: Power On Device
            deviceManager->uiPowerOnDevice();
            break;
        case 5: 
            // PDF Step 28: Power Off Device
            deviceManager->uiPowerOffDevice();
            break;
        case 6: {
            // PDF Step 17, 19: Change Mode (Harf/Sayı Girdisine Uyumlu)
            char m;
            std::cout << "Mod Seciniz [(N)ormal, (E)vening, (P)arty, (C)inema]: ";
            
            // Harfli girdiyi alıyoruz
            std::cin >> m;
            
            // Büyük/küçük harf kontrolü yapıyoruz
            if (m == 'N' || m == 'n') {
                modeDirector->changeMode(ModeType::Normal);
            }
            else if (m == 'E' || m == 'e') {
                modeDirector->constructEveningMode();
            }
            else if (m == 'P' || m == 'p') {
                modeDirector->constructPartyMode();
            }
            else if (m == 'C' || m == 'c') {
                modeDirector->constructCinemaMode();
            }
            else {
                std::cout << "Gecersiz Mod secimi. Lutfen N, E, P veya C giriniz.\n";
            }
            break;
        }
        case 7: {
            // PDF Step 21, 23: Change State & Previous One
            char s;
            std::cout << "Durum Sec [(N)ormal, (H)igh Performance, (S)leep, (P)revious]: ";
            std::cin >> s;
            if (s == 'N' || s == 'n') stateManager->setState(Normal);
            else if (s == 'H' || s == 'h') stateManager->setState(HighPerformance);
            else if (s == 'S' || s == 's') stateManager->setState(Sleep);
            else if (s == 'P' || s == 'p') {
                std::cout << "Onceki duruma donuluyor...\n";
                stateManager->revertToPreviousState();
            }
            else std::cout << "Gecersiz Durum.\n";
            break;
        }
        case 8: { // KULLANIM KILAVUZU (MANUAL)
            std::cout << "\n=======================================================\n";
            std::cout << "             MSH AKILLI EV SİSTEMİ KILAVUZU\n";
            std::cout << "=======================================================\n";
            std::cout << "Bu sistem, mimari gereksinimlere (LLR) uygun olarak, 7 gelistiricinin\n";
            std::cout << "modullerinin Singleton deseni (LLR 7.1) ile birlestirilmesiyle calismaktadir.\n";
            std::cout << "-------------------------------------------------------\n\n";

            std::cout << "1. Sistem Durumu (Dev 4 - Memento):\n";
            std::cout << "   - Mevcut sistemin calisma durumunu ve kisitlamalari raporlar (LLR 4.5).\n\n";

            std::cout << "2. Cihaz Ekle (Dev 2 - Prototype/Abstract Factory):\n";
            std::cout << "   - Yeni cihaz tipini ve adedini sorar. Prototype deseni (clone) ile\n";
            std::cout << "     ayni tipteki cihazlar kopyalanir (LLR 2.4).\n\n";

            std::cout << "3. Cihaz Kaldir (Dev 2 - Cihaz Yonetimi):\n";
            std::cout << "   - Silinecek cihazin ID'si istenerek kaldirilir (LLR 2.5).\n\n";

            std::cout << "4. & 5. Cihaz Ac/Kapat (Dev 3 - Cihaz Kontrolu):\n";
            std::cout << "   - Secilen cihazi manuel olarak acar veya kapatir (REQ 6).\n";
            std::cout << "   - Kritik cihazlar (Alarm/Dedektor) kapatilamaz (LLR 3.3).\n\n";

            std::cout << "6. Mod Secimi (Dev 5 - Builder Pattern):\n";
            std::cout << "   - Party, Cinema, Night modlarindan biri Builder deseniyle kurulur (LLR 5.1).\n";
            std::cout << "   - Guvenlik cihazlari mod degisikliginden etkilenmez (LLR 5.5).\n\n";

            std::cout << "7. Sistem Durumu Degistir (Dev 4 - State Yonetimi):\n";
            std::cout << "   - Normal, Sleep, Performans durumlari arasinda gecis yapilir.\n";
            std::cout << "   - 'Previous' secenegi ile Memento deseni kullanilarak Geri Alinir (LLR 4.3).\n\n";

            std::cout << "9. Hakkinda (About):\n";
            std::cout << "   - Gelistirici ekip ve proje bilgilerini gosterir.\n\n";

            std::cout << "10. CIKIS ve KAYDET (Dev 1/7 - DataManager):\n";
            std::cout << "   - Sistemi kapatir ve DataManager ile son durumu kaydeder (LLR 7.5).\n";
            
            std::cout << "Not: Guvenlik Simulasyonu (Dev 6) icin gizli secenek 11 kullanilabilir.\n";
            std::cout << "=======================================================\n";
            break; 
        }

        case 9: { // HAKKINDA (ABOUT)
            std::cout << "\n=======================================================\n";
            std::cout << "                  HAKKINDA (ABOUT)\n";
            std::cout << "=======================================================\n";
            std::cout << "PROJE ADI: My Sweet Home (MSH) Akilli Ev Sistemi\n";
            std::cout << "DERS     : BIL464 Design Patterns with C++\n";
            std::cout << "DONEM    : Guz 2025\n";
            std::cout << "-------------------------------------------------------\n";
            std::cout << "GELISTIRICI EKIP (GRUP 7):\n\n";
            std::cout << "Dev 1: ILAYDA KAHRAMAN      (Veri Yonetimi & Singleton)\n";
            std::cout << "Dev 2: ELIF BETUL OZCELIK   (Cihaz Yonetimi & Prototype)\n";
            std::cout << "Dev 3: ZEHRA NUREFSAN SAL   (Cihaz Uygulamalari & Factory)\n";
            std::cout << "Dev 4: PELIN KESKIN         (Durum Yonetimi & Memento)\n";
            std::cout << "Dev 5: CANAN INAL           (Mod Yonetimi & Builder)\n";
            std::cout << "Dev 6: AZRA BAYRAM          (Guvenlik & Chain of Resp.)\n";
            std::cout << "Dev 7: RAVZA KUSULAY        (Entegrasyon & Mediator/Facade)\n";
            std::cout << "=======================================================\n";
            break;
        }
        case 11: // Gizli Seçenek: Güvenlik Testi (Senaryoları çalıştırmak için)
            {
                std::string incident;
                std::cout << "[SIMULASYON] Olay Tetikle (MOTION_DETECTED / SMOKE_DETECTED): ";
                std::cin >> incident;
                securityManager->handleEvent(incident);
            }
            break;
        default: 
            std::cout << "Gecersiz secim!" << std::endl; 
            break;
    }
}