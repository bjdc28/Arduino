#include <SoftwareSerial.h>
SoftwareSerial SIM800 (2,3);  //2->tx, 3->rx

char incomingChar;

void setup(){
  SIM800.begin(19200);
  Serial.begin(9600);
//  Serial.begin(19200);
  delay(8000);
  SIM800.print("AT+CMGF=1\r");
  delay(100);
  SendMessage();
  delay(100);
  SIM800.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}



void sim(){
  if(SIM800.available() >0) {
    incomingChar=SIM800.read();
    Serial.println(incomingChar);
    if(incomingChar=='a') {
      delay(10);
      SendMessageA();
    }
    if(incomingChar=='b') {
      delay(10);
      SendMessageB();
    }
    if(incomingChar=='?') {
      delay(10);
      SendMessageQ();
    }
  }
}


void SendMessageM(){
  SIM800.println("AT+CMGS=\"09487278245\"");
  delay(100);
  SIM800.println("test_multiple");
  delay(100);
  SIM800.println((char)26);// ASCII code of CTRL+Z
  delay(100);
  SIM800.println();
  delay(5000);
}


void SendMessageQ(){
  SIM800.println("AT+CMGS=\"09487278245\"");
  delay(100);
  SIM800.println("test_Q");
  delay(100);
  SIM800.println((char)26);// ASCII code of CTRL+Z
  delay(100);
  SIM800.println();
  delay(5000);
}


 void SendMessage(){
  SIM800.println("AT+CMGS=\"09487278245\"");
  delay(100);
  SIM800.println("test");
  delay(100);
  SIM800.println((char)26);// ASCII code of CTRL+Z
  delay(100);
  SIM800.println();
  delay(5000);
}



 void SendMessageA(){
  SIM800.println("AT+CMGS=\"09487278245\"");
  delay(100);
  SIM800.println("test_1");
  delay(100);
  SIM800.println((char)26);// ASCII code of CTRL+Z
  delay(100);
  SIM800.println();
  delay(5000);
}


void SendMessageB(){
  SIM800.println("AT+CMGS=\"09487278245\"");
  delay(100);
  SIM800.println("test_2");
  delay(100);
  SIM800.println((char)26);// ASCII code of CTRL+Z
  delay(100);
  SIM800.println();
  delay(5000);
}


 void loop(){
  sim();
}
