#include "DataManager.h"
#include <fstream>
#include <sstream> // *** EKLEME: std::stringstream için zorunlu. ***
#include "Logger.h" // Loglama işlemlerini yönetmek için Logger'ı kullanıyoruz.

// LLR 1.3: saveState Uygulaması
void DataManager::saveState(const std::string& activeMode, int deviceCount) {
    // C++98 uyumu için c_str() metodu ile dosya yolu pointer'ını veriyoruz.
    std::ofstream configFile(configFilePath.c_str()); 
    
    Logger::getInstance()->log("DataManager: Sistem durumu kaydediliyor.");

    if (configFile.is_open()) {
        // Konfigürasyon dosyasını basit bir formatta yazıyoruz: Key=Value
        configFile << "ActiveMode=" << activeMode << std::endl; 
        configFile << "DeviceCount=" << deviceCount << std::endl;
        configFile.close();
        Logger::getInstance()->log("DataManager: Durum başarıyla kaydedildi.");
    } else {
        Logger::getInstance()->log("HATA: DataManager konfigürasyon dosyası yazılamadı.");
    }
}

// LLR 1.4: loadState Uygulaması
void DataManager::loadState(std::string& activeMode, int& deviceCount) {
    std::ifstream configFile(configFilePath.c_str());
    std::string line;
    
    Logger::getInstance()->log("DataManager: Sistem durumu yükleniyor.");

    if (configFile.is_open()) {
        while (std::getline(configFile, line)) {
            // Key=Value formatını ayır
            std::string key;
            std::string value;
            size_t delimiterPos = line.find('=');

            if (delimiterPos != std::string::npos) {
                key = line.substr(0, delimiterPos);
                value = line.substr(delimiterPos + 1);
                
                if (key == "ActiveMode") {
                    activeMode = value;
                } else if (key == "DeviceCount") {
                    // Sayısal değeri dönüştür.
                    std::stringstream ss(value);
                    ss >> deviceCount; 
                    // Sayı dönüştürme hatası kontrolü (İleride LLR olarak detaylandırılabilir.)
                }
            }
        }
        configFile.close();
        Logger::getInstance()->log("DataManager: Durum başarıyla yüklendi. Aktif Mod: " + activeMode);
    } else {
        // Konfigürasyon dosyası yoksa/açılmazsa, varsayılan değerlerle devam et.
        Logger::getInstance()->log("UYARI: Konfigürasyon dosyası bulunamadı. Varsayılan ayarlar kullanılıyor.");
    }
}