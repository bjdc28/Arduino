#include <SPI.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h> // F Malpartida's NewLiquidCrystal library
#define I2C_ADDR 0x27 // Define I2C Address for controller
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#define BACKLIGHT 3

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

int Red = 9;
int coinpin = 2;

volatile int pulse = 0;
volatile unsigned long timelastPulse = 0;

boolean coinInsert = false;
int buttonState = 0;
int credits = 0;


void setup() {
  Serial.begin(9600);
  delay(2000);
  lcd.begin (20,4); // initialize the lcd
  lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(HIGH);
  pinMode (coinpin, INPUT_PULLUP);
  pinMode (Red, OUTPUT);
}




void coinInterrupt(){
  pulse++;
  timelastPulse = millis();

  digitalWrite(Red, HIGH);
}

void displayCredit(){
  if (credits == 0){
    lcd.clear();
    lcd.print("Paper Vendo");
    lcd.setCursor(1, 1);
    lcd.print("-[INSERT COIN]-");
    delay(1000);
    lcd.clear();

    lcd.print("Paper Vendo");
    lcd.setCursor(1, 1);
    lcd.print ("- P1 P5 P10 -");
    delay(1000);
    lcd.clear();
  }
  else{
    lcd.setCursor(0, 0);
    lcd.print("Paper Vendo");
    lcd.setCursor(0, 1);
    lcd.print("Php: P");
    lcd.print(credits);
  }
}

void loop() {
  displayCredit();

  attachInterrupt(digitalPinToInterrupt(coinpin), coinInterrupt, FALLING);

  unsigned long lastTime = millis() - timelastPulse;

  if((pulse > 0) && (lastTime > 24)){

    coinInsert = false;
    credits += pulse;
    pulse = 0;
    
  }

  switch(credits){
    case 5:
    digitalWrite(Red, HIGH);
    break;

    case 10:
    digitalWrite(Red, HIGH);
    break;

    case 15:
    digitalWrite(Red, HIGH);

    case 25:
    digitalWrite(Red, HIGH);

    case 35:
    digitalWrite(Red, HIGH);

    case 50:
    digitalWrite(Red, HIGH);
    break;
    default:
    
    digitalWrite(Red, LOW);
    
  }
}
