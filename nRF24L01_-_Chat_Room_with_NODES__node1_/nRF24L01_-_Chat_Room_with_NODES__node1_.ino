
#include <nRF24L01.h>
#include <SPI.h>  
#include <RF24.h>
int led1 = 5;
int led2 = 6;
byte pipeNum = 0;
const byte pipe1 = 1;
const byte pipe2 = 2;

RF24 radio(7, 8); // CE, CSN
const uint64_t addressRxd[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL };
byte address[][6] = {"00001", "00002", "00003", "00004", "00005", "00006"};
struct package
{
  char text[200];
  int from = 0;
};
package data;

void setup() 
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
//  Serial.begin(9600);
  delay(1000);
  radio.begin();
  radio.setChannel(115);
  radio.setPALevel(RF24_PA_MIN);
  // Open up to six pipes to receive data
  radio.openReadingPipe(0, addressRxd[0]);
  radio.openReadingPipe(1, addressRxd[1]);
  radio.openReadingPipe(2, addressRxd[2]);
//  radio.openReadingPipe(3, addressRxd[3]);
//  radio.openReadingPipe(4, addressRxd[4]);
//  radio.openReadingPipe(5, addressRxd[5]);
radio.openWritingPipe(address[2]);
}


void ReadData()
{
  digitalWrite(led2, LOW);
  digitalWrite(led1, HIGH);
  radio.startListening();
//  if (radio.available())
//    {
     while (radio.available(&pipeNum))
      {
      radio.read( &data, sizeof(data) );
      delay(20);
      WriteData();
      }
//    }
}


void WriteData()
{
  
//  Serial.println(pipeNum);
  radio.stopListening();
  if (pipeNum == pipe1){
    radio.openWritingPipe(address[3]);
  }
  if (pipeNum == pipe2){
    radio.openWritingPipe(address[2]);
  }
  delay(30);
  radio.write(&data, sizeof(data));
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(1);
}


void loop()  
{
  ReadData();
}

