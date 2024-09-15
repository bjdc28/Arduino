#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A2 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

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
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);


int limSwitch_left = 3;
int limSwitch_right = 4;

int rel1 = 5;
int rel2 = 6;
int rel3 = 7;
int rel4 = 8;
int rel5 = 9;
int button1 = 10;
int button2 = 11;
int button3 = 12;
int button4 = 13;
int humidity = 0;
double temp_low = 36.5;                      //Default Temperature - Low cuttoff
double temp_high = 37.8;                     //Default Temperature - High cuttoff
double temperature = 0;
int humidity_low = 50;                  //Default Humidity - Low cuttoff
int humidity_high = 60;                 //Default Humidity - High cuttoff
int setUp = 0;
int cycle = 1;

boolean manual = false;
boolean clockwise = false;
boolean humidityState_low = false;
boolean tempActivate = false;
boolean humActivate = false;
boolean left_activated = false;
boolean right_activated = false;

int manualLastState = HIGH;
int manualCurrentState = HIGH;
unsigned long manualPressedTime = 0;
unsigned long manualReleasedTime = 0;
const int manualPressedDelay = 900;

unsigned long prevDHT = 0;
unsigned long currDHT;
const long intDHT = 2000;
unsigned long prevMenu = 0;
unsigned long currMenu;
const long intMenu = 250;
unsigned long prevMinus = 0;
unsigned long currMinus;
const long intMinus = 250;
unsigned long prevAdd = 0;
unsigned long currAdd;
const long intAdd = 250;
unsigned long prevManual = 0;
unsigned long currManual;
const long intManual = 300;
unsigned long prevSwing = 0;
unsigned long currSwing;
//const long intSwing = 5400000;            //Swing delay, in milliseconds. 1000 millis = 1 second. 7200000 millis = 2 hours
const long intSwing = 7200000;
unsigned long prevDispCycle = 0;
unsigned long currDispCycle;
const long intDispCycle = 500;


void setup() {
  dht.begin();
  lcd.begin (16,2);
  sensors.begin();
  lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(HIGH);
  pinMode(rel1, OUTPUT);
  pinMode(rel2, OUTPUT);
  pinMode(rel3, OUTPUT);
  pinMode(rel4, OUTPUT);
  pinMode(rel5, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(limSwitch_left, INPUT_PULLUP);
  pinMode(limSwitch_right, INPUT_PULLUP);
  digitalWrite(rel1, HIGH);
  digitalWrite(rel2, HIGH);
  digitalWrite(rel3, HIGH);
  digitalWrite(rel4, HIGH);
  digitalWrite(rel5, HIGH);
  updateDHT();
//  Serial.begin(9600);
}


void updateDHT() {
  currDHT = millis();
  if (currDHT - prevDHT >= intDHT){
    prevDHT = currDHT;
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);
    humidity = dht.readHumidity();
    
  }
}


void swing(){
  currSwing = millis();
  if (currSwing - prevSwing >= intSwing){
    prevSwing = currSwing;
    if (digitalRead(limSwitch_left) == LOW){
      digitalWrite(rel3, HIGH);
      delay(250);
      digitalWrite(rel2, LOW);
      left_activated = true;
    }
    if (digitalRead(limSwitch_right) == LOW){
      digitalWrite(rel3, LOW);
      delay(250);
      digitalWrite(rel2, LOW);
      right_activated = true;
    }
  }
}


void menuPressed(){
  currMenu = millis();
  if (digitalRead(button1) == LOW){
    if (currMenu - prevMenu >= intMenu){
      prevMenu = currMenu;
      if (!manual){
        setUp++;
        if (setUp > 4){
        setUp = 0;
        }
      }
    }
  }
}


