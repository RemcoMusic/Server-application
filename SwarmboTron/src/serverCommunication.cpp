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

void serverCommunication::sendVoltage(uint16_t msg)
{
  Udp.beginPacket(serverIP, serverPort);
  // debugE("* Voltage1: %u", msg>>8);
  // debugE("* Voltage2: %u", msg);
  Udp.write(msg);
  Udp.write(msg>>8);
  Udp.endPacket();
}

bool serverCommunication::listen()
{
  bool received = false;
  currentMillis = millis();

  int packetSize = Udp.parsePacket();

  if (packetSize)
  {
    Udp.read(rx_buffer, sizeof(udpData));

    memcpy((void*)&udpData, rx_buffer, sizeof(udpData));
    startMillis = currentMillis;
    received = true;
  }

  if (currentMillis - startMillis >= timeoutPeriod)
  {
    udpData.status = OFF;
  }
  return received;
}
