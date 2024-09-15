//https://circuitdigest.com/microcontroller-projects/chatroom-using-arduino-and-processing
#include <nRF24L01.h>
#include <SPI.h>  
#include <RF24.h>  // Manicbug LIB to be downloaded
RF24 radio (7, 8); // CE to 7 and 8 to CS
struct package
{
  char  text[20]; //Text to transmit on air
};
//byte addresses[][6] = {"0"}; 
char inData[20]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character
 int val;
typedef struct package Package;
Package data;
void setup() 
{
  Serial.begin(9600);
  delay(1000);
  //Serial.print("Setup Initialized");
  radio.begin(); 
  radio.setChannel(115);  //115 band above WIFI signals
  radio.setPALevel(RF24_PA_MIN); //MIN power low rage
  radio.setDataRate( RF24_250KBPS ) ;  //Minimum speed
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
void ReadData()
{
radio.openReadingPipe(1, 0xF0F0F0F0AA); //Which pipe to read, 40 bit Address
  radio.startListening(); //Sopt Transminting and start Reveicing 
  if ( radio.available()) 
  {
    while (radio.available())
    {
      radio.read( &data, sizeof(data) );
    }
  // Serial.print("\nReceived:");
    Serial.println(data.text);
  }
}
void WriteData()
{
  radio.stopListening(); //Stop Receiving and start transminitng 
  radio.openWritingPipe(0xF0F0F0F066);//Sends data on this 40-bit address
  radio.write(&data, sizeof(data)); 
    //Serial.print("\nSent:");
    //Serial.println(data.msg);
  delay(300);
}
