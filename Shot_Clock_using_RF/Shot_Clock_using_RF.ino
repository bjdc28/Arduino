Receiver Codes (Shot Clock)
#include <SPI.h>
#include "RF24.h"


RF24 radio(9, 10);
/**********************************************************/

byte addresses[][6] = {"3Node", "4Node"};

byte shotclock;
bool decimal;

struct payload_t {
  int firstbutton;
  int secondbutton;
  int thirdbutton;
  int fourthbutton;
  int fifthbutton;
};

int latch = 8;
int data = 9;
int clck = 10;

int d1 = 1;
int d2 = 2;

int firstdigit = 2;
int seconddigit = 4;

int f1;
int f2;

int interval = 1000;
int value;
int dot = 0;

boolean state = false;
boolean mode = false;

unsigned long current;
unsigned long previous;
unsigned long current1;
unsigned long previous1;


void setup()
{
  Serial.begin(115200);
  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(clck, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  radio.begin();
  radio.setChannel(95);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.startListening();
}


void loop() {
  if (mode == true) {
    startpause();
  }
  if (mode == false) {
    Display();
  }
  if (radio.available()) {
    payload_t payload;
    radio.read(&payload, sizeof(payload));
    if (payload.firstbutton == HIGH) {
      startpause();
    }
    if (payload.secondbutton == HIGH) {
      reset24();
    }
    if (payload.thirdbutton == HIGH) {
      reset14();
    }
    if (payload.fourthbutton == HIGH){
      increment();
    }
    if (payload.fifthbutton == HIGH){
      decrement();
    }
  }
}

void startpause() {
  current1 = millis();
  if (current1 - previous1 >= 250) {
    previous1 = current1;
    state = !mode;
    mode = state;
  }
}


void start() {
  Display();
  current = millis();
  if (current - previous >= interval) {
    previous = current;
    countdown();
  }
}

void countdown() {
  seconddigit--;
  if (seconddigit < 0) {
    seconddigit = 9;
    firstdigit--;
  }
  if (interval == 1000 && firstdigit == 0 ) {
    interval = 100;
    firstdigit = 9;
    seconddigit = 9;
    dot = 128;
  }
  if ( firstdigit == 0 && seconddigit == 0) {
    firstdigit  = 0;
    seconddigit = 0;
    mode = false;
    state = false;
    interval = 1000;
  }
}

void Display() {
  digitValue(firstdigit, d1);
  digitValue(seconddigit, d2);
  DisplayValue();
  Serial.print(firstdigit);
  if ( interval == 100) {
    Serial.print(".");
  }
  Serial.println(seconddigit);

}

void DisplayValue() {
  digitalWrite(latch, LOW);
  shiftOut(data, clck, MSBFIRST, f2 >> 0);
  shiftOut(data, clck, MSBFIRST, f1 >> 0);
  digitalWrite(latch, HIGH);
}

void digitValue(int x, int y) {
  switch (x) {
    case 0:
      value = 63;
      break;

    case 1:
      value = 6;
      break;

    case 2:
      value = 91;
      break;

    case 3:
      value = 79;
      break;

    case 4:
      value = 102;
      break;

    case 5:
      value = 109;
      break;

    case 6:
      value = 125;
      break;

    case 7:
      value = 7;
      break;

    case 8:
      value = 127;
      break;

    case 9 :
      value = 103;
      break;
  }

  switch (y) {
    case 1:
      f1 = value;
      break;

    case 2:
      f2 = value;
      break;
  }
}

void reset24() {
  current1 = millis();
  if ( current1 - previous1 >= 150) {
    previous1 = current1;
    interval = 1000;
    firstdigit = 2;
    seconddigit = 4;
    dot = 0;
  }
}

void reset14() {
  current1 = millis();
  if (current1 - previous1 >= 150) {
    previous1 = current1;
    interval = 1000;
    firstdigit = 1;
    seconddigit = 4;
    dot = 0;
  }
}
void increment() {
  current1 = millis();
  if ( current1 - previous1 >= 150) {
    previous1 = current1;
    if ( mode == false) {
      seconddigit++;
      if (interval == 1000) {
        if (seconddigit > 9 && 1 < firstdigit < 2) {
          seconddigit = 0;
          firstdigit++;
        }
        if (seconddigit > 4 && firstdigit == 2) {
          seconddigit = 0;
          firstdigit = 0;
        }
      }
      if (interval == 100) {
        if (seconddigit > 9 && firstdigit  < 9) {
          seconddigit = 0;
          firstdigit++;
        }
        if (seconddigit > 9 && firstdigit == 9) {
          seconddigit = 0;
          firstdigit = 0;
        }
      }
    }
  }
}

void decrement() {
  current1 = millis();
  if (current1 - previous1 >= 150) {
    previous1 = current1;
    if (mode == false) {
      seconddigit--;
      if (interval == 1000) {
        if (seconddigit < 0 && firstdigit > 0) {
          seconddigit = 9;
          firstdigit--;
        }
        if (seconddigit < 0 && firstdigit == 0) {
          seconddigit = 4;
          firstdigit = 2;
        }
      }
      if (interval == 100) {
        if (seconddigit < 0 && firstdigit > 0) {
          seconddigit = 9;
          firstdigit--;
        }
        if (seconddigit < 0 && firstdigit == 0) {
          seconddigit = 0;
          firstdigit = 0;
        }
      }
    }
  }

