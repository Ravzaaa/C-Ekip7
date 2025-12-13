#include <iostream>
#include <vector>
#include <string>
#include <thread> // Timer ve bekleme için
#include <chrono> // Zaman birimleri için

// --- DIŞ KAYNAKLAR ---
#include "Logger.h"  // İlayda
#include "Device.h"  // Zehra

using namespace std;

// --- SABITLER ---
const string EVENT_MOTION = "MOTION_DETECTED";
const string EVENT_SMOKE = "SMOKE_DETECTED";
const string EVENT_GAS = "GAS_DETECTED";

// =============================================================
//  BOLUM 1: OBSERVER PATTERN (Gözlemci)
// =============================================================

class Observer {
public:
    virtual void update(string event) = 0;
    virtual ~Observer() = default;
};

class LoggerObserver : public Observer {
public:
    void update(string event) override {
        // Singleton Logger kullanımı
        Logger::getInstance()->log("[SECURITY - OBSERVER]: " + event);
    }
};

class AlarmObserver : public Observer {
public:
    void update(string event) override {
        cout << "[ALARM UNIT]: DIT! DIT! DIT! Sensor tetiklendi -> " << event << endl;
    }
};

class SMSObserver : public Observer {
public:
    void update(string event) override {
        cout << "[SMS SERVICE]: Sayin Kullanici, evinizde " << event << " tespit edildi!" << endl;
    }
};

class Subject {
private:
    vector<Observer*> observers;
public:
    void attach(Observer* o) {
        observers.push_back(o);
    }
    void notify(string event) {
        cout << "\n--- [SENSOR] ALGILAMA YAPILDI: " << event << " ---" << endl;
        for (Observer* o : observers) {
            o->update(event);
        }
        cout << "------------------------------------------------" << endl;
    }
    virtual ~Subject() = default;
};

// =============================================================
//  BOLUM 2: DEVICE ENTEGRASYONU (Sensörler)
// =============================================================

// CAMERA: Hem Device (Zehra) hem Subject (Sen)
class Camera : public Device, public Subject {
public:
    Camera(string name = "Guvenlik Kamerasi") : Device(name) {}

    // --- Device Zorunlu Fonksiyonları ---
    void powerOn() override {
        setActive(true);
        cout << "[DEVICE]: " << getName() << " (ID: " << getId() << ") sistemi baslatildi." << endl;
    }

    void powerOff() override {
        setActive(false);
        cout << "[DEVICE]: " << getName() << " kapatildi." << endl;
    }

    void reportStatus() const override {
        cout << "[STATUS]: " << getName() << " : " << getStatus() << endl;
    }

    Device* clone() const override { return new Camera(*this); }

    // --- Algılama Fonksiyonu ---
    void detectMotion() {
        if (getActiveStatus()) { 
             notify(EVENT_MOTION);
        } else {
             cout << "[INFO]: " << getName() << " pasif, hareket yok sayildi." << endl;
        }
    }
};

// DETECTOR: Hem Device (Zehra) hem Subject (Sen)
class Detector : public Device, public Subject {
public:
    Detector(string name = "Yangin Dedektoru") : Device(name) {}

    void powerOn() override {
        setActive(true);
        cout << "[DEVICE]: " << getName() << " (ID: " << getId() << ") aktif edildi." << endl;
    }

    void powerOff() override {
        cout << "[UYARI]: " << getName() << " kritik cihazdir, kapatilmasi onerilmez!" << endl;
        setActive(false); // Yine de kapatma fonksiyonu olmalı
    }

    void reportStatus() const override {
        cout << "[STATUS]: " << getName() << " : " << getStatus() << endl;
    }

    Device* clone() const override { return new Detector(*this); }
    bool isCritical() const override { return true; }

    void detectSmoke() {
        if (getActiveStatus()) notify(EVENT_SMOKE);
    }
    void detectGas() {
        if (getActiveStatus()) notify(EVENT_GAS);
    }
};

// =============================================================
//  BOLUM 3: CHAIN OF RESPONSIBILITY (Zincir)
// =============================================================

class Handler {
protected:
    Handler* nextHandler = nullptr;
public:
    void setNext(Handler* h) { this->nextHandler = h; }
    virtual void handle(string event) = 0;
    virtual ~Handler() = default;
};

// --- Halka 1: Alarm (Kullanıcı Tepkisi Bekler) ---
class AlarmHandler : public Handler {
public:
    void handle(string event) override {
        cout << "\n[ZINCIR-1] AlarmHandler: YUKSEK SESLI ALARM CALIYOR! (WIIU WIIU)" << endl;
        
        // Simülasyon: Kullanıcıya alarmı susturması için süre ver
        cout << "   -> (Sistem kullanicinin alarmi susturmasini bekliyor...)" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        
        cout << "   -> [SURE DOLDU]: Kullanici mudahelesi yok. Zincir devam ediyor." << endl;
        
        if (nextHandler != nullptr) {
            nextHandler->handle(event);
        }
    }
};

