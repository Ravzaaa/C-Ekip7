#include <iostream>
#include "Light.h"
#include "Camera.h"
#include "TV.h"
#include "Alarm.h"
#include "Detector.h"


int main() {
    std::cout << "Akilli Ev Sistemi Baslatiliyor...\n";

    // Light nesnesi olustur
    Light salonIsigi("Salon Isigi", "Sari", 80);

    // Isigi ac
    salonIsigi.powerOn();

    // Durumu yazdir
    salonIsigi.reportStatus();

    // Isigi kapat
    salonIsigi.powerOff();

    // Tekrar durumu yazdir
    salonIsigi.reportStatus();

    // Camera nesnesi olustur
    Camera guvenlikKamerasi("Guvenlik Kamerasi");

    guvenlikKamerasi.powerOn();
    guvenlikKamerasi.startRecording();
    guvenlikKamerasi.reportStatus();

    guvenlikKamerasi.stopRecording();
    guvenlikKamerasi.powerOff();
    guvenlikKamerasi.reportStatus();

    TV salonTV("Salon TV", "Samsung", "QLED", 7, 25);


    salonTV.powerOn();
    salonTV.setChannel(12);
    salonTV.setVolume(40);
    salonTV.reportStatus();
    salonTV.powerOff();
    salonTV.reportStatus();

    Alarm evAlarmi("Alarm Sistemi");

    evAlarmi.powerOn();
    evAlarmi.reportStatus();

    evAlarmi.powerOff();    //  Kapatma denemesi → reddedilmeli
    evAlarmi.reportStatus();

    Detector evDedektoru("Dedektor Sistemi", true, true);

    evDedektoru.powerOn();
    evDedektoru.detectGas(true);
    evDedektoru.detectSmoke(true);
    evDedektoru.reportStatus();
    evDedektoru.powerOff();   // reddedilecek



    return 0;
}
