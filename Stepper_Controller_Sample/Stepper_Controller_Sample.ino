const int dirPin = 2;
const int pulsPin = 3;
const int enPin = 7;


void setup() {
//  Serial.begin(9600);
  pinMode(dirPin, OUTPUT);
  pinMode(pulsPin, OUTPUT);
  
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
}

void loop() {
  digitalWrite(dirPin, HIGH);

  for(int x = 0; x < 1600; x++){
    digitalWrite(pulsPin, HIGH);
    delay(2);
    digitalWrite(pulsPin, LOW);
    delay(2);
  }
  delay(1000);

  digitalWrite(dirPin, LOW);

  for(int x = 0; x < 1600; x++){
    digitalWrite(pulsPin, HIGH);
    delay(2);
    digitalWrite(pulsPin, LOW);
    delay(2);
  }
  delay(1000);
}
