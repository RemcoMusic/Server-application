#include <Arduino.h>
#include "debug.h"

class ReadVoltage
{
    public:
        void setup();
        double read();
    private:
        const static int voltageReadPin = 35; 
        int voltageDeviderValue = 4095;
        int ADC_VALUE = 0;
        int voltage_value = 0; 
};