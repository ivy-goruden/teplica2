#include "all_objects.h"

RTC_Manager rtcManager;

Soil_Humidity soilHumidity(soilHumidityPin, 2000, minSoilHumidity);
Air_Humidity airHumidity(dhtPin, 2000);
Thermometer thermometer(dhtPin, 2000);
Lamp lamp(lampPin, 500);
Bobber bobber(bobberPin, 1000);
Piezo piezo(piezoPin, 1000, bobber);
waterMotor motor(motorPin, motorPeriod, soilHumidity, bobber);

Sensor *sensors[] = {&airHumidity, &thermometer, &soilHumidity, &bobber};
const int SENSORS_COUNT = sizeof(sensors) / sizeof(sensors[0]);

LCD lcd(1500, sensors, SENSORS_COUNT);

Device *devices[] = {&lamp, &motor, &lcd};
const int DEVICES_COUNT = sizeof(devices) / sizeof(devices[0]);

void initServices() {
  for (int i = 0; i < SENSORS_COUNT; ++i) {
    sensors[i]->init();
  }
  for (int i = 0; i < DEVICES_COUNT; ++i) {
    devices[i]->init();
  }
  rtcManager.init();
}

void runDevices() {
  for (int i = 0; i < DEVICES_COUNT; ++i) {
    devices[i]->run();
  }
}
