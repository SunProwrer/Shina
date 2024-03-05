#pragma once
#include "RPMCounter.h"
#include <AbstractArduinoCommands.h>
#include "count.h"

extern void foo();

class hallRPMCouner : public RPMCounter{
public:
    hallRPMCouner(uint8_t inputPort) {
        this->inputPort = inputPort;
        this->minOutputVal = 0;
        this->maxOutputVal = 1024;

        attachInterrupt(inputPort, foo, RISING);
    }

    ~hallRPMCouner() { }

    int16_t getFactRPM() {
        return map(constrain(factRPM, 0, 10000), 0, 10000, minOutputVal, maxOutputVal);
    }

    void setMinOutputVal(int16_t minOutputVal) {
        this->minOutputVal = minOutputVal;
    }

    void setMaxOutputVal(int16_t maxOutputVal) {
        this->maxOutputVal = maxOutputVal;
    }

    void setNumIntPerRoute(uint8_t ints) {
        kolMagnetsPerRoute = ints;
    }
protected:
    void countRPM() {
        static uint32_t lastTime = 0;
        uint32_t currentTime = micros();
        factRPM = (int16_t)(60 / ((float)(currentTime - lastTime) * kolMagnetsPerRoute) * 10000000);
        lastTime = currentTime;
    }

    uint8_t inputPort;
    uint8_t kolMagnetsPerRoute;
    uint16_t minOutputVal;
    uint16_t maxOutputVal;
};
