#include <iostream>
#include <vector>
#include <string>
#include <thread> // Timer simulasyonu icin
#include <chrono> // Timer simulasyonu icin

using namespace std;

// ==========================================
// 1. PATTERN: OBSERVER PATTERN (Gozlemci)
// ==========================================
// Amac: LLR 6.1 ve 6.2'yi saglamak. Sensorler (Subject) bir durum algiladiginda
// ilgili birimlere (Logger, Alarm, SMS) haber verir.

// --- Observer Interface (UML: Observer) ---
class Observer {
public:
    virtual void update(string event) = 0;
    virtual ~Observer() = default;
};

// --- Concrete Observers (UML: LoggerObserver, AlarmObserver, SMSObserver) ---
class LoggerObserver : public Observer {
public:
    void update(string event) override {
        cout << "[LOGGER]: Sistem kaydina eklendi: " << event << endl;
    }
};

class AlarmObserver : public Observer {
public:
    void update(string event) override {
        cout << "[ALARM UNIT]: Uyari alindi! Sistem tetikleniyor: " << event << endl;
    }
};

class SMSObserver : public Observer {
public:
    void update(string event) override {
        cout << "[SMS SERVICE]: Kullaniciya mesaj gonderildi: " << event << endl;
    }
};

// --- Subject Interface/Base Class (UML: Subject) ---
class Subject {
private:
    vector<Observer*> observers;
public:
    void attach(Observer* o) {
        observers.push_back(o);
    }

    void detach(Observer* o) {
        // Basitlesirme icin detach implementasyonu opsiyonel birakildi
    }

    void notify(string event) {
        cout << "\n--- SENSOR TETIKLENDI: " << event << " ---" << endl;
        for (Observer* o : observers) {
            o->update(event); // Tum gozlemcilere haber ver
        }
        cout << "--------------------------------------" << endl;
    }
    virtual ~Subject() = default;
};

// --- Concrete Subjects (UML: Camera, Detector) ---
class Camera : public Subject {
public:
    void detectMotion() {
        // LLR 6.3: Kamera hareket algilarsa
        notify("MOTION_DETECTED");
    }
};

class Detector : public Subject {
public:
    void detectSmoke() {
        // LLR 6.4: Duman algilandiginda
        notify("SMOKE_DETECTED");
    }
    void detectGas() {
        notify("GAS_DETECTED");
    }
};

// ====================================================
// 2. PATTERN: CHAIN OF RESPONSIBILITY (Sorumluluk Zinciri)
// ====================================================
// Amac: LLR 6.3, 6.5, 6.6, 6.7'yi saglamak. Olayi (Event) sirasiyla
// Alarm -> Isik -> Polis/Itfaiye seklinde islemek.

// --- Handler Abstract Class (UML: Handler) ---
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

// --- Timer Class (UML: Timer) ---
// LLR 6.7'deki sirali isletim ve zamanlamayi simule eder.
class Timer {
public:
    static void schedule(Handler* h, int interval, string event) {
        cout << "... (Zamanlayici " << interval << "ms bekliyor) ..." << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        if (h != nullptr) {
            h->handle(event);
        }
    }
};

// --- Concrete Handlers (UML: AlarmHandler, LightHandler, PoliceHandler, FireDeptHandler) ---

// 1. Halka: Alarm Calmasi
class AlarmHandler : public Handler {
public:
    void handle(string event) override {
        if (event == "MOTION_DETECTED" || event == "SMOKE_DETECTED") {
            cout << "[CHAIN - 1] AlarmHandler: Yuksek sesli alarm caliyor!" << endl;

            // Siradaki isleme gec (Zamanlayici ile - LLR 6.7)
            if (nextHandler != nullptr) {
                Timer::schedule(nextHandler, 1000, event); // 1 saniye sonra digerine gec
            }
        }
        else {
            // Ilgili degilse direkt pasla
            if (nextHandler != nullptr) nextHandler->handle(event);
        }
    }
};

