int x = 2;
unsigned long prevMillis = 0;
unsigned long currMillis;
const long interval = 75; 

void setup() {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
  }

void loop() {
  currMillis = millis();
  
  if (currMillis - prevMillis >= interval){
    prevMillis = currMillis;
    if (x == 7){
      digitalWrite (6, LOW);
      x = 2;
    }
    if (x > 2){
      digitalWrite (x-1, LOW);
    }
    if (x < 7){
      digitalWrite (x, HIGH);
      x++;
    }
}
}
