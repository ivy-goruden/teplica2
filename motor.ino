int motorPin = 7;
int motorPeriod = 500;

class waterMotor : public Device{
  public:
    int hour = 19;
    int minute = 0;
    bool enabled = false;
    void init(){
      pinMode(pin, OUTPUT);
    }
    void run(){
      if(getHour()==hour and getMinute()==minute and getSecond()<=1 and needWater()){
        water_motor(levelSensor);
        enabled = true;
        prev_millis=getMillis();
      }
      if (isTime() and enabled) {
        digitalWrite(pin, LOW);
        prev_millis=getMillis();
      }
    }
    bool needWater(){
      //unimplemented
      return true;
    }
}

waterMotor motor = waterMotor(motorPin, motorPeriod);