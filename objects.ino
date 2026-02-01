#include "all_objects.h"

Soil_Humidity soilHumidity(soilHumidityPin, 2000, minSoilHumidity);
Air_Humidity airHumidity(dhtPin, 2000);
Thermometer thermometer(dhtPin, 2000);
Piezo piezo(piezoPin, 0);
Water_Level waterLevel(echoPin, trigPin, 2000, piezo);
Lamp lamp(lampPin, 500);
waterMotor motor(motorPin, motorPeriod, soilHumidity);

Sensor *sensors[] = {&airHumidity, &thermometer, &soilHumidity, &waterLevel};
const int SENSORS_COUNT = sizeof(sensors) / sizeof(sensors[0]);

LCD lcd(1000, sensors, SENSORS_COUNT);

Device *devices[] = {&lamp, &motor, &lcd};
const int DEVICES_COUNT = sizeof(devices) / sizeof(devices[0]);

void initServices() {
  for (int i = 0; i < SENSORS_COUNT; ++i) {
    sensors[i]->init();
  }
  for (int i = 0; i < DEVICES_COUNT; ++i) {
    devices[i]->init();
  }
  initTime();
}

void runDevices() {
  for (int i = 0; i < DEVICES_COUNT; ++i) {
    devices[i]->run();
  }
}
