#pragma once

#include "Device.h"

class Piezo : public Device {
public:
  Piezo(int p, unsigned long per)
      : Device(p, per) {}

  void init() {
    pinMode(pin, OUTPUT);
  }

  void run() {
    if (isTime()) {
      if (enabled) {
        noTone(pin);
      } else {
        tone(pin, 10);
      }
      enabled = !enabled;
      prev_millis = millis();
    }
  }
};

