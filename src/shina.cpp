#include "shina.h"
#include "stdint.h"

Shina::Shina() {
    condition.aimRPM = 0;
    condition.controlVal = 0;
    condition.factRPM = 0;
    condition.IOSettings = 0b00000000;
    condition.libSettings = 0b00000000;
}

Shina::~Shina() {
    if (condition.libSettings & 1)
    {
        delete regulator;
        delete counter;
        delete setter;
        delete signalSender;
        delete ioModule;
    }
    
}

void Shina::tick() {
    condition.factRPM = counter->getFactRPM();
    condition.aimRPM = setter->getAimRPM();

    regulator->setAimRPM(condition.aimRPM);
    regulator->setFactRPM(condition.factRPM);
    condition.controlVal = regulator->getControlVal();

    signalSender->setControlVal(condition.controlVal);


}

void Shina::setRegulator(Regulator& regulator) {
    this->regulator = &regulator;
}

void Shina::setRPMCounter(RPMCounter& counter) {
    this->counter = &counter;
}

void Shina::setRPMSetter(RPMSetter& setter) {
    this->setter = &setter;
}

void Shina::setMotorSignalSender(MotorSignalSender& signalSender) {
    this->signalSender = &signalSender;
}

void Shina::setIOModule(IOModule& ioModule) {
    this->ioModule = &ioModule;
}

void getInfoFromIO() {
}