// 2. Halka: Isiklarin Acilmasi / Yanip Sonmesi
class LightHandler : public Handler {
public:
    void handle(string event) override {
        if (event == "MOTION_DETECTED") {
            cout << "[CHAIN - 2] LightHandler: Isiklar surekli acildi." << endl;
        }
        else if (event == "SMOKE_DETECTED") {
            // LLR 6.5: Isiklari 1 saniye aralikla acip kapat (Simulasyon)
            cout << "[CHAIN - 2] LightHandler: Isiklar acil durum modunda yanip sonuyor (BLINK)!" << endl;
        }

        // Siradaki isleme gec
        if (nextHandler != nullptr) {
            Timer::schedule(nextHandler, 1500, event); // 1.5 saniye sonra yetkiliye haber ver
        }
    }
};

// 3. Halka: Polis (Sadece Hareket Algilanirsa)
class PoliceHandler : public Handler {
public:
    void handle(string event) override {
        if (event == "MOTION_DETECTED") {
            // LLR 6.3 son adim: Polisi ara
            cout << "[CHAIN - 3] PoliceHandler: 155 Polis araniyor... Guvenlik ihlali!" << endl;
        }
        else {
            // Hareket degilse (ornegin yanginsa), zincirdeki bir sonrakine (Itfaiye) pasla
            if (nextHandler != nullptr) nextHandler->handle(event);
        }
    }
};

// 4. Halka: Itfaiye (Sadece Duman/Gaz Algilanirsa)
class FireDeptHandler : public Handler {
public:
    void handle(string event) override {
        if (event == "SMOKE_DETECTED" || event == "GAS_DETECTED") {
            // LLR 6.6: Kullanici tepki vermezse itfaiyeyi ara
            cout << "[CHAIN - 4] FireDeptHandler: 110 Itfaiye araniyor... Yangin tehlikesi!" << endl;
        }
    }
};

// ==========================================
// MAIN (TEST SENARYOSU)
// ==========================================
int main() {
    // 1. Observer Kurulumu (Gozlemcileri Olustur)
    LoggerObserver* logger = new LoggerObserver();
    AlarmObserver* alarmObs = new AlarmObserver();
    SMSObserver* smsObs = new SMSObserver();

    // 2. Subject Kurulumu (Sensorleri Olustur ve Gozlemcileri Ekle)
    Camera* camera = new Camera();
    Detector* detector = new Detector();

    // Kamera'ya kimler abone? (LLR 6.1, 6.2)
    camera->attach(logger);
    camera->attach(smsObs);

    // Dedektor'e kimler abone?
    detector->attach(logger);
    detector->attach(alarmObs); // Dedektor alarm sistemini direkt tetikler (LLR 6.4)
    detector->attach(smsObs);

    // 3. Chain of Responsibility Kurulumu (Zinciri Olustur)
    // Siralama: Alarm -> Light -> Police -> FireDept
    AlarmHandler* alarmH = new AlarmHandler();
    LightHandler* lightH = new LightHandler();
    PoliceHandler* policeH = new PoliceHandler();
    FireDeptHandler* fireH = new FireDeptHandler();

    // Zinciri bagla (setNext)
    alarmH->setNext(lightH);
    lightH->setNext(policeH);
    policeH->setNext(fireH);

    cout << "=== SENARYO 1: HIRSIZ (KAMERA HAREKET ALGILADI) ===" << endl;
    // Adim 1: Sensor algilar ve Observer'lari uyarir (Log ve SMS gider)
    camera->detectMotion();

    // Adim 2: Sistem tepki zincirini baslatir (LLR 6.3: Alarm -> Isik -> Polis)
    cout << "\n>>> Guvenlik Protokolu Baslatiliyor (Zincir) <<<" << endl;
    alarmH->handle("MOTION_DETECTED");

    cout << "\n\n=== SENARYO 2: YANGIN (DEDEKTOR DUMAN ALGILADI) ===" << endl;
    // Adim 1: Sensor algilar (Log, SMS ve Alarm Observer calisir)
    detector->detectSmoke();

    // Adim 2: Sistem tepki zincirini baslatir (LLR 6.5, 6.6: Alarm -> Isik(Blink) -> Itfaiye)
    cout << "\n>>> Yangin Protokolu Baslatiliyor (Zincir) <<<" << endl;
    alarmH->handle("SMOKE_DETECTED");

    // Bellek temizligi
    delete logger; delete alarmObs; delete smsObs;
    delete camera; delete detector;
    delete alarmH; delete lightH; delete policeH; delete fireH;

    return 0;
}