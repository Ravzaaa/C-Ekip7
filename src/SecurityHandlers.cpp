#include "../include/SecurityHandlers.h"
#include "../include/Timer.h"

void AlarmHandler::handle(string event) {
    if (event == "MOTION_DETECTED" || event == "SMOKE_DETECTED") {
        cout << "[CHAIN - 1] AlarmHandler: Yuksek sesli alarm caliyor!" << endl;
        if (nextHandler != nullptr) {
            Timer::schedule(nextHandler, 1000, event);
        }
    } else {
        if (nextHandler != nullptr) nextHandler->handle(event);
    }
}

void LightHandler::handle(string event) {
    if (event == "MOTION_DETECTED") {
        cout << "[CHAIN - 2] LightHandler: Isiklar surekli acildi." << endl;
    } else if (event == "SMOKE_DETECTED") {
        cout << "[CHAIN - 2] LightHandler: Isiklar acil durum modunda yanip sonuyor (BLINK)!" << endl;
    }
    if (nextHandler != nullptr) {
        Timer::schedule(nextHandler, 1500, event);
    }
}

void PoliceHandler::handle(string event) {
    if (event == "MOTION_DETECTED") {
        cout << "[CHAIN - 3] PoliceHandler: 155 Polis araniyor... Guvenlik ihlali!" << endl;
    } else {
        if (nextHandler != nullptr) nextHandler->handle(event);
    }
}

void FireDeptHandler::handle(string event) {
    if (event == "SMOKE_DETECTED" || event == "GAS_DETECTED") {
        cout << "[CHAIN - 4] FireDeptHandler: 110 Itfaiye araniyor... Yangin tehlikesi!" << endl;
    }
}