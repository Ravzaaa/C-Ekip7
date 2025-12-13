#include "../include/Timer.h"
#include "../include/SecurityHandlers.h" // Handler'i artik tanimasi lazim
#include <iostream>
#include <thread>
#include <chrono>

void Timer::schedule(Handler* h, int interval, std::string event) {
    std::cout << "... (Zamanlayici " << interval << "ms bekliyor) ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(interval)); // Windows ayarini yapmistik
    if (h != nullptr) {
        h->handle(event);
    }
}