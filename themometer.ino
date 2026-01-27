// int termometr = A8;

// class Sensor: public Service {
//   public:
//     char name;
//     virtual int getValue() = 0;
// }

class Thermometer : public Sensor {
public:
  char name = "Температура" void init() {
    TroykaThermometer thermometer(pin);
    pinMode(pin, INPUT);
  }
  void getValue() {}
}