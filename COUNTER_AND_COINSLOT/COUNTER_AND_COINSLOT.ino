
int cs;
int t;
int p;
int q; 
int r;
int s;
int w = 0;
int x = 0;
int y = 0;
int z= 0;
int w1 = 0;
int x1 = 0;
int y1 = 0;
int z1= 0;
int w5 = 0;
int x5 = 0;
int y5 = 0;
int z5= 0;
int w10 = 0;
int x10 = 0;
int y10 = 0;
int z10 = 0;
int start = A0;
int pumpcold = 10;
int pumphot = 11;
int startled= 0;
int hotled=12;
int coldled = 13;
int cathode_tens = 6;
int cathode_ones = 7;
int cathode_tenths = 8;
int cathode_hundreths = 9;
unsigned long prevMills1 =0;
unsigned long currMills1;
const long interval1=10;
unsigned long prevMills2 =0;
unsigned long currMills2;
const long interval2=250;
unsigned long prevMills3 = 0;
unsigned long currMills3;
const long interval3=250;
unsigned long prevMills4 = 0;
unsigned long currMills4;
const long interval4=250;
unsigned long prevMills5 = 0;
unsigned long currMills5;
const long interval5=2;
unsigned long prevMills6 = 0;
unsigned long currMills6;
const long interval6=1;
volatile unsigned long pulsetime;
const int coinInt = 2;
volatile int coinsValue = 0;
int coinsChange = 0;
boolean STOP = true;
boolean ST = true;
boolean BUGNAW = true;
boolean INIT = true;
int CASE=0;
int total= 0;
int val;
void setup() {
Serial.begin(9600);   
for (int i=22; i<29; i++){
pinMode (i, OUTPUT);}
for (int i=22; i<29; i++){
digitalWrite (i, HIGH);}
pinMode(cathode_tens,OUTPUT);
pinMode(cathode_ones,OUTPUT);
pinMode(cathode_tenths,OUTPUT);
pinMode(cathode_hundreths,OUTPUT);
attachInterrupt(digitalPinToInterrupt(coinInt), coinInserted, RISING);  


}
void led(int a, int b, int c, int d, int e, int f, int g){
    if (a == 0){
    digitalWrite(22, LOW);}
    if (b == 0){
    digitalWrite(23, LOW);}
    if (c == 0){
    digitalWrite(24, LOW);}
    if (d == 0){
    digitalWrite(25, LOW);}
    if (e == 0){
    digitalWrite(26, LOW);}
    if (f == 0){
    digitalWrite(27, LOW);}
    if (g == 0){
    digitalWrite(28, LOW);}
  }
void disp(int digit){
  if (digit == 0){led(0,0,0,0,0,0,1);}
  if (digit == 1){led(1,0,0,1,1,1,1);}
  if (digit == 2){led(0,0,1,0,0,1,0);}
  if (digit == 3){led(0,0,0,0,1,1,0);}
  if (digit == 4){led(1,0,0,1,1,0,0);}
  if (digit == 5){led(0,1,0,0,1,0,0);}
  if (digit == 6){led(0,1,0,0,0,0,0);}
  if (digit == 7){led(0,0,0,1,1,1,1);}
  if (digit == 8){led(0,0,0,0,0,0,0);}
  if (digit == 9){led(0,0,0,0,1,0,0);}
  }
  void coinInserted(){
coinsValue = coinsValue + 1;  
  pulsetime = millis(); 
     
}
void count(){
  currMills1=millis();
  if (STOP==false){
    if (currMills1-prevMills1>=interval1){
    prevMills1 = currMills1;
     z--;
     if (z<0){
      y--;
      z=9;
     }
     if (y<0){
      x--;
      y=9;
     }
     if (x<0){
      w--;
      x=9;
     }
     if (w<0){
      
      x = 0;
      y= 0;
      w = 0;
      z = 0;
      
     STOP = true;
     ST = true;
     
     }
}
  }
}

void coinslot()
{
  if(coinsValue>0&&millis()-pulsetime>500){
    coinsChange = coinsValue;
    coinsValue = 0;        
  }
switch (coinsChange){
  case 1:
  cs= 1;
  coinsChange=0;
  break;
  case 2:
  cs= 5;
  coinsChange=0;
  break;
  case 3:
  cs= 10;
  coinsChange=0;
  break;
}
}
void counter(){
 if (cs ==1){cs = 0;
         t = w*1000+x*100+y*10+z; 
   t = t+1;
   total = total+1;
   z1++;
     if (z1>9){
      y1++;
      z1=0;
     }
     if (y1>9){
      x1++;
      y1=0;
     }
     if (x1>9){
      w1++;
      x1=0;
     }
     if (w1>9){
      x1 =9;
      y1 = 9;
      z1= 9;
     }
     w = t/1000; 
  x =  (t - w*1000)/100;
  y =  (t- w*1000 - x*100)/10;
  z = t- w*1000-x*100 - y*10;

 }
if (cs==5){cs = 0;
         t = w*1000+x*100+y*10+z; 
    t = t +5;
   total = total+5;
   z5++;
     if (z5>9){
      y5++;
      z5=0;
     }
     if (y5>9){
      x5++;
      y5=0;
     }
     if (x5>9){
      w5++;
      x5=0;
     }
     if (w5>9){
      x5 =9;
      y5 = 9;
      z5= 9;
     }
     w = t/1000; 
  x =  (t - w*1000)/100;
  y =  (t- w*1000 - x*100)/10;
  z = t- w*1000-x*100 - y*10;
}
if (cs ==10){cs = 0;
         t = w*1000+x*100+y*10+z; 
  t=t+10;
   total = total+10;
   z10++;
     if (z10>9){
      y10++;
      z10=0;
     }
     if (y10>9){
      x10++;
      y10=0;
     }
     if (x10>9){
      w10++;
      x10=0;
     }
     if (w10>9){
      x10 =9;
      y10 = 9;
      z10= 9;
  }
     w = t/1000; 
  x =  (t - w*1000)/100;
  y =  (t- w*1000 - x*100)/10;
  z = t- w*1000-x*100 - y*10; 
}
  Serial.println(w);
    Serial.println(x);  
      Serial.println(y);  
        Serial.println(z);    
}
void turnoff() 
{
  for (int j = 22; j<29; j++)
  {
  digitalWrite(j, HIGH);}
  
  digitalWrite(cathode_tens,LOW);
  digitalWrite(cathode_ones,LOW);
  digitalWrite(cathode_tenths,LOW);
  digitalWrite(cathode_hundreths,LOW);
}
void multi()
{
  currMills5 = millis();
  if(currMills5 - prevMills5 >= interval5)
  {
  prevMills5 = currMills5;
  CASE++;
  }
  switch (CASE){
    case 1:
    turnoff();
    disp(w);
    digitalWrite(cathode_tens,HIGH);
    break;
    
    case 2:
    turnoff();
    disp(x);
    digitalWrite(cathode_ones,HIGH);
    break;

     case 3:
    turnoff();
    disp(y);
    digitalWrite(cathode_tenths,HIGH);
    break;

    case 4:
    turnoff();
    disp(z);
    digitalWrite(cathode_hundreths,HIGH);
    CASE = 0;
    break;
  }
  
}

void loop()
{
count();
counter();
coinslot();
multi();

}
