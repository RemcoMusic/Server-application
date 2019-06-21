#include <Arduino.h>
#include "debug.h"

class ReadVoltage
{
    public:
        void setup();
        int read();
    private:
        const static int voltageReadPin = 35; 
        int voltageDeviderValue = 4095;
        double ADC_VALUE = 0;
        double voltage_value = 0; 
};