#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>
#include <map>
#include <iostream>

/**
 * @class DataManager
 * @brief Sistem durumunu kalıcı belleğe kaydetme ve yükleme sınıfı. 
 * İlgili Pattern: Command (saveState ve loadState Command objeleri tarafından kullanılabilir).
 */
class DataManager {
private:
    std::string configFilePath;
    // Harita, key-value konfigürasyonlarını tutar (Örn: activeMode: Normal)
    std::map<std::string, std::string> settings; 

public:
    DataManager() : configFilePath("system_config.cfg") {}

    // LLR 1.3: Sistem kapatılırken son durumu kaydeder.
    void saveState(const std::string& activeMode, int deviceCount); 

    // LLR 1.4: Sistem başlatılırken son durumu geri yükler.
    void loadState(std::string& activeMode, int& deviceCount); 
};

#endif // DATAMANAGER_H