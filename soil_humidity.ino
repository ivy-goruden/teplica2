int humidityPin = A3;

class Soil_Humidity : public Sensor {
public:
  char name = "Влажность почвы";
  void init() {
    pinMode(pin, INPUT);
  }
  char[] getValue() {
    return analogRead(pin)
  }
}