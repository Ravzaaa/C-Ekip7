#include <iostream>
#include "Light.h"

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

    return 0;
}
