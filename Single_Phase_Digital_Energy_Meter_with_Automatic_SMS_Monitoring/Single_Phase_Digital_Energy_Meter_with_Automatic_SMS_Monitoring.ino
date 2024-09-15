#include <SoftwareSerial.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <DS3231.h>
#include "EmonLib.h"
#define I2C_ADDR 0x27
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#define BACKLIGHT 3
#define TIMEOUT 5000
#define VOLT_CAL 154.91
#define CURRENT_CAL 66.45

SoftwareSerial sim800(2,3);

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
EnergyMonitor emon1;
File EnerFile;


DS3231  rtc(SDA, SCL);
Time t;


float volts = 0;
float amps = 0;
float power = 0;
float energy = 0;


const int chipSelect = 10;
char incomingChar;
String EnergyString;
String DateString;
String TimeString;

unsigned int currSec;
unsigned int nextSec = 0;
unsigned int currSec2;
unsigned int nextSec2 = 0;
unsigned int currSec3;
unsigned int nextSec3 = 0;
unsigned int currMin;
unsigned int nextMin = 0;
unsigned int minutes = 0;
unsigned int currDate;
unsigned int nextDate = 0;

const int sampleInterval = 5;    //interval in minutes
const int billDate = 1;          //schedule date of billing


void setup(){
  sim800.begin(9600);
  Serial.begin(9600);
  lcd.begin (20,4);
  lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(HIGH);
  rtc.begin();
  emon1.voltage (1,VOLT_CAL,1.7);
  emon1.current (0,CURRENT_CAL);
  if (SD.begin(chipSelect))
  EnerFile = SD.open("ENER.txt");
  if (EnerFile){
    while (EnerFile.available()){
      energy = EnerFile.parseFloat();
    }
    EnerFile.close();
  }
  delay(10000);
  sim800.println("AT");
  delay(1000);
  sim800.println("AT+CMGF=1");
  delay(1000);
  sim800.println("AT+CNMI=2,2,0,0,0");
  delay(1000);
  send_ready();
}



void send_ready(){
  sim800.println("AT+CMGS=\"09487278245\"");       //Change sim number
  delay(500);
  sim800.println("Power Meter: READY");
  sim800.write(0x1a);
  delay(500);
}



void send_data(){
  EnergyString = String(energy);
  DateString = String(rtc.getDateStr());
  TimeString = String(rtc.getTimeStr());
  delay(500);
  sim800.println("AT+CMGS=\"09487278245\"");       //Change sim number
  delay(500);
  sim800.print("SN:635425254; Dela Cuadra; Fatima, GSC; ");          //Change info
  sim800.print(EnergyString);
  sim800.print("kWhr; ");
  sim800.print(DateString);
  sim800.print("; ");
  sim800.println(TimeString);
  sim800.write(0x1a);
  delay(500);
}



void parameters(){
  emon1.calcVI(20,2000);
  float supplyVoltage = emon1.Vrms;
  float currentDrawn = emon1.Irms;
  float sum_of_volts = 0;
  float sum_of_amps = 0;
  for (int x = 0; x < 300; x++){
    sum_of_volts += supplyVoltage;
    sum_of_amps += currentDrawn;
  }
  volts = sum_of_volts/300;
  amps = (sum_of_amps/300) - 0.10823;
  power = volts * amps ;
  currSec = t.sec;
  if (nextSec != currSec){
    nextSec = t.sec;
    energy = energy + (power)/(3600000);
  }
  if (amps < 0){
    amps = 0;
    power = 0;
  }
}



void displaydata(){
  currSec2 = t.sec;
  if (nextSec2 != currSec2){
    nextSec2 = t.sec;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Voltage: ");
    lcd.setCursor(8,0);
    lcd.print(volts);
    lcd.setCursor(16,0);
    lcd.print("V");
    lcd.setCursor(0,1);
    lcd.print("Current: ");
    lcd.setCursor(8,1);
    lcd.print(amps);
    lcd.setCursor(16,1);
    lcd.print("A");
    lcd.setCursor(0,2);
    lcd.print("Power: ");
    lcd.setCursor(8,2);
    lcd.print(power);
    lcd.setCursor(16,2);
    lcd.print("W");
    lcd.setCursor(0,3);
    lcd.print("Energy: ");
    lcd.setCursor(8,3);
    lcd.print(energy);
    lcd.setCursor(16,3);
    lcd.print("kWhr");
  }
}



void save(){
  currSec3 = t.sec;
  if (nextSec3 != currSec3){
    nextSec3 = t.sec;
    SD.remove("ENER.txt");
    EnerFile = SD.open("ENER.txt", FILE_WRITE);
    if (EnerFile){
      EnerFile.print(energy);
      EnerFile.close();
    }
  }
}



void autoSend_sample(){
  currMin = t.min;
  if (nextMin != currMin){
    nextMin = t.min;
    minutes++;
    if (minutes >= sampleInterval){
      send_data();
      minutes = 0;
    }
  }
}



void autoSend(){
  currDate = t.date;
  if (nextDate != currDate){
    nextDate = t.date;
    if (nextDate == billDate){
      send_data();
    }
  }
}



void loop(){
  t = rtc.getTime();
  parameters();
  displaydata();
  save();
//  autoSend();
  autoSend_sample();
  if (sim800.available()>0){
    incomingChar = sim800.read();
    Serial.println(incomingChar);
    if (incomingChar == '?'){
      send_data();
    }
  }
  if (Serial.available()){
    sim800.write(Serial.read());
  }
}
