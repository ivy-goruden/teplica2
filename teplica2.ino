#include "all_objects.h"

int lampPin = 1;
int motorPin = 7;
int motorPeriod = 500;
int soilHumidityPin = A1;
int dhtPin = A3;
int echoPin = A2;
int trigPin = 8;
int piezoPin = 6;

const int minSoilHumidity = 100;
const int water_max = 11;

void initServices();
void runDevices();

void setup() {
  Serial.begin(9600);
  initServices();
}
void loop() { runDevices(); }
