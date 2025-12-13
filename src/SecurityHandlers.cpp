#include "../include/SecurityHandlers.h"
#include <thread> // Sleep için
#include <chrono> // Zaman birimleri için


using namespace std;

// --- ALARM HANDLER ---
void AlarmHandler::handle(string event) {
    cout << "\n[ZINCIR-1] AlarmHandler: YUKSEK SESLI ALARM CALIYOR! (WIIU WIIU)" << endl;
    
    // Simülasyon: Kullanıcıya süre ver
    cout << "   -> (Sistem kullanicinin alarmi susturmasini bekliyor...)" << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    cout << "   -> [SURE DOLDU]: Kullanici mudahelesi yok. Zincir devam ediyor." << endl;
    
    if (nextHandler != nullptr) {
        nextHandler->handle(event);
    }
}

// --- LIGHT HANDLER (BLINK EFEKTİ) ---
void LightHandler::handle(string event) {
    if (event == "MOTION_DETECTED" || event == "SMOKE_DETECTED") {
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

// --- POLICE HANDLER ---
void PoliceHandler::handle(string event) {
    if (event == "MOTION_DETECTED") {
        cout << "\n[ZINCIR-3] PoliceHandler: !!! 155 POLIS MERKEZI ARANIYOR !!!" << endl;
        cout << "   -> Konum ve olay bilgisi polise iletildi." << endl;
    } else if (nextHandler != nullptr) {
        nextHandler->handle(event);
    }
}

// --- FIRE DEPT HANDLER ---
void FireDeptHandler::handle(string event) {
    if (event == "SMOKE_DETECTED" || event == "GAS_DETECTED") {
        cout << "\n[ZINCIR-4] FireDeptHandler: !!! 110 ITFAIYE ARANIYOR !!!" << endl;
        cout << "   -> Yangin ihbari yapildi." << endl;
    }
}