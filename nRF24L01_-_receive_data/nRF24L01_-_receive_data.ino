//https://circuitdigest.com/microcontroller-projects/chatroom-using-arduino-and-processing

#include <nRF24L01.h>
#include <SPI.h>  
#include <RF24.h>

RF24 radio (7, 8);                           // CE to 7 and CSN to 8
byte address[][6] = {"00001", "00002"};

struct package
{
  double reading1;
  double reading2;
};
package data;

struct Control
{
  int cont = 0;
};
Control control;


void setup() 
{
  Serial.begin(9600);
  delay(1000);                               //for stabilization of RF Module
//  Serial.print("Setup Initialized");
  radio.begin();                             //start RF
  radio.setChannel(115);                     //Channel range = 0-124, Recommended Channel = 100 - 124 (for not interfering w/ WiFi)
  radio.setPALevel(RF24_PA_MIN);             //Set Power level, can be of these (RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX)
  radio.openReadingPipe(1, address[1]);      //Change to address[1] for the other device
  radio.openWritingPipe(address[0]);         //Change to address[0] for the other device
}

void readSerial(){
  while (Serial.available()>0){
    control.cont = (Serial.read() - 48);
    delay(1);
    WriteData();
  }
}


void ReadData()                              //for reading DATA
{
  radio.startListening();                    //Enable listening
    while (radio.available())
    {
      radio.read( &data, sizeof(data) );
    }
//    Serial.print("\nReceived Data: ");
}

void WriteData()
{
  radio.stopListening();
  radio.write(&control, sizeof(control));
  delay(1);
}


void loop()  
{
  readSerial();
  ReadData();
  Serial.print(data.reading1);
  Serial.print(",");
  Serial.println(data.reading2);
  delay(50);
}

