#include <nRF24L01.h>
#include <SPI.h>  
#include <RF24.h>

RF24 radio (9, 53);                           // CE to 7 and CS to 8
byte address[][6] = {"00001", "00002"};
int dataHandler;

struct package
{
  int relay;
};
package data;

struct message
{
  int msg;
};
message MSG;


void setup() 
{
  Serial.begin(9600);
  delay(1000);
  Serial.println("Input Number Codes.");
  Serial.println("1 = Relay 1 ON");
  Serial.println("2 = Relay 1 OFF");
  Serial.println("3 = Relay 2 ON");
  Serial.println("4 = Relay 2 OFF");
  Serial.println("Waiting...");
  radio.begin();
  radio.setChannel(115);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, address[0]);
  radio.openWritingPipe(address[1]);
}



void codeMsg(int msg_val)
{
  if(msg_val == 1){
    Serial.println("Relay 1: ON");
    Serial.println("");
  }
  
  if(msg_val == 2){
    Serial.println("Relay 1: OFF");
    Serial.println("");
  }
  
  if(msg_val == 3){
    Serial.println("Relay 2: ON");
    Serial.println("");
  }
  
  if(msg_val == 4){
    Serial.println("Relay 2: OFF");
    Serial.println("");
  }
}


void ReadData()
{
  radio.startListening();
    while (radio.available())
    {
      radio.read( &MSG, sizeof(MSG) );
      codeMsg(MSG.msg);
    }
  }


void WriteData()
{
  radio.stopListening();
  radio.write(&data, sizeof(data));
  delay(1);
}


void loop()  
{
  while(Serial.available()>0)
  { 
      dataHandler = (Serial.read() - 48);
      data.relay = dataHandler;
      WriteData();
      Serial.print("User Input: ");
      Serial.println(dataHandler);
  }
  ReadData();
}

