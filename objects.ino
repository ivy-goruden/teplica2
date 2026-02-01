class Service {
protected:
  int pin;
  unsigned long prev_millis;
  unsigned long period;
  Service(int p, unsigned long per) : pin(p), prev_millis(0), period(per) {}
  virtual void init() = 0;
  bool isTime() { return millis() >= prev_millis + period; }
};

class Sensor : public Service {
public:
  String name;
  Sensor(int p, unsigned long per) : Service(p, per), name("") {}
  virtual String getValue() = 0;
};

class Device : public Service {
protected:
  bool enabled;

public:
  Device(int p, unsigned long per) : Service(p, per), enabled(false) {}
  virtual void run() = 0;
  bool isWorking() { return enabled; }
};

Soil_Humidity soilHumidity(soilHumidityPin, 2000, minSoilHumidity);
Air_Humidity airHumidity(dhtPin, 2000);
Thermometer thermometer(dhtPin, 2000);
Piezo piezo(piezoPin, 0);
Water_Level waterLevel(echoPin, trigPin, 2000, piezo);
Lamp lamp(lampPin, 500);
waterMotor motor(motorPin, motorPeriod, soilHumidity);

Sensor *sensors[] = {&airHumidity, &thermometer, &soilHumidity, &waterLevel};
const int SENSORS_COUNT = sizeof(sensors) / sizeof(sensors[0]);

Device *devices[] = {&lamp, &motor};
const int DEVICES_COUNT = sizeof(devices) / sizeof(devices[0]);

void initServices() {
  for (int i = 0; i < SENSORS_COUNT; ++i) {
    sensors[i]->init();
  }
  for (int i = 0; i < DEVICES_COUNT; ++i) {
    devices[i]->init();
  }
  Time time;
  time.init();
}

void runDevices() {
  for (int i = 0; i < DEVICES_COUNT; ++i) {
    devices[i]->run();
  }
}
