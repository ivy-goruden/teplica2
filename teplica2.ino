#include <Arduino.h>
#include <LiquidCrystal.h>

// const int buttonPin = 13;
// int buttonState = 0;
const int minSoilHumidity = 100;

void initServices();
void runDevices();

void setup() {
  Serial.begin(9600);
  initServices();
}
void loop() { runDevices(); }
