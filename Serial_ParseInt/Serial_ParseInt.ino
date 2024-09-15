char x = 0;

void setup() {
  Serial.begin(9600);
  
}

void loop() {
    while (Serial.available() > 0){
      x = (Serial.read());
      delay(1);
      Serial.println(x);
      if (x == 'a'){
        Serial.println("asasas");
      }
    }
  
  delay(1);
}
