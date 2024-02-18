#pragma once
#include "motorSignalSender.h"
#include <Servo.h>
#include <Arduino.h>

class servoRPMSetter : public MotorSignalSender {
public:
    servoRPMSetter(Servo& servo) {
        this->servo = &servo;
    }

    void setControlVal(int16_t controlVal) {
        int16_t signal = convertToMicroseconds(controlVal);
        servo->writeMicroseconds(signal);
    }
    
protected:
    int16_t convertToMicroseconds(int16_t controlVal) {
        return map(controlVal, 0, 1000, 800, 2300);
    }

    Servo* servo;
};