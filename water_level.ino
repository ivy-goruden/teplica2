int echoPin = A2;
int trigPin = 8;
int piezoPin = 6;


Piezo piezo = Piezo(piezoPin, 0);
Water_Level water_level = Water_Level(echoPin, trigPin, 2000, piezo);

class Water_Level : public Sensor {
public:
  String name = "Бак наполнен на";
  void init() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
  }
  String getValue() {
    long duration, cm;
    if (isTime()) {
      levelSensor = getDistance();
      if (levelSensor != 0) {
        levelSensor = round((oldLevelSensor * (averageFactor - 1) + levelSensor) / averageFactor);
        oldLevelSensor = levelSensor;
      } else {
        levelSensor = oldLevelSensor;
      }
      water = int(100 - (levelSensor / water_max * 100));
      checkWater(water);
    }
    return String(water) + "%";
  }
  Water_Level(int echoPin, int trigPin, unsigned long per, Piezo piezo)
    : echoPin(echoPin), trigPin(trigPin), peiod(per), piezo(piezo) {}
private:
  int echoPin;
  int trigPin;
  int oldLevelSensor;
  int water = 0;
  const byte averageFactor = 5;
  float water_max = 11;
  Piezo piezo;
  const int minWater = 10;
  int microsecondsToCentimeters(long microseconds) {
    return microseconds / 29 / 2;
  }
  int getDistance(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    return microsecondsToCentimeters(duration);
  }
  void checkWater(int water){
    if (piezo.isWorking() && water >= waterMin){
      piezo.run();
    }
    if (!piezo.isWorking() && water < waterMin){
      piezo.run();
    }
  }
}

class Piezo : public Device {

public:
  void init() {
    pinMode(pin, OUTPUT);
  }
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

  Piezo(int pin, unsigned long per)
    : (pin(pin), peiod(per)) {}
}
