int level_25 = 2;   //IN
int level_50 = 3;   //IN
int level_75 = 4;   //IN
int level_100 = 5;  //IN
int relPump = 6;    //OUT
int relAlarm = 7;   //OUT
int ST1_led = 8;    //OUT
int ST1_sw = 9;     //IN
int ST2_led = 10;   //OUT
int ST2_sw = 11;    //IN
int ST3_led = 12;   //OUT
int ST3_sw = 13;    //IN

boolean pumpStart = false;


void setup() {
  pinMode(level_25, INPUT);
  pinMode(level_50, INPUT);
  pinMode(level_75, INPUT);
  pinMode(level_100, INPUT);
  pinMode(relPump, OUTPUT);
  pinMode(relAlarm, OUTPUT);
  pinMode(ST1_led, OUTPUT);
  pinMode(ST1_sw, INPUT_PULLUP);
  pinMode(ST2_led, OUTPUT);
  pinMode(ST2_sw, INPUT_PULLUP);
  pinMode(ST3_led, OUTPUT);
  pinMode(ST3_sw, INPUT_PULLUP);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);

  digitalWrite(relPump, HIGH);
  digitalWrite(relAlarm, HIGH);

  digitalWrite(A4, HIGH);
  delay(200);

  digitalWrite(A4, LOW);
  digitalWrite(A3, HIGH);
  delay(200);

  digitalWrite(A3, LOW);
  digitalWrite(A2, HIGH);
  delay(200);

  digitalWrite(A2, LOW);
  digitalWrite(A1, HIGH);
  delay(200);

  digitalWrite(A1, LOW);
  digitalWrite(A0, HIGH);
  delay(200);

  digitalWrite(A0, LOW);
  digitalWrite(ST1_led, HIGH);
  delay(200);

  digitalWrite(ST1_led, LOW);
  digitalWrite(ST2_led, HIGH);
  delay(200);

  digitalWrite(ST2_led, LOW);
  digitalWrite(ST3_led, HIGH);
  delay(200);

  digitalWrite(ST3_led, LOW);
  delay(200);

  digitalWrite(ST1_led, HIGH);
  digitalWrite(ST2_led, HIGH);
  digitalWrite(ST3_led, HIGH);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  delay(2000);
  
  digitalWrite(ST1_led, LOW);
  digitalWrite(ST2_led, LOW);
  digitalWrite(ST3_led, LOW);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
}


void Indicators(){
  if (digitalRead(level_100) == LOW){
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    digitalWrite(A4, HIGH);
  }
  if (digitalRead(level_75) == LOW && digitalRead(level_100) == HIGH){
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    digitalWrite(A4, LOW);
  }
  if (digitalRead(level_50) == LOW && digitalRead(level_75) == HIGH){
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
  }
  if (digitalRead(level_25) == LOW && digitalRead(level_50) == HIGH){
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
  }
  if (digitalRead(level_25) == HIGH){
    digitalWrite(A0, HIGH);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
  }
}


void Alarm(){
  if (digitalRead(level_25) == HIGH){
    digitalWrite(relAlarm, LOW);
  }
  if (digitalRead(level_25) == LOW){
    digitalWrite(relAlarm, HIGH);
  }
}


void Pump(){
  if (digitalRead(level_50) == HIGH` || digitalRead(level_25) == HIGH){
    digitalWrite(relPump, LOW);
    pumpStart = true;
  }
  if (digitalRead(level_100) == LOW){
    if (pumpStart == true){
      digitalWrite(relPump, HIGH);
      pumpStart = false;
    }
  }
}


void Stations(){
  if (digitalRead(level_25) == HIGH){
    digitalWrite(ST1_led, LOW);
    digitalWrite(ST2_led, LOW);
    digitalWrite(ST3_led, LOW);
  }
  
  if (digitalRead(level_25) == LOW){
    if (digitalRead(ST1_sw) == LOW){
      digitalWrite(ST1_led, HIGH);
    }
    if (digitalRead(ST1_sw) == HIGH){
      digitalWrite(ST1_led, LOW);
    }
    if (digitalRead(ST2_sw) == LOW){
      digitalWrite(ST2_led, HIGH);
    }
    if (digitalRead(ST2_sw) == HIGH){
      digitalWrite(ST2_led, LOW);
    }
    if (digitalRead(ST3_sw) == LOW){
      digitalWrite(ST3_led, HIGH);
    }
    if (digitalRead(ST3_sw) == HIGH){
      digitalWrite(ST3_led, LOW);
    }
  }
  
}

void loop() {
  Indicators();
  Alarm();
  Pump();
  Stations();
}
