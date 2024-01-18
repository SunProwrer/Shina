#include <stdint.h>

class RPMSetter {
    public:
        virtual int16_t getAimRPM() const = 0;
    private:
        int16_t aimRPM;
};
