//https://circuitdigest.com/microcontroller-projects/chatroom-using-arduino-and-processing

#include <nRF24L01.h>
#include <SPI.h>  
#include <RF24.h>
int pwm = 7;
double a;
double b;
RF24 radio (9, 53);                           // CE to 7 and CSN to 8
byte address[][6] = {"00001", "00002"};

struct package
{
  double reading1;
  double reading2;
};
package data;


void setup() 
{
  pinMode(pwm, OUTPUT);
//  Serial.begin(9600);
  delay(1000);                               //for stabilization of RF Module
//  Serial.print("Setup Initialized");
  radio.begin();                             //start RF
  radio.setChannel(115);                     //Channel range = 0-124, Recommended Channel = 100 - 124 (for not interfering w/ WiFi)
  radio.setPALevel(RF24_PA_MIN);             //Set Power level, can be of these (RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX)
  radio.openReadingPipe(1, address[0]);      //Change to address[1] for the other device
  radio.openWritingPipe(address[1]);         //Change to address[0] for the other device
}





void WriteData()                             //for writing DATA
{
  radio.stopListening();                     //must stop listening before writing
  radio.write(&data, sizeof(data));          //sends DATA
//  Serial.println(data.reading);            //prints the content
}


void loop()  
{
  a = ((analogRead(A0)/1023.0)*39.88);
  data.reading1 = a;
  b = ((analogRead(A1)/1023.0)*38.63);
  data.reading2 = b;
  WriteData();
  if (a > 28.0){
    if (b <= 28.0){
      analogWrite(pwm, 255);
    }
    if (b > 28.0){
      analogWrite(pwm, 0);
    }
  }
  if (a <= 28.0){
    analogWrite(pwm, 0);
  }
//  Serial.print(a);
//  Serial.print(",");
//  Serial.println(b);
  delay(250);
}

