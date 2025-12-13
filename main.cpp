#include <iostream>
#include <limits>
#include "MSH.h"

static void menuYazdir() {
    std::cout << "\n=============================\n";
    std::cout << "MSH Durum Yonetimi - Menu\n";
    std::cout << "1) Normal Moda Gec\n";
    std::cout << "2) Yuksek Performans Moda Gec\n";
    std::cout << "3) Uyku (Sleep) Moda Gec\n";
    std::cout << "4) Onceki Duruma Don (Undo)\n";
    std::cout << "5) Mevcut Durumu Goster\n";
    std::cout << "0) Cikis\n";
    std::cout << "Seciminiz: ";
}

int main() {
    MSH msh; // default Normal (LLR 4.4)

    std::cout << "Merhaba! MSH baslatildi. Varsayilan durum: Normal.\n";
    msh.applyRestrictions();  // ilk durum raporu

    int secim = -1;

    while (true) {
        menuYazdir();

        if (!(std::cin >> secim)) {
            // hatali giris temizle
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Gecersiz giris. Lutfen sayi girin.\n";
            continue;
        }

        switch (secim) {
            case 1:
                std::cout << "\n[MAIN] Normal moda geciliyor...\n";
                msh.setState(State::Normal);
                break;

            case 2:
                std::cout << "\n[MAIN] Yuksek performans moda geciliyor...\n";
                msh.setState(State::HighPerformance);
                break;

            case 3:
                std::cout << "\n[MAIN] Uyku (Sleep) moda geciliyor...\n";
                msh.setState(State::Sleep);
                break;

            case 4:
                std::cout << "\n[MAIN] Onceki duruma donuluyor...\n";
                msh.revertToPreviousState();
                break;

            case 5:
                std::cout << "\n[MAIN] Mevcut durum raporu isteniyor...\n";
                msh.applyRestrictions();
                break;

            case 0:
                std::cout << "\nCikis yapiliyor. Iyi gunler!\n";
                return 0;

            default:
                std::cout << "Gecersiz secim. 0-5 arasi secin.\n";
                break;
        }
    }
}
