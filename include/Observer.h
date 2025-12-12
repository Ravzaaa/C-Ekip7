#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- Observer Interface ---
class Observer {
public:
    virtual void update(string event) = 0;
    virtual ~Observer() = default;
};

// --- Concrete Observers ---
// NOT: Dev 1'den Logger gelince burayı güncelleyeceğiz.
class LoggerObserver : public Observer {
public:
    void update(string event) override {
        cout << "[LOGGER]: Sistem kaydina eklendi: " << event << endl; 
        // ILERIDE: Logger::getInstance()->log(event); olacak.
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

// --- Subject Base Class ---
class Subject {
private:
    vector<Observer*> observers;
public:
    void attach(Observer* o) {
        observers.push_back(o);
    }
    void detach(Observer* o) {
        // Detach islemi simdilik bos
    }
    void notify(string event) {
        cout << "\n--- SENSOR TETIKLENDI: " << event << " ---" << endl;
        for (Observer* o : observers) {
            o->update(event);
        }
        cout << "--------------------------------------" << endl;
    }
    virtual ~Subject() = default;
};