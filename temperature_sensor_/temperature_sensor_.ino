

void setup() {
  Serial.begin(9600);

}

void loop() {
//  Serial.print(millis());
//  Serial.print(" ");
  Serial.print(analogRead(2) * 0.48828125);
  Serial.print(" ");
  Serial.print("Celcius");
  Serial.println(" ");
  delay(1000);
  

}
