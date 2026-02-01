int lampPin = 1;

class Lamp : public Device {
public:
  int hour = 7; // 7 утра
  int minute = 0;
  void init() { pinMode(pin, OUTPUT); }
  Lamp(int p, unsigned long per) : Device(p, per) {}
  void run() {
    if (hour() == this->hour && minute() == this->minute && second() <= 1) {
      digitalWrite(pin, HIGH);
      enabled = !enabled;
      prev_millis = millis();
    }
    if (isTime() && enabled) {
      digitalWrite(pin, LOW);
      enabled = false;
      prev_millis = millis();
    }
  }
};
