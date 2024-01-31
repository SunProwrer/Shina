#include <stdint.h>

struct Condition
{
    public:
        uint16_t factRPM;
        uint16_t aimRPM;
        uint16_t controlVal;
        u_int8_t IOSettings;
        u_int8_t libSettings;
};
