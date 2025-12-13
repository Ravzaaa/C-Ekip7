#pragma once
#include <string>

// Handler sinifini henuz tanimlamadik, o yuzden sadece adini soyluyoruz (Forward Declaration)
class Handler; 

class Timer {
public:
    static void schedule(Handler* h, int interval, std::string event);
};