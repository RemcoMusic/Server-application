#include <Arduino.h>
#include "serverCommunication.h"

WiFiUDP Udp;

void serverCommunication::setup()
{
  Udp.begin(localUdpPort);
  startMillis = millis(); 
}

void serverCommunication::send(uint8_t msg)
{
  Udp.beginPacket(serverIP, serverPort);
  Udp.write(msg);
  Udp.endPacket();
  debugE("message send");
}

void serverCommunication::listen()
{
  currentMillis = millis(); 

  int packetSize = Udp.parsePacket();
  
  if (packetSize)
  {
    int len = Udp.read(rx_buffer, sizeof(udpData));
    if (len > 0)
    {
      rx_buffer[len] = '\0';
    }

    memcpy((void*)&udpData, rx_buffer, sizeof(udpData));
    startMillis = currentMillis; 
  }

  if (currentMillis - startMillis >= timeoutPeriod)  
  {
    //timeout
    udpData.status = OFF;
    //ESP.restart();
  } 
}








