#include <nRF24L01.h>
#include <SPI.h>  
#include <RF24.h>

RF24 radio (7, 8);                           // CE to 7 and CS to 8
byte address[][6] = {"00001", "00002"};


struct package
{
  int relay = 0;
};
package data;

struct message
{
  int msg;
};
message MSG;



void setup() 
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Waiting for Instructions:");
  radio.begin();
  radio.setChannel(115);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, address[1]);
  radio.openWritingPipe(address[0]);
}


void relayControl()
{
  if (data.relay == 1){
    digitalWrite(2, LOW);
    MSG.msg = 1;
    delay(50);
    WriteMsg();
  }
  if (data.relay == 2){
    digitalWrite(2, HIGH);
    MSG.msg = 2;
    delay(50);
    WriteMsg();
  }
  if (data.relay == 3){
    digitalWrite(3, LOW);
    MSG.msg = 3;
    delay(50);
    WriteMsg();
  }
  if (data.relay == 4){
    digitalWrite(3, HIGH);
    MSG.msg = 4;
    delay(50);
    WriteMsg();
  }
}


void WriteMsg()
{
  radio.stopListening();
  radio.write(&MSG, sizeof(MSG));
    Serial.print("\nResponse Sent: ");
    Serial.println(MSG.msg);
  delay(50);
}


void ReadData()
{
  radio.startListening();
  while (radio.available())
    {
      radio.read(&data, sizeof(data));
      relayControl();
  }
}


void loop()  
{
 ReadData();
}

