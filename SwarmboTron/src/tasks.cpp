#include <Arduino.h>
#include "tasks.h"

OTA OTAUpdate;
serverCommunication server;
MotorDriver motor;
ReadVoltage voltageReader;
LedDriver led;
debug debugger;

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

  xTaskCreate(
    debuggerTask,
    "debuggerTask",
    10000,
    NULL,
    1,
    NULL);
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
      //server.send(voltageReader.read());
      debugE("Sending data");
      server.send(5);
    } 
    server.listen();
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

void Tasks::motorDriver(void * parameter)
{
  for(;;)
  {
    if(!globalData.motorDebug)
    {
      motor.driveMotor();
      vTaskDelay(10/portTICK_PERIOD_MS);
    }
    else
    {
      if(globalData.DriveForward)
      {
        motor.setMotorSpeed(1000,1000);
      }
      if(globalData.TurnLeft)
      {
        motor.setMotorSpeed(300,1024);
      }
      if(globalData.TurnRight)
      {
        motor.setMotorSpeed(1024,300);
      }
      else
      {
        motor.setMotorSpeed(0,0);
      } 
    }
  }
}

void Tasks::OTAtask(void * parameter)
{
  OTAUpdate.startOTA();
  for(;;)
  {
    OTAUpdate.handle();
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

void Tasks::LEDtask(void * parameter)
{
  led.setup();
  for(;;)
  {
    led.selectMode();
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

void Tasks::debuggerTask(void * parameter)
{
  debugger.setup();
  for(;;)
  {
    debugger.loop();
  }
}




