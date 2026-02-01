#pragma once

#include "Service.h"

class Device : public Service {
protected:
  bool enabled;

public:
  Device(int p, unsigned long per)
      : Service(p, per), enabled(false) {}

  virtual void run() = 0;

  bool isWorking() const { return enabled; }
};

