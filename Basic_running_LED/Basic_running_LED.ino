int x = 2;
int y;

void setup() {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
  }

void loop() {
  y = analogRead (A0);
  if (x == 7){
    x = 2;
  }
  digitalWrite (x, HIGH);
  x++;
  delay (y);
  digitalWrite(x-1, LOW);
}