void minusPressed(){
  currMinus = millis();
  if (digitalRead(button2) == LOW){
      if (currMinus - prevMinus >= intMinus){
      prevMinus = currMinus;
      if (!manual){
        if (setUp == 1){
          temp_low = temp_low - 0.1;
          if (temp_low < 25){
            temp_low = 45;
          }
          if (temp_low > temp_high){
            temp_low = temp_high - 1;
          }
        }
        if (setUp == 2){
          temp_high = temp_high - 0.1;
          if (temp_high < 25){
            temp_high = 45;
          }
          if (temp_high < temp_low){
            temp_high = temp_low + 1;
          }
        }
        if (setUp == 3){
          humidity_low--;
          if (humidity_low < 20){
            humidity_low = 80;
          }
          if (humidity_low > humidity_high){
            humidity_low = humidity_high - 1;
          }
        }
        if (setUp == 4){
          humidity_high--;
          if (humidity_high < 20){
            humidity_high = 80;
          }
          if (humidity_high < humidity_low){
            humidity_high = humidity_low + 1;
          }
        }
      }
    }
  }
}


void AddPressed(){
  currAdd = millis();
  if (digitalRead(button3) == LOW){
    if (currAdd - prevAdd >= intAdd){
      prevAdd = currAdd;
      if (!manual){
        if (setUp == 1){
          temp_low = temp_low + 0.1;
          if (temp_low > 45){
            temp_low = 25;
          }
          if (temp_low > temp_high){
            temp_low = temp_high - 1;
          }
        }
        if (setUp == 2){
          temp_high = temp_high + 0.1;
          if (temp_high > 45){
            temp_high = 25;
          }
          if (temp_high < temp_low){
            temp_high = temp_low + 1;
          }
        }
        if (setUp == 3){
          humidity_low++;
          if (humidity_low > 80){
            humidity_low = 20;
          }
          if (humidity_low > humidity_high){
            humidity_low = humidity_high - 1;
          }
        }
        if (setUp == 4){
          humidity_high++;
          if (humidity_high > 80){
            humidity_high = 20;
          }
          if (humidity_high < humidity_low){
            humidity_high = humidity_low + 1;
          }
        }
      }
    }
  }
}


void manualPressed(){
  currManual = millis();
  if (digitalRead(button4) == LOW){
    if (currManual - prevManual >= intManual){
      prevManual = currManual;
      manual = !manual;
    }
  }
}


//void manualPressed(){
//  manualCurrentState = digitalRead(button4);
//  if (manualLastState == HIGH && manualCurrentState == LOW){
//    manualPressedTime = millis();
//  }
//  else if (manualLastState == LOW && manualCurrentState == HIGH){
//    manualReleasedTime = millis();
//
//    long manualPressDuration = manualReleasedTime - manualPressedTime;
//
//    if (manualPressDuration > manualPressedDelay){
//      manual = !manual;
//    }
//  }
//  manualLastState = manualCurrentState;
//}


