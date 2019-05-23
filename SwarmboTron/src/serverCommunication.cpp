#include <Arduino.h>
#include "serverCommunication.h"

WiFiUDP Udp;

void serverCommunication::setup()
{
  Udp.begin(localUdpPort);
}

void serverCommunication::send(uint8_t msg)
{
  Udp.beginPacket(serverIP, serverPort);
  Udp.write(msg);
  Udp.endPacket();
}

void serverCommunication::listen()
{
  int packetSize = Udp.parsePacket();
  
  if (packetSize)
  {
   int len = Udp.read(rx_buffer, sizeof(udpData));
   if (len > 0)
   {
     rx_buffer[len] = '\0';
   }
    memcpy((void*)&udpData, rx_buffer, sizeof(udpData));
  }
 
}








