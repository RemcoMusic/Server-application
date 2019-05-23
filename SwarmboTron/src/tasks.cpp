#include <Arduino.h>
#include "tasks.h"

OTA OTAUpdate;
serverCommunication server;
MotorDriver motor;
ReadVoltage voltageReader;
LedDriver led;

unsigned long startMillis;
unsigned long currentMillis;
unsigned long period = 5000;  

Tasks::Tasks()
{
  xTaskCreate(
    motorDriver,
    "motorDriver",
    10000,
    NULL,
    1,
    NULL);

  xTaskCreate(
    serverCommunication,
    "serverCommunication",
    10000,
    NULL,
    1,
    NULL);

  xTaskCreate(
    OTAtask,
    "OTA",
    10000,
    NULL,
    1,
    NULL);

  xTaskCreate(
    LEDtask,
    "LEDtask",
    10000,
    NULL,
    1,
    NULL);

  Serial.println("Setup Done");
}

void Tasks::serverCommunication(void * parameter)
{
  voltageReader.setup();
  server.setup();
  startMillis = millis(); 
  for(;;)
  {
    if(udpData.status == OFF)
    {
      period = 100;
    }
    else
    {
      period = 10000;
    }
    
    currentMillis = millis(); 
    if (currentMillis - startMillis >= period)  
    {
      startMillis = currentMillis; 
      server.send(voltageReader.read());
    }
    server.listen();
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

void Tasks::motorDriver(void * parameter)
{
  for(;;)
  {
    motor.driveMotor();
  }
}

void Tasks::OTAtask(void * parameter)
{
  OTAUpdate.startOTA();
  for(;;)
  {
    OTAUpdate.handle();
  }
}

void Tasks::LEDtask(void * parameter)
{
  led.setup();
  for(;;)
  {
    led.selectMode(); 
  }
}


