#include <stdint.h>

class Regulator {
    public:
        virtual void setFactRPM(int16_t rpm) const = 0;
        virtual void setAimRPM(int16_t rpm) const = 0;
        virtual int16_t getControlVal() const = 0;
    private:
        int16_t factRPM;
        int16_t aimRPM;
        int16_t controlSignal;
};
