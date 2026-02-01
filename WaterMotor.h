#pragma once

#include "Device.h"
#include "SoilHumidity.h"
#include <TimeLib.h>

class waterMotor : public Device {
private:
  Soil_Humidity soilHumidity;

public:
  int hour = 19;
  int minute = 0;

  waterMotor(int p, unsigned long per, Soil_Humidity soilHumSensor)
      : Device(p, per), soilHumidity(soilHumSensor) {}

  void init() { pinMode(pin, OUTPUT); }

  void run() {
    if (::hour() == hour && ::minute() == minute && ::second() <= 1 &&
        needWater()) {
      digitalWrite(pin, HIGH);
      enabled = true;
      prev_millis = millis();
    }
    if (isTime() && enabled) {
      digitalWrite(pin, LOW);
      enabled = false;
      prev_millis = millis();
    }
  }

  bool needWater() { return soilHumidity.needWater(); }
};
