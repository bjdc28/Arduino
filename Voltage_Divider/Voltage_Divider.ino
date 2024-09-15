double a;

void setup() {
  Serial.begin(9600);

}

void loop() {
  a = ((analogRead(A0)/1023.0)*38.28);
  Serial.println(a);
  delay(1000);
}





