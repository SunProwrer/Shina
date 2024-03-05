#pragma once
#include <stdint.h>

class RPMSetter {
    public:
        virtual int16_t getAimRPM() = 0;
    private:
        volatile int16_t aimRPM;
};
