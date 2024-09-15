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

const int dirPin = 2;
const int pulsPin = 3;
const int enPin = 7;

const int strt = 8;
const int minus = 9;
const int add = 10;
const int ent = 11;
const int rst = 12;

const int rain = 13;

const int fwdLim = 4;
const int revLim = 5;

unsigned long prevMStart = 0;
unsigned long currMStart;
const long intMStart = 250;

unsigned long prevStart = 0;
unsigned long currStart;
const long intStart = 250;

unsigned long prevMinus = 0;
unsigned long currMinus;
const long intMinus = 250;

unsigned long prevAdd = 0;
unsigned long currAdd;
const long intAdd = 250;

unsigned long prevEnt = 0;
unsigned long currEnt;
const long intEnt = 250;

unsigned long prevDisp = 0;
unsigned long currDisp;
const long intDisp = 500;

unsigned long prevInt = 0;
unsigned long currInt;
const long intInt = 1000;

boolean start_1 = false;
boolean pause_1 = false;

boolean start = false;
boolean pause = false;
unsigned int currSec;
unsigned int nextSec = 0;

boolean motStart = false;
boolean motStop = false;
boolean fwd = false;

int hrs = 0;
int mins = 0;
int secs = 0;
int hrs_1 = 0;
int mins_1 = 0;
int secs_1 = 0;
int hrs_2 = 0;
int mins_2 = 0;
int secs_2 = 0;

double multiplier = 0;

int low = 0;
int mid = 0;
int high = 0;

int selectDisplay = 1;
int intensity = 0;

int tempVal = 0;

DS3231  rtc(SDA, SCL);
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
Time t;





void setup() {
  rtc.begin();
  lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(HIGH);

  pinMode(strt, INPUT_PULLUP);
  pinMode(minus, INPUT_PULLUP);
  pinMode(add, INPUT_PULLUP);
  pinMode(ent, INPUT_PULLUP);
  pinMode(rst, INPUT_PULLUP);

  pinMode(rain, INPUT);

  pinMode(fwdLim, INPUT_PULLUP);
  pinMode(revLim, INPUT_PULLUP);
  pinMode(strt, INPUT_PULLUP);
  pinMode(dirPin, OUTPUT);
  pinMode(pulsPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, HIGH);
  
  mainDisplay();

//  Serial.begin(9600);
}


void rotation() {
  if (fwd){
    digitalWrite(dirPin, HIGH);
  }
  else {
    digitalWrite(dirPin, LOW);
  }
}


void motorStop() {
  analogWrite(pulsPin, 0);
}


void motorStart() {
  analogWrite(pulsPin, 180);
}


void startStepper() {
  if (motStart == true){
    rotation();
    motorStart();
  }
  if (motStart == false){
    motorStop();
  }
}


void setMultiplier() {
  mins_2 = (mins_1 * multiplier);
  hrs_2 = (hrs_1 * multiplier);
  if (mins_2 > 59){
    hrs_2++;
    mins_2 = (mins_1 - 60);
  }
}


void timer() {
  currSec = t.sec;
  if (nextSec != currSec){
    
    nextSec = t.sec;
    
    secs_1--;
    secs_2--;
    
    if (secs_1 < 0){
      secs_1 = 59;
      mins_1--;
    }
    else if (mins_1 < 0){
      mins_1 = 59;
      hrs_1--;
    }
    else if (secs_2 < 0){
      secs_2 = 59;
      mins_2--;
    }
    else if (mins_2 < 0){
      mins_2 = 59;
      hrs_2--;
    }
  }
}


void setIntensity() {
  currInt = millis();
  if (currInt - prevInt >= intInt){
    prevInt = currInt;
    //insert code
    tempVal = analogRead(A5);
    if (digitalRead(rain) == HIGH){
      if (tempVal <= mid){
        intensity = 1;
        start = false;
      }
      else if ((tempVal > mid) && (tempVal < high)){
        intensity = 2;
        if (start_1){
          start = true;      
        }
      }
      else if (tempVal >= high){
        intensity = 3;
        if (start_1){
          start = true;
        }
      }
    }
    else if (digitalRead(rain) == LOW){
      intensity = 0;
      start = false;
    }
    //insert code
  }
}


