#include "all_objects.h"

int lampPin = 1;
int motorPin = 7;
int motorPeriod = 500;
int soilHumidityPin = A3;
int dhtPin = 46;
int echoPin = A2;
int trigPin = 8;
int piezoPin = 6;

const int minSoilHumidity = 100;

void initServices();
void runDevices();

void setup() {
  Serial.begin(9600);
  initServices();
}
void loop() { runDevices(); }
