int temp;
int fan = 9;

void setup() {
  Serial.begin(9600);
  pinMode (fan, OUTPUT);

}

void loop() {
  temp = analogRead(2);
  Serial.print(temp * 0.48828125);
  Serial.print(" ");
  Serial.print("Celcius");
  Serial.println(" ");
  Serial.print(temp);
  Serial.print(" ");
  
  if (temp <= 60){
    analogWrite(fan, 0);
  }
  if (temp > 60 && temp <=68){
    analogWrite(fan, 20);
  }
  if (temp > 68){
    analogWrite(fan, 255);
  }
  delay(1000);
  

}
