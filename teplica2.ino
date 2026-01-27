#include <LiquidCrystal.h>
#include <TroykaDHT.h>
/////////////////////////////////
////////////////////////////////
#include <Ethernet.h> // for communication with NTP Server via UDP
#include <SPI.h>      // for communication with Ethernet Shield
#include <TimeLib.h>  // for update/display of time
byte mac[] = {0xAA, 0xBB, 0xCC, 0x00, 0xFE, 0xED};
IPAddress timeSrvr(129, 6, 15, 28);
unsigned long previousMillis_time = 0;
EthernetUDP ethernet_UDP;
unsigned int localPort = 8888;

// variable to store previous displayed time

time_t prevDisplay = 0;

// array to hold incoming/outgoing NTP messages
// NTP time message is 48 bytes long
byte messageBuffer[48];
///////////////////////////////
/////////////////////////////
float water_max = 11;
int piezoPin = 6;

int soil_humidity_val = 0;
int oldLevelSensor = 0;
DHT dht(48, DHT11);
int humidityPin = A3;
long levelSensor = 0;
unsigned long previousMillis_print = 0;
unsigned long previousMillis_level = 0;
unsigned long previousMillis_motor = 0;
unsigned long previousMillis_lamp = 0;
const byte averageFactor = 5;
long duration, cm;
int echoPin = A2;
int trigPin = 8;
int airPin = A9;
int water;
const int buttonPin = 13;
int buttonState = 0;

void lamp_func(int timer);
void termometr_func();
int hour_now = 0;
int minute_now = 0;
int second_now = 0;
LiquidCrystal lcd(38, 36, 34, 32, 30, 28);
void setup() {
  lcd.begin(20, 4);
  Serial.begin(9600);
  lcd.setCursor(0, 1);
  lcd.print("Soil Humidity: "); // 15
  lcd.setCursor(0, 0);
  lcd.print("Temperature: "); // 13
  lcd.setCursor(0, 2);
  lcd.print("Air Humidity: "); // 14
  lcd.setCursor(0, 3);
  lcd.print("Water level: "); // 13
  //  rtc.adjust(DateTime(2007,8,9, 5, 59, 30));
  //   water_level();

  ////////////////////////////////////////
  sync_time();
  Serial.println("start");
  while (oldLevelSensor == 0) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    oldLevelSensor = microsecondsToCentimeters(duration);
  }
  Serial.println("end");
  water_level();
  print_func();

  pinMode(buttonPin, INPUT);
  pinMode(A5, INPUT);

  //  Serial.print(oldLevelSensor);
  pinMode(8, OUTPUT);
  //  digitalWrite(8, HIGH);
  pinMode(lamp, OUTPUT);
  pinMode(termometr, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  dht.begin();
}
void voice(int water) {
  if (water >= water_max) {
    tone(piezoPin, 10);
  } else {
    noTone(piezoPin);
  }
}
void print_func() {
  Serial.println("soil");
  int soil_humidity_val = analogRead(humidityPin);
  lcd.setCursor(0, 1);
  lcd.print("Soil Humidity: "); // 15
  lcd.setCursor(14, 1);
  lcd.print(soil_humidity_val);
  dht.read();
  int temp = dht.getTemperatureC();
  // lcd.setCursor(0, 0);
  // lcd.print("Temperature: ");//13
  lcd.setCursor(12, 0);
  lcd.print(temp);
  // lcd.setCursor(0, 2);
  // lcd.print("Air Humidity: ");//14
  lcd.setCursor(13, 2);
  lcd.print(dht.getHumidity());
  // lcd.setCursor(0, 3);
  // lcd.print("Water level: ");//13
  int watr = int(100 - (levelSensor / water_max * 100));
  lcd.setCursor(12, 3);
  lcd.print(watr);
  lcd.print("%");
  //  lcd.begin(20, 4);
  //  lcd.setCursor(0,1);
  //  lcd.println("Soil Humidity: ");
  //  Serial.println("soil end");
}
void loop() {
  time_func();

  if ((unsigned long)(currentMillis - previousMillis_motor) >= 100) {
    previousMillis_level = currentMillis;
    water_level();
  }
  print_func();
  voice(levelSensor);
  if ((unsigned long)(currentMillis - previousMillis_print) >= 2000) {
    previousMillis_print = currentMillis;
  }
  if (hour_now == 19 and minute_now == 0 and second_now <= 1) {
    previousMillis_motor = currentMillis;
    water_motor(levelSensor);
  }
  if ((unsigned long)(currentMillis - previousMillis_motor) >= 500) {
    digitalWrite(motorPin, LOW);
  }
}

/*
   helper function for getTime()
   this function sends a request packet 48 bytes long
*/
void sendRequest(IPAddress address) {
  // set all bytes in messageBuffer to 0
  memset(messageBuffer, 0, 48);

  // create the NTP request message

  messageBuffer[0] = 0b11100011; // LI, Version, Mode
  messageBuffer[1] = 0;          // Stratum, or type of clock
  messageBuffer[2] = 6;          // Polling Interval
  messageBuffer[3] = 0xEC;       // Peer Clock Precision
  // array index 4 to 11 is left unchanged - 8 bytes of zero for Root Delay &
  // Root Dispersion
  messageBuffer[12] = 49;
  messageBuffer[13] = 0x4E;
  messageBuffer[14] = 49;
  messageBuffer[15] = 52;

  // send messageBuffer to NTP server via UDP at port 123
  ethernet_UDP.beginPacket(address, 123);
  ethernet_UDP.write(messageBuffer, 48);
  ethernet_UDP.endPacket();
}
