#include "pidRegulator.h"

pidRegulator::pidRegulator() : pidRegulator::pidRegulator(1, 1, 1, 0.1) {
}

pidRegulator::pidRegulator(float kp, float ki, float kd, float dt) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->dt = dt;

    this->p = 0;
    this->i = 0;
    this->d = 0;
}

pidRegulator::~pidRegulator() {
}

void pidRegulator::setFactRPM(int16_t rpm) {
    this->factRPM = rpm;
}

void pidRegulator::setAimRPM(int16_t rpm) {
    this->aimRPM = rpm;
}

int16_t pidRegulator::getControlVal() {
    this->countPID();
    return this->controlSignal;
}

void pidRegulator::setP(float kp) {
    this->kp = kp;
}

void pidRegulator::setI(float ki) {
    this->ki = ki;
}

void pidRegulator::setD(float kd) {
    this->kd = kd;
}

void pidRegulator::setDt(float dt) {
    this->dt = dt;
}

void pidRegulator::countPID() {
    //TODO add map()
    this->controlSignal = (int16_t)(this->p * this->kp + this->i * this->ki + this->d * this->kd);
}

void pidRegulator::countErr() {
    this->err = this->aimRPM - this->factRPM;
}

void pidRegulator::countP() {
    this->countErr();
    this->d = this->err;
}

void pidRegulator::countI() {
    this->i += err * dt;
}

void pidRegulator::countD() {
    static float prevErr = 0;
    this->d = (err - prevErr) / dt;
    prevErr = err;
}
