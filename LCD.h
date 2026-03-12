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
      : Device(0, per), lcd(10, 8, 5, 4, 3, 2), sensors(sensorsArray),
        sensorsCount(count), index(0) {}
  void clearLine(int line) {
    lcd.setCursor(0, line); // Move the cursor to the start of the desired line
    for (int i = 0; i < 20; i++) {
      lcd.print(" "); // Print a space character
    }
    lcd.setCursor(
        0, line); // Return the cursor to the start of the line for new text
  }
  void init() {
    lcd.begin(20, 4);
    lcd.print("STARTING....");
    lcd.setCursor(0, 0);
  }

  void run() {
    if (isTime() && sensorsCount > 0) {
      index = (index + 1) % sensorsCount;
      lcd.setCursor(0, index % 4);
      clearLine(index % 4);
      String text =
          String(sensors[index]->name + ": " + sensors[index]->getValue());
      if (text.length() > 20) {
        text = text.substring(0, 20);
      }
      lcd.print(text);
      prev_millis = millis();
    }
  }
};
