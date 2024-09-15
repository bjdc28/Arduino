#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

RF24 radio(7, 8);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t nodeBoiler = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t nodeGreentank = 01;

unsigned long prevRFsend = 0;
unsigned long currRFsend;
const long intRFsend = 350;

unsigned long prevWater = 0;
unsigned long currWater;
const long intWater = 500;

unsigned long prevBtnMot = 0;
unsigned long currBtnMot;
const long intBtnMot = 250;

unsigned long prevBtnManAuto = 0;
unsigned long currBtnManAuto;
const long intBtnManAuto = 350;

unsigned long prevLedBlink = 0;
unsigned long currLedBlink;
const long intLedBlink = 500;

unsigned long prevLedBlinkMot = 0;
unsigned long currLedBlinkMot;
const long intLedBlinkMot = 200;

bool motorStartInstruct = false;
int waterLevelVal = 0;

bool motorStartActual = false;

bool ledRed = false;
bool ledMotor = false;
bool motorManual = true;
int waterLow = 2;
int waterMid = 3;
int waterHi = 4;
int btnMot = 5;
int btnManAuto = 6;
int ledMotStart = 9;
int ledMotStop = 10;
int ledLow = A0;
int ledMid = A1;
int ledHi = A2;
int ledRx = A3;
int ledMan = A4;
int ledAuto = A5;

struct payload {
  int instruct;
  int actual;
};
payload data;


void setup(){
  pinMode(waterLow, INPUT);
  pinMode(waterMid, INPUT);
  pinMode(waterHi, INPUT);
  pinMode(btnMot, INPUT_PULLUP);
  pinMode(btnManAuto, INPUT_PULLUP);
  pinMode(ledMotStart, OUTPUT);
  pinMode(ledMotStop, OUTPUT);
  pinMode(ledLow, OUTPUT);
  pinMode(ledMid, OUTPUT);
  pinMode(ledHi, OUTPUT);
  pinMode(ledRx, OUTPUT);
  pinMode(ledMan, OUTPUT);
  pinMode(ledAuto, OUTPUT);
  digitalWrite(ledMotStart, LOW);
  digitalWrite(ledMotStop, LOW);
  digitalWrite(ledLow, LOW);
  digitalWrite(ledMid, LOW);
  digitalWrite(ledHi, LOW);
  digitalWrite(ledRx, LOW);
  digitalWrite(ledMan, LOW);
  digitalWrite(ledAuto, LOW);
  SPI.begin();
  radio.begin();
  network.begin(90, nodeBoiler);  //(channel, node address)
  ledManualAuto();
//  Serial.begin(9600);
}

void ledBlink(){
  currLedBlink = millis();
  if (currLedBlink - prevLedBlink >=intLedBlink){
    prevLedBlink = currLedBlink;
    //insert code below
    if (ledRed == false){
      digitalWrite(ledLow, LOW);
    }
    if (ledRed == true){
      digitalWrite(ledLow, HIGH);
    }
    ledRed =! ledRed;
  }
}

void ledBlinkMotor(){
  currLedBlinkMot = millis();
  if (currLedBlinkMot - prevLedBlinkMot >=intLedBlinkMot){
    prevLedBlinkMot = currLedBlinkMot;
    //insert code below
//    Serial.println("led motor");
    if (ledMotor == false){
      digitalWrite(ledMotStart, LOW);
      digitalWrite(ledMotStop, LOW);
      Serial.println("led motor - false");
    }
    if (ledMotor == true){
//      Serial.println("led motor - false");
      if (motorStartInstruct == false){
        digitalWrite(ledMotStart, LOW);
        digitalWrite(ledMotStop, HIGH);
      }
      if (motorStartInstruct == true){
        digitalWrite(ledMotStart, HIGH);
        digitalWrite(ledMotStop, LOW);
      }
    }
    ledMotor =! ledMotor;
  }
}

void ledMotorStatus(){
  if (motorStartInstruct == motorStartActual){
    if (motorStartActual == false){
      digitalWrite(ledMotStart, LOW);
      digitalWrite(ledMotStop, HIGH);
    }
    if (motorStartActual == true){
      digitalWrite(ledMotStart, HIGH);
      digitalWrite(ledMotStop, LOW);
    }
    Serial.println("Instruct = Actual");
  }
  if (motorStartInstruct != motorStartActual){
    ledBlinkMotor();
    Serial.println("Instruct != Actual");
  }
}

