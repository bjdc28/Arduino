#include <Servo.h>
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;
Servo servo;
int pos = 0;

void setup() {
servo.attach(9);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

}

void loop() {
 
  speedControl();
  
   
}

void speedControl() {
  // Turn on motors

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  int i = 255;
    analogWrite(enB, i);
    delay(2000);
  
    analogWrite(enB, 0);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(2000);
  
   for (pos = 0; pos <= 180; pos += 5) { 
    
    servo.write(pos);             
    delay(15);                      
  }
  for (pos = 180; pos >= 0; pos -= 5) { 
    servo.write(pos);             
    delay(15);         

    
  } 
  delay(2000);
}
