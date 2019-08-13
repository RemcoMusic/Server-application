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
  // xTaskCreate(
  //   motorDriver,
  //   "motorDriver",
  //   10000,
  //   NULL,
  //   1,
  //   NULL);

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
    if(!globalData.motorDebug)
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
        server.sendVoltage(voltageReader.read());
        //server.send(5);
      }
      bool received = server.listen();
      if(received)
      {
        motor.driveMotor();
      }
    }
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

// void Tasks::motorDriver(void * parameter)
// {
//   for(;;)
//   {
//       motor.driveMotor();
//       vTaskDelay(10/portTICK_PERIOD_MS);
//   }
// }

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
    if(OTAUpdate.started == false)
    {
      led.selectMode();
    }
    else
    {

    }
    vTaskDelay(10/portTICK_PERIOD_MS);
  }
}

void Tasks::debuggerTask(void * parameter)
{
  debugger.setup();
  for(;;)
  {
    debugger.loop();
    vTaskDelay(10/portTICK_PERIOD_MS);

  }
}
