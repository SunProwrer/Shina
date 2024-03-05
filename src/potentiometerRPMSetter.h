#pragma once
#include "RPMSetter.h"
#include <AbstractArduinoCommands.h>

class potentiometerRPMSetter : public RPMSetter {
public:
    potentiometerRPMSetter(uint8_t inputPort) {
        this->inputPort = inputPort;
        this->minOutputVal = 0;
        this->maxOutputVal = 1024;
    }

    ~potentiometerRPMSetter() { }

    int16_t getAimRPM() {
        return map(readAnalogSignal(inputPort), 0, 256, minOutputVal, maxOutputVal);
    }

    void setMinOutputVal(int16_t minOutputVal) {
        this->minOutputVal = minOutputVal;
    }

    void setMaxOutputVal(int16_t maxOutputVal) {
        this->maxOutputVal = maxOutputVal;
    }
protected:
    uint8_t inputPort;
    uint16_t minOutputVal;
    uint16_t maxOutputVal;
};
