#pragma once

#include "Device.h"
#include "Sensor.h"
#include <LiquidCrystal.h>

class LCD : public Device {
private:
  LiquidCrystal lcd;
  Sensor **sensors;
  int sensorsCount;
  int index;

public:
  LCD(unsigned long per, Sensor **sensorsArray, int count)
      : Device(0, per), lcd(38, 36, 34, 32, 30, 28), sensors(sensorsArray),
        sensorsCount(count), index(0) {}

  void init() {
    lcd.begin(20, 4);
    lcd.print("STARTING....");
    lcd.setCursor(0, 0);
  }

  void run() {
    if (isTime() && sensorsCount > 0) {
      index = (index + 1) % sensorsCount;
      lcd.setCursor(0, index % 4);
      String text =
          String(sensors[index]->name + ": " + sensors[index]->getValue());
      if (text.length() > 20) {
        text = text.substring(0, 20);
      }
      Serial.println(text);
      lcd.print(text);
      prev_millis = millis();
    }
  }
};
