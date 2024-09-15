int w = 0;
int x = 0;
int y = 0;
int z = 0;
int anode_ones = 10;
int anode_tens = 11;
int anode_hund = 12;
int anode_thou = 13;
int BCD_0 = 2;
int BCD_1 = 3;
int BCD_2 = 4;
int BCD_3 = 5;
unsigned long prevMillis = 0;
unsigned long currMillis;
const long interval_1 = 100;
int delayTime = 1;


void setup() {
  pinMode(BCD_0, OUTPUT);
  pinMode(BCD_1, OUTPUT);
  pinMode(BCD_2, OUTPUT);
  pinMode(BCD_3, OUTPUT);
  pinMode(anode_ones, OUTPUT);
  pinMode(anode_tens, OUTPUT);
  pinMode(anode_hund, OUTPUT);
  pinMode(anode_thou, OUTPUT);
}


void displayDigit (int number)  //active high
{
  if (number == 0){digitalWrite (BCD_0, LOW);
                 digitalWrite (BCD_1, LOW);
                 digitalWrite (BCD_2, LOW);
                 digitalWrite (BCD_3, LOW);}
  if (number == 1) digitalWrite (BCD_3, HIGH);
  if (number == 2) digitalWrite (BCD_2, HIGH);
  if (number == 3){digitalWrite (BCD_2, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (number == 4) digitalWrite (BCD_1, HIGH);
  if (number == 5){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (number == 6){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_2, HIGH);}
  if (number == 7){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_2, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (number == 8) digitalWrite (BCD_0, HIGH);
  if (number == 9){digitalWrite (BCD_0, HIGH);
                 digitalWrite (BCD_3, HIGH);}  
}

void turnOff() //active high
{
  digitalWrite(anode_ones,LOW);
  digitalWrite(anode_tens,LOW);
  digitalWrite(anode_hund,LOW);
  digitalWrite(anode_thou,LOW);
  digitalWrite(BCD_0, LOW);
  digitalWrite(BCD_1, LOW);
  digitalWrite(BCD_2, LOW);
  digitalWrite(BCD_3, LOW);
}


void loop() {
  
  currMillis = millis();

  if (currMillis - prevMillis >= interval_1){
    z++;
    if (z == 10){
      y++;
      z=0;
    }
    if (y == 10){
      x++;
      y=0;
    }
    if (x == 10){
      w++;
      x=0;
    }
    if (w == 10){
      w=0;
      z=0;
    }
    prevMillis = currMillis;
  }
  
  turnOff();
  digitalWrite (anode_thou, HIGH);
  displayDigit(w);
  delay(delayTime);
  
  turnOff();
  digitalWrite (anode_hund, HIGH);
  displayDigit(x);
  delay(delayTime);
  
  turnOff();
  digitalWrite (anode_tens, HIGH);
  displayDigit(y);
  delay(delayTime);
  
  turnOff();
  digitalWrite (anode_ones, HIGH);
  displayDigit(z);
  delay(delayTime);
}




