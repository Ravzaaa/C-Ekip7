#include <iostream>
#include <string>

// Include klasöründeki başlık dosyalarını çağırıyoruz:
#include "Logger.h"      
#include "DataManager.h" 
#include "Command.h"     

// --- Örnek Komut Sınıfı (Command Pattern) ---

/**
 * @class SaveStateCommand
 * @brief Sistem durumunu kaydetme komutunu uygular.
 * Bu sınıf, DataManager'ı kullanmak üzere Command arayüzünü somutlaştırır.
 */
class SaveStateCommand : public Command {
private:
    DataManager* dataManager;
    std::string currentMode;
    int currentDeviceCount;

public:
    // Kurucu
    SaveStateCommand(DataManager* dm, const std::string& mode, int count)
        : dataManager(dm), currentMode(mode), currentDeviceCount(count) {}

    // Command arayüzünün somut uygulaması
    void execute() override {
        // DataManager'ın saveState metodunu çağırır.
        dataManager->saveState(currentMode, currentDeviceCount);
    }
    // Sanal yıkıcı
    ~SaveStateCommand() override {} 
};

// --- Ana Test Programı ---
int main() {
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "MSH (My Sweet Home) Test Başlangıcı" << std::endl;
    
    // 1. Loglama Sistemini Başlatma (Singleton Testi)
    Logger* systemLog = Logger::getInstance();
    systemLog->log("TEST: MSH Sistemi başlatılıyor...");

    // 2. DataManager ve Varsayılan Durum Ayarları
    DataManager dataManager;
    std::string activeMode = "Normal";  // Varsayılan mod
    int deviceCount = 0;                // Başlangıç cihaz sayısı

    // 3. Önceki Durumu Yükleme Testi
    dataManager.loadState(activeMode, deviceCount);

    // 4. Durum Güncelleme Simülasyonu
    systemLog->log("TEST: Kullanıcı Modu 'Cinema' olarak değiştirdi.");
    activeMode = "Cinema";
    
    systemLog->log("TEST: Kullanıcı 4 Kamera ve 1 TV ekledi.");
    deviceCount = 5;
    
    // 5. Command Pattern ile Durum Kaydetme Testi
    // Son durumu kaydetmek için bir Komut nesnesi oluştur.
    SaveStateCommand saveCmd(&dataManager, activeMode, deviceCount);
    systemLog->log("TEST: Kapanış Komutu tetikleniyor: Son durum kaydediliyor.");
    
    saveCmd.execute(); // Komutu çalıştır (Bu, DataManager'ı çağırır ve dosyaya yazar.)

    // 6. Temizleme ve Kapanma
    systemLog->log("TEST: MSH sistemi başarıyla sonlandırıldı.");
    
    std::cout << "TEST SONUCU: Başarıyla tamamlandı. system_operation.log dosyasını kontrol edin." << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    return 0;
}