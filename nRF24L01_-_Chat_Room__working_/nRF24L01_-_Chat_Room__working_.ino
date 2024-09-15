//https://circuitdigest.com/microcontroller-projects/chatroom-using-arduino-and-processing
#include <nRF24L01.h>
#include <SPI.h>  
#include <RF24.h>

RF24 radio (7, 8); // CE to 7 and 8 to CS
byte address[][6] = {"00001", "00002"};
char inData[200];
char inChar;
byte index = 0;
int val;

struct package
{
  char  text[200];
};
package data;


void setup() 
{
  Serial.begin(9600);
  delay(1000);
  Serial.print("Setup Initialized");
  radio.begin(); 
  //
  radio.setChannel(115);
  //
  radio.setPALevel(RF24_PA_MIN);
  
  radio.openReadingPipe(1, address[0]); //Change to address[1] for the other device
  
  radio.openWritingPipe(address[1]);    //Change to address[0] for the other device
}


void ReadData()
{
  radio.startListening();
  if ( radio.available()) 
  {
    while (radio.available())
    {
      radio.read( &data, sizeof(data) );
    }
    Serial.print("\nReceived:");
    Serial.println(data.text);
  }
}


void WriteData()
{
  radio.stopListening();
  radio.write(&data, sizeof(data)); 
    Serial.print("\nSent:");
    Serial.println(data.text);
  delay(300);
}


void loop()  
{
  while(Serial.available()>0)
  { 
    val = Serial.peek();
    if(index < 199)
      {
      inChar = Serial.read();
      inData[index] = inChar;
      index++;
    }
  
  
  
     if (val=='.') inData[index] = '\0';
     
//      { 
      strcpy(data.text, inData);
      WriteData();
      while (index>=0)
        {
        inData[index] = ' ';
        index--;
        }
      
}
  ReadData();
}

