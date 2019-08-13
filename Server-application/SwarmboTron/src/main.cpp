#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include "tasks.h"

const char* ssid = "swarmboTron";
const char* password = "swarmboTron";


void connectWifi()
{
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
  }
}

void setup() 
{
  Serial.begin(115200);
  Serial.println("Booting");
  connectWifi();
  Tasks initTasks; 
}

void loop() 
{
  delay(500);
}