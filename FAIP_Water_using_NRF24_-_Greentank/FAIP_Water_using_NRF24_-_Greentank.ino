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

int senseMotStart = 3;
int ledRX = 4;
int ledREL1 = 5;
int ledREL2 = 6;
int REL1 = 9;
int REL2 = 10;
bool motorStart = false;

struct payload {
  int instruct;
  int actual;
};
payload data;


void setup() {
  pinMode(senseMotStart, INPUT_PULLUP);
  pinMode(ledRX, OUTPUT);
  pinMode(ledREL1, OUTPUT);
  pinMode(ledREL2, OUTPUT);
  pinMode(REL1, OUTPUT);
  pinMode(REL2, OUTPUT);
  digitalWrite(ledRX, LOW);
  digitalWrite(ledREL1, LOW);
  digitalWrite(ledREL2, LOW);
  digitalWrite(REL1, HIGH);
  digitalWrite(REL2, HIGH);
  SPI.begin();
  radio.begin();
  network.begin(90, nodeGreentank);  //(channel, node address)
//  digitalWrite(REL1, LOW);
//  digitalWrite(REL2, LOW);
}

void relayControl(){
  if (motorStart == false){
    digitalWrite(REL1, HIGH);
    digitalWrite(ledREL1, LOW);
  }
  if (motorStart == true){
    digitalWrite(REL1, LOW);
    digitalWrite(ledREL1, HIGH);
  }
}

void motorStatus(){
  if (digitalRead(senseMotStart) == HIGH){
    data.actual = 0;
  }
  if (digitalRead(senseMotStart) == LOW){
    data.actual = 1;
  }
}

void RFsendToBoiler(){
  RF24NetworkHeader header(nodeBoiler, 'T');
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
    RFsendToBoiler();
  }
}

void RFreceive(){
  while (network.available()){
    digitalWrite(ledRX, HIGH);
    RF24NetworkHeader header;
    network.peek(header);
    if (header.type == 'T'){
      network.read(header, &data, sizeof(data));
      if (data.instruct == 0){
        motorStart = false;
      }
      if (data.instruct == 1){
        motorStart = true;
      }
    }
    digitalWrite(ledRX, LOW);
  }
}

void loop() {
  network.update();
  RFreceive();
  relayControl();
  motorStatus();
  RFsendInterval();
}
