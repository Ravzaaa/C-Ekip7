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
    std::cout << "\n--- ANA MENU ---" << std::endl;
    std::cout << "1. Sistem Durumu (State Info)" << std::endl;
    std::cout << "2. Cihaz Ekle" << std::endl;
    std::cout << "3. Cihaz Kaldir" << std::endl;
    std::cout << "4. Mod Secimi (Builder: Party, Cinema, Night)" << std::endl;
    std::cout << "5. Guvenlik Testi (Simulasyon)" << std::endl;
    std::cout << "6. Cihaz Listesi" << std::endl;
    std::cout << "7. Sistem Durumu Degistir (State: Sleep, Performance)" << std::endl;
    std::cout << "8. YARDIM / KILAVUZ" << std::endl;
    std::cout << "9. Geri Al (State - Undo)" << std::endl;
    std::cout << "10. CIKIS ve KAYDET" << std::endl;
    std::cout << "----------------" << std::endl;
}

void MSH::handleInput(int choice) {
    switch (choice) {
        case 1: 
            // Dev 4: State bilgilerini yazdır
            stateManager->applyRestrictions(); 
            break;
        case 2: 
            // Dev 2: Cihaz ekleme UI
            deviceManager->uiAddDevice(); 
            break;
        case 3: 
            // Dev 2: Cihaz silme UI
            deviceManager->uiRemoveDevice(); 
            break;
        case 4: {
            // Dev 5: Builder Mod Seçimi
            int m;
            std::cout << "Mod Seciniz (1:Normal, 2:Night, 3:Party, 4:Cinema): ";
            std::cin >> m;
            if (m == 1) modeDirector->changeMode(ModeType::Normal);
            else if (m == 2) modeDirector->constructEveningMode();
            else if (m == 3) modeDirector->constructPartyMode();
            else if (m == 4) modeDirector->constructCinemaMode();
            else std::cout << "Gecersiz Mod.\n";
            break;
        }
        case 5: {
            // Dev 6: Güvenlik Testi
            std::string incident;
            std::cout << "Simule edilecek olay (MOTION_DETECTED, SMOKE_DETECTED): ";
            std::cin >> incident;
            securityManager->handleEvent(incident);
            break;
        }
        case 6: 
            // Dev 2: Listeleme
            deviceManager->listDevices(); 
            break;
        case 7: {
            // Dev 4: State Değişimi
            int s;
            std::cout << "Durum Sec (0:Normal, 1:Performance, 2:Sleep): ";
            std::cin >> s;
            if(s==0) stateManager->setState(Normal);
            else if(s==1) stateManager->setState(HighPerformance);
            else if(s==2) stateManager->setState(Sleep);
            break;
        }
        case 8: {
            std::cout << "\n=======================================================\n";
            std::cout << "             MSH AKILLI EV SİSTEMİ KILAVUZU\n";
            std::cout << "=======================================================\n";
            std::cout << "Bu sistem, mimari gereksinimlere (LLR) uygun olarak, 7 gelistiricinin\n";
            std::cout << "modullerinin Singleton deseni (LLR 7.1) ile birlestirilmesiyle calismaktadir.\n";
            std::cout << "-------------------------------------------------------\n\n"; // Ekstra boş satır
            
            std::cout << "1. Sistem Durumu (Dev 4 - Memento):\n";
            std::cout << "   - Mevcut sistemin calisma durumunu (Normal, Sleep, Performans) ve bu duruma ait\n";
            std::cout << "     kisitlamalari raporlar (LLR 4.5).\n\n"; // Ekstra boş satır

            std::cout << "2. Cihaz Ekle (Dev 2 - Prototype/Abstract Factory):\n";
            std::cout << "   - Yeni cihaz tipini ve adedini sorar. Abstract Factory ile prototip olusturulur,\n";
            std::cout << "     Prototype deseni (clone) ile ayni tipteki cihazlar kopyalanir (LLR 2.4).\n";
            std::cout << "   - ID atamasi sistem tarafindan otomatik yapilir.\n\n"; // Ekstra boş satır

            std::cout << "3. Cihaz Kaldir (Dev 2 - Cihaz Yonetimi):\n";
            std::cout << "   - Mevcut cihaz listesini goruntuler ve kullanicidan silinecek cihazin ID'sini ister (LLR 2.5).\n\n"; // Ekstra boş satır

            std::cout << "4. Mod Secimi (Dev 5 - Builder Pattern):\n";
            std::cout << "   - Partymode, Cinemamode veya Eveningmode gibi 4 ana moddan birini aktif eder (LLR 5.1).\n";
            std::cout << "   - Modu olusturmak icin Builder deseni kullanilir (LLR 5.2-5.4).\n";
            std::cout << "   - Guvenlik cihazlari mod degisikliginden etkilenmez, her zaman acik kalir (LLR 5.5).\n\n"; // Ekstra boş satır
            
            std::cout << "5. Guvenlik Testi (Dev 6 - Chain of Responsibility/Observer):\n";
            std::cout << "   - Hareket (MOTION_DETECTED) veya Duman (SMOKE_DETECTED) gibi olaylari simule eder.\n";
            std::cout << "   - Olay, Chain of Responsibility deseni (Alarm -> Isik -> Polis/Itfaiye) uzerinden islenir (LLR 6.3, 6.4).\n\n"; // Ekstra boş satır

            std::cout << "6. Cihaz Listesi (Dev 2/3):\n";
            std::cout << "   - Sisteme ekli tum cihazlarin ID, Isim ve Durum (reportStatus) bilgilerini gosterir (LLR 3.5).\n\n"; // Ekstra boş satır

            std::cout << "7. Sistem Durumu Degistir (Dev 4 - State Yonetimi):\n";
            std::cout << "   - Sistemi Normal, Yuksek Performans veya Uyku durumlarindan birine alir (LLR 4.1).\n";
            std::cout << "   - Durum degisimi oncesinde Memento deseni ile anlik durum kaydedilir (LLR 4.2).\n\n"; // Ekstra boş satır

            std::cout << "9. Geri Al (Dev 4 - Memento Pattern):\n";
            std::cout << "   - Sistemin bir onceki calisma durumuna (State) geri donulmesini saglar (LLR 4.3).\n\n"; // Ekstra boş satır

            std::cout << "10. CIKIS ve KAYDET (Dev 1/7 - DataManager):\n";
            std::cout << "   - Sistemi kapatir. Kapatmadan once DataManager (LLR 1.3) ile son durumu (Aktif Mod, Cihaz Sayisi) ve Cihaz Listesini kaydeder (LLR 7.5).\n";
            std::cout << "=======================================================\n";
            break; 
        }
        case 9:
            // Dev 4: Geri Al (Memento)
            std::cout << "Eski duruma donuluyor...\n";
            stateManager->revertToPreviousState();
            stateManager->applyRestrictions();
            break;
        default: 
            std::cout << "Gecersiz secim!" << std::endl; 
            break;
    }
}