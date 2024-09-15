//unfinished
int x = 2;
int y;

void setup() {
  pinMode (2, OUTPUT);
  pinMode (3, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (6, OUTPUT);

}

void loop() {
  
  digitalWrite (x-1, LOW);
  if (x == 7){
    x=2;
  }
  digitalWrite (x, HIGH);
  x = x+1;
  delay (250);

}
