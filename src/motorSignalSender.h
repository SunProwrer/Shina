#include <stdint.h>

class MotorSignalSender {
    public:
        virtual void setControlVal(int16_t controlVal) const = 0;
    private:
        int16_t controlVal;
};
