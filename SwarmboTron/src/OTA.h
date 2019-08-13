#pragma once
#include <Arduino.h>

class OTA
{
    public:
      bool started = false;
        void startOTA();
        void handle();
};
