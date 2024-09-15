int w = 0;
int x = 0;
int y = 0;
int z = 0;
int A = 0;
int anode_ones = 10;
int anode_tens = 11;
int anode_hund = 12;
int anode_thou = 13;
int BCD_D = 2;
int BCD_C = 3;
int BCD_B = 4;
int BCD_A = 5;
int button_1 = 7;
int button_2 = 8;

unsigned long prevMillis_1 = 0;
unsigned long currMillis_1;
unsigned long prevMillis_2 = 0;
unsigned long currMillis_2;
unsigned long prevMillis_3 = 0;
unsigned long currMillis_3;


const long interval_1 = 10;
const long interval_2 = 250;
const long interval_3 = 2;

boolean pause = true;
boolean start = true;


void setup() {
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  pinMode(BCD_D, OUTPUT);
  pinMode(BCD_C, OUTPUT);
  pinMode(BCD_B, OUTPUT);
  pinMode(BCD_A, OUTPUT);
  pinMode(anode_ones, OUTPUT);
  pinMode(anode_tens, OUTPUT);
  pinMode(anode_hund, OUTPUT);
  pinMode(anode_thou, OUTPUT);
//  Serial.begin(9600);
}


void displayDigit (int number)  //active high
{
  if (number == 0){digitalWrite (BCD_D, LOW);
                   digitalWrite (BCD_C, LOW);
                   digitalWrite (BCD_B, LOW);
                   digitalWrite (BCD_A, LOW);}
  if (number == 1) digitalWrite (BCD_A, HIGH);
  if (number == 2) digitalWrite (BCD_B, HIGH);
  if (number == 3){digitalWrite (BCD_B, HIGH);
                   digitalWrite (BCD_A, HIGH);}
  if (number == 4) digitalWrite (BCD_C, HIGH);
  if (number == 5){digitalWrite (BCD_C, HIGH);
                   digitalWrite (BCD_A, HIGH);}
  if (number == 6){digitalWrite (BCD_C, HIGH);
                   digitalWrite (BCD_B, HIGH);}
  if (number == 7){digitalWrite (BCD_C, HIGH);
                   digitalWrite (BCD_B, HIGH);
                   digitalWrite (BCD_A, HIGH);}
  if (number == 8) digitalWrite (BCD_D, HIGH);
  if (number == 9){digitalWrite (BCD_D, HIGH);
                   digitalWrite (BCD_A, HIGH);}  
}


void turnOff() //active high
{
  digitalWrite(anode_ones,LOW);
  digitalWrite(anode_tens,LOW);
  digitalWrite(anode_hund,LOW);
  digitalWrite(anode_thou,LOW);
  digitalWrite(BCD_D, LOW);
  digitalWrite(BCD_C, LOW);
  digitalWrite(BCD_B, LOW);
  digitalWrite(BCD_A, LOW);
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
//      Serial.println(millis());
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
  currMillis_3 = millis();
  if (currMillis_3 - prevMillis_3 >= interval_3)
  {
    prevMillis_3 = currMillis_3;
    A++;
  }
  switch (A){
    case 1:
      turnOff();
      displayDigit(w);
      digitalWrite (anode_thou, HIGH);
      break;
    
    case 2:
      turnOff();
      displayDigit(x);
      digitalWrite (anode_hund, HIGH);
      break;
      
    case 3:
      turnOff();
      displayDigit(y);
      digitalWrite (anode_tens, HIGH);
      break;
      
    case 4:
      turnOff();
      displayDigit(z);
      digitalWrite (anode_ones, HIGH);
      A = 0;
      break;
  }
}



void loop() 
{
  start_stop();
  reseter();
  counter();
  multiplexer();
}




