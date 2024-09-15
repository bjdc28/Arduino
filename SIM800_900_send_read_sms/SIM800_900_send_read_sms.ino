//***********************************************//
//        GSM/GPRS SEND AND READ SMS             //
//                                               //
//	This sketch is used to test              //
//	e-Gizmo SIM800,800L,900D,900 modules/kits  //
//  Wiring Connection:                           //
//  SIM800/900 modules to UARTPORT/gizDuino MCUs //
//		RXD	-	TX(D3)           //
//		TXD	-	RX(D2)           //
//		GND	-	GND              //
//	by e-Gizmo Mechatronix Central           //
//          http://www.egizmo.com                //
//***********************************************//

//INCLUDED LIBRARIES
#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

//SERIAL PIN ASSIGNMENT, BAUDRATE, PHONE NUMBER, MESSAGE
#define PIN_TX    7
#define PIN_RX    8
#define BAUDRATE  9600
#define PHONE_NUMBER "+639487278245"       //CELLPHONE NUMBER
#define MESSAGE  "YOUR_MESSAGE_HERE"  //COMPOSE YOUR MESSAGE HERE
#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH];
int messageIndex = 0;

char phone[16];
char datetime[24];

GPRS GSMTEST(PIN_TX,PIN_RX,BAUDRATE);//RX,TX,BAUDRATE

void setup() {
  Serial.begin(9600);
  while(!GSMTEST.init()) {
      delay(1000);
      Serial.print("INIT ERROR\r\n");
  }  
  Serial.println("GSM INIT SUCCESS");
  Serial.println("START TO SEND MESSAGE ...");
  Serial.print("..");
  delay(1000);
  Serial.println(".....");
  delay(1000);
  
  GSMTEST.sendSMS(PHONE_NUMBER,MESSAGE); //DEFINE PHONE NUMBER AND TEXT
}

void loop() {
   //READ THE INCOMING SMS MESSAGE
   Serial.println("   ");
   Serial.println("   ");
   messageIndex = GSMTEST.isSMSunread();
   if (messageIndex > 0) { //AT LEAST, THERE IS ONE UNREAD SMS
      GSMTEST.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);           
      //IN ORDER NOT TO FUL SIM Memory, IS BETTER TO DELETE IT
      GSMTEST.deleteSMS(messageIndex);
      Serial.print("FROM NUMBER: ");
      Serial.println(phone);  
      Serial.print("DATE/TIME");
      Serial.println(datetime);        
      Serial.print("RECEIVED MESSAGE: ");
      Serial.println(message); 
}
}
