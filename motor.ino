int motorPin = 7;
int motorPeriod = 500;

class waterMotor : public Device {
private:
  Soil_Humidity soilHumidity;

public:
  int hour = 19;
  int minute = 0;
  void init() { pinMode(pin, OUTPUT); }
  waterMotor(int p, unsigned long per, Soil_Humidity soilHumSensor)
      : Device(p, per), soilHumidity(soilHumSensor) {}
  void run() {
    if (hour() == this->hour && minute() == this->minute && second() <= 1 &&
        needWater()) {
      digitalWrite(pin, HIGH);
      enabled = true;
      prev_millis = millis();
    }
    if (isTime() && enabled) {
      digitalWrite(pin, LOW);
      enabled = false;
      prev_millis = millis();
    }
  }
  bool needWater() { return soilHumidity.needWater(); }
};