void resetPressed() {
  if (digitalRead(rst) == LOW){
    if (selectDisplay == 1){
      start = false;
      pause = false;
      start_1 = false;
      pause_1 = false;
      hrs = 0;
      mins = 0;
      secs = 0;
      hrs_1 = 0;
      mins_1 = 0;
      secs_1 = 0;
      hrs_2 = 0;
      mins_2 = 0;
      secs_2 = 0;
      
    }
    else if (selectDisplay == 2){
      start = false;
      pause = false;
      start_1 = false;
      pause_1 = false;
      hrs = 0;
      mins = 0;
      secs = 0;
      hrs_1 = 0;
      mins_1 = 0;
      secs_1 = 0;
      hrs_2 = 0;
      mins_2 = 0;
      secs_2 = 0;
      
    }
    else if (selectDisplay == 5){
      multiplier = 0;
    }
  }
}


void strtPressed() {
//  if (secs > 0 || mins > 0 || hrs > 0){
    currStart = millis();
    if (digitalRead(strt) == LOW){
      if (currStart - prevStart >= intStart){
        prevStart = currStart;
        //insert code
        updateTime();
        if (secs > 0 || mins > 0 || hrs > 0){
          if (selectDisplay == 1){
          if (intensity > 1){
            secs = secs_1;
            mins = mins_1;
            hrs = hrs_1;
            start_1 = !pause_1;
            pause_1 = start_1;
            if (start_1){
              start = !pause;
              pause = start;
            }
          }
        }
        }
        
        
        else if (selectDisplay == 5){
          setMultiplier();
          confirmation();
          updateDisplay();
        }
        //insert code
      }
    }
//  }
}


void minusPressed() {
  currMinus = millis();
  if (digitalRead(minus) == LOW){
    if (currMinus - prevMinus >= intMinus){
      prevMinus = currMinus;
      
      //insert code
      updateTime();
      if (selectDisplay == 2){
        hrs_1++;
        if (hrs_1 > 99){
          hrs_1 = 0;
        }
        secs = secs_1;
        mins = mins_1;
        hrs = hrs_1;
        inputTime();
        setMultiplier();
      }
      else if (selectDisplay == 5){
        multiplier = (multiplier + 0.01);
      }
      //insert code
    }
  }
}


void addPressed() {
  currAdd = millis();
  if (digitalRead(add) == LOW){
    if (currAdd - prevAdd >= intAdd){
      prevAdd = currAdd;
      //insert code
      updateTime();
      if (selectDisplay == 2){
        mins_1++;
        if (mins_1 > 60){
          mins_1 = 0;
        }
        secs = secs_1;
        mins = mins_1;
        hrs = hrs_1;
        inputTime();
        setMultiplier();
      }
      else if (selectDisplay == 3){
        mid = analogRead(A5);
        confirmation();
        updateDisplay();
      }
      else if (selectDisplay == 4){
        high = analogRead(A5);
        confirmation();
        updateDisplay();
      }
      else if (selectDisplay == 5){
        multiplier++;
      }
      
      //insert code
    }
  }
}


void entPressed() {
  currEnt = millis();
  if (digitalRead(ent) == LOW){
    if (currEnt - prevEnt >= intEnt){
      prevEnt = currEnt;
      //insert code
      selectDisplay++;
      if (selectDisplay > 5){
        selectDisplay = 1;
      }
      //insert code
    }
  }
}


void confirmation() {
  lcd.clear();
  lcd.home();
  lcd.setCursor(2,0);
  lcd.print("Saved...");
  delay(500);
}


void inputTime() {
  lcd.clear();
  lcd.home();
  lcd.setCursor(1,0);
  lcd.print("Exposure Time");
  lcd.setCursor(0,1);
  lcd.print("Hrs:");
  lcd.setCursor(4,1);
  lcd.print(hrs_1);
  lcd.setCursor(8,1);
  lcd.print("Mins:");
  lcd.setCursor(13,1);
  lcd.print(mins_1);
}


