class Service {
  protected::
    int pin;
    unsigned long prev_millis = 0;
    unsigned long period;

    virtual void init() = 0;
    virtual void run() = 0;
    bool isTime(){
      return getMillis() >= prev_millis + period
    }
};

class Sensor: public Service {
  public:
    char name;
    virtual int getValue() = 0;
}

class Device: public Service {
  virtual void run() = 0;
  Device(p, per) : pin(p), prev_millis(0), period(per) {} 
}