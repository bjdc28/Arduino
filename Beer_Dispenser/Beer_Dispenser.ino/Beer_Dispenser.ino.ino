//===================================
//Set Timer
//for beverage A:
const int timerA_a = 0;   //x10  second
const int timerA_b = 5;   //x1   second
const int timerA_c = 5;   //x100 milliseconds
//for beverage B:
const int timerB_a = 0;   //x10  second
const int timerB_b = 5;   //x1   second
const int timerB_c = 1;   //x100 milliseconds
//===================================

//digital pin assign
int m1 = 5;         //out - pwm
int m2 = 9;         //out - pwm
int led1 = 6;       //out - pwm
int led2 = 10;      //out - pwm
int led_ind = 12;   //out
int btn1 = 2;       //in
int btn2 = 3;       //in

//analog pin assign
int sensor1 = A1;
int sensor2 = A2;
int coin_slot = A0;

//number of coins
int coin_amount = 0;

//led animation
int brightness1 = 0;
int brightness2 = 255;
int fadeAmount1 = 5;
int fadeAmount2 = 5;

int a1, b1, c1, a2, b2, c2;

unsigned long coin_prev = 0;
unsigned long coin_curr;

unsigned long led_prev = 0;
unsigned long led_curr;

unsigned long count1_prev = 0;
unsigned long count1_curr;
unsigned long count2_prev = 0;
unsigned long count2_curr;

const long count1_interval = 100;
const long count2_interval = 100;
const long coin_interval = 75;
const long led_interval = 50;

//for toggle
boolean coin_inserted = false;
boolean drink1_disabled = false;
boolean drink2_disabled = false;
boolean count1_start = false;
boolean count2_start = false;
boolean sensor1_activated = false;
boolean sensor2_activated = false;


void setup() {
//  Serial.begin(9600);
  a1 = timerA_a;
  b1 = timerA_b;
  c1 = timerA_c;
  a2 = timerB_a;
  b2 = timerB_b;
  c2 = timerB_c;
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led_ind, OUTPUT);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
}


void ledFade(){
  led_curr = millis();
  if (coin_inserted == false){
    if (led_curr - led_prev >= led_interval){
      led_prev = led_curr;
      
      analogWrite(led1, brightness1);
      brightness1 = brightness1 + fadeAmount1;
      if (brightness1 <= 0 || brightness1 >= 255) {
        fadeAmount1 = -fadeAmount1;
      }
      
      analogWrite(led2, brightness2);
      brightness2 = brightness2 - fadeAmount2;
      if (brightness1 <= 0 || brightness1 >= 255) {
        fadeAmount2 = -fadeAmount2;
      }
    }
  }
}


void ledOn(){
  if (coin_inserted == true){
    if (drink2_disabled == true){
      analogWrite(led1, 255);
      analogWrite(led2, 0);
    }
    else if (drink1_disabled == true){
      analogWrite(led2, 255);
      analogWrite(led1, 0);
    }
    else{
      analogWrite(led1, 255);
      analogWrite(led2, 255);
    }
    digitalWrite(led_ind, HIGH);
  }
  else{
    digitalWrite(led_ind, LOW);
  }
}


void coinActivate(){
  coin_curr = millis();
  if (analogRead(coin_slot) <= 1000){
    if (coin_curr - coin_prev >= coin_interval){
      coin_prev = coin_curr;
      coin_inserted = true;
      coin_amount++;
    }
  }
}


void coinDeactivate(){
  coin_inserted = false;
  coin_amount = 0;
  drink1_disabled = false;
  drink2_disabled = false;
  count1_start = false;
  count2_start = false;
}


void drinkPressed_1(){
//  ----------------------------
  if (analogRead(sensor1) >= 1000){
    sensor1_activated = true;
    if (coin_amount > 0){
      if (drink1_disabled == false){
        drink2_disabled = true;
        count1_start = true;
      }
    }
  }
  if (analogRead(sensor1) < 1000){
    sensor1_activated = false;
    count1_start = false;
  }
//  ----------------------------
  if (sensor1_activated == false){
    if (coin_amount > 0){
      if (digitalRead(btn1) == LOW){
        if (drink1_disabled == false){
          drink2_disabled = true;
          count1_start = true;
        }
      }
    }
    if (digitalRead(btn1) == HIGH){
      count1_start = false;
    }
  }
//  ----------------------------
}


void drinkPressed_2(){
//  ----------------------------
  if (analogRead(sensor2) >= 1000){
    sensor2_activated = true;
    if (coin_amount > 0){
      if (drink2_disabled == false){
        drink1_disabled = true;
        count2_start = true;
      }
    }
  }
  if (analogRead(sensor2) < 1000){
    sensor2_activated = false;
    count2_start = false;
  }
//  ----------------------------
  if (sensor2_activated == false){
    if (coin_amount > 0){
      if (digitalRead(btn2) == LOW){
        if (drink2_disabled == false){
          drink1_disabled = true;
          count2_start = true;
        }
      }
    }
    if (digitalRead(btn2) == HIGH){
      count2_start = false;
    }
  }
//  ----------------------------
}


void pourDrink_1(){
  if (count1_start == true){
    analogWrite(m1, 255);
  }
  if (count1_start == false){
    analogWrite(m1, 0);
  }
}


void pourDrink_2(){
  if (count2_start == true){
    analogWrite(m2, 255);
  }
  if (count2_start == false){
    analogWrite(m2, 0);
  }
}


void count1(){
  count1_curr = millis();
  if (count1_start == true){
    if (count1_curr - count1_prev >= count1_interval){
      count1_prev = count1_curr;
      c1--;
      if (c1 < 0){
        b1--;
        c1 = 9;
      }
      if (b1 < 0){
        a1--;
        b1 = 9;
      }
      if (a1<=0 && b1<=0 && c1<=0){
        coin_amount--;
        a1 = timerA_a;
        b1 = timerA_b;
        c1 = timerA_c;
      }
      if (coin_amount <= 0){
        a1 = timerA_a;
        b1 = timerA_b;
        c1 = timerA_c;
        count1_start = false;
        coinDeactivate();
      }
    }
  }
}


void count2(){
  count2_curr = millis();
  if (count2_start == true){
    if (count2_curr - count2_prev >= count2_interval){
      count2_prev = count2_curr;
      c2--;
      if (c2 < 0){
        b2--;
        c2 = 9;
      }
      if (b2 < 0){
        a2--;
        b2 = 9;
      }
      if (a2<=0 && b2<=0 && c2<=0){
        coin_amount--;
        a2 = timerB_a;
        b2 = timerB_b;
        c2 = timerB_c;
      }
      if (coin_amount <= 0){
        a2 = timerB_a;
        b2 = timerB_b;
        c2 = timerB_c;
        count1_start = false;
        coinDeactivate();
      }
    }
  }
}


void loop() {
  drinkPressed_1();
  drinkPressed_2();
  ledFade();
  ledOn();
  coinActivate();
  count1();
  count2();
  pourDrink_1();
  pourDrink_2();
}
