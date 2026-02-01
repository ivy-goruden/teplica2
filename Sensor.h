#pragma once

#include <Arduino.h>
#include "Service.h"

class Sensor : public Service {
public:
  String name;

  Sensor(int p, unsigned long per)
      : Service(p, per), name("") {}

  virtual String getValue() = 0;
};

