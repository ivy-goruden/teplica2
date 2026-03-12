#pragma once

#include <DS1307RTC.h>
#include <TimeLib.h>
#include <Wire.h>

class RTC_Manager {

public:
  void init() {
    tmElements_t tm;
    while (!RTC.read(tm)) {
      if (RTC.chipPresent()) {
        Serial.println("The DS1307 is stopped.  Please run the SetTime");
        Serial.println("example to initialize the time and begin running.");
        Serial.println();
      } else {
        Serial.println("DS1307 read error!  Please check the circuitry.");
        Serial.println();
      }
      delay(9000);
    }
    setSyncProvider(RTC.get);
  }
};
