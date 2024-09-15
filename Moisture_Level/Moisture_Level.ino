#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27 // Define I2C Address for controller
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#define BACKLIGHT 3


unsigned long prevMillis = 0;
const long interval = 50;
unsigned long currMillis;

unsigned long prevMillis2 = 0;
const long interval2 = 1000;
unsigned long currMillis2;

unsigned long prevMillis3 = 0;
const long interval3 = 250;
unsigned long currMillis3;

unsigned long prevMillis4 = 0;
const long interval4 = 250;
unsigned long currMillis4;

boolean display_inserted = false;
boolean sensor_inserted = false;
boolean counter_start = false;
int minute = 2;
int second = 57;

int sensor_pin = A0; 
int output_value ;
int pump = 7;
int led_red = 11;
int led_green = 12;
int value = 0;
int samples = 0;
int final_value = 0;

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {
  lcd.begin (20,4);
  lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(HIGH);
  pinMode(pump, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  Serial.begin(9600);
  Serial.println("Reading From the Sensor ...");
  delay(2000);
  }
  
void measure()
{
  currMillis = millis();
  
  if (currMillis - prevMillis >= interval){
    prevMillis = currMillis;
    
    output_value= analogRead(sensor_pin);
    output_value = map(output_value,550,0,0,100);
    
    value = value + output_value;
    samples++;
    
    if (samples == 20){
      final_value = (value/20);
      if (final_value < 0){
        lcd_case5();
        sensor_inserted = false;
      }
      else{
        sensor_inserted = true;
      }
      
      samples = 0;
      value = 0;
    }    
  }
}

void counter(){
  if (counter_start){
    digitalWrite(pump, HIGH);
    digitalWrite(led_green, HIGH);
    currMillis2 = millis();
    if (currMillis2 - prevMillis2 >= interval2){
      prevMillis2 = currMillis2;
      second--;
      if (second < 0){
        minute--;
        second = 59;
      }
      if (minute <= 0 && second <= 0){
        minute = 2;
        second = 57;
        digitalWrite(pump, LOW);
        digitalWrite(led_green, LOW);
        digitalWrite(led_red, HIGH);
        delay(5000);
        digitalWrite(led_red, LOW);
        counter_start = false;
      }
      
    }
  }
  digitalWrite(pump, LOW);
}

void lcd_case0(){
  currMillis4 = millis();
  if (currMillis4 - prevMillis4 >= interval4){
    prevMillis4 = currMillis4;
    lcd.clear();
    lcd.home();
    lcd.setCursor(3,1);
    lcd.print("Moisture Level");
    lcd.setCursor(8,2);
    lcd.print(final_value);
    lcd.setCursor(11,2);
    lcd.print("%");
  }
}

void lcd_case1(){ //moisture level - 30%, pump start
  currMillis3 = millis();
  if (currMillis3 - prevMillis3 >= interval3){
    prevMillis3 = currMillis3;
    lcd.clear();
    lcd.home();
    lcd.setCursor(3,0);
    lcd.print("Moisture Level");
    lcd.setCursor(8,1);
    lcd.print(final_value);
    lcd.setCursor(11,1);
    lcd.print("%");
    lcd.setCursor(3,2);
    lcd.print("Time Remaining");
    lcd.setCursor(8,3);
    lcd.print(minute);
    lcd.setCursor(9,3);
    lcd.print(":");
    lcd.setCursor(10,3);
    lcd.print(second);
  }
}

void lcd_case2(){ //moistue level - 30%, starting irrigation
  lcd.clear();
  lcd.home();
  lcd.setCursor(4,0);
  lcd.print("TWP Reached");
  lcd.setCursor(1,1);
  lcd.print("Moisture Level 30%");
  lcd.setCursor(4,2);
  lcd.print("Initializing");
  lcd.setCursor(3,3);
  lcd.print("Irrigation...");
}

void lcd_case3(){ //sensor inserted - 1
  lcd.clear();
  lcd.home();
  lcd.setCursor(2,0);
  lcd.print("Sensor Inserted");
  lcd.setCursor(8,1);
  lcd.print("on");
  lcd.setCursor(4,2);
  lcd.print("Soil Sample");
}

void lcd_case4(){ //sensor inserted - 2
  lcd.clear();
  lcd.home();
  lcd.setCursor(2,1);
  lcd.print("Sensor Analyzing");
  lcd.setCursor(2,2);
  lcd.print("Moisture Content");
}

void lcd_case5(){ //sensor removed
  lcd.clear();
  lcd.home();
  lcd.setCursor(2,1);
  lcd.print("Sensor Removed!");
}

void control(){
  if (sensor_inserted){
    lcd_case3();
    delay(5000);
    lcd_case4();
    delay(5000);
    while (final_value > 0){
      measure();
      if (final_value > 30){
        lcd_case0();
      }
      if (final_value <=30 && final_value > 0){
        counter_start = true;
        lcd_case2();
        delay(5000);
        while (counter_start){
          measure();
          lcd_case1();
          counter();
        }
      }
    }
  }
}


void loop() {
  control();
  counter();
  measure();
  }
