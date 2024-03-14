#pragma once
#include <stdlib.h>
#include "IOModule.h"
#include "condition.h"
//#include <cstring.h>
#include <AbstractConsole.h>

class SerialIOModule : public IOModule{
public:
    SerialIOModule() { }

    SerialIOModule(AbstractConsole& console) {
        this->console = &console;
    }

    ~SerialIOModule() { }

    void setAbstractConsole(AbstractConsole& console) {
        this->console = &console;
    }

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
        console->print(msg);
        console->println(val);
    }

    void readCondition() {
        if (Serial.available()) {

            console->println("Start parsing");

            char buf[24];
            uint8_t kol = Serial.readBytesUntil(';', buf, 24);
            
            console->println("Start decripting");

            for (uint8_t i = 0; i < kol; i++) {
                char item = buf[i];
                char value[8];
                uint8_t j;
                for (j = 0; buf[++i] != ','; j++) {
                    value[j] = buf[i];
                }
                if (j == 0) continue;
                
                value[i] = 0;
                int16_t intVal = atoi(value);
                switch (item) {
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
                    console->print("Invalid param: \"");
                    console->print(item);
                    console->print(value);
                    console->println("\"");
                    break;
                }
            }
            
            console->println("End parsing");
        }
    }
protected:
    Condition condition;
private:
    AbstractConsole* console;
};

