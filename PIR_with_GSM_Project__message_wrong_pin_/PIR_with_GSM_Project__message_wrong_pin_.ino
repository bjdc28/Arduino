#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Keypad.h>
#define I2C_ADDR 0x27
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#define BACKLIGHT 3
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
SoftwareSerial SIM900A(10,11);  //10->tx, 11->rx

const int ROW_NUM    = 4;
const int COLUMN_NUM = 4;

char key = 0;
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

boolean detect = true;
boolean sensorRdy = true;
boolean input = false;

int cursorColumn = 0;
int PIRpin = 12;
int pinCode = 0;
int pinTemp = 0;
int disp = 1;

unsigned long prevMotion = 0;
unsigned long currMotion;
const long intMotion = 150;

unsigned long prevDisp = 0;
unsigned long currDisp;
const long intDisp = 500;

void setup() {
  lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(HIGH);
  SIM900A.begin(9600);
  pinMode(PIRpin, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  randomSeed(analogRead(0));
}


void sendMessage(){
  SIM900A.println("AT+CMGF=1");
  delay(1000);
  SIM900A.println("AT+CMGS=\"+639771008160\"\r"); //Mobile phone number to send message
  delay(1000);
  SIM900A.println(pinCode);
  delay(100);
  SIM900A.println((char)26);
}


void sendMessageWrongPin(){
  SIM900A.println("AT+CMGF=1");
  delay(1000);
  SIM900A.println("AT+CMGS=\"+639771008160\"\r"); //Mobile phone number to send message
  delay(1000);
  SIM900A.println("Incorrect pin! Please enter again.");
  delay(100);
  SIM900A.println((char)26);
}


void motionDetected(){
  currMotion = millis();
  if (digitalRead(PIRpin) == HIGH){
    if (currMotion - prevMotion >= intMotion){
      prevMotion = currMotion;
      //insert code
        if (sensorRdy){
          disp = 2;
          sensorRdy = false;
        }
      //insert code
    }
  }
}


void setDisplay(){
  if (disp == 1){
    lcd.clear();
    lcd.home();
    lcd.setCursor(2,0);
    lcd.print("standby...");
  }
  if (disp == 2){
    lcd.clear();
    lcd.home();
    lcd.setCursor(0,0);
    lcd.print("A - send PIN");
    lcd.setCursor(0,1);
    lcd.print("D - cancel");
    input = true;
  }
}


void getInput(){
  if (input){
    if (disp == 2){
      if (key == 'A'){
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13,  LOW);
        pinCode = random(1000, 9999);
        sendMessage();
        lcd.clear();
        lcd.home();
        lcd.setCursor(3,0);
        lcd.print("PIN Sent!");
        delay(2000);
        SIM900A.println("AT+CNMI=2,2,0,0,0");
        lcd.clear();
        lcd.home();
        lcd.setCursor(0,0);
        lcd.print("Enter Pin:");
        key = 0;
        disp = 3;
      }
      if (key == 'D'){
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
        disp = 1;
        sensorRdy = true;
        input = false;
        key = 0;
      }
    }
    if (disp == 3){
      if ((key - 48 >= 0) && (key - 48 <= 9)) {
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
        lcd.setCursor(cursorColumn, 1);
        lcd.print(key);

        if (cursorColumn == 0){
          pinTemp = ((key - 48) * 1000);
        }
        if (cursorColumn == 1){
          pinTemp = pinTemp + ((key - 48) * 100);
        }
        if (cursorColumn == 2){
          pinTemp = pinTemp + ((key - 48) * 10);
        }
        if (cursorColumn == 3){
          pinTemp = pinTemp + (key - 48);
        }
        
        cursorColumn++;
        if (cursorColumn == 5){
          lcd.clear();
          cursorColumn = 0;
          pinTemp = 0;
          lcd.setCursor(0, 0);
          lcd.print("Enter PIN:");
        }
      }
      if (key == 'B'){
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
        lcd.clear();
        cursorColumn = 0;
        lcd.setCursor(0, 0);
        lcd.print("Enter PIN:");
        key = 0;
      }
      if (key == 'C'){
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
        pinCode = random(1000, 9999);
        sendMessage();
        lcd.clear();
        lcd.home();
        lcd.setCursor(3,0);
        lcd.print("PIN Sent!");
        delay(2000);
        SIM900A.println("AT+CNMI=2,2,0,0,0");
        lcd.clear();
        lcd.home();
        lcd.setCursor(0,0);
        lcd.print("Enter Pin:");
        key = 0;
        disp = 3;
      }
      if (key == 'A'){
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
        lcd.clear();
        if (pinTemp == pinCode){
          lcd.setCursor(0, 0);
          lcd.print("PIN Correct!");
          digitalWrite(13, HIGH);
          delay(200);
          digitalWrite(13, LOW);
          delay(100);
          digitalWrite(13, HIGH);
          delay(200);
          digitalWrite(13, LOW);
          delay(100);
          digitalWrite(13, HIGH);
          delay(200);
          digitalWrite(13, LOW);
          delay(2000);
          sensorRdy = true;
          disp = 1;
          pinTemp = 0;
          pinCode = 0;
          key = 0;
        }
        if (pinTemp != pinCode){
          sendMessageWrongPin();
          lcd.setCursor(0, 0);
          lcd.print("PIN Incorrect!");
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13, LOW);
          delay(2000);
          SIM900A.println("AT+CNMI=2,2,0,0,0");
        }
        cursorColumn = 0;
        pinTemp = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter PIN:");
      }
      if (key == 'D'){
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
        sensorRdy = true;
        disp = 1;
        pinTemp = 0;
        pinCode = 0;
        key = 0;
      }
    }
  }
}


void updateDisplay() {
  currDisp = millis();
  if (currDisp - prevDisp >= intDisp){
    prevDisp = currDisp;
    setDisplay();
  }
}


void loop() {
  key = keypad.getKey();
  motionDetected();
  updateDisplay();
  getInput();
}
