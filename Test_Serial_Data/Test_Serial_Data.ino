double x;
double y;
char text[40];

void setup() {
  Serial.begin(9600);
}

void loop() {
//  x = random(0.0,40.0);
//  y = random(0.0,40.0);
  x = 32.34;
  y = 29.53;
  Serial.print(x);
  Serial.print(",");
  Serial.println(y);
  delay(50);
}
