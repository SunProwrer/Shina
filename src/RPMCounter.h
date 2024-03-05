#pragma once
#include <stdint.h>

class RPMCounter {
    public:
        virtual int16_t getFactRPM() = 0;
    protected:
        volatile int16_t factRPM;
};
