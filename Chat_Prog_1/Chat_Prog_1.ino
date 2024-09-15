//https://circuitdigest.com/microcontroller-projects/chatroom-using-arduino-and-processing

#include <SPI.h>  
#include "RF24.h"  // Manicbug LIB to be downloaded
RF24 myRadio (8, 10); // CE to 8 and 10 to CS
struct package
{
  char  text[20]; //Text to transmit on air
};
typedef struct package Package;
Package data;
char inData[20]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character
 int val;
void setup()
{
  Serial.begin(9600);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(115);  //115 band above WIFI signals
  myRadio.setPALevel(RF24_PA_MIN); //MIN power low rage
  myRadio.setDataRate( RF24_250KBPS ) ; //Minimum speed
  //Serial.print("Setup Initialized");
}
void loop()
{
  while(Serial.available()>0) //Get values from user
  { 
    val = Serial.peek();
    if(index < 19) // One less than the size of the array
      {
          inChar = Serial.read(); // Read a character
          inData[index] = inChar; // Store it
          index++; // Increment where to write next
          inData[index] = '\0'; // Null terminate the string
      }
     if (val=='#')
      { 
       strcpy( data.text, inData);
        WriteData(); //Put module in Transmit mode
   while (index!=0)
      {
      inData[index] = ' ';
      index--;
      }
      }
  }
 ReadData(); //Put module Receive mode
}
void WriteData()
{
  myRadio.stopListening(); //Stop Receiving and start transminitng 
  myRadio.openWritingPipe( 0xF0F0F0F0AA);  //Sends data on this 40-bit address
  myRadio.write(&data, sizeof(data)); 
//Serial.print("\nSent:");
//Serial.println(data.text);
  delay(300);
}
void ReadData()
{ 
myRadio.openReadingPipe(1, 0xF0F0F0F066); // Which pipe to read, 40 bit Address
  myRadio.startListening();  //Stop Transminting and start Reveicing 
  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }
    //Serial.print("\nReceived:");
    Serial.println(data.text);
  }
}
