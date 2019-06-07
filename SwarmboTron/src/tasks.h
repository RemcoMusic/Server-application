#include "OTA.h"
#include "serverCommunication.h"
#include "motorDriver.h"
#include "readVoltage.h"
#include "ledDriver.h"
#include "globals.h"

class Tasks
{
    public:
        Tasks();
        static void serverCommunication(void * parameter);
        static void motorDriver(void * parameter);
        static void OTAtask(void * parameter);
        static void LEDtask(void * parameter);
};