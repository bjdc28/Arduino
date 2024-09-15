int mainLevel_low = 8;
int mainLevel_hi = 9;
int st1Level_low = 6;
int st1Level_hi = 7;
int st1Level_alarm = 5;
int st2Level_low = 3;
int st2Level_hi = 4;
int st2Level_alarm = 2;
int mainRelay_alarm = 13;
int mainRelay_pump = 12;
int st1Relay_pump = 11;
int st2Relay_pump = 10;

int mainSensorCal_low = 100;
int mainSensorCal_hi = 100;
int st1SensorCal_low = 100;
int st1SensorCal_hi = 100;
int st2SensorCal_low = 100;
int st2SensorCal_hi = 100;

unsigned long prevMillis = 0;
unsigned long currMillis;

bool mainPumpStart = false;
bool st1PumpStart = false;
bool st2PumpStart = false;
bool mainAlarm = false;
bool station1Alarm = false;
bool station2Alarm = false;


void setup() {
//  Serial.begin(9600);
  pinMode (mainLevel_low, OUTPUT);
  pinMode (mainLevel_hi, OUTPUT);
  pinMode (st1Level_low, OUTPUT);
  pinMode (st1Level_hi, OUTPUT);
  pinMode (st1Level_alarm, OUTPUT);
  pinMode (st2Level_low, OUTPUT);
  pinMode (st2Level_hi, OUTPUT);
  pinMode (st2Level_alarm, OUTPUT);
  pinMode (mainRelay_alarm, OUTPUT);
  pinMode (mainRelay_pump, OUTPUT);
  pinMode (st1Relay_pump, OUTPUT);
  pinMode (st2Relay_pump, OUTPUT);

  digitalWrite (mainRelay_alarm, HIGH);
  digitalWrite (mainRelay_pump, HIGH);
  digitalWrite (st1Relay_pump, HIGH);
  digitalWrite (st2Relay_pump, HIGH);
}


void Controls(){
  //main tank
  if (analogRead(A0) < mainSensorCal_hi){
    digitalWrite (mainLevel_hi, HIGH);
    mainPumpStart = false;
  }
  if (analogRead(A0) > mainSensorCal_hi){
    digitalWrite (mainLevel_hi, LOW);
  }
  if (analogRead(A1) < mainSensorCal_low){
    digitalWrite (mainLevel_low, HIGH);
    mainAlarm = false;
  }
  if (analogRead(A1) > mainSensorCal_low){
    digitalWrite (mainLevel_low, LOW);
    mainAlarm = true;
    mainPumpStart = true;
  }
  
  //station1 tank
  if (analogRead(A2) < st1SensorCal_hi){
    digitalWrite (st1Level_hi, HIGH);
    st1PumpStart = false;
  }
  if (analogRead(A2) > st1SensorCal_hi){
    digitalWrite (st1Level_hi, LOW);
  }
  if (analogRead(A3) < st1SensorCal_low){
    digitalWrite (st1Level_low, HIGH);
    digitalWrite (st1Level_alarm, LOW);
    station1Alarm = false;
  }
  if (analogRead(A3) > st1SensorCal_low){
    digitalWrite (st1Level_low, LOW);
    digitalWrite (st1Level_alarm, HIGH);
    station1Alarm = true;
    st1PumpStart = true;
  }
  
  //station2 tank
  if (analogRead(A4) < st2SensorCal_hi){
    digitalWrite (st2Level_hi, HIGH);
    st2PumpStart = false;
  }
  if (analogRead(A4) > st2SensorCal_hi){
    digitalWrite (st2Level_hi, LOW);
  }
  if (analogRead(A5) < st2SensorCal_low){
    digitalWrite (st2Level_low, HIGH);
    digitalWrite (st2Level_alarm, LOW);
    station2Alarm = false;
  }
  if (analogRead(A5) > st2SensorCal_low){
    digitalWrite (st2Level_low, LOW);
    digitalWrite (st2Level_alarm, HIGH);
    station2Alarm = true;
    st2PumpStart = true;
  }
}


void Pump(){
  if (mainPumpStart == true){
    digitalWrite (mainRelay_pump, LOW);
  }
  if (mainPumpStart == false){
    digitalWrite (mainRelay_pump, HIGH);
  }
  if (st1PumpStart == true){
    digitalWrite (st1Relay_pump, LOW);
  }
  if (st1PumpStart == false){
    digitalWrite (st1Relay_pump, HIGH);
  }
  if (st2PumpStart == true){
    digitalWrite (st2Relay_pump, LOW);
  }
  if (st2PumpStart == false){
    digitalWrite (st2Relay_pump, HIGH);
  }
}


void Alarm(){
  currMillis = millis();
  if (station1Alarm == true || station2Alarm == true && mainAlarm == false){
    if (currMillis - prevMillis >= 5000){
      prevMillis = currMillis;
      digitalWrite (mainRelay_alarm, LOW);
      delay (50);
      digitalWrite (mainRelay_alarm, HIGH);
    }
  }
  if (mainAlarm == true){
    if (currMillis - prevMillis >= 1000){
      prevMillis = currMillis;
      digitalWrite (mainRelay_alarm, LOW);
      delay (50);
      digitalWrite (mainRelay_alarm, HIGH);
    }
  }
}


void loop() {
//  Serial.println(analogRead(0));
//  Serial.println(analogRead(1));
//  Serial.println(analogRead(2));
//  Serial.println(analogRead(3));
//  Serial.println(analogRead(4));
//  Serial.println(analogRead(5));
//  Serial.println("------------------------");
//  delay(1000);

  Controls();
  Pump();
  Alarm();
}
