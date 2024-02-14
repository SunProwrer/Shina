#pragma once
#include "regulator.h"

class pidRegulator : public Regulator
{
public:
    pidRegulator() : pidRegulator(1, 1, 1, 0.1) {}

    pidRegulator(float kp, float ki, float kd, float dt) {
        this->kp = kp;
        this->ki = ki;
        this->kd = kd;
        this->dt = dt;

        this->p = 0;
        this->i = 0;
        this->d = 0;
    }

    ~pidRegulator() {}

    void setFactRPM(int16_t rpm) {
        this->factRPM = rpm;
    }

    void setAimRPM(int16_t rpm) {
        this->aimRPM = rpm;
    }

    void setP(float kp) {
        this->kp = kp;
    }

    void setI(float ki) {
        this->ki = ki;
    }

    void setD(float kd) {
        this->kd = kd;
    }

    void setDt(float dt) {
        this->dt = dt;
    }

    int16_t getControlVal() {
        this->countPID();
        return this->controlSignal;
    }
private:
    void countErr() {
        this->err = this->aimRPM - this->factRPM;
    }
    
    void countP() {
        this->countErr();
        this->d = this->err;
    }

    void countI() {
        this->i += err * dt;
    }

    void countD() {
        static float prevErr = 0;
        this->d = (err - prevErr) / dt;
        prevErr = err;
    }

    void countPID() {
        //TODO add map()
        this->controlSignal = (int16_t)(this->p * this->kp + this->i * this->ki + this->d * this->kd);
    }
protected:
    float p, kp;
    float i, ki;
    float d, kd;
    float err;
    float dt;
};
