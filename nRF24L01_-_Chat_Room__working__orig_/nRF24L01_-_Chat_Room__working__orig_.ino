//https://circuitdigest.com/microcontroller-projects/chatroom-using-arduino-and-processing

#include <nRF24L01.h>
#include <SPI.h>  
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
byte address[][6] = {"1Node", "2Node"};
char inData[200];                            //maximum character
char inChar;
byte index = 0;
int val;

struct package
{
  char text[200];
};
package data;



void setup() 
{
  Serial.begin(9600);
  delay(1000);                               //for stabilization of RF Module
  Serial.print("Setup Initialized");
  radio.begin();                             //\start RF
  radio.setChannel(115);                     //Channel range = 0-124, Recommended Channel = 100 - 124 (for not interfering w/ WiFi)
  radio.setPALevel(RF24_PA_MIN);             //Set Power level, can be of these (RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX)
  radio.openReadingPipe(1, address[1]);      //Change to address[1] for the other device
  radio.openWritingPipe(address[0]);         //Change to address[0] for the other device
}


void ReadData()                              //for reading DATA
{
  radio.startListening();                    //Enable listening
  if ( radio.available())                    //Checking for radio availability
  {
    while (radio.available())
    {
      radio.read( &data, sizeof(data) );
    }
    Serial.print("\nReceived:");
    Serial.println(data.text);               //print received DATA
  }
}


void WriteData()                             //for writing DATA
{
  radio.stopListening();                     //must stop listening before writing
  radio.write(&data, sizeof(data));          //sends DATA
    Serial.print("\nMy Data: ");
    Serial.println(data.text);               //prints the content
  delay(1);
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
      inData[index] = '\0';
      }
     if (val=='.')
      { 
      strcpy( data.text, inData);
      WriteData();
      while (index!=0)
        {
        inData[index] = ' ';
        index--;
        }
      }
  }
  ReadData();
}

