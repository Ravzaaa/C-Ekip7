#pragma once
#include <string>
#include <iostream>

// Handler Arayüzü
class Handler {
protected:
    Handler* nextHandler = nullptr;
public:
    virtual ~Handler() = default;
    void setNext(Handler* h) { this->nextHandler = h; }
    virtual void handle(std::string event) = 0;
};

// Somut Handler Sınıfları
class AlarmHandler : public Handler {
public:
    void handle(std::string event) override;
};

class LightHandler : public Handler {
public:
    void handle(std::string event) override;
};

class PoliceHandler : public Handler {
public:
    void handle(std::string event) override;
};

class FireDeptHandler : public Handler {
public:
    void handle(std::string event) override;
};