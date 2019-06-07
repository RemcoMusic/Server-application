#include <Arduino.h>
#include "readVoltage.h"

void ReadVoltage::setup()
{
 pinMode(voltageReadPin, INPUT);
}

int ReadVoltage::read()
{
    ADC_VALUE = analogRead(voltageReadPin);
    voltage_value = (ADC_VALUE * 3.3 ) / (voltageDeviderValue);
    return voltage_value;
}