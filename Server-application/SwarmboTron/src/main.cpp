#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include "tasks.h"

const char* ssid = "swarmboTron";
const char* password = "swarmboTron";

void connectWifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
}

void setup() 
{
  Serial.begin(115200);
  Serial.println("Booting");
  connectWifi();
  delay(2000);
  Tasks initTasks; 
}

void loop() 
{
  delay(500);
}