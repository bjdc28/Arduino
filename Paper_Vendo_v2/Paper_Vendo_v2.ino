#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#define BACKLIGHT 3

Servo myservo;
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

int pos = 0;
int coinsChange = 0;
int coinPin = 2;
int credits = 0;
int papers = 0;
int mSpeed = 3;
int m1 = 4;
int m2 = 5;
int button = 7;

boolean dispense = false;

volatile int pulse = 0;
volatile unsigned long timelastPulse = 0;

unsigned long prevDisp = 0;
unsigned long currDisp;
const long intDisp = 500;

unsigned long prevButton = 0;
unsigned long currButton;
const long intButton = 250;

unsigned long prevHold = 0;
unsigned long currHold;
const long intHold = 100;

void setup() {
  delay(2000);
  lcd.begin (20,4);
  lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(HIGH);
  pinMode (coinPin, INPUT);
  pinMode (mSpeed, OUTPUT);
  pinMode (m1, OUTPUT);
  pinMode (m2, OUTPUT);
  pinMode (button, INPUT_PULLUP);
  myservo.attach(9);
  myservo.write(0);
//  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(coinPin), coinInterrupt, RISING);
  delay(3000);
}

void coinInterrupt(){
  pulse++;
  timelastPulse = millis();

}

void displayCredit(){
  if (!dispense){
    if (credits == 0){
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Paper Vendo");
      lcd.setCursor(2, 1);
      lcd.print("-[INSERT COIN]-");
      delay(1000);
      lcd.clear();

      lcd.setCursor(5, 0);
      lcd.print("Paper Vendo");
      lcd.setCursor(3, 1);
      lcd.print ("- P1 P5 P10 -");
      delay(1000);
      lcd.clear();
    }
    else{
      lcd.setCursor(5, 0);
      lcd.print("Paper Vendo");
      lcd.setCursor(0, 1);
      lcd.print("Php: P");
      lcd.print(credits);
      papers = credits * 2;
      lcd.setCursor(0, 2);
      lcd.print("Paper: ");
      lcd.print(papers);
    }
  }
  if (dispense){
    currDisp = millis();
    if (currDisp - prevDisp >= intDisp){
      prevDisp = currDisp;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Do not insert coin!");
      lcd.setCursor(3, 1);
      lcd.print("Please wait...");
      lcd.setCursor(0, 2);
      lcd.print("Paper: ");
      lcd.print(papers);
    }
  }
}

void dispensePaper(){
  if (dispense){
    if (papers > 0){
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      analogWrite(mSpeed, 180);
      delay(3300);
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      analogWrite(mSpeed, 0);
      for (pos = 0; pos <= 180; pos += 5) { 
        myservo.write(pos);             
        delay(15);
      }
      delay(500);
      for (pos = 180; pos >= 0; pos -= 5) { 
        myservo.write(pos);             
        delay(15);
      }
      papers--;
    }
    else {
      papers = 0;
      credits = 0;
      dispense = false;
    }
  }
}

void buttonPressed(){
  currButton = millis();
  if (digitalRead(button) == LOW){
    if (currButton - prevButton >= intButton){
      prevButton = currButton;
      //insert code
      dispense = true;
      //insert code
    }
  }
}

void Interrupt(){
  
  if ((pulse > 0) && (millis() - timelastPulse > 400)){
    coinsChange = pulse;
    pulse = 0;
  }
  switch (coinsChange){
    case 1:
    credits += 1;
    coinsChange = 0;
    break;

    case 2:
    credits += 1;
    coinsChange = 0;
    break;

    case 5:
    credits += 5;
    coinsChange = 0;
    break;

    case 6:
    credits += 5;
    coinsChange = 0;
    break;

    case 9:
    credits += 10;
    coinsChange = 0;
    break;

    case 10:
    credits += 10;
    coinsChange = 0;
    break;
  }
}


void loop() {
  displayCredit();
  dispensePaper();
  Interrupt();
  buttonPressed();
//  Serial.println(pulse);
}
