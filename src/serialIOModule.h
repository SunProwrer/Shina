#pragma once
#include <stdlib.h>
#include "IOModule.h"
#include "condition.h"
//#include <cstring.h>
#include <AbstractConsole.h>
#include <Arduino.h>

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

    void attachCondition(Condition& condition) {
        this->condition = &condition;
        this->condition->IOSettings = this->condition->IOSettings | (15);
    }

    void tick() {
        if (bitRead(condition->IOSettings, 2)) sendFactRPM();
        if (bitRead(condition->IOSettings, 3)) sendAimRPM();
        if (bitRead(condition->IOSettings, 4)) sendControlVal();
        console->println(" ");
        readCondition();
    }

    void sendFactRPM() {
        if (bitRead(condition->IOSettings, 5)) {
            sendDataWithMessage("Fact RPM: ", condition->factRPM);
        } else {
            console->print(condition->factRPM);
            console->print(",");
        }
    }

    void sendAimRPM() {
        if (bitRead(condition->IOSettings, 5)) {
            sendDataWithMessage("Aim RPM: ", condition->aimRPM);
        } else {
            console->print(condition->aimRPM);
            console->print(",");
        }
    }

    void sendControlVal() {
        if (bitRead(condition->IOSettings, 5)) {
            sendDataWithMessage("Control value: ", condition->controlVal);
        } else {
            console->print(condition->controlVal);
            console->print(",");
        }
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
            uint8_t kol = Serial.readBytesUntil(';', buf, 23);
            buf[kol] = '\0';
            console->println(buf);
            console->println(kol);
            
            console->println("Start decripting");
            console->println("i");

            for (uint8_t i = 0; i < kol; i++) {
                console->println(i);
                char item = buf[i];
                char value[8];
                uint8_t j;
                for (j = 0; buf[++i] != ',' && buf[i] != '\0' ; j++) {
                    value[j] = buf[i];
                }
                if (j == 0) continue;
                
                value[i] = 0;
                int16_t intVal = atoi(value);
                switch (item) {
                case 'r':
                    condition->aimRPM = intVal;
                    break;
                case 'c':
                    bitWrite(condition->IOSettings, 1, intVal);
                    break;
                case 'a':
                    bitWrite(condition->IOSettings, 2, intVal);
                    break;
                case 'f':
                    bitWrite(condition->IOSettings, 3, intVal);
                    break;
                case 's':
                    bitWrite(condition->IOSettings, 4, intVal);
                    break;
                case 'm':
                    bitWrite(condition->IOSettings, 5, intVal);
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
    Condition* condition;
private:
    AbstractConsole* console;
};

