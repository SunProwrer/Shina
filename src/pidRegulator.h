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
        countPID();
        return controlSignal;
    }
private:
    void countErr() {
        err = aimRPM - factRPM;
    }
    
    void countP() {
        countErr();
        p = err;
    }

    void countI() {
        i += err * dt;
    }

    void countD() {
        static float prevErr = 0;
        d = (err - prevErr) / dt;
        prevErr = err;
    }

    void countPID() {
        //TODO add map()
        countP();
        countI();
        countD();
        controlSignal = (int16_t)(p * kp + i * ki + d * kd);
    }
protected:
    float p, kp;
    float i, ki;
    float d, kd;
    float err;
    float dt;
};
