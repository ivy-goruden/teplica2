#pragma once

#include "Device.h"
#include <TimeLib.h>

class Lamp : public Device {
public:
  int hour = 7;
  int minute = 0;

  Lamp(int p, unsigned long per) : Device(p, per) {}

  void init() { pinMode(pin, OUTPUT); }

  void run() {
    if (::hour() == hour && ::minute() == minute && ::second() <= 1) {
      digitalWrite(pin, HIGH);
      enabled = !enabled;
      prev_millis = millis();
    }
    if (isTime() && enabled) {
      digitalWrite(pin, LOW);
      enabled = false;
      prev_millis = millis();
    }
  }
};
