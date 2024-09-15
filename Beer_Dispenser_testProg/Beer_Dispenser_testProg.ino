int m1 = 5;         //out - pwm
int m2 = 9;         //out - pwm
int led1 = 6;       //out - pwm
int led2 = 10;      //out - pwm
int led_ind = 12;   //out
int btn1 = 2;       //in
int btn2 = 3;       //in
int sensor1 = A1;
int sensor2 = A2;
int coin_slot = A0;


void setup() {
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led_ind, OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);

//  analogWrite(m1, 255);
//  analogWrite(m2, 255);
  analogWrite(led1, 255);
  analogWrite(led2, 255);
  digitalWrite(led_ind, HIGH);
}

void loop() {
  if (analogRead(sensor1) >= 1000 || digitalRead(btn1) == LOW){
    analogWrite(m1, 255);
    
  }
  else if (analogRead(sensor2) >= 1000 || digitalRead(btn2) == LOW){
    analogWrite(m2, 255);
    
  }
  else{
    analogWrite(m1, 0);
    analogWrite(m2, 0);
  }
  Serial.print(analogRead(sensor1));
  Serial.print(", ");
  Serial.print(analogRead(sensor2));
  Serial.print(", ");
  Serial.println(analogRead(coin_slot));
  delay(10);

}
