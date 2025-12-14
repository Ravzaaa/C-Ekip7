#include <iostream>
#include "include/MSH.h" // MSH Singleton sınıfını dahil ediyoruz

// Geliştirici 7 (Entegrasyon) Notu:
// Tüm sistem MSH sınıfı üzerinden yönetilmektedir (LLR 7.1 ve 7.6).
// Main fonksiyonu sadece sistemi başlatır.

int main() {
    // LLR 7.1: Singleton Instance'ı al
    MSH* smartHomeSystem = MSH::getInstance();

    // LLR 7.6: Sistemi başlat ve ana döngüye gir
    smartHomeSystem->initSystem();

    return 0;
}