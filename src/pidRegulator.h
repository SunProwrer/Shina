#pragma once
#include "regulator.h"

class pidRegulator : public Regulator
{
protected:
    float p, kp;
    float i, ki;
    float d, kd;
    float err;
    float dt;
private:
    void countErr();
    void countP();
    void countI();
    void countD();
    void countPID();
public:
    pidRegulator();
    pidRegulator(float kp, float ki, float kd, float dt);
    ~pidRegulator();
    void setAimRPM(int16_t rpm);
    void setFactRPM(int16_t rpm);
    void setP(float kp);
    void setI(float ki);
    void setD(float kd);
    void setDt(float dt);
    int16_t getControlVal();
};
