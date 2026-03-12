#include "all_objects.h"
#include <Ethernet.h>
#include <SPI.h>
#include <TimeLib.h>

byte ntpMessageBuffer[48];
const byte ntpMac[6] = {0xAA, 0xBB, 0xCC, 0x00, 0xFE, 0xED};
IPAddress ntpServer(129, 6, 15, 28);
EthernetUDP ethernet_UDP;
unsigned int ntpLocalPort = 8888;

void sendNtpRequest() {
  memset(ntpMessageBuffer, 0, 48);
  ntpMessageBuffer[0] = 0b11100011;
  ntpMessageBuffer[1] = 0;
  ntpMessageBuffer[2] = 6;
  ntpMessageBuffer[3] = 0xEC;
  ntpMessageBuffer[12] = 49;
  ntpMessageBuffer[13] = 0x4E;
  ntpMessageBuffer[14] = 49;
  ntpMessageBuffer[15] = 52;
  ethernet_UDP.beginPacket(ntpServer, 123);
  ethernet_UDP.write(ntpMessageBuffer, 48);
  ethernet_UDP.endPacket();
}

time_t getTime() {
  while (ethernet_UDP.parsePacket() > 0) {
  }

  sendNtpRequest();
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = ethernet_UDP.parsePacket();
    if (size >= 48) {
      ethernet_UDP.read(ntpMessageBuffer, 48);
      unsigned long secsSince1900;
      secsSince1900 = (unsigned long)ntpMessageBuffer[40] << 24;
      secsSince1900 |= (unsigned long)ntpMessageBuffer[41] << 16;
      secsSince1900 |= (unsigned long)ntpMessageBuffer[42] << 8;
      secsSince1900 |= (unsigned long)ntpMessageBuffer[43];
      return secsSince1900 - 2208988800UL;
    }
  }
  return 0;
}

void initTime() {
  while (Ethernet.begin(ntpMac) == 0) {
    Serial.println("Ethernet is not configured");
    delay(1000);
  }
  Serial.println("Ethernet is configured");
  ethernet_UDP.begin(ntpLocalPort);
  setSyncProvider(getTime);
}
