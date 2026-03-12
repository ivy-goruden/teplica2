#pragma once

#include "Bobber.h"
#include "Device.h"

class Piezo : public Device {
public:
  Piezo(int p, unsigned long per, Bobber &b) : Device(p, per), bobber(b) {}
  Bobber &bobber;
  void init() { pinMode(pin, OUTPUT); }

  void run() {
    if (isTime()) {
      if (bobber.enoughWater()) {
        noTone(pin);
        enabled = false;
      } else if (!enabled) {
        tone(pin, 10);
        enabled = true;
      }
      prev_millis = millis();
    }
  }
};
