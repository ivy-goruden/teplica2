int lampPin = 1;

class Lamp : public Device{
    private:
        bool enabled = false;
    public:
        int hour = 7; // 7 утра
        int minute = 0;
    void init(){
        pinMode(pin, OUTPUT);
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

Lamp lamp = Lamp(lampPin, 500);