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
  connectWifi();
  Tasks initTasks; 
}

void loop() 
{
  if(WiFi.status() != WL_CONNECTED)
  {
    debugE("Connection lost, reconnecting!");
    WiFi.reconnect();
  }
  delay(200);
}