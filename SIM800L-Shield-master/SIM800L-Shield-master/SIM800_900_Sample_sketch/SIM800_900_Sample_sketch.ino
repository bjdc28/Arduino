/*
  GSM Send Sketch for Arduino
  
  Initializes GSM Module and sends an SMS to recipient
  
  The circuit:
  *Arduino pin 0 (RX) - GSM Module (TX)
  *Arduino pin 1 (TX) - GSM Module (RX)
  
  Created 2010
  by Meann Zabanal
  Modified 
  by John for GSM Shield testing
  Modified August 20, 2015
  by Amoree for GSM Shield testing Serial Monitor
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

char Rx_data[150];
unsigned char Rx_index = 0;
int i = 0;
char msg[160];
int sig;

#define DEBUG true
void setup()  
{
  Serial.begin(9600);
  mySerial.begin(19200);
  
  init_GSM();
  send_msg("222", "BAL");  
}

void loop()
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}

void send_msg(char *number, char *msg)
{
  char at_cmgs_cmd[30] = {'\0'};
  char msg1[160] = {'\0'};
  char ctl_z = 0x1A;

  sprintf(msg1, "%s%c", msg, ctl_z);
  sprintf(at_cmgs_cmd, "AT+CMGS=\"%s\"\r\n",number);
  
  sendGSM(at_cmgs_cmd);
  delay(100);
  delay(100);
  delay(100);
  sendGSM(msg1);
  delay(100);
}

void sendGSM(char *string){
  mySerial.write(string);
  delay(90);
}

void clearString(char *strArray) {
  int j;
  for (j = 100; j > 0; j--)
    strArray[j] = 0x00;
}

void send_cmd(char *at_cmd, char clr){
  char *stat = '\0';
  while(!stat){
    sendGSM(at_cmd);
    delay(200);
    readSerialString(Rx_data);
    Serial.write(Rx_data);
    
    stat = strstr(Rx_data, "OK");
    Serial.println("Success");
    delay(50000);
  }
  if (clr){
    clearString(Rx_data);
    delay(200);
    stat = '\0';
  }
}

void init_GSM(){
  
 
  sendData("AT\r\n",1000,DEBUG); // AT

  sendData("AT+CMGF=1\r\n",1000,DEBUG); //AT+CMGF=1
  sendData("AT+CMGD=1\r\n",1000,DEBUG); //AT+CMGD=1

  delay(1000);
  delay(1000);
  delay(1000);
}

void readSerialString (char *strArray) {
  
  if(!mySerial.available()) {
    return;
  }
  
  while(mySerial.available()) {
    strArray[i] = mySerial.read();
    i++;
  }
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    mySerial.print(command); 
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(mySerial.available())
      {
        
   
        char c = mySerial.read();
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}




