int a = 8;
int b = 7;
int c = 6;
int d = 5;
int e = 4;
int f = 3;
int g = 2;
int anode_1 = 9;
int anode_2 = 10;
int x = 0;
int y = 0;


unsigned long prevMillis = 0;
unsigned long currMillis;
const long interval = 1000;

void setup() {               
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(anode_1, OUTPUT);
  pinMode(anode_2, OUTPUT);
  
}

void displayDigit(int digit)
{
 if(digit!=1 && digit != 4)
 digitalWrite(a,LOW);
 
 if(digit != 5 && digit != 6)
 digitalWrite(b,LOW);
 
 if(digit !=2)
 digitalWrite(c,LOW);

 if(digit != 1 && digit !=4 && digit !=7)
 digitalWrite(d,LOW);
 
 if(digit == 2 || digit ==6 || digit == 8 || digit==0)
 digitalWrite(e,LOW);
 
 if(digit != 1 && digit !=2 && digit!=3 && digit !=7)
 digitalWrite(f,LOW);
 
 if (digit!=0 && digit!=1 && digit !=7)
 digitalWrite(g,LOW);
 
}
void turnOff()
{
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
  digitalWrite(anode_1, LOW);
  digitalWrite(anode_2, LOW);
}


void loop() { 
  currMillis = millis();

    
  if (currMillis - prevMillis >= interval){
    prevMillis = currMillis;
    x++;
    if (x == 10){
      y++;
      x=0;
    }
    if (y == 10){
      x=0;
      y=0;
    }
  }
  turnOff();
  digitalWrite(anode_2, HIGH);
  displayDigit(x);
  delay(2);
  
  turnOff();
  digitalWrite(anode_1, HIGH);
  displayDigit(y);
  delay(2);
}
