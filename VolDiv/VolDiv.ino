void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //double a = ((analogRead(A0)/1023.0)*38.69852); //Solar Panel VD Circuit.
  //Serial.println(a);
  double b = ((analogRead(A1)/1023.0)*37.69635); // Battery VD Circuit.
  Serial.println(b);
  delay(100);
}
