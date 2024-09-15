
#include <nRF24L01.h>
#include <SPI.h>  
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
//const uint64_t addressRxd[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };
byte address[][6] = {"1Node, 2Node, 3Node, 4Node, 5Node, 6Node, 7Node"};
char inData[200];
char inChar;
byte index = 0;
int val;

struct package
{
  char text[200];
  int from = 1;
};
package data;

struct package1
{
  
};
package1 



void setup() 
{
  Serial.begin(9600);
  delay(1000);
  Serial.print("Setup Initialized");
  radio.begin();
  radio.setChannel(115);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, address[2]);      
  radio.openWritingPipe(addressRxd[1]);
  delay(250);
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
    Serial.print(data.text);
    Serial.print(", ");
    Serial.println(data.from);
  }
}


void WriteData()
{
  radio.stopListening();
  data.from = 1;
  radio.write(&data, sizeof(data));
    Serial.print("\nMy Data: ");
    Serial.println(data.text);
  delay(10);
  radio.openReadingPipe(1, address[2]);
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

