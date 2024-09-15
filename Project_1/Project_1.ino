int a = 8;  //For displaying segment "a"
int b = 7;  //For displaying segment "b"
int c = 6;  //For displaying segment "c"
int d = 5;  //For displaying segment "d"
int e = 4;  //For displaying segment "e"
int f = 3;  //For displaying segment "f"
int g = 2;  //For displaying segment "g"
int w = 0;
int x = 0;
int btn_1 = 12;
int btn_2 = 13;
int anode_ones = 9;
int anode_tens = 10;
int A = 0;


boolean pause = true;

unsigned long prevMillis_1 = 0;
unsigned long currMillis_1;
unsigned long prevMillis_2 = 0;
unsigned long currMillis_2;
unsigned long prevMillis_3 = 0;
unsigned long currMillis_3;

const long interval_1 = 1000;
const long interval_2 = 250;
const long interval_3 = 5;


void setup() {
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G

  pinMode(anode_ones, OUTPUT);
  pinMode(anode_tens, OUTPUT);
  pinMode(btn_1, INPUT);
  pinMode(btn_2, INPUT);
}


void displayDigit(int digit)
{
 //Conditions for displaying segment a
 if(digit!=1 && digit != 4)
 digitalWrite(a,LOW);
 
 //Conditions for displaying segment b
 if(digit != 5 && digit != 6)
 digitalWrite(b,LOW);
 
 //Conditions for displaying segment c
 if(digit !=2)
 digitalWrite(c,LOW);
 
 //Conditions for displaying segment d
 if(digit != 1 && digit !=4 && digit !=7)
 digitalWrite(d,LOW);
 
 //Conditions for displaying segment e 
 if(digit == 2 || digit ==6 || digit == 8 || digit==0)
 digitalWrite(e,LOW);
 
 //Conditions for displaying segment f
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
  digitalWrite(anode_ones, LOW);
  digitalWrite(anode_tens, LOW);
}


void start_stop()
{
  currMillis_2 = millis();
  if (digitalRead(btn_1) == HIGH){
      if (currMillis_2 - prevMillis_2 >= interval_2){
      prevMillis_2 = currMillis_2;
      pause = !pause;
      }
    }
    }


void increment()
{
  currMillis_2 = millis();
  if (digitalRead(btn_2) == HIGH){
    if (currMillis_2 - prevMillis_2 >= interval_2){
       prevMillis_2 = currMillis_2;
       if (pause == true){
          if (w != 2 || x != 4){
            x++;
       
               if (x > 9){
                x = 0;
                w++;
                }
          }
          else{
            x = 0;
            w = 0;
          }
        }
    }
  }
}


void counter()
{
  currMillis_1 = millis();
  if (pause == false){
    if (currMillis_1 - prevMillis_1 >= interval_1){
    prevMillis_1 = currMillis_1;
      x--;
    if (x < 0){
      w--;
      x = 9;
    }
    
    if (w < 0){
      w = 0;
      x = 0;
      pause = true;
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
      displayDigit(x);
      digitalWrite (anode_tens, HIGH);
      break;
    
    case 2:
      turnOff();
      displayDigit(w);
      digitalWrite (anode_ones, HIGH);
      A=0;
      break;
      
  }
}

void loop() {
  
  multiplexer();
  counter();
  increment();
  start_stop();

}
