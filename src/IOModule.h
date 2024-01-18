#include <stdint.h>

class IOModule {
    public:
        virtual void sendFactRPM(int16_t rpm) const = 0;
        virtual void sendAimRPM(int16_t rpm) const = 0;
        virtual void sendControlVal(int16_t controlVal) const = 0;
        virtual int16_t getAimRPM() const = 0;
        virtual u_int8_t getIOSettings() const = 0;
};
