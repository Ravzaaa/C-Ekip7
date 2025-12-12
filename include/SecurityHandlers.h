#pragma once
#include <string>
#include <iostream>

using namespace std;

class Handler {
protected:
    Handler* nextHandler = nullptr;
public:
    void setNext(Handler* h) { this->nextHandler = h; }
    virtual void handle(string event) = 0;
    virtual ~Handler() = default;
};

class AlarmHandler : public Handler {
public:
    void handle(string event) override;
};

class LightHandler : public Handler {
public:
    void handle(string event) override;
};

class PoliceHandler : public Handler {
public:
    void handle(string event) override;
};

class FireDeptHandler : public Handler {
public:
    void handle(string event) override;
};