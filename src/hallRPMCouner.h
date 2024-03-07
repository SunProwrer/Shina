#pragma once
#include "RPMCounter.h"
#include <AbstractCommands.h>
#include "count.h"

extern void countRPM();
extern void setDataPtr(countData& dataPrt);

class HallRPMCouner : public RPMCounter{
public:
    HallRPMCouner(uint8_t inputPort) {
        this->inputPort = inputPort;
        this->minOutputVal = 0;
        this->maxOutputVal = 1024;

        dataMas.kolMagnetsPerRoute = 6;

        setDataPtr(dataMas);
        attachInterrupt(digitalPinToInterrupt(inputPort), countRPM, RISING);
    }

    ~HallRPMCouner() { }

    int16_t getFactRPM() {
        return map(constrain(dataMas.factRPM, 0, 10000), 0, 10000, minOutputVal, maxOutputVal);
    }

    void setMinOutputVal(int16_t minOutputVal) {
        this->minOutputVal = minOutputVal;
    }

    void setMaxOutputVal(int16_t maxOutputVal) {
        this->maxOutputVal = maxOutputVal;
    }

    void setNumIntPerRoute(uint8_t ints) {
        dataMas.kolMagnetsPerRoute = ints;
    }
protected:
    countData dataMas;
    uint8_t inputPort;
    uint16_t minOutputVal;
    uint16_t maxOutputVal;
};
