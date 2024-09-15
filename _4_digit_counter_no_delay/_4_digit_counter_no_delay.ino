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
const long interval_1 = 10;
int delayTime = 1;

//    0000,//0
//    0001,//1
//    0010,//2
//    0011,//3
//    0100,//4
//    0101,//5
//    0110,//6
//    0111,//7
//    1000,//8
//    1001,//9


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


void displayOnes (int ones)  //active high
{
  digitalWrite (anode_ones, HIGH);
  if (ones == 0){digitalWrite (BCD_0, LOW);
                 digitalWrite (BCD_1, LOW);
                 digitalWrite (BCD_2, LOW);
                 digitalWrite (BCD_3, LOW);}
  if (ones == 1) digitalWrite (BCD_3, HIGH);
  if (ones == 2) digitalWrite (BCD_2, HIGH);
  if (ones == 3){digitalWrite (BCD_2, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (ones == 4) digitalWrite (BCD_1, HIGH);
  if (ones == 5){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (ones == 6){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_2, HIGH);}
  if (ones == 7){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_2, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (ones == 8) digitalWrite (BCD_0, HIGH);
  if (ones == 9){digitalWrite (BCD_0, HIGH);
                 digitalWrite (BCD_3, HIGH);}  
}

void displayTens (int tens)  //active high
{
  digitalWrite (anode_tens, HIGH);
  if (tens == 0){digitalWrite (BCD_0, LOW);
                 digitalWrite (BCD_1, LOW);
                 digitalWrite (BCD_2, LOW);
                 digitalWrite (BCD_3, LOW);}
  if (tens == 1) digitalWrite (BCD_3, HIGH);
  if (tens == 2) digitalWrite (BCD_2, HIGH);
  if (tens == 3){digitalWrite (BCD_2, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (tens == 4) digitalWrite (BCD_1, HIGH);
  if (tens == 5){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (tens == 6){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_2, HIGH);}
  if (tens == 7){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_2, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (tens == 8) digitalWrite (BCD_0, HIGH);
  if (tens == 9){digitalWrite (BCD_0, HIGH);
                 digitalWrite (BCD_3, HIGH);}  
}

void displayHund (int hund)  //active high
{
  digitalWrite (anode_hund, HIGH);
  if (hund == 0){digitalWrite (BCD_0, LOW);
                 digitalWrite (BCD_1, LOW);
                 digitalWrite (BCD_2, LOW);
                 digitalWrite (BCD_3, LOW);}
  if (hund == 1) digitalWrite (BCD_3, HIGH);
  if (hund == 2) digitalWrite (BCD_2, HIGH);
  if (hund == 3){digitalWrite (BCD_2, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (hund == 4) digitalWrite (BCD_1, HIGH);
  if (hund == 5){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (hund == 6){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_2, HIGH);}
  if (hund == 7){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_2, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (hund == 8) digitalWrite (BCD_0, HIGH);
  if (hund == 9){digitalWrite (BCD_0, HIGH);
                 digitalWrite (BCD_3, HIGH);}  
}

void displayThou (int thou)  //active high
{
  digitalWrite (anode_thou, HIGH);
  if (thou == 0){digitalWrite (BCD_0, LOW);
                 digitalWrite (BCD_1, LOW);
                 digitalWrite (BCD_2, LOW);
                 digitalWrite (BCD_3, LOW);}
  if (thou == 1) digitalWrite (BCD_3, HIGH);
  if (thou == 2) digitalWrite (BCD_2, HIGH);
  if (thou == 3){digitalWrite (BCD_2, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (thou == 4) digitalWrite (BCD_1, HIGH);
  if (thou == 5){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (thou == 6){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_2, HIGH);}
  if (thou == 7){digitalWrite (BCD_1, HIGH);
                 digitalWrite (BCD_2, HIGH);
                 digitalWrite (BCD_3, HIGH);}
  if (thou == 8) digitalWrite (BCD_0, HIGH);
  if (thou == 9){digitalWrite (BCD_0, HIGH);
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

//  turnOff();
  
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
  displayThou(w);
  delay(delayTime);
  
  turnOff();
  displayHund(x);
  delay(delayTime);
  
  turnOff();
  displayTens(y);
  delay(delayTime);
  
  turnOff();
  displayOnes(z);
  delay(delayTime);
}




