#include <DS3231.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27 //Input LCD Address here
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#define BACKLIGHT 3

DS3231  rtc(SDA, SCL);
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {
  rtc.begin();
  lcd.begin (20,4);
  lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(HIGH);


  lcd.clear();
  lcd.home();
  lcd.setCursor(5,0);
  lcd.print("Hello");
  lcd.setCursor(5,1);
  lcd.print("World");

}

void loop() {
  lcd.clear();
  lcd.home();
  
  lcd.setCursor(0,0);
  lcd.print(rtc.getDateStr());
  lcd.setCursor(0,1);
  lcd.print(rtc.getTimeStr());
  delay(1000);
}
