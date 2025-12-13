#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include <iomanip> // <iomanip> burada mevcut olmalı

/**
 * @class Logger
 * @brief Singleton Pattern uygulanan Logger sınıfı. 
 * LLR 1.1: Sistem genelinde tekil loglama yönetimi sağlar.
 * LLR 1.2: İşlem kayıtlarını tarih-saat etiketiyle kalıcı belleğe (dosyaya) yazar.
 */
class Logger {
private:
    // LLR 1.1: Tekil örneği tutan statik pointer (Singleton Pattern).
    static Logger* instance; 
    std::string logFilePath;
    std::ofstream logFile;

    // LLR 1.1: Kurucuyu (Constructor) private yaparak dışarıdan nesne oluşturulmasını engeller.
    Logger(); 

    // Kopyalama ve atama işlemlerini engelle (C++98 için: private olarak tanımlayıp implementation yapmamak).
    Logger(const Logger&);
    Logger& operator=(const Logger&);

public:
    // LLR 1.1: Tekil örneği elde etmek için kullanılan statik erişim metodu.
    static Logger* getInstance();

    // LLR 1.2: Log mesajını dosyaya yazan fonksiyon.
    void log(const std::string& message);

    // Uygulama kapanırken dosya akışını kapatmak için.
    void closeLog();
    
    // Yıkıcı (Destructor).
    ~Logger();
};

#endif // LOGGER_H