#include <Arduino.h>
#include "readVoltage.h"

void ReadVoltage::setup()
{
 pinMode(voltageReadPin, INPUT);
}

int ReadVoltage::read()
{
    // ADC_VALUE = analogRead(voltageReadPin);
    // voltage_value = (ADC_VALUE * 3.3 ) / (voltageDeviderValue);
    // return voltage_value;

    double batteryValue = analogRead(voltageReadPin);
    const int maxValue = 4096;
    const float r1 = 9100;
    const float r2 = 5100;
    const float vref = 3.3;
    double currentVoltage = ((r1+r2)/r2)*((float)batteryValue/maxValue)*vref;
    int IntVoltage = currentVoltage * 100;
    debugE("* Voltage: %d", IntVoltage);
    return IntVoltage;
}