const int dirPin = 2;
const int pulsPin = 3;
const int enPin = 7;

boolean motStart = false;
boolean motStop = false;
boolean fwd = false;

unsigned long prevMStart = 0;
unsigned long currMStart;
const long intMStart = 250;

const int fwdLim = 4;
const int revLim = 5;
//const int fwdLim = 4;
//const int revLim = 5;
const int strt = 12;

void setup() {
  pinMode(fwdLim, INPUT_PULLUP);
  pinMode(revLim, INPUT_PULLUP);
  pinMode(strt, INPUT_PULLUP);
  pinMode(dirPin, OUTPUT);
  pinMode(pulsPin, OUTPUT);
  
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
}


void rotation() {
  if (fwd){
    digitalWrite(dirPin, HIGH);
    if (digitalRead(fwdLim) == LOW){
      motStart = false;
      fwd = false;
    }
  }
  else {
    digitalWrite(dirPin, LOW);
    if (digitalRead(revLim) == LOW){
      motStart = false;
      fwd = true;
    }
  }
}

void motorStop() {
  analogWrite(pulsPin, 0);
}

void motorStart() {
  analogWrite(pulsPin, 125);
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


void startPressed() {
  currMStart = millis();
  if (digitalRead(strt) == LOW){
    if (currMStart - prevMStart >= intMStart){
      prevMStart = currMStart;
      //insert code
      motStart = !motStop;
      motStop = motStart;
      //insert code
    }
  }
}

void loop() {
  startStepper();
  startPressed();

}
