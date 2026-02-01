#pragma once

#include <Arduino.h>

class Service {
protected:
  int pin;
  unsigned long prev_millis;
  unsigned long period;

  Service(int p, unsigned long per) : pin(p), prev_millis(0), period(per) {}

  bool isTime() { return millis() >= prev_millis + period; }

public:
  virtual void init() = 0;
};
