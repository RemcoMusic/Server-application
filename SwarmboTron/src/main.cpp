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
  connectWifi();
  Serial.println("Wifi connected");
  Tasks initTasks; 
  Serial.println("Tasks started");
}

void loop() 
{
  if(WiFi.status() != WL_CONNECTED)
  {
    WiFi.reconnect();
  }
  delay(200);
}