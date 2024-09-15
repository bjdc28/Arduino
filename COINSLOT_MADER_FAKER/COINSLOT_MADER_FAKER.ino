const int coinInt = 0; 
volatile unsigned long ptime;
int t;
volatile int coinsValue = 0;

int coinsChange = 0;                  


void setup()
{
  Serial.begin(9600);                 

  attachInterrupt(coinInt, coinInserted, RISING);   

}
void coinInserted()    

{
  coinsValue = coinsValue + 1;  
  ptime = millis();                       

}
void loop()
{
  if(coinsValue>0&&millis()-ptime>400){
    coinsChange = coinsValue;
    coinsValue = 0;        
  }
switch (coinsChange){
  case 1:
  t = 1;
  Serial.println(t);
  coinsChange=0;
  break;
  case 2:
  t = 5;
  Serial.println(t);
  coinsChange=0;
  break;
  case 3:
  t = 10;
  Serial.println(t);
  coinsChange=0;
  break;
}
}

