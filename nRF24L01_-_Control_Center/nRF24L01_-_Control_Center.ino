#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(7, 8);
RF24Network network(radio);


int watchTime1 = 0;
int watchTime2 = 0;

const uint16_t controller = 02;
const uint16_t station_1 = 0111;
const uint16_t station_2 = 0121;
//const uint16_t controller = 00;
//const uint16_t station_1 = 02;
//const uint16_t station_2 = 01;

double ST1_SPvol;
double ST1_BATvol;
double ST1_SPcur;
double ST1_timer1;
double ST2_SPvol;
double ST2_BATvol;
double ST2_SPcur;
double ST2_timer2;

int cont_val = 0;
int ST1_conn = 0;
int ST2_conn = 0;
int CC_conn = 0;
unsigned long prevMillis = 0;
unsigned long prevMillis1 = 0;
unsigned long prevMillis2 = 0;
unsigned long interval = 350;
unsigned long timeout1 = 5000;
unsigned long timeout2 = 5001;


struct payload_1 {
  double spv1;
  double btv1;
  double spc1;
  double timer;
};
payload_1 data1;


struct payload_2 {
  double spv2;
  double btv2;
  double spc2;
  double timer;
};
payload_2 data2;


struct payload_3 {
  int Rs1;
  int Rb1;
  int Rl1;
};
payload_3 control1;


struct payload_4 {
  int Rs2;
  int Rb2;
  int Rl2;
};
payload_4 control2;



void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ controller);
}


void WatchTimerST1() {
  if (watchTime1 == ST1_timer1) {
    if (millis() - prevMillis1 >= timeout1) {
      prevMillis1 = millis();
      ST1_conn = 2;
      //      Serial.println("failed_st1");
    }
  }
  else {
    prevMillis1 = millis();
    ST1_conn = 1;
    watchTime1 = ST1_timer1;
  }
}


void WatchTimerST2() {
  if (watchTime2 == ST2_timer2) {
    if (millis() - prevMillis2 >= timeout2) {
      prevMillis2 = millis();
      ST2_conn = 2;
      //      Serial.println("failed_st2");
    }
  }
  else {
    prevMillis2 = millis();
    ST2_conn = 1;
    watchTime2 = ST2_timer2;
  }
}


void SerialWrite() {
  if (millis() - prevMillis >= interval) {
    prevMillis = millis();
    RFsendST1();
    RFsendST2();

    Serial.print(ST1_SPvol); //0
    Serial.print(",");
    Serial.print(ST1_BATvol); //1
    Serial.print(",");
    Serial.print(ST1_SPcur); //2
    Serial.print(",");

    Serial.print(ST2_SPvol); //3
    Serial.print(",");
    Serial.print(ST2_BATvol); //4
    Serial.print(",");
    Serial.print(ST2_SPcur); //5
    Serial.print(",");

    Serial.print(ST1_conn); //6
    Serial.print(",");
    Serial.print(ST2_conn); //7
    Serial.print(",");
    Serial.println(CC_conn); //8
  }
}


void SerialRead() {
  while (Serial.available() > 0) {
    cont_val = (Serial.read() - 48);
    ValidateSerial();
    //    Serial.println(cont_val);
  }
}


void ValidateSerial() {
  if (cont_val == 0) {
    control1.Rs1 = 2;
    control1.Rb1 = 2;
    control1.Rl1 = 2;
    control2.Rs2 = 2;
    control2.Rb2 = 2;
    control2.Rl2 = 2;
  }
  if (cont_val == 1) control1.Rs1 = 1;
  if (cont_val == 2) control1.Rs1 = 2;
  if (cont_val == 3) control1.Rb1 = 1;
  if (cont_val == 4) control1.Rb1 = 2;
  if (cont_val == 5) control1.Rl1 = 1;
  if (cont_val == 6) control1.Rl1 = 2;
  if (cont_val == 7) control2.Rs2 = 1;
  if (cont_val == 8) control2.Rs2 = 2;
  if (cont_val == 9) control2.Rb2 = 1;
  if (cont_val == 49) control2.Rb2 = 2;
  if (cont_val == 50) control2.Rl2 = 1;
  if (cont_val == 51) control2.Rl2 = 2;
}


void RFsendST1() {
  RF24NetworkHeader header(station_1, 'T');
  boolean ST1_sent = network.write(header, &control1, sizeof(control1));
  if (ST1_sent) {
    CC_conn = 1;
  }
  else {
    CC_conn = 2;
  }
}


void RFsendST2() {
  RF24NetworkHeader header(station_2, 'T');
  boolean ST2_sent = network.write(header, &control2, sizeof(control2));
  if (ST2_sent) {
    CC_conn = 1;
  }
  else {
    CC_conn = 2;
  }
}


void RFreceive1() {
  while (network.available()) {
    RF24NetworkHeader header;
    network.peek(header);
    if (header.type == 'T') {
      network.read(header, &data1, sizeof(data1));
      if (header.from_node == station_1) {
        ST1_SPvol = data1.spv1;
        ST1_BATvol = data1.btv1;
        ST1_SPcur = data1.spc1;
        ST1_timer1 = data1.timer;
      }
      if (header.from_node == station_2) {
        ST2_SPvol = data1.spv1;
        ST2_BATvol = data1.btv1;
        ST2_SPcur = data1.spc1;
        ST2_timer2 = data1.timer;
      }
    }
  }
}


void loop() {
  network.update();
  RFreceive1();
  SerialRead();
  SerialWrite();
  WatchTimerST1();
  WatchTimerST2();
}
