class Service {
  protected:
    int pin;
    unsigned long prev_millis = 0;
    unsigned long period;

    virtual void init() = 0;
    bool isTime(){
      return getMillis() >= prev_millis + period
    }
};

class Sensor: public Service {
  public:
    char name;
    virtual char[] getValue() = 0;
    Sensor(p, per) : pin(p), prev_millis(0), period(per) {} 
}

class Device: public Service {
  private:
    bool enabled = false;
  public:
    virtual void run() = 0;
    Device(p, per) : pin(p), prev_millis(0), period(per) {}
    void isWorking(){
      return enabled;
    }
}