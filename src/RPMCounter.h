#pragma once
#include <stdint.h>

class RPMCounter {
    public:
        virtual int16_t getFactRPM() = 0;
    private:
        int16_t factRPM;
};
