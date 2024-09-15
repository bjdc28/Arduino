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

void setup() {
  pinMode(BCD_0, OUTPUT);
  pinMode(BCD_1, OUTPUT);
  pinMode(BCD_2, OUTPUT);
  pinMode(BCD_3, OUTPUT);
  pinMode(anode_ones, OUTPUT);
  pinMode(anode_tens, OUTPUT);
  pinMode(anode_hund, OUTPUT);
  pinMode(anode_thou, OUTPUT);
  digitalWrite (anode_ones, HIGH);
  digitalWrite (anode_tens, HIGH);
  digitalWrite (anode_hund, HIGH);
  digitalWrite (anode_thou, HIGH);
}

void displayOnes (int ones)  //active high
{
//  digitalWrite (anode_ones, HIGH);
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

void turnOff() //active high
{

  digitalWrite(BCD_0, LOW);
  digitalWrite(BCD_1, LOW);
  digitalWrite(BCD_2, LOW);
  digitalWrite(BCD_3, LOW);
}


void loop() {
  
  displayOnes(z);
  delay(1000);
  z++;
  if (z==10){
    z=0;
  }
  turnOff();

}
