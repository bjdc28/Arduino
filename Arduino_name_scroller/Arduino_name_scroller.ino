int pin1 = 2;
int pin2 = 3;                                    //                            --6--
int pin3 = 4;                                    //                         5 |     | 7
int pin4 = 5;                                    //                           |--4--|
int pin5 = 6;                                    //                         1 |     | 3
int pin6 = 7;                                    //                            --2--
int pin7 = 8;
int gnd1 = 9;                                    //                          gnd1 is display 1's gnd
int gnd2 = 11;                                   //                          gnd2 is display 2's gnd
int timer = 200;

void setup(){
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);                //Sets up all of the pins
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(gnd1, OUTPUT);
  pinMode(gnd2, OUTPUT);
}

void loop() {
  
  
  
  for (int i=0; i<timer; i++){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B0);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);                                                                          // A
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);
   delay(1);
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);
   delay(1);
   
  }
  
  for (int i=0; i<timer; i++){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);                                                                                     //Ar
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);
   delay(1);
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B0);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);
   delay(1);
   
  }
  
  for (int i=0; i<timer; i++){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B0);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);                                                                             //rd
   delay(1);
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);
   delay(1);
   
  }
  
  for (int i=0; i<timer; i++){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);                                                                              //du
   delay(1);
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);
   delay(1);
   
  }
  
  for (int i=0; i<timer; i++){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);                                                                           //ui
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);
   delay(1);
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);
   delay(0.2);
   
  }
  
  for (int i=0; i<timer; i++){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);
   delay(0.2);
   digitalWrite(pin1, B1);                                                                                 //in
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);
   delay(1);
   
  }
  
  for (int i=0; i<timer; i++){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);
   delay(1);
   digitalWrite(pin1, B1);                                                                                    //no
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);
   delay(1);
   
  }
  
  for (int i=0; i<timer; i++){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);                                                                                 //o
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);
   delay(1);
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B0);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);
   delay(1);
   
  }
  
  for (int i=0; i<timer; i++){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B0);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);
   delay(1);                                                                                              //NULL
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B0);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);
   delay(1);
   
  }
  
  
  
}

