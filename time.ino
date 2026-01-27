

void sync_time() {
  while (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");  // display error
    delay(1000);                                                // retry after 1 sec
  }
  ethernet_UDP.begin(localPort);
  setSyncProvider(getTime);
}

time_t getTime() {
  while (ethernet_UDP.parsePacket() > 0);  // discard packets remaining to be parsed

  Serial.println("Transmit NTP Request message");

  // send packet to request time from NTP server
  sendRequest(timeSrvr);

  // wait for response
  uint32_t beginWait = millis();

  while (millis() - beginWait < 1500) {

    int size = ethernet_UDP.parsePacket();

    if (size >= 48) {
      Serial.println("Receiving NTP Response");

      // read data and save to messageBuffer
      ethernet_UDP.read(messageBuffer, 48);

      // NTP time received will be the seconds elapsed since 1 January 1900
      unsigned long secsSince1900;

      // convert to an unsigned long integer the reference timestamp found at byte 40 to 43
      secsSince1900 = (unsigned long)messageBuffer[40] << 24;
      secsSince1900 |= (unsigned long)messageBuffer[41] << 16;
      secsSince1900 |= (unsigned long)messageBuffer[42] << 8;
      secsSince1900 |= (unsigned long)messageBuffer[43];

      // returns UTC time
      return secsSince1900 - 2208988800UL;
    }
  }

  // error if no response
  Serial.println("Error: No Response.");
  return 0;
}
void time_func() {
  Serial.print(hour_now);
  Serial.print(":");
  Serial.print(minute_now);
  Serial.print(":");
  Serial.println(second_now);
  if (timeStatus() != timeNotSet) {  // check if the time is successfully updated
    hour_now = hour();
    minute_now = minute();
    second_now = second();
  }
}
int getHour(){
  return hour();
}

int getMinute(){
  return minute();
}

int getSecond(){
  return second();
}

unsigned long getMillis(){
  return millis();
}
