#include <Ethernet.h>  // for communication with NTP Server via UDP
#include <SPI.h>       // for communication with Ethernet Shield
#include <TimeLib.h>   // for update/display of time

class Time {
private:
  byte messageBuffer[48];
  byte mac[] = { 0xAA, 0xBB, 0xCC, 0x00, 0xFE, 0xED };
  IPAddress timeSrvr(129, 6, 15, 28);
  EthernetUDP ethernet_UDP;
  unsigned int localPort = 8888;
  void init(){
    
  }
  void sendRequest(IPAddress address) {
    memset(messageBuffer, 0, 48);
    messageBuffer[0] = 0b11100011;  // LI, Version, Mode
    messageBuffer[1] = 0;           // Stratum, or type of clock
    messageBuffer[2] = 6;           // Polling Interval
    messageBuffer[3] = 0xEC;        // Peer Clock Precision
    messageBuffer[12] = 49;
    messageBuffer[13] = 0x4E;
    messageBuffer[14] = 49;
    messageBuffer[15] = 52;
    ethernet_UDP.beginPacket(address, 123);
    ethernet_UDP.write(messageBuffer, 48);
    ethernet_UDP.endPacket();
  }
  time_t getTime() {
    while (ethernet_UDP.parsePacket() > 0) {};

    Serial.println("Transmit NTP Request message");
    sendRequest(timeSrvr);
    uint32_t beginWait = millis();
    while (millis() - beginWait < 1500) {
      int size = ethernet_UDP.parsePacket();

      if (size >= 48) {
        Serial.println("Receiving NTP Response");
        ethernet_UDP.read(messageBuffer, 48);
        unsigned long secsSince1900;

        secsSince1900 = (unsigned long)messageBuffer[40] << 24;
        secsSince1900 |= (unsigned long)messageBuffer[41] << 16;
        secsSince1900 |= (unsigned long)messageBuffer[42] << 8;
        secsSince1900 |= (unsigned long)messageBuffer[43];

        return secsSince1900 - 2208988800UL;
      }
    }

    Serial.println("Error: No Response.");
    return 0;
  }
public:
  void sync_time() {
    while (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");  // display error
      delay(1000);                                                // retry after 1 sec
    }
    ethernet_UDP.begin(localPort);
    setSyncProvider(getTime);
  }
  int getHour() {
    return hour();
  }

  int getMinute() {
    return minute();
  }

  int getSecond() {
    return second();
  }

  unsigned long getMillis() {
    return millis();
  }
}
