#include <iostream>
#include <vector>
#include <string>
#include <thread> // Timer simulasyonu (std::this_thread)
#include <chrono> // Zaman birimleri (std::chrono)

#include "Logger.h" 

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
        // LLR 6.2: Log mesajı bildirimi

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

// --- 1.4 Concrete Subjects (Sensorler) ---
// LLR 6.1: Kamera ve Dedektörler
class Camera : public Subject {
public:
    void detectMotion() {
        // LLR 6.3: Hareket algılandığında tetikle
        notify("MOTION_DETECTED");
    }
};

class Detector : public Subject {
public:
    void detectSmoke() {
        // LLR 6.4: Duman algılandığında tetikle
        notify("SMOKE_DETECTED");
    }
    void detectGas() {
        notify("GAS_DETECTED");
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
//  MAIN
// =============================================================
int main() {
    cout << "========================================" << endl;
    cout << "   MSH GUVENLIK MODULU (DEV 6) TESTI    " << endl;
    cout << "========================================" << endl;

    LoggerObserver* logger = new LoggerObserver();
    SMSObserver* sms = new SMSObserver();
    AlarmObserver* alarm = new AlarmObserver(); 

    Camera* camera = new Camera();
    Detector* detector = new Detector();

    SecurityManager* secManager = new SecurityManager();

    camera->attach(logger);
    camera->attach(sms); 

    detector->attach(logger);
    detector->attach(alarm); 
    detector->attach(sms);

    cout << "\n\n>>> SENARYO 1 BASLIYOR: HAREKET ALGILANDI <<<" << endl;
    camera->detectMotion();
    
    cout << ">>> Otomasyon Zinciri Baslatiliyor..." << endl;
    secManager->handleEvent("MOTION_DETECTED");

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    cout << "\n\n>>> SENARYO 2 BASLIYOR: DUMAN ALGILANDI <<<" << endl;
    detector->detectSmoke();

    cout << ">>> Otomasyon Zinciri Baslatiliyor..." << endl;
    secManager->handleEvent("SMOKE_DETECTED");

    delete logger; delete sms; delete alarm;
    delete camera; delete detector;
    delete secManager;

    cout << "\n\n========================================" << endl;
    cout << "   TEST BASARIYLA TAMAMLANDI.           " << endl;
    cout << "========================================" << endl;

    return 0;
}