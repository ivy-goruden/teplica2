#pragma once

#include "Device.h"
#include <TimeLib.h>

class Lamp : public Device {
public:
  int hour_start = 6;
  int minute_start = 0;
  int hour_end = 22;
  int minute_end = 0;

  Lamp(int p, unsigned long per) : Device(p, per) {}

  void init() { pinMode(pin, OUTPUT); }

  void run() {
    if ((::hour() > hour_start || ::hour() < hour_end) && !enabled) {
      digitalWrite(pin, HIGH);
      enabled = true;
      prev_millis = millis();
    }
    if ((::hour() < hour_start || ::hour() > hour_end) && enabled) {
      digitalWrite(pin, LOW);
      enabled = false;
      prev_millis = millis();
    }
  }
};
