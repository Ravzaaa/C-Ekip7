#ifndef COMMAND_H
#define COMMAND_H

/**
 * @class Command
 * @brief Command Pattern için soyut arayüz (interface). 
 * LLR 1.5: Tüm geliştiricilerin kullanacağı ortak komut yapısını tanımlar.
 */
class Command {
public:
    // LLR 1.5: Tüm somut komut sınıflarının uygulaması gereken sanal fonksiyon.
    // Sanal yıkıcı (virtual destructor) türetilmiş sınıfların doğru şekilde yok edilmesi için gereklidir.
    virtual void execute() = 0; 
    virtual ~Command() {} 
};

#endif // COMMAND_H