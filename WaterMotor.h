#pragma once

#include "Bobber.h"
#include "Device.h"
#include "SoilHumidity.h"
#include <TimeLib.h>

class waterMotor : public Device {
private:
  Soil_Humidity &soilHumidity;
  Bobber &bobber;

public:
  int hour = 8;
  int minute = 30;

  waterMotor(int p, unsigned long per, Soil_Humidity &soilHumSensor,
             Bobber &bobberSensor)
      : Device(p, per), soilHumidity(soilHumSensor), bobber(bobberSensor) {}

  void init() { pinMode(pin, OUTPUT); }

  void run() {
    if (::hour() == hour && ::minute() == minute && ::second() <= 1 &&
        needWater() && hasWater()) {
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
  bool hasWater() { return bobber.enoughWater(); }
};
