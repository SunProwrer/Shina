#ifndef shinaLib
#define shinaLib
#include "condition.h"
#include "regulator.h"
#include "RPMCounter.h"
#include "RPMSetter.h"
#include "motorSignalSender.h"
#include "IOModule.h"

class Shina {
    public:
        void tick();
        void setRegulator(Regulator& regulator);
        void setRPMCounter(RPMCounter& counter);
        void setRPMSetter(RPMSetter& setter);
        void setMotorSignalSender(MotorSignalSender& signalSender);
        void setIOModule(IOModule& ioModule);
    private:
        Condition condition;
        Regulator* regulator;
        RPMCounter* counter;
        RPMSetter* setter;
        MotorSignalSender* signalSender;
        IOModule* ioModule;
};

#endif