#include <LiquidCrystal.h>
#include <Arduino.h>

// const int buttonPin = 13;
// int buttonState = 0;
Time time = Time();
LiquidCrystal lcd(38, 36, 34, 32, 30, 28);
int dhtPin = 46;

Air_Humidity airHumidity = Air_Humidity(dhtPin, 2000);
Thermometer thermometer = Thermometer(dhtPin, 2000);
void setup() {
  lcd.begin(20, 4);
  lcd.print("STARTING....");
  Serial.begin(9600);
  sync_time();
}
void loop() {
  time_func();
  water_level();
  print_func();
  water_motor(levelSensor);
}
