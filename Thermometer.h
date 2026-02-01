#pragma once

#include "Sensor.h"
#include <TroykaDHT.h>

class Thermometer : public Sensor {
private:
  DHT dht;

public:
  Thermometer(int p, unsigned long per) : Sensor(p, per), dht(p, DHT11) {
    name = "Temperature";
  }

  void init() { dht.begin(); }

  String getValue() {
    dht.read();
    switch (dht.getState()) {
    case DHT_OK:
      return String(dht.getTemperatureC());
    case DHT_ERROR_CHECKSUM:
      return "Checksum error";
    case DHT_ERROR_TIMEOUT:
      return "Time out error";
    case DHT_ERROR_NO_REPLY:
      return "Sensor not connected";
    }
    return "";
  }
};

class Air_Humidity : public Sensor {
private:
  DHT dht;

public:
  Air_Humidity(int p, unsigned long per) : Sensor(p, per), dht(p, DHT11) {
    name = "Air Humidity";
  }

  void init() { dht.begin(); }

  String getValue() {
    dht.read();
    switch (dht.getState()) {
    case DHT_OK:
      return String(dht.getHumidity());
    case DHT_ERROR_CHECKSUM:
      return "Checksum error";
    case DHT_ERROR_TIMEOUT:
      return "Time out error";
    case DHT_ERROR_NO_REPLY:
      return "Sensor not connected";
    }
    return "";
  }
};
