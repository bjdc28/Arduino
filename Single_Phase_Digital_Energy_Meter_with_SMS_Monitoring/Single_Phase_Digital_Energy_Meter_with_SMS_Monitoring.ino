#include <GPRS.h>
#include <SoftwareSerial.h>
#include <EmonLib.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include "Sdfat.h"
#include "sim800.h"
#define TIMEOUT 5000
#define VOLT_CAL 249.75
#define CURRENT_CAL 62.85


SdFat SD;
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7);
EnergyMonitor emon1;
File EnerFile;
GPRS gprs;


bool Cons = false;
String MyString;
char currentLine[35] = "";
int currentLineIndex = 0;
bool nextLineIsMessage = false;


float volts = 0;
float amps = 0;
float power = 0;
float energy = 0;


unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long interval = 1000;
unsigned long interval2 = 1000;
unsigned long interval3 = 1000;


const int chipsSelect = 10;


void setup(){
  lcd.begin (20,4);
  lcd.setBacklightPin (3,POSITIVE);
  lcd.setBacklight (HIGH);

  emon1.voltage (1,VOLT_CAL,1.7);
  emon1.current (0,CURRENT_CAL);

  if (SD.begin(chipselect))
  EnerFile = SD.open("ENER.txt");
  if (EnerFile){
    while (EnerFile.available()){
      energy = EnerFile.parseFloat();
    }
    EnerFile.close();
  }
  gprs.preInit();
  while (0 != gprs.init()){
    delay(10);
  }
  if (0 != gprs.sendCmdAndWaitForResp("AT+CMGF=1\r\n","OK",TIMEOUT)){
    ERROR("ERROR:CNMI");
    return;
  }
  if (0 != gprs.sendCmdAndWaitForResp("AT+CNMI=1,2,0,0,0\r\n","OK",TIMEOUT)){
    ERROR("ERROR:CNMI");
    return;
  }
}



void Reply(){
  gprs.preInit();
  while (0 != gprs.init()){
    delay(10);
  }
  if (Cons == true){
    energy;
    Cons = false;
  }
  MyString = String(energy,2);
  MyString = ("kWhr Consumption:" = MyString);
  int str_len = MyString.length()+1;
  char char_array[str_len];
  MyString.toCharArray(char_array,str_len);
  gprs.sendSMS("09487278245",char_array);
}



void SIM(){
  if (gprs.serialSIM800.available()){
    char lastCharRead = gprs.serialSIM800.read();
    if (lastCharRead == '\r' || lastCharRead == '\n'){
      String lastLine = String(currentLine);
      if (lastLine.startsWith("+CMT:")){
        nextLineIsMessage = true;
      }
      else if (lastLine.length()>0){
        if (nextLineIsMessage){
          if (lastLine.indexOf("CONS")>=0){
            Cons = true;
            Reply();
          }
          nextLineIsMessage = false;
        }
      }
      for (int i = 0; i<sizeof(currentLine); ++i){
        currentLine[i] = (char)0;
      }
      currentLineIndex = 0;
    }
    else{
      currentLine[currentLineIndex++]=lastCharRead;
    }
  }
}



void parameters(){
  emon1.calcVI(20,2000);
  float supplyVoltage = emon1.Vrms;
  float currentDrawn = emon1.Irms;
  float sum_of_volts = 0;
  for (int x = 0; x < 300; x++){
    sum_of_volts += supplyVoltage;
  }
  float sum_of_amps = 0;
  for (int x = 0; x < 300; x++){
    sum_of_amps += currentDrawn;
  }
  volts = sum_of_volts/300;
  amps = (sum_of_amps/300) - 0.10823;
  power = volts * amps;
  unsigned long currentMillis3 = millis();
  if (currentMillis3 - previousMillis3 >= interval3){
    previousMillis3 = currentMillis3;
    energy = energy + (power)/(3600000);
  }
  if (amps < 0){
    amps = 0;
    power = 0;
  }
}



void displaydata(){
  unsigned long currentMillis2 = millis();
  if (currentMillis2 - previousMillis2 >= interval){
    previousMillis2 = currentMillis2;
    lcd.setCursor(0,0);
    lcd.print("Voltage: ");
    lcd.setCursor(9,0);
    lcd.print(volts);
    lcd.setCursor(16,0);
    lcd.print("V");
    lcd.setCursor(0,1);
    lcd.print("Current: ");
    lcd.setCursor(9,1);
    lcd.print(amps);
    lcd.setCursor(16,1);
    lcd.print("A");
    lcd.setCursor(0,2);
    lcd.print("Power: ");
    lcd.setCursor(9,2);
    lcd.print(power);
    lcd.setCursor(16,2);
    lcd.print("W");
    lcd.setCursor(0,3);
    lcd.print("Energy: ");
    lcd.setCursor(9,3);
    lcd.print(energy);
    lcd.setCursor(16,3);
    lcd.print("kWhr");
  }
}



void save(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    SD.remove("ENER.txt");
    EnerFile = SD.open("ENER.txt", FILE_WRITE);
    if (EnerFile){
      EnerFile.print(energy);
      EnerFile.close();
    }
  }
}



void loop(){
  parameters();
  displaydata();
  save();
  SIM();
}
