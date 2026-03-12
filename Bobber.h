#pragma once

#include "Bobber.h"
#include "Sensor.h"

class Bobber : public Sensor {

public:
  Bobber(int pin, unsigned long per) : Sensor(pin, per) { name = "Water"; }
  void init() { pinMode(pin, INPUT); }

  String getValue() {
    if (digitalRead(pin)) {
      return "Enough";
    } else {
      return "Not Enough";
    }
  }

  bool enoughWater() { return digitalRead(pin); }
};