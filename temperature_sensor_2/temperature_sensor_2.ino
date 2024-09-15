/*
Simple Temperature uses the lm35 in the basic centigrade temperature configuration
*/
float tempFirst;
float tempSecond;
float tempCel;
float tempFar;
float temporary;
int input = 2;
int pin1 = 2;
int pin2 = 3;
int pin3 = 4;
int pin4 = 5;
int pin5 = 6;
int pin6 = 7;
int pin7 = 8;
int gnd1 = 11;
int gnd2 = 9;
int timer = 500;
int i = 0;
short ones, tens, hundreds;

void setup()
{
  Serial.begin(9600);
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




void tens_0(){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);
}
void tens_1(){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);

}
void tens_2(){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B0);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);

}
void tens_3(){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);

}
void tens_4(){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);

}
void tens_5(){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);

}
void tens_6(){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);

}
void tens_7(){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);

}
void tens_8(){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);

}
void tens_9(){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B0);
   digitalWrite(gnd2, B1);

}


void ones_0(){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);
}
void ones_1(){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);

}
void ones_2(){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B0);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);

}
void ones_3(){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);

}
void ones_4(){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B0);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);

}
void ones_5(){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);

}
void ones_6(){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B0);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);

}
void ones_7(){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B0);
   digitalWrite(pin5, B0);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);

}
void ones_8(){
   digitalWrite(pin1, B1);
   digitalWrite(pin2, B1);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);

}
void ones_9(){
   digitalWrite(pin1, B0);
   digitalWrite(pin2, B0);
   digitalWrite(pin3, B1);
   digitalWrite(pin4, B1);
   digitalWrite(pin5, B1);
   digitalWrite(pin6, B1);
   digitalWrite(pin7, B1);
   digitalWrite(gnd1, B1);
   digitalWrite(gnd2, B0);

}

void loop()
{
  
  delay(1);
  tempSecond = analogRead(input);
  
  Serial.print("RAW DATA: ");
  Serial.print (tempSecond);
  Serial.println(" ");
  
  //converts raw data into degrees celsius and prints it out
  // 5000mV/1024=.48828125
  tempCel = tempSecond * 0.48828125;
  Serial.print("CELSIUS: ");
  Serial.print(tempCel);
  Serial.println("*C ");
  
  //converts celsius into fahrenheit 
  temporary = tempCel *9 / 5;
  tempFar = temporary + 32;
  Serial.print("FAHRENHEIT: ");
  Serial.print(tempFar);
  Serial.println("*F");

  Serial.println(" ");
  Serial.println("====================================");
  Serial.println(" ");

  //}
/*
hundreds = int(tempCel/100);
hundreds = hundreds-(int(hundreds/10)*10);
*/
Serial.println(tempCel);
  tens = int(tempCel/10);
  tens = tens-(int(tens/10)*10);

  ones = tempCel-(int(tempCel/10)*10);
Serial.println(tens);
Serial.println(ones);
  for (int i=0; i<timer; i++){
    if (tens == 0){
      tens_0();
    }
    if (tens == 1){
      tens_1();
    }
    if (tens == 2){
      tens_2();
    }
    if (tens == 3){
      tens_3();
    }
    if (tens == 4){
      tens_4();
    }
    if (tens == 5){
      tens_5();
    }
    if (tens == 6){
      tens_6();
    }
    if (tens == 7){
      tens_7();
    }
    if (tens == 8){
      tens_8();
    }
    if (tens == 9){
      tens_9();
    }
delay(1);
    if (ones == 0){
      ones_0();
    }
    if (ones == 1){
      ones_1();
    }
    if (ones == 2){
      ones_2();
    }
    if (ones == 3){
      ones_3();
    }
    if (ones == 4){
      ones_4();
    }
    if (ones == 5){
      ones_5();
    }
    if (ones == 6){
      ones_6();
    }
    if (ones == 7){
      ones_7();
    }
    if (ones == 8){
      ones_8();
    }
    if (ones == 9){
      ones_9();
    }
delay(1);
  }
  
}
