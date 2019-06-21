#include <Arduino.h>
#include "serverCommunication.h"

WiFiUDP Udp;

void serverCommunication::setup()
{
  Udp.begin(localUdpPort);
  startMillis = millis(); 
}

// void serverCommunication::send(uint8_t msg)
// {
//   Udp.beginPacket(serverIP, serverPort);
//   Udp.write(msg);
//   Udp.endPacket();
// }

void serverCommunication::sendVoltage(double msg)
{
  Udp.beginPacket(serverIP, serverPort);
  voltageByte.val = msg;
  Udp.write(voltageByte.b,4);
  Udp.endPacket();
}

void serverCommunication::listen()
{
  currentMillis = millis(); 

  int packetSize = Udp.parsePacket();
  
  if (packetSize)
  {
    Udp.read(rx_buffer, sizeof(udpData));

    memcpy((void*)&udpData, rx_buffer, sizeof(udpData));
    startMillis = currentMillis; 
  }

  if (currentMillis - startMillis >= timeoutPeriod)  
  {
    udpData.status = OFF;
  } 
}








