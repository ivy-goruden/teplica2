int echoPin = A2;
int trigPin = 8;
int piezoPin = 6;

class Piezo : public Device {
public:
  Piezo(int p, unsigned long per) : Device(p, per) {}
  void init() { pinMode(pin, OUTPUT); }
  void run() {
    if (isTime()) {
      if (enabled) {
        noTone(pin);
      } else {
        tone(pin, 10);
      }
      enabled = !enabled;
    }
  }
};

class Water_Level : public Sensor {
public:
  Water_Level(int echoPinValue, int trigPinValue, unsigned long per,
              Piezo piezoDevice)
      : Sensor(echoPinValue, per), echoPin(echoPinValue), trigPin(trigPinValue),
        oldLevelSensor(0), water(0), water_max(11), piezo(piezoDevice) {
    name = "Бак наполнен на";
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
      water = int(100 - (levelSensor / water_max * 100));
      checkWater(water);
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
