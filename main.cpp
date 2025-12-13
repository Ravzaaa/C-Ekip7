#include "../include/MSH.h"

int main() {
    // Uygulamayı Singleton üzerinden başlat
    MSH::getInstance()->initSystem();
    return 0;
}