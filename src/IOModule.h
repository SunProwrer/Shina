#pragma once
#include <stdint.h>

class IOModule {
    public:
        virtual void sendFactRPM(int16_t rpm) = 0;
        virtual void sendAimRPM(int16_t rpm) = 0;
        virtual void sendControlVal(int16_t controlVal) = 0;
        virtual int16_t getAimRPM() = 0;
        virtual uint8_t getIOSettings() = 0;
};
