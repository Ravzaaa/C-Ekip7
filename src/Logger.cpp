#include "Logger.h"
#include <iostream> // Hata mesajları için

// Statik üye değişkenin başlatılması (İlk başta NULL/0).
Logger* Logger::instance = 0; 

// LLR 1.1: Kurucu (Constructor) Uygulaması
Logger::Logger() : logFilePath("system_operation.log") {
    // Log dosyası, nesne ilk oluşturulduğunda açılır.
    logFile.open(logFilePath.c_str(), std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "HATA: Log dosyası açılamadı: " << logFilePath << std::endl;
    } else {
        log("Sistem başlatıldı. Loglama işlemi başladı."); 
    }
}

Logger::~Logger() {
    closeLog();
}

// LLR 1.1: getInstance Uygulaması
Logger* Logger::getInstance() {
    if (instance == 0) { // İlk çağrıda nesne oluşturulur.
        instance = new Logger();
    }
    return instance;
}

// LLR 1.2: log Uygulaması
void Logger::log(const std::string& message) {
    if (logFile.is_open()) {
        // Tarih/Saat Etiketi Hazırlama
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        
        // Log Formatı: [YYYY-MM-DD HH:MM:SS] Mesaj
        logFile << "[" 
                << (now->tm_year + 1900) << "-" 
                << std::setfill('0') << std::setw(2) << (now->tm_mon + 1) << "-" 
                << std::setfill('0') << std::setw(2) << now->tm_mday << " " 
                << std::setfill('0') << std::setw(2) << now->tm_hour << ":" 
                << std::setfill('0') << std::setw(2) << now->tm_min << ":" 
                << std::setfill('0') << std::setw(2) << now->tm_sec 
                << "] " << message << std::endl;

        logFile.flush(); // Hemen dosyaya yazılmasını sağla (Veri bütünlüğü için önemli).
    }
}

// Uygulama kapanırken dosya akışını kapatmak için.
void Logger::closeLog() {
    if (logFile.is_open()) {
        log("Sistem kapatılıyor. Loglama işlemi sonlandırıldı.");
        logFile.close();
    }
}