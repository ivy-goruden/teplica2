int lampPin = 1;

// void lamp_func()
// {
//     if (lamp_sost = LOW) lamp_sost = HIGH;
//     if (lamp_sost = HIGH)lamp_sost = LOW;
//     digitalWrite(lamp, lamp_sost);
// }

class Lamp : public Device{
    private:
        bool enabled = false;
    public:
        int hour = 7; // 7 утра
        int minute = 0;
    void init(){
        pinMode(lamp, OUTPUT);
    }
    void run(){
        if(getHour()==hour and getMinute()==minute and getSecond()<=1){
            digitalWrite(pin, lampstate);
            enabled = !enabled;
            prev_millis=getMillis();
        }
        if (isTime() and enabled) {
            digitalWrite(pin, LOW);
            prev_millis=getMillis();
        }
    }
}

lamp = Lamp(lampPin, 500);