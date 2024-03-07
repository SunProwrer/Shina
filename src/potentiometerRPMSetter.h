#pragma once
#include "RPMSetter.h"
#include <AbstractCommands.h>

class PotentiometerRPMSetter : public RPMSetter {
public:
    PotentiometerRPMSetter(uint8_t inputPort) {
        this->inputPort = inputPort;
        this->minOutputVal = 0;
        this->maxOutputVal = 1024;
    }

    ~PotentiometerRPMSetter() { }

    void setAbstractCommands(AbstractCommands& hardware) {
        this->hardware = &hardware;
    }

    int16_t getAimRPM() {
        return map(hardware->readAnalogSignal(inputPort), 0, 256, minOutputVal, maxOutputVal);
    }

    void setMinOutputVal(int16_t minOutputVal) {
        this->minOutputVal = minOutputVal;
    }

    void setMaxOutputVal(int16_t maxOutputVal) {
        this->maxOutputVal = maxOutputVal;
    }
protected:
    AbstractCommands* hardware;
    uint8_t inputPort;
    uint16_t minOutputVal;
    uint16_t maxOutputVal;
};