void ledManualAuto(){
  if (motorManual == false){
    digitalWrite(ledMan, LOW);
    digitalWrite(ledAuto, HIGH);
  }
  if (motorManual == true){
    digitalWrite(ledMan, HIGH);
    digitalWrite(ledAuto, LOW);
  }
}

void motorAutoStart(){
  if (motorManual == false){
    motorStartInstruct = true;
  }
}

void motorAutoStop(){
  if (motorManual == false){
    motorStartInstruct = false;
  }
}

void waterLevel(){
  currWater = millis();
  if (currWater - prevWater >=intWater){
    prevWater = currWater;
    //insert code below
    if ((digitalRead(waterLow) == LOW) && (digitalRead(waterMid) == HIGH) && (digitalRead(waterHi) == HIGH)){
      digitalWrite(ledLow, HIGH);
      digitalWrite(ledMid, LOW);
      digitalWrite(ledHi, LOW);
      motorAutoStart();
      waterLevelVal = 1;
    }
    if ((digitalRead(waterLow) == LOW) && (digitalRead(waterMid) == LOW) && (digitalRead(waterHi) == HIGH)){
      digitalWrite(ledLow, LOW);
      digitalWrite(ledMid, HIGH);
      digitalWrite(ledHi, LOW);
      motorAutoStart();
      waterLevelVal = 2;
    }
    if ((digitalRead(waterLow) == LOW) && (digitalRead(waterMid) == LOW) && (digitalRead(waterHi) == LOW)){
      digitalWrite(ledLow, LOW);
      digitalWrite(ledMid, LOW);
      digitalWrite(ledHi, HIGH);
      motorAutoStop();
      waterLevelVal = 3;
    }
    if ((digitalRead(waterLow) == HIGH) && (digitalRead(waterMid) == LOW) && (digitalRead(waterHi) == HIGH)){
      //Red LED Blinking
      ledBlink();
      motorAutoStart();
      waterLevelVal = 0;
    }
    if ((digitalRead(waterLow) == HIGH) && (digitalRead(waterMid) == HIGH) && (digitalRead(waterHi) == LOW)){
      //Red LED Blinking
      ledBlink();
      motorAutoStart();
      waterLevelVal = 0;
    }
    if ((digitalRead(waterLow) == HIGH) && (digitalRead(waterMid) == HIGH) && (digitalRead(waterHi) == HIGH)){
      //Red LED Blinking
      ledBlink();
      motorAutoStart();
      waterLevelVal = 0;
    }
  }
}

void motorPressed(){
  currBtnMot = millis();
  if (digitalRead(btnMot) == LOW){
    if (currBtnMot - prevBtnMot >=intBtnMot){
      prevBtnMot = currBtnMot;
      //insert code below
      if (motorManual == true){
         motorStartInstruct =! motorStartInstruct;
//         Serial.println("motor pressed");
//         Serial.println(motorStartInstruct);
//         Serial.println(motorStartActual);
      }
    }
  }
}

void manualAutoPressed(){
  currBtnManAuto = millis();
  if (currBtnManAuto - prevBtnManAuto >=intBtnManAuto){
    prevBtnManAuto = currBtnManAuto;
    //insert code below
    if (digitalRead(btnManAuto) == HIGH){
      motorManual = true;
    }
    if (digitalRead(btnManAuto) == LOW){
      motorManual = false;
    }
    ledManualAuto();
  }
}

void RFsendToGreentank(){
  if (motorStartInstruct == false) data.instruct = 0;
  if (motorStartInstruct == true) data.instruct = 1;
  
  RF24NetworkHeader header(nodeGreentank, 'T');
  boolean sent = network.write(header, &data, sizeof(data));
  if (sent){
    //insert confirm code
  }
  else {
    //insert failed code
  }
}

void RFsendInterval(){
  currRFsend = millis();
  if (currRFsend - prevRFsend >=intRFsend){
    prevRFsend = currRFsend;
    //insert code below
    RFsendToGreentank();
  }
}

void RFreceive(){
  while (network.available()){
    digitalWrite(ledRx, HIGH);
    RF24NetworkHeader header;
    network.peek(header);
    if (header.type == 'T'){
      network.read(header, &data, sizeof(data));
      if (data.actual == 0){
        motorStartActual = false;
      }
      if (data.actual == 1){
        motorStartActual = true;
      }
    }
    digitalWrite(ledRx, LOW);
  }
}

void loop(){
  network.update();
  RFreceive();
  waterLevel();
  ledMotorStatus();
  motorPressed();
  manualAutoPressed();
  RFsendInterval();
}
