//***********************************************//
//                 GPRS SMS Read                 //
//    This sketch is used to test seeeduino      //
//    GPRS_Shield's reading SMS function.To make //
//    it work, you should insert SIM card        //
//    to Seeeduino GPRS Shield,enjoy it!         //
//                                               //
//    There are two methods to read SMS:         //
//    1. GPRS_LoopHandle.ino  -> in order to     //
//       recieve "+CMTI: "SM""                   //
//       may be you need to send this command    //
//       to your shield: "AT+CNMI=2,2,0,0,0"     //
//    2. GPRS_SMSread.ino -> you have to check   //
//       if there are any UNREAD sms, and you    //
//       don't need to check serial data         //
//       continuosly                             //
//                                               //
//     create on 2015/05/14, version: 1.0        //
//     by op2op2op2(op2op2op2@hotmail.com)       //
//                                               //
//	This library was tested in               //
//	e-Gizmo SIM800,900D,900 modules/kits     //
//   Wiring Connection:                          //
//   SIM800/900 modules to UARTPORT/gizDuino MCUs//
//		RXD	-	TX(D3)           //
//		TXD	-	RX(D2)           //
//		GND	-	GND              //
//	by e-Gizmo Mechatronix Central           //
//          http://www.egizmo.com                //
//***********************************************//

//INCLUDE LIBRARIES
#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

//SERIAL PIN ASSIGNMENT, BAUDRATE, MESSAGE LENGTH
#define PIN_TX    2
#define PIN_RX    3
#define BAUDRATE  9600

#define MESSAGE_LENGTH 160
char message[MESSAGE_LENGTH];
int messageIndex = 0;

char phone[16];
char datetime[24];

GPRS GSMTEST(PIN_TX,PIN_RX,BAUDRATE);//RX,TX,PWR,BAUDRATE

void setup() {
  Serial.begin(9600);
  while(!GSMTEST.init()) {
      Serial.print("INIT ERROR\r\n");
      delay(1000);
  }
  delay(3000);  
  Serial.println("INITIALIZE SUCCESS!..");
  Serial.println("PLEASE CALL OR SEND SMS MESSAGE TO ME!");
}

void loop() {
   messageIndex = GSMTEST.isSMSunread();
   if (messageIndex > 0) { //AT LEAST, THERE IS ONE UNREAD SMS
      GSMTEST.readSMS(messageIndex, message, MESSAGE_LENGTH, phone, datetime);           
      //IN ORDER NOT TO FULL SIM MEMORY, IS BETTER TO DELETE IT
      GSMTEST.deleteSMS(messageIndex);
      Serial.print("FROM NUMBER: ");
      Serial.println(phone);  
      Serial.print("DATETIME: ");
      Serial.println(datetime);        
      Serial.print("RECEIVED MESSAGE: ");
      Serial.println(message);    
   }
}
