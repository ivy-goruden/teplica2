// int motorPin = 7;


 
// void water_motor(int water){
// //  Serial.print(buttonState);
//   int soil_humidity_val = analogRead(humidityPin);
//   if (water<water_max and soil_humidity_val<=400){
//       // turn LED on:
//       digitalWrite(7, HIGH);
//       delay(500);
//       digitalWrite(7, LOW);      

//   }
// }


class waterMotor : public Service{
  private:
    const int pin = 7;
    unsigned long prev_millis = 0;
    unsigned long period = 500;
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
      if (isTime() and !enabled) {
        digitalWrite(pin, LOW);
        prev_millis=getMillis();
      }
    }
    bool needWater(){
      //unimplemented
      return true;
    }
}