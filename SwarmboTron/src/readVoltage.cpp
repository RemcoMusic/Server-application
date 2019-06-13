#include <Arduino.h>
#include "readVoltage.h"

void ReadVoltage::setup()
{
 pinMode(voltageReadPin, INPUT);
}

double ReadVoltage::read()
{
    // ADC_VALUE = analogRead(voltageReadPin);
    // voltage_value = (ADC_VALUE * 3.3 ) / (voltageDeviderValue);
    // return voltage_value;

    double batteryValue = analogRead(voltageReadPin);
    const int maxValue = 4096;
    const float r1 = 9100;
    const float r2 = 5100;
    const float vref = 3.6;
    double currentVoltage = ((r1+r2)/r2)*((float)batteryValue/maxValue)*vref;
    debugI("* Current voltage: %d", currentVoltage);
    return currentVoltage;
}