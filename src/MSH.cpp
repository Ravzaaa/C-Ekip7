#include "../include/MSH.h"

// Singleton örneğini boş başlat
MSH* MSH::instance = nullptr;

// Kurucu Fonksiyon: Alt sistemleri oluşturur
MSH::MSH() {
    stateManager = new StateManager();
    modeManager = new ModeManager();
    deviceManager = new DeviceManager();
    dataManager = new DataManager();
    securityManager = new SecurityManager();
}

// Singleton Erişim Fonksiyonu (LLR 7.1)
MSH* MSH::getInstance() {
    if (instance == nullptr) {
        instance = new MSH();
    }
    return instance;
}

// Ana Sistem Döngüsü (LLR 7.6)
void MSH::initSystem() {
    std::cout << "\n=== MSH AKILLI EV SISTEMINE HOS GELDINIZ ===" << std::endl;
    
    bool isRunning = true;
    int choice;

    while (isRunning) {
        showMenu();
        std::cout << "Seciminiz: ";
        
        // Harf girilirse hata vermesini önleyen kontrol (LLR 7.3)
        if (!(std::cin >> choice)) {
            std::cout << "HATA: Lutfen sadece sayi giriniz!" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        // Çıkış işlemi (LLR 7.5)
        if (choice == 10) {
            std::cout << "Sistem kapaniyor ve kaydediliyor..." << std::endl;
            dataManager->saveState();
            isRunning = false;
        } else {
            handleInput(choice);
        }
    }
}

// Menü Yazdırma (LLR 7.2)
void MSH::showMenu() {
    std::cout << "\n--- ANA MENU ---" << std::endl;
    std::cout << "1. Sistem Durumu" << std::endl;
    std::cout << "2. Cihaz Ekle" << std::endl;
    std::cout << "3. Cihaz Kaldir" << std::endl;
    std::cout << "4. Mod Secimi" << std::endl;
    std::cout << "5. Guvenlik" << std::endl;
    std::cout << "6. Cihaz Listesi" << std::endl;
    std::cout << "7. Komut Testi" << std::endl;
    std::cout << "8. YARDIM / KILAVUZ" << std::endl;
    std::cout << "9. Geri Al" << std::endl;
    std::cout << "10. CIKIS" << std::endl;
    std::cout << "----------------" << std::endl;
}

// Girdi İşleme
void MSH::handleInput(int choice) {
    switch (choice) {
        case 1: std::cout << ">> Durum islemleri..." << std::endl; break;
        case 2: std::cout << ">> Cihaz ekleme islemleri..." << std::endl; break;
        case 3: std::cout << ">> Cihaz silme islemleri..." << std::endl; break;
        case 4: std::cout << ">> Mod secimi islemleri..." << std::endl; break;
        case 5: std::cout << ">> Guvenlik islemleri..." << std::endl; break;
        case 6: deviceManager->listDevices(); break;
        case 8: 
            std::cout << "\n[KILAVUZ] Menuden numara secerek islem yapabilirsiniz." << std::endl; 
            break; // LLR 7.4
        default: 
            std::cout << "Gecersiz secim! 1-10 arasi giriniz." << std::endl; 
            break;
    }
}