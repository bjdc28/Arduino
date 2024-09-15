int led1 = 2;
int led2 = 3;
int led3 = 9;
int dat1;
int dat2;


void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void readData(){
  
  if (Serial.available()>0){
      int c = (Serial.read()-48);
      dat1 = c;
  }
}

void control_1(){
      if (dat1 < 5){
        switch (dat1){
        
        case 1:
          digitalWrite(led1, LOW);
          break;
          
        case 2:
          digitalWrite(led1, HIGH);
          break;
          
        case 3:
          digitalWrite(led2, LOW);
          break;
          
        case 4:
          digitalWrite(led2, HIGH);
          break;
      }
     }
     if (dat1 >=5){
        dat2 = map(dat1, 5, 9, 0, 255);
        analogWrite(led3, dat2);
     }   
}


void loop() {
  
  readData();
  control_1();
  delay(1);
  }
