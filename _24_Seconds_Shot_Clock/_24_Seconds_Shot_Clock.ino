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
int button_1 = 7;
int button_2 = 8;
int delayTime = 1;

unsigned long prevMillis_1 = 0;
unsigned long currMillis_1;
unsigned long prevMillis_2 = 0;
unsigned long currMillis_2;

const long interval_1 = 10;
const long interval_2 = 250;

boolean pause = true;
boolean start = true;


void setup() {
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
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


void start_stop()
{
  currMillis_2 = millis();
  if (digitalRead(button_1) == LOW){
      if (currMillis_2 - prevMillis_2 >= interval_2){
      prevMillis_2 = currMillis_2;
      pause = !start;
      start = pause;
      if (w == 0 && x == 0 && y == 0 && z == 0){
        w = 2;
        x = 4;
        y = 0;
        z = 0;
      }
    }
    }
}


void reseter()
{
  currMillis_2 = millis();
  if (digitalRead(button_2) == LOW){
    if (currMillis_2 - prevMillis_2 >= interval_2){
       prevMillis_2 = currMillis_2;
       w = 2;
       x = 4;
       y = 0;
       z = 0;
    }
    }
}


void counter()
{
  currMillis_1 = millis();
  if (pause == false){
    if (currMillis_1 - prevMillis_1 >= interval_1){
    prevMillis_1 = currMillis_1;
    z--;
    if (z < 0){
      y--;
      z = 9;
    }
    if (y < 0){
      x--;
      y = 9;
    }
    if (x < 0){
      w--;
      x = 9;
    }
    if (w < 0){
      w = 0;
      x = 0;
      y = 0;
      z = 0;
      pause = true;
      start = true;
    }
    }
  }
}


void multiplexer()
{
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



void loop() 
{
  start_stop();
  reseter();
  counter();
  multiplexer();
}




