#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include "SevSeg.h"
SevSeg sevseg;

int LED1 = 22;
int LED2 = 24;
int LED3 = 26;
int LED4 = 28;
int LED5 = 30;
int LED6 = 32;
int rel1 = 34;
int rel2 = 36;
int rel3 = 38;
int rel4 = 40;
int motor = 45;
int button1 = 42;
int button2 = 44;
int button3 = 46;
int button4 = 48;
int temperature = 0;
int humidity = 0;
int temp_low = 37;
int temp_high = 38;
int humidity_low = 50;
int humidity_high = 60;
int motor_speed = 200;
int motor_delay = 300;
int motor_delayFinal = 3000;
int display1 = 0;
int setUp = 0;
int cycle = 1;

boolean manual = false;
boolean clockwise = false;
boolean humidityState_low = false;
boolean tempActivate = false;
boolean humActivate = false;

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
const long intManual = 350;
unsigned long prevDispOp = 0;
unsigned long currDispOp;
const long intDispOp = 1000;
unsigned long prevDispSet = 0;
unsigned long currDispSet;
const long intDispSet = 500;
unsigned long prevSwing = 0;
unsigned long currSwing;
const long intSwing = 8000;
//const long intSwing = 7200000;
unsigned long swingDelay = 0;


void setup() {
  dht.begin();
  byte numDigits = 6;
  byte digitPins[] = {3, 4, 5, 14, 15, 16};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_ANODE;
  bool updateWithDelays = false;
  bool leadingZeros = false;
  bool disableDecPoint = false;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
//  Serial.begin(9600);
  pinMode(rel1, OUTPUT);
  pinMode(rel2, OUTPUT);
  pinMode(rel3, OUTPUT);
  pinMode(rel4, OUTPUT);
  pinMode(motor, OUTPUT);
  analogWrite(motor, 255);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  digitalWrite(rel1, HIGH);
  digitalWrite(rel2, HIGH);
  digitalWrite(rel3, HIGH);
  digitalWrite(rel4, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(rel3, LOW);
  delay(1500);
  digitalWrite(rel3, HIGH);
  delay(3500);
  updateDHT();
}


void updateDHT() {
  currDHT = millis();
  if (currDHT - prevDHT >= intDHT){
    prevDHT = currDHT;
//    DHT.read11(dht_apin);
//    temperature = DHT.temperature;
//    humidity = DHT.humidity;
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
  }
}


void swing(){
  currSwing = millis();
  if (currSwing - prevSwing >= intSwing){
    prevSwing = currSwing;
    motor_delayFinal = motor_delay * 10;
    swingDelay = motor_delayFinal + millis();
    if (clockwise){
      digitalWrite(rel4, LOW);
      delay(500);
      analogWrite(motor, motor_speed);
    }
    if (!clockwise){
      digitalWrite(rel4, HIGH);
      delay(500);
      analogWrite(motor, motor_speed);
    }
    clockwise = !clockwise;
  }
}


void menuPressed(){
  currMenu = millis();
  if (digitalRead(button1) == LOW){
    if (currMenu - prevMenu >= intMenu){
      prevMenu = currMenu;
      if (!manual){
        setUp++;
        if (setUp > 6){
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
        if (setUp ==1){
          temp_low--;
          if (temp_low < 25){
            temp_low = 45;
          }
          if (temp_low > temp_high){
            temp_low = temp_high - 1;
          }
        }
        if (setUp ==2){
          temp_high--;
          if (temp_high < 25){
            temp_high = 45;
          }
          if (temp_high < temp_low){
            temp_high = temp_low + 1;
          }
        }
        if (setUp ==3){
          humidity_low--;
          if (humidity_low < 20){
            humidity_low = 80;
          }
          if (humidity_low > humidity_high){
            humidity_low = humidity_high - 1;
          }
        }
        if (setUp ==4){
          humidity_high--;
          if (humidity_high < 20){
            humidity_high = 80;
          }
          if (humidity_high < humidity_low){
            humidity_high = humidity_low + 1;
          }
        }
        if (setUp ==5){
          motor_speed--;
          if (motor_speed < 1){
            motor_speed = 254;
          }
        }
        if (setUp ==6){
          motor_delay--;
          if (motor_delay < 1){
            motor_delay = 999;
            motor_delayFinal = motor_delay * 10;
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
        if (setUp ==1){
          temp_low++;
          if (temp_low > 45){
            temp_low = 25;
          }
          if (temp_low > temp_high){
            temp_low = temp_high - 1;
          }
        }
        if (setUp ==2){
          temp_high++;
          if (temp_high > 45){
            temp_high = 25;
          }
          if (temp_high < temp_low){
            temp_high = temp_low + 1;
          }
        }
        if (setUp ==3){
          humidity_low++;
          if (humidity_low > 80){
            humidity_low = 20;
          }
          if (humidity_low > humidity_high){
            humidity_low = humidity_high - 1;
          }
        }
        if (setUp ==4){
          humidity_high++;
          if (humidity_high > 80){
            humidity_high = 200;
          }
          if (humidity_high < humidity_low){
            humidity_high = humidity_low + 1;
          }
        }
        if (setUp ==5){
          motor_speed++;
          if (motor_speed > 254){
            motor_speed = 1;
          }
        }
        if (setUp ==6){
          motor_delay++;
          if (motor_delay > 999){
            motor_delay = 1;
            motor_delayFinal = motor_delay * 10;
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
      if (manual){
        sevseg.blank();
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
        digitalWrite(LED5, HIGH);
        digitalWrite(LED6, HIGH);
      }
      if (!manual){
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);
        digitalWrite(LED6, LOW);
      }
    }
  }
}


void display_operation(){
  currDispOp = millis();
  if (currDispOp - prevDispOp >= intDispOp){
    prevDispOp = currDispOp;
//    temperature = DHT.temperature;
//    humidity = DHT.humidity;
    if (setUp == 0){
      digitalWrite(LED6, LOW);
      display1 = ((temperature * 1000) + humidity);
      sevseg.setNumber(display1, 0);
    }
  }
}


void display_setup(){
  currDispSet = millis();
  if (currDispSet - prevDispSet >= intDispSet){
    prevDispSet = currDispSet;
    if (setUp == 1){
      digitalWrite(LED1, HIGH);
      sevseg.setNumber(temp_low, 0);
    }
    if (setUp == 2){
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      sevseg.setNumber(temp_high, 0);
    }
    if (setUp == 3){
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      sevseg.setNumber(humidity_low, 0);
    }
    if (setUp == 4){
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      sevseg.setNumber(humidity_high, 0);
    }
    if (setUp == 5){
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, HIGH);
      sevseg.setNumber(motor_speed, 255);
    }
    if (setUp == 6){
      digitalWrite(LED5, LOW);
      digitalWrite(LED6, HIGH);
      sevseg.setNumber(motor_delay, 255);
    }
  }
}


void relayControl(){
  if (temperature < temp_low){
    tempActivate = true;
    digitalWrite(rel1, LOW);
  }
  if (temperature > temp_high){
    tempActivate = false;
    digitalWrite(rel1, HIGH);
  }
  if (humidity < humidity_low){
    humActivate = true;
    if (humidityState_low == false){
      humidityState_low = !humidityState_low;
      digitalWrite(rel3, LOW);
      delay(150);
      digitalWrite(rel3, HIGH);
    }
  }
  if (humidity > humidity_high){
    humActivate = false;
    if (humidityState_low == true){
      humidityState_low = !humidityState_low;
      digitalWrite(rel3, LOW);
      delay(150);
      digitalWrite(rel3, HIGH);
      delay(150);
      digitalWrite(rel3, LOW);
      delay(150);
      digitalWrite(rel3, HIGH);
    }
  }
  if ((tempActivate) || (humActivate)){
    digitalWrite(rel2, LOW);
  }
  if ((!tempActivate) && (!humActivate)){
    digitalWrite(rel2, HIGH);
  }
}


void loop() {
  sevseg.refreshDisplay();
  updateDHT();
  menuPressed();
  minusPressed();
  AddPressed();
  manualPressed();
//  Serial.println(humidity);
  
  if (manual){
    if (digitalRead(button2) == LOW){
      digitalWrite(rel4, LOW);
      analogWrite(motor, motor_speed);
    }
    if (digitalRead(button3) == LOW){
      digitalWrite(rel4, HIGH);
      analogWrite(motor, motor_speed);
    }
    if ((digitalRead(button2) == HIGH) && (digitalRead(button3) == HIGH)){
      analogWrite(motor, 255);
    }
  }
  if (!manual){
    swing();
    display_operation();
    display_setup();
    relayControl();
    if (swingDelay <= millis()){
      analogWrite(motor, 255);
    }
  }
}