void inputLevel1() {
  lcd.clear();
  lcd.home();
  lcd.setCursor(3,0);
  lcd.print("Set Level");
  lcd.setCursor(3,1);
  lcd.print("Low:");
  lcd.setCursor(8,1);
  lcd.print(analogRead(A5));
}


void inputLevel2() {
  lcd.clear();
  lcd.home();
  lcd.setCursor(3,0);
  lcd.print("Set Level");
  lcd.setCursor(3,1);
  lcd.print("High:");
  lcd.setCursor(8,1);
  lcd.print(analogRead(A5));
}


void inputLevel3() {
  lcd.clear();
  lcd.home();
  lcd.setCursor(3,0);
  lcd.print("Multiplier");
  lcd.setCursor(5,1);
  lcd.print(multiplier);
}


void mainDisplay() {
  lcd.clear();
  lcd.home();
  lcd.setCursor(1,0);
  lcd.print("Time Remaining");
  lcd.setCursor(0,1);
  lcd.print(hrs);
  lcd.setCursor(2,1);
  lcd.print(":");
  lcd.setCursor(3,1);
  lcd.print(mins);
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(secs);
  lcd.setCursor(9,1);
  lcd.print("|");
  if (intensity == 0){
    lcd.setCursor(10,1);
    lcd.print("Rainy");
  }
  if (intensity == 1){
    lcd.setCursor(10,1);
    lcd.print("Dark");
  }
  else if (intensity == 2){
    lcd.setCursor(10,1);
    lcd.print("Cloudy");
  }
  else if (intensity == 3){
    lcd.setCursor(10,1);
    lcd.print("Sunny");
  }
}


void updateDisplay() {
  currDisp = millis();
  if (currDisp - prevDisp >= intDisp){
    prevDisp = currDisp;
//    debug();
    updateTime();
    if (selectDisplay == 1){
      //insert code
      mainDisplay();
      //insert code
    }
    if (selectDisplay == 2){
      //insert code
      inputTime();
      //insert code
    }
    if (selectDisplay == 3){
      //insert code
      inputLevel1();
      //insert code
    }
    if (selectDisplay == 4){
      //insert code
      inputLevel2();
      //insert code
    }
    if (selectDisplay == 5){
      //insert code
      inputLevel3();
      //insert code
    }
  }
}


void countDown() {
  if (start == true){
    fwd = true;
    if (digitalRead(fwdLim) == LOW){
      motStart = false;
    }
    if (digitalRead(fwdLim) == HIGH){
      motStart = true;
    }
    timer();
  }
  else if (start == false){
    fwd = false;
    if (digitalRead(revLim) == LOW){
      motStart = false;
    }
    if (digitalRead(revLim) == HIGH){
      motStart = true;
    }
  }
}


void updateTime() {
  if (intensity == 2){
    secs = secs_2;
    mins = mins_2;
    hrs = hrs_2;
  }
  else if (intensity == 3){
    secs = secs_1;
    mins = mins_1;
    hrs = hrs_1;
  }
  resetValues();
}


void resetValues() {
  if (mins < 0){
      start = false;
      pause = false;
      start_1 = false;
      pause_1 = false;
      hrs = 0;
      mins = 0;
      secs = 0;
      hrs_1 = 0;
      mins_1 = 0;
      secs_1 = 0;
      hrs_2 = 0;
      mins_2 = 0;
      secs_2 = 0;
  }
  else if (hrs < 0){
      start = false;
      pause = false;
      start_1 = false;
      pause_1 = false;
      hrs = 0;
      mins = 0;
      secs = 0;
      hrs_1 = 0;
      mins_1 = 0;
      secs_1 = 0;
      hrs_2 = 0;
      mins_2 = 0;
      secs_2 = 0;
  }
}


//void debug() {
//  Serial.println(mins);
//  Serial.println(hrs);
//  Serial.println(mins_1);
//  Serial.println(hrs_1);
//  Serial.println(mins_2);
//  Serial.println(hrs_2);
//}


void loop() {
  t = rtc.getTime();
  countDown();  
  resetPressed();
  entPressed();
  strtPressed();
  minusPressed();
  addPressed();
  setIntensity();
  startStepper();  
  updateDisplay();
}
