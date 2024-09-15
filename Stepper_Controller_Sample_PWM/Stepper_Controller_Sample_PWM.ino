const int dirPin = 2;
const int pulsPin = 3;
const int enPin = 7;
int serRead = Serial.read();

void setup() {
  Serial.begin(9600);
  pinMode(dirPin, OUTPUT);
  pinMode(pulsPin, OUTPUT);
  
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
}

void loop() {
  digitalWrite(dirPin, HIGH);
  analogWrite(pulsPin, 200);
  delay(2000);
  analogWrite(pulsPin, 0);
  delay(500);
  digitalWrite(dirPin, LOW);
  analogWrite(pulsPin, 200);
  delay(2000);
  analogWrite(pulsPin, 0);
  delay(500);
}
