#include <TroykaDHT.h>

class Thermometer : public Sensor {
public:
  char name = "Температура";
  void init() {
    DHT dht(pin, DHT11);
    dht.begin();
  }
  char[] getValue() {
    dht.read();
    switch(dht.getState()) {
    case DHT_OK:
      return dht.getTemperatureC();
    case DHT_ERROR_CHECKSUM:
      return "Checksum error";
    // превышение времени ожидания
    case DHT_ERROR_TIMEOUT:
      return "Time out error";
    case DHT_ERROR_NO_REPLY:
      return "Sensor not connected";
  }
  }
}

class Air_Humidity : public Sensor {
public:
  char name = "Влажность воздуха";
  void init() {
    DHT dht(pin, DHT11);
    dht.begin();
  }
  char[] getValue() {
    dht.read();
    switch(dht.getState()) {
    case DHT_OK:
      return dht.getHumidity();
    case DHT_ERROR_CHECKSUM:
      return "Checksum error";
    // превышение времени ожидания
    case DHT_ERROR_TIMEOUT:
      return "Time out error";
    case DHT_ERROR_NO_REPLY:
      return "Sensor not connected";
  }
  }
}
