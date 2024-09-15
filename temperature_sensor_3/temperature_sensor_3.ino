int pin = 2;
int temp;


void setup() {
  Serial.begin(9600);

}

void loop() {
  temp = analogRead (pin);
//  Serial.print(millis());
//  Serial.print(" ");
  Serial.print(temp * 0.48828125);
  Serial.print(" ");
  Serial.print("Celcius");
  Serial.println(" ");
  Serial.print(temp);
  Serial.print(" ");
  delay(1000);
  

}
