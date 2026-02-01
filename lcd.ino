class LCD : public Device {
protected:
  LiquidCrystal lcd(38, 36, 34, 32, 30, 28);
  Sensor *sensors;
  int index;
  void init() {
    lcd.begin(20, 4);
    lcd.print("STARTING....");
    lcd.setCursor(0, 0);
    lcd.autoscroll();
  }
  void run() {
    if (isTime() && len(sensors) > 0) {
      index = (index + 1) % len(sensors);
      lcd.print(sensors[index].name + ":" + sensors[index].getValue);
    }
  }
  LCD(Sensor *sensors) : sensors(sensors), index(0) {}
}
