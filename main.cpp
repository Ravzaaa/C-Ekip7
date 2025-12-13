#include <iostream>
#include <vector>
#include <string>
#include <thread> // Timer simulasyonu (std::this_thread)
#include <chrono> // Zaman birimleri (std::chrono)

// --- DIŞ KAYNAKLAR (Diğer Geliştiriciler) ---
#include "Logger.h"  // Dev 1 (İlayda)
#include "Device.h"  // Dev 3 (Zehra)

using namespace std;

// =============================================================
//  BOLUM 1: OBSERVER PATTERN (Gozlemci - LLR 6.1, 6.2)
// =============================================================

// --- 1.1 Observer Interface ---
class Observer {
public:
    virtual void update(string event) = 0;
    virtual ~Observer() = default;
};

// --- 1.2 Concrete Observers ---
class LoggerObserver : public Observer {
public:
    void update(string event) override {
        // LLR 6.2: Log mesajı bildirimi (Dosyaya yazar)
        Logger::getInstance()->log("[SECURITY - OBSERVER]: " + event);
    }
};

class AlarmObserver : public Observer {
public:
    void update(string event) override {
        // LLR 6.2: Alarm bildirimi
        cout << "[ALARM UNIT]: Sensor tetiklendi! Alarm calisiyor -> " << event << endl;
    }
};

class SMSObserver : public Observer {
public:
    void update(string event) override {
        // LLR 6.2: SMS bildirimi
        cout << "[SMS SERVICE]: Kullaniciya uyari mesaji gonderildi -> " << event << endl;
    }
};

// --- 1.3 Subject Base Class ---
class Subject {
private:
    vector<Observer*> observers;
public:
    void attach(Observer* o) {
        observers.push_back(o);
    }
    void notify(string event) {
        cout << "\n--- [SENSOR] Durum Algilandi: " << event << " ---" << endl;
        for (Observer* o : observers) {
            o->update(event);
        }
        cout << "------------------------------------------------" << endl;
    }
    virtual ~Subject() = default;
};

// --- 1.4 Concrete Subjects (Sensorler - Device Entegreli) ---

// KAMERA SINIFI: Hem bir Cihaz (Device) hem de bir Gözlemlenen (Subject)
class Camera : public Device, public Subject {
public:
    // Yapıcı metod: İsim alır, Device sınıfına iletir.
    Camera(string name = "Guvenlik Kamerasi") : Device(name) {}

    // --- Device'dan Gelen Zorunlu Fonksiyonlar ---
    void powerOn() override {
        setActive(true);
        cout << "[DEVICE]: " << getName() << " (ID: " << getId() << ") ACILDI." << endl;
    }

    void powerOff() override {
        setActive(false);
        cout << "[DEVICE]: " << getName() << " (ID: " << getId() << ") KAPATILDI." << endl;
    }

    void reportStatus() const override {
        cout << "[STATUS]: " << getName() << " durumu: " << getStatus() << endl;
    }

    // Prototype Pattern (Kopyalama)
    Device* clone() const override {
        return new Camera(*this);
    }

    // --- Dev 6 (benim) Fonksiyonu ---
    void detectMotion() {
        // Sadece cihaz aktifse (fişi takılıysa) algılar!
        if (getActiveStatus()) { 
             notify("MOTION_DETECTED");
        } else {
             cout << "[UYARI]: " << getName() << " kapali, hareket algilanmadi." << endl;
        }
    }
};

// DEDEKTÖR SINIFI: Hem bir Cihaz (Device) hem de bir Gözlemlenen (Subject)
class Detector : public Device, public Subject {
public:
    Detector(string name = "Yangin Dedektoru") : Device(name) {}

    // --- Device'dan Gelen Zorunlu Fonksiyonlar ---
    void powerOn() override {
        setActive(true);
        cout << "[DEVICE]: " << getName() << " (ID: " << getId() << ") ACILDI." << endl;
    }

    void powerOff() override {
        setActive(false);
        cout << "[DEVICE]: " << getName() << " KAPATILDI." << endl;
    }

    void reportStatus() const override {
        cout << "[STATUS]: " << getName() << " sensor durumu: " << getStatus() << endl;
    }

    Device* clone() const override {
        return new Detector(*this);
    }

    // Dedektör kritiktir (Device.h'deki sanal fonksiyonu eziyoruz)
    bool isCritical() const override { return true; }

    // --- Dev 6 (benim) Fonksiyonları ---
    void detectSmoke() {
        if (getActiveStatus()) {
             notify("SMOKE_DETECTED");
        }
    }
    void detectGas() {
        if (getActiveStatus()) {
             notify("GAS_DETECTED");
        }
    }
};

// =============================================================
//  BOLUM 2: CHAIN OF RESPONSIBILITY & TIMER (Zincir - LLR 6.3-6.7)
// =============================================================

// Forward Declaration
class Handler;

// --- 2.1 Timer Class ---
class Timer {
public:
    static void schedule(Handler* h, int interval, string event);
};

// --- 2.2 Handler Interface ---
class Handler {
protected:
    Handler* nextHandler = nullptr;
public:
    void setNext(Handler* h) {
        this->nextHandler = h;
    }
    virtual void handle(string event) = 0;
    virtual ~Handler() = default;
};

// --- Timer Implementation ---
void Timer::schedule(Handler* h, int interval, string event) {
    if (h != nullptr) {
        cout << "   ... (Zamanlayici isliyor: " << interval << "ms bekleyiniz) ..." << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        h->handle(event);
    }
}

// --- 2.3 Concrete Handlers ---

// ADIM 1: Alarm
class AlarmHandler : public Handler {
public:
    void handle(string event) override {
        if (event == "MOTION_DETECTED" || event == "SMOKE_DETECTED") {
            cout << "[ZINCIR-1] AlarmHandler: YUKSEK SESLI ALARM CALIYOR!" << endl;
            if (nextHandler != nullptr) {
                Timer::schedule(nextHandler, 1000, event); 
            }
        } else if (nextHandler != nullptr) {
            nextHandler->handle(event);
        }
    }
};

// ADIM 2: Işıklar
class LightHandler : public Handler {
public:
    void handle(string event) override {
        if (event == "MOTION_DETECTED") {
            cout << "[ZINCIR-2] LightHandler: Tum isiklar ACILDI (Aydinlatma Saglandi)." << endl;
        } 
        else if (event == "SMOKE_DETECTED") {
            cout << "[ZINCIR-2] LightHandler: Isiklar ACIL DURUM modunda YANIP SONUYOR!" << endl;
        }

        if (nextHandler != nullptr) {
            Timer::schedule(nextHandler, 1500, event); 
        }
    }
};

// ADIM 3: Polis
class PoliceHandler : public Handler {
public:
    void handle(string event) override {
        if (event == "MOTION_DETECTED") {
            cout << "[ZINCIR-3] PoliceHandler: 155 POLIS MERKEZI ARANIYOR... (Guvenlik Ihlali)" << endl;
        } else if (nextHandler != nullptr) {
            nextHandler->handle(event);
        }
    }
};

// ADIM 4: İtfaiye
class FireDeptHandler : public Handler {
public:
    void handle(string event) override {
        if (event == "SMOKE_DETECTED" || event == "GAS_DETECTED") {
            cout << "[ZINCIR-4] FireDeptHandler: 110 ITFAIYE ARANIYOR... (Yangin Tehlikesi)" << endl;
        }
    }
};

// =============================================================
//  BOLUM 3: SECURITY MANAGER
// =============================================================
class SecurityManager {
private:
    Handler* alarmHandler;
    Handler* lightHandler;
    Handler* policeHandler;
    Handler* fireHandler;

public:
    SecurityManager() {
        alarmHandler = new AlarmHandler();
        lightHandler = new LightHandler();
        policeHandler = new PoliceHandler();
        fireHandler = new FireDeptHandler();

        alarmHandler->setNext(lightHandler);
        lightHandler->setNext(policeHandler);
        policeHandler->setNext(fireHandler);
    }

    ~SecurityManager() {
        delete alarmHandler;
        delete lightHandler;
        delete policeHandler;
        delete fireHandler;
    }

    void handleEvent(string event) {
        if (alarmHandler) {
            alarmHandler->handle(event);
        }
    }
};

// =============================================================
//  MAIN (TEST)
// =============================================================
int main() {
    cout << "========================================" << endl;
    cout << "   MSH GUVENLIK MODULU (DEV 6) TESTI    " << endl;
    cout << "========================================" << endl;

    // 1. OBSERVER KURULUMU
    LoggerObserver* logger = new LoggerObserver();
    SMSObserver* sms = new SMSObserver();
    AlarmObserver* alarm = new AlarmObserver(); 

    // 2. CIHAZ (DEVICE) KURULUMU
    cout << "\n>>> Cihazlar (Device) Olusturuluyor..." << endl;
    Camera* camera = new Camera("Salon Kamerasi");
    Detector* detector = new Detector("Duman Dedektoru");

    // Cihazları açıyoruz (Device.h'den gelen özellik)
    camera->powerOn();
    detector->powerOn();

    // 3. YONETICI KURULUMU
    SecurityManager* secManager = new SecurityManager();

    // 4. BAGLANTILAR
    camera->attach(logger);
    camera->attach(sms); 

    detector->attach(logger);
    detector->attach(alarm); 
    detector->attach(sms);

    // -----------------------------------------------------
    // SENARYO 1: HAREKET ALGILANDI (HIRSIZ)
    // -----------------------------------------------------
    cout << "\n\n>>> SENARYO 1 BASLIYOR: HAREKET ALGILANDI <<<" << endl;
    camera->detectMotion();
    
    cout << ">>> Otomasyon Zinciri Baslatiliyor..." << endl;
    secManager->handleEvent("MOTION_DETECTED");

    // Bekleme simülasyonu
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    // -----------------------------------------------------
    // SENARYO 2: DUMAN ALGILANDI (YANGIN)
    // -----------------------------------------------------
    cout << "\n\n>>> SENARYO 2 BASLIYOR: DUMAN ALGILANDI <<<" << endl;
    detector->detectSmoke();

    cout << ">>> Otomasyon Zinciri Baslatiliyor..." << endl;
    secManager->handleEvent("SMOKE_DETECTED");

    // -----------------------------------------------------
    // KAPANIŞ VE TEMİZLİK
    // -----------------------------------------------------
    cout << "\n\n>>> Sistem Kapatiliyor..." << endl;
    camera->powerOff();
    detector->powerOff();

    delete logger; delete sms; delete alarm;
    delete camera; delete detector;
    delete secManager;

    cout << "\n========================================" << endl;
    cout << "   TEST BASARIYLA TAMAMLANDI.           " << endl;
    cout << "========================================" << endl;

    return 0;
}