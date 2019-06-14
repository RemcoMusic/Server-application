#pragma once
#include <Arduino.h>
#include "globals.h"
#include "RemoteDebug.h" 
#include "OTA.h"

class debug
{
    public:
        void setup();
        void loop();
};

extern RemoteDebug Debug;