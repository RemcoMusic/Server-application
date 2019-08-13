#include <Arduino.h>
#include <ArduinoOTA.h>
#include "OTA.h"

void OTA::startOTA()
{
  ArduinoOTA.setHostname("SwarmboTronOTA");
    ArduinoOTA.onStart([&]() mutable
    {
      started = true;
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
      {
        type = "sketch";
      }
      else
      {
        type = "filesystem";
      }
    });

    ArduinoOTA.begin();
}

void OTA::handle()
{
  ArduinoOTA.handle();
}
