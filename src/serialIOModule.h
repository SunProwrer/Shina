#pragma once
#include "IOModule.h"
#include "condition.h"
#include "cstring"
#include <AbstractArduinoCommands.h>

class serialIOModule : public IOModule{
public:
    serialIOModule() {

    }

    ~serialIOModule() { }

    void sendFactRPM(int16_t rpm) {
        sendDataWithMessage("Fact RPM: ", rpm);
    }

    void sendAimRPM(int16_t rpm) {
        sendDataWithMessage("Aim RPM: ", rpm);
    }

    void sendControlVal(int16_t controlVal) {
        sendDataWithMessage("Control value: ", controlVal);
    }

    int16_t getAimRPM() {
        readCondition();
        return condition.aimRPM;
    }

    uint8_t getIOSettings() {
        readCondition();
        return condition.IOSettings;
    }
private:
    void sendDataWithMessage(const char* msg, int16_t val) {
        consolePrint(msg);
        consolePrintln(val);
    }

    void readCondition() {
        if (Serial.available()) {
            char buf[24];
            uint8_t kol = Serial.readBytesUntil(';', &buf, 24);
            for (uint8_t i = 0; i < kol; i++) {
                char item = buf[i];
                char value[8];
                for (uint8_t j = 0; buf[++i] != ','; j++) {
                    value[j] = buf[i];
                }
                value[i] = 0;
                int16_t intVal = atoi(value);
                switch (item)
                {
                case 'r':
                    condition.aimRPM = intVal;
                    break;
                case 'c':
                    bitWrite(condition.IOSettings, 1, intVal);
                    break;
                case 'a':
                    bitWrite(condition.IOSettings, 2, intVal);
                    break;
                case 'f':
                    bitWrite(condition.IOSettings, 3, intVal);
                    break;
                case 's':
                    bitWrite(condition.IOSettings, 4, intVal);
                    break;
                
                default:
                    break;
                }
            }
        }
    }
protected:
    Condition condition;
};

