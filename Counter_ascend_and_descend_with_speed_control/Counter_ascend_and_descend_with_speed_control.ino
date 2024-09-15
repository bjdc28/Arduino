int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
int x = 10;
int DC;


unsigned long prevMillis = 0;
unsigned long currMillis;
long interval = 1;

void setup() {               
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(12, INPUT);
  
}

void displayDigit(int digit)
{
 if(digit!=1 && digit != 4)
 digitalWrite(a,HIGH);
 
 if(digit != 5 && digit != 6)
 digitalWrite(b,HIGH);
 
 if(digit !=2)
 digitalWrite(c,HIGH);

 if(digit != 1 && digit !=4 && digit !=7)
 digitalWrite(d,HIGH);
 
 if(digit == 2 || digit ==6 || digit == 8 || digit==0)
 digitalWrite(e,HIGH);
 
 if(digit != 1 && digit !=2 && digit!=3 && digit !=7)
 digitalWrite(f,HIGH);
 
 if (digit!=0 && digit!=1 && digit !=7)
 digitalWrite(g,HIGH);
 
}
void turnOff()
{
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,LOW);
  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
}


void loop() { 
  currMillis = millis();
  interval = analogRead(A0);
  DC = digitalRead(12);
    
  if (currMillis - prevMillis >= interval){
    prevMillis = currMillis;
    if(DC == 1){
    turnOff();
    if (x == 0){
    x = 10;
    }
    x--;    
    displayDigit(x);
  }

    if(DC == 0){
    turnOff();
    if (x == 10){
    x = 0;
    }
    x++;    
    displayDigit(x-1);
  }
  }
}
