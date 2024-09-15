#include <SoftwareSerial.h>
SoftwareSerial SIM900A(2,3);  //10->tx, 11->rx
void setup()
{
  SIM900A.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println ("SIM900A Ready");
  delay(100);
  Serial.println ("Type s to send message or r to receive message");
  randomSeed(analogRead(0));
  SIM900A.println("AT");
}
void loop()
{
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }
 if (SIM900A.available()>0)
   Serial.write(SIM900A.read());
}
 void SendMessage()
{
  Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(100);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"09487278245\"\r"); //Mobile phone number to send message
  delay(100);
  Serial.println ("Set SMS Content");
//  int a = random(1000,9999);
//  Serial.println(a);
  SIM900A.println("test");// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println ("Message has been sent ->SMS bjdc");
//  RecieveMessage();
}
 void RecieveMessage()
{
  Serial.println ("SIM900A Receive SMS");
  delay (1000);
  SIM900A.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  Serial.write ("Unread Message done");
 }
