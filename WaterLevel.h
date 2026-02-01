#pragma once

#include "Piezo.h"
#include "Sensor.h"

class Water_Level : public Sensor {
public:
  Water_Level(int echoPinValue, int trigPinValue, unsigned long per,
              Piezo piezoDevice, int water_max)
      : Sensor(echoPinValue, per), echoPin(echoPinValue), trigPin(trigPinValue),
        oldLevelSensor(0), water(0), water_max(water_max), piezo(piezoDevice) {
    name = "Water level";
  }

  void init() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  String getValue() {
    if (isTime()) {
      int levelSensor = getDistance();
      if (levelSensor != 0) {
        levelSensor =
            round((oldLevelSensor * (averageFactor - 1) + levelSensor) /
                  averageFactor);
        oldLevelSensor = levelSensor;
      } else {
        levelSensor = oldLevelSensor;
      }
      water = min(max(int(100 - (levelSensor / water_max * 100)), 0), 100);
      checkWater(water);
      prev_millis = millis();
    }
    return String(water) + "%";
  }

private:
  int echoPin;
  int trigPin;
  int oldLevelSensor;
  int water;
  const byte averageFactor = 5;
  float water_max;
  Piezo piezo;
  const int minWater = 10;

  int microsecondsToCentimeters(long microseconds) {
    return microseconds / 29 / 2;
  }

  int getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    return microsecondsToCentimeters(duration);
  }

  void checkWater(int value) {
    if (piezo.isWorking() && value >= minWater) {
      piezo.run();
    }
    if (!piezo.isWorking() && value < minWater) {
      piezo.run();
    }
  }
};
