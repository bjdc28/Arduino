int Overload = 2;
int WaterLevel1 = 3;
int WaterLevel2 = 4;
int Phase = 5;
int Motor = 6;    //active high
int aLight = 7;   //active low
int Buzzer = 8;   //active low
int ledRun = 11;
int ledStop = 10;
int ledFault = 9;
int Stop = 13;
int Reset = 12;

boolean alarmActivate = false;
boolean Start = false;
boolean Fault = false;

void setup(){
  pinMode(Overload, INPUT_PULLUP);
  pinMode(WaterLevel1, INPUT_PULLUP);
  pinMode(WaterLevel2, INPUT_PULLUP);
  pinMode(Phase, INPUT_PULLUP);
  pinMode(Motor, OUTPUT); 
  pinMode(aLight, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(ledRun, OUTPUT);
  pinMode(ledStop, OUTPUT);
  pinMode(ledFault, OUTPUT);
  pinMode(Stop, INPUT_PULLUP);
  pinMode(Reset, INPUT_PULLUP);
  digitalWrite(Motor, 0);
  digitalWrite(aLight, 1);
  digitalWrite(Buzzer, 1);
  digitalWrite(ledStop, 1);
}

void Run(){
  if (Start){
    digitalWrite(ledRun, 1);
    if (digitalRead(Overload) == 1){
      if (digitalRead(Phase) == 1){
        
        if (digitalRead(WaterLevel1) == 1){
          digitalWrite(aLight, 0);
          digitalWrite(Motor, 0);
        }
        if (digitalRead(WaterLevel1) == 0){
          digitalWrite(aLight, 1);
          if ((digitalRead(WaterLevel2) == 1)){
            digitalWrite(Motor, 1);
          }
          if ((digitalRead(WaterLevel2) == 0)){
            digitalWrite(Motor, 0);
          }
        }
        
      }
      if (digitalRead(Phase) == 0){
        alarmActivate = true;
        digitalWrite(ledRun, 0);
        digitalWrite(ledStop, 1);
        digitalWrite(ledFault, 1);
        Fault = true;
        Start = false;
      }
    }
    if (digitalRead(Overload) == 0){
      alarmActivate = true;
      digitalWrite(ledRun, 0);
      digitalWrite(ledStop, 1);
      digitalWrite(ledFault, 1);
      Fault = true;
      Start = false;
    }
  }
}

void ReadButton(){
  if (Fault){
    if (digitalRead(Reset) == 0){
      digitalWrite(ledFault, 0);
      alarmActivate = false;
      Fault = false;
      Start = true;
    }
    if (digitalRead(Stop) == 0){
      digitalWrite(ledFault, 0);
      alarmActivate = false;
      Fault = false;
    }
  }
  if (digitalRead(Stop) == 0){
    Start = false;
    digitalWrite(Motor, 0);
    digitalWrite(ledRun, 0);
    digitalWrite(ledStop, 1);
  }
  if (digitalRead(Reset) == 0){
    Start = true;
    digitalWrite(ledRun, 1);
    digitalWrite(ledStop, 0);
  }
}

void Alarm(){
  if (alarmActivate){
    digitalWrite(Motor, 0);
    digitalWrite(aLight, 0);
    digitalWrite(Buzzer, 0);
    digitalWrite(ledRun, 0);
    digitalWrite(ledStop, 1);
  }
  if (!alarmActivate){
    digitalWrite(aLight, 1);
    digitalWrite(Buzzer, 1);
  }
}

void loop(){
  Run();
  ReadButton();
  Alarm();
}
