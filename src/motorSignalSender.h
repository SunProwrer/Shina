#pragma once
#include <stdint.h>

class MotorSignalSender {
    public:
        virtual void setControlVal(int16_t controlVal) = 0;
    private:
        int16_t controlVal;
};
