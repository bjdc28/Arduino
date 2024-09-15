int a;

void setup() {
  Serial.begin(9600);
}

void aa(){
  Serial.print ("asasas");
}

void loop() {
//  aa();
  
  a = 6;
  delay(1);
  if (a < 10 && a > 5) {
     Serial.println ("Pangit");
    }
  delay (1000);

}
