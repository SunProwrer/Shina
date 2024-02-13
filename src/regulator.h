#pragma once
#include <stdint.h>

class Regulator {
    public:
        virtual void setFactRPM(int16_t rpm) = 0;
        virtual void setAimRPM(int16_t rpm) = 0;
        virtual int16_t getControlVal() = 0;
    protected:
        int16_t factRPM;
        int16_t aimRPM;
        int16_t controlSignal;
};