// --- Halka 2: Işıklar (Yanıp Sönme Efekti - LLR 6.5) ---
class LightHandler : public Handler {
public:
    void handle(string event) override {
        if (event == EVENT_MOTION || event == EVENT_SMOKE) {
            cout << "\n[ZINCIR-2] LightHandler: Isiklar uyari moduna alindi." << endl;
            
            // BLINK (YANIP SÖNME) DÖNGÜSÜ
            for(int i=0; i<3; i++) {
                cout << "   * ISIKLAR ACILDI *" << endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(300)); 
                cout << "   . isiklar kapandi ." << endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
            cout << "   -> Isik uyarisi tamamlandi." << endl;
        }

        if (nextHandler != nullptr) {
            nextHandler->handle(event);
        }
    }
};

// --- Halka 3: Polis (Sadece Hırsızlık) ---
class PoliceHandler : public Handler {
public:
    void handle(string event) override {
        if (event == EVENT_MOTION) {
            cout << "\n[ZINCIR-3] PoliceHandler: !!! 155 POLIS MERKEZI ARANIYOR !!!" << endl;
            cout << "   -> Konum ve olay bilgisi polise iletildi." << endl;
        } else if (nextHandler != nullptr) {
            // Hareket değilse bir sonrakine pasla
            nextHandler->handle(event);
        }
    }
};

// --- Halka 4: İtfaiye (Sadece Yangın/Gaz) ---
class FireDeptHandler : public Handler {
public:
    void handle(string event) override {
        if (event == EVENT_SMOKE || event == EVENT_GAS) {
            cout << "\n[ZINCIR-4] FireDeptHandler: !!! 110 ITFAIYE ARANIYOR !!!" << endl;
            cout << "   -> Yangin ihbari yapildi." << endl;
        }
    }
};

// =============================================================
//  YÖNETİCİ SINIF (SecurityManager)
// =============================================================
class SecurityManager {
private:
    Handler* alarmHandler;
    Handler* lightHandler;
    Handler* policeHandler;
    Handler* fireHandler;

public:
    SecurityManager() {
        // Zincir Halkalarını Oluştur
        alarmHandler = new AlarmHandler();
        lightHandler = new LightHandler();
        policeHandler = new PoliceHandler();
        fireHandler = new FireDeptHandler();

        // Zinciri Bağla: Alarm -> Işık -> Polis -> İtfaiye
        alarmHandler->setNext(lightHandler);
        lightHandler->setNext(policeHandler);
        policeHandler->setNext(fireHandler);
    }

    ~SecurityManager() {
        delete alarmHandler; delete lightHandler;
        delete policeHandler; delete fireHandler;
    }

    void handleEvent(string event) {
        if (alarmHandler) {
            cout << ">>> GUVENLIK PROTOKOLU BASLATILIYOR <<<" << endl;
            alarmHandler->handle(event);
        }
    }
};

// =============================================================
//  MAIN (TEST SENARYOSU)
// =============================================================
int main() {
    cout << "===========================================" << endl;
    cout << "   MSH GUVENLIK MODULU      " << endl;
    cout << "===========================================" << endl;

    // 1. KURULUM
    LoggerObserver* logger = new LoggerObserver();
    SMSObserver* sms = new SMSObserver();
    
    // 2. CIHAZLAR
    Camera* camera = new Camera("Ana Kapi Kamerasi");
    Detector* detector = new Detector("Koridor Duman Sensoru");
    
    // Cihazları aç (Device Özelliği)
    camera->powerOn();
    detector->powerOn();

    // 3. YONETICI
    SecurityManager* secManager = new SecurityManager();

    // 4. BAGLANTILAR
    camera->attach(logger);
    camera->attach(sms);
    detector->attach(logger);
    detector->attach(sms); 

    // -----------------------------------------------------
    // SENARYO 1: HIRSIZ GİRİYOR
    // -----------------------------------------------------
    cout << "\n\n*** SENARYO 1: HAREKET ALGILANDI ***" << endl;
    // Biraz bekle (Gerçekçilik için)
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    camera->detectMotion(); // Sensör tetiklenir
    secManager->handleEvent(EVENT_MOTION); // Otomasyon başlar

    // -----------------------------------------------------
    // SENARYO 2: YANGIN ÇIKIYOR
    // -----------------------------------------------------
    cout << "\n\n*** SENARYO 2: DUMAN ALGILANDI ***" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    detector->detectSmoke(); // Sensör tetiklenir
    secManager->handleEvent(EVENT_SMOKE); // Otomasyon başlar

    // -----------------------------------------------------
    // KAPANIŞ
    // -----------------------------------------------------
    cout << "\n\n>>> Sistem Kapatiliyor..." << endl;
    camera->powerOff();
    detector->powerOff();

    delete logger; delete sms;
    delete camera; delete detector;
    delete secManager;

    cout << "\n===========================================" << endl;
    cout << "   TEST BASARIYLA TAMAMLANDI.              " << endl;
    cout << "===========================================" << endl;

    return 0;
}