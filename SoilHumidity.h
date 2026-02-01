#pragma once

#include "Sensor.h"

class Soil_Humidity : public Sensor {
private:
  int minHumidity;

public:
  Soil_Humidity(int p, unsigned long per, int minHum)
      : Sensor(p, per), minHumidity(minHum) {
    name = "Soil Humidity";
  }

  void init() {
    pinMode(pin, INPUT);
  }

  String getValue() {
    return String(analogRead(pin));
  }

  bool needWater() {
    return analogRead(pin) <= minHumidity;
  }
};

