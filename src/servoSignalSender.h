#pragma once
#include "motorSignalSender.h"
#include <Servo.h>
#include <Arduino.h>

class servoSignalSender : public MotorSignalSender {
public:
    servoSignalSender(Servo& servo) {
        this->servo = &servo;

        this->minMicroseconds = 800;
        this->maxMicroseconds = 2300;
        this->minInputVal = 0;
        this->maxInputVal = 1000;
    }

    ~servoSignalSender() { }

    void setControlVal(int16_t controlVal) {
        int16_t signal = convertToMicroseconds(controlVal);
        servo->writeMicroseconds(signal);
    }

    void setMinInputVal(int16_t minInputVal) {
        this->minInputVal = minInputVal;
    }

    void setMaxInputVal(int16_t maxInputVal) {
        this->maxInputVal = maxInputVal;
    }

    void setMinMicroseconds(int16_t minMicroseconds) {
        this->minMicroseconds = minMicroseconds;
    }

    void setMaxMicroseconds(int16_t maxMicroseconds) {
        this->maxMicroseconds = maxMicroseconds;
    }

protected:
    int16_t convertToMicroseconds(int16_t controlVal) {
        return map(controlVal, minInputVal, maxInputVal, minMicroseconds, maxMicroseconds);
    }

    Servo* servo;
    int16_t minMicroseconds;
    int16_t maxMicroseconds;
    int16_t minInputVal;
    int16_t maxInputVal;
};