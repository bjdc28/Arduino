

float current = 0;
int rawcurrent = 0;
const int sensorpin = A0; 
int offset = 0;
int I;

void setup() 
{ 
 Serial.begin(9600); 
 offset = analogRead(A0);
}
  
void loop() 
{ 
  float raw_current;
  raw_current = analogRead(A0);
  I = ((raw_current-offset)*0.045); // adjustment

  delay(500);
  Serial.print("Current = "); 
  Serial.print(I);
  Serial.println("A"); 
}