void display_cycle(){
  currDispCycle = millis();
  if (currDispCycle - prevDispCycle >= intDispCycle){
    prevDispCycle = currDispCycle;
    if (!manual){
      if (setUp == 0){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("T:");
        lcd.setCursor(2,0);
        lcd.print(temperature);
        lcd.setCursor(7,0);
        lcd.print("C");
        lcd.setCursor(9,0);
        lcd.print("H:");
        lcd.setCursor(11,0);
        lcd.print(humidity);
        lcd.setCursor(13,0);
        lcd.print("%");

        lcd.setCursor(0,1);
        lcd.print(temp_low);
        lcd.setCursor(6,1);
        lcd.print(temp_high);
        lcd.setCursor(12,1);
        lcd.print(humidity_low);
        lcd.setCursor(14,1);
        lcd.print(humidity_high);
      }
      if (setUp == 1){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("T:");
        lcd.setCursor(2,0);
        lcd.print(temperature);
        lcd.setCursor(7,0);
        lcd.print("C");
        lcd.setCursor(9,0);
        lcd.print("H:");
        lcd.setCursor(11,0);
        lcd.print(humidity);
        lcd.setCursor(13,0);
        lcd.print("%");

        lcd.setCursor(0,1);
        lcd.print(temp_low);
      }
      if (setUp == 2){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("T:");
        lcd.setCursor(2,0);
        lcd.print(temperature);
        lcd.setCursor(7,0);
        lcd.print("C");
        lcd.setCursor(9,0);
        lcd.print("H:");
        lcd.setCursor(11,0);
        lcd.print(humidity);
        lcd.setCursor(13,0);
        lcd.print("%");

        lcd.setCursor(6,1);
        lcd.print(temp_high);
      }
      if (setUp == 3){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("T:");
        lcd.setCursor(2,0);
        lcd.print(temperature);
        lcd.setCursor(7,0);
        lcd.print("C");
        lcd.setCursor(9,0);
        lcd.print("H:");
        lcd.setCursor(11,0);
        lcd.print(humidity);
        lcd.setCursor(13,0);
        lcd.print("%");

        lcd.setCursor(12,1);
        lcd.print(humidity_low);
      }
      if (setUp == 4){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("T:");
        lcd.setCursor(2,0);
        lcd.print(temperature);
        lcd.setCursor(7,0);
        lcd.print("C");
        lcd.setCursor(9,0);
        lcd.print("H:");
        lcd.setCursor(11,0);
        lcd.print(humidity);
        lcd.setCursor(13,0);
        lcd.print("%");

        lcd.setCursor(14,1);
        lcd.print(humidity_high);
      }
    
    }
    if (manual){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("T:");
        lcd.setCursor(2,0);
        lcd.print(temperature);
        lcd.setCursor(7,0);
        lcd.print("C");
        lcd.setCursor(9,0);
        lcd.print("H:");
        lcd.setCursor(11,0);
        lcd.print(humidity);
        lcd.setCursor(13,0);
        lcd.print("%");

        lcd.setCursor(3,1);
        lcd.print("MANUAL!");
    }
  }
}


void relayControl(){
  if (temperature < temp_low){
    tempActivate = true;
    digitalWrite(rel1, LOW);
  }
  if (temperature >= temp_high){
    tempActivate = false;
    digitalWrite(rel1, HIGH);
  }
  if (humidity < humidity_low){
    humActivate = true;
    if (humidityState_low == false){
      humidityState_low = !humidityState_low;
      digitalWrite(rel5, LOW);
    }
  }
  if (humidity > humidity_high){
    humActivate = false;
    if (humidityState_low == true){
      humidityState_low = !humidityState_low;
      digitalWrite(rel5, HIGH);
    }
  }
  if ((tempActivate) || (humActivate)){
    digitalWrite(rel4, LOW);
  }
  if ((!tempActivate) && (!humActivate)){
    digitalWrite(rel4, HIGH);
  }
}


void loop() {
//  Serial.println(digitalRead(button1));
//  Serial.println(digitalRead(button2));
//  Serial.println(digitalRead(button3));
//  Serial.println(digitalRead(button4));
  updateDHT();
  menuPressed();
  minusPressed();
  AddPressed();
  manualPressed();
  display_cycle();
  relayControl();
  if (manual){
    if ((digitalRead(button2) == LOW) && (digitalRead(limSwitch_left) == HIGH)){
      digitalWrite(rel3, LOW);
      delay(250);
      digitalWrite(rel2, LOW);
    }
    if ((digitalRead(button3) == LOW) && (digitalRead(limSwitch_right) == HIGH)){
      digitalWrite(rel3, HIGH);
      delay(250);
      digitalWrite(rel2, LOW);
    }
    if ((digitalRead(button2) == LOW) && (digitalRead(limSwitch_left) == LOW)){
      digitalWrite(rel2, HIGH);
    }
    if ((digitalRead(button3) == LOW) && (digitalRead(limSwitch_right) == LOW)){
      digitalWrite(rel2, HIGH);
    }
    if ((digitalRead(button2) == HIGH) && (digitalRead(button3) == HIGH)){
      digitalWrite(rel2, HIGH);
    }
  }
  if (!manual){
    swing();
    if (left_activated){
      if (digitalRead(limSwitch_right) == LOW){
        digitalWrite(rel2, HIGH);
        left_activated = false;
      }
    }
    if (right_activated){
      if (digitalRead(limSwitch_left) == LOW){
        digitalWrite(rel2, HIGH);
        right_activated = false;
      }
    }
  }
}
