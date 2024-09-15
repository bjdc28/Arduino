//***********************************************//
//	        GSM/GPRS LOOP HANDLE		 //
//	This sketch is used to test seeeduino 	 //
//	GPRS_Shield's call answering and 	 //
//	reading SMS function.To make it work,	 //
//	you should insert SIM card		 //
//	to Seeeduino GPRS Shield,enjoy it!	 //
//                                               //
//	create on 2015/05/14, version: 1.0       //
//	by lawliet.zou(lawliet.zou@gmail.com)    //
//                                               //
//	This library was tested in               //
//	e-Gizmo SIM800,900D,900 modules/kits     //
//   Wiring Connection:                          //
//   SIM800/900 modules to UARTPORT/gizDuino MCUs//
//		RXD		-	TX(D3)	 //
//		TXD		-	RX(D2)	 //
//		GND		-	GND	 //
//	by e-Gizmo Mechatronix Central	     	 //
//         http://www.e-gizmo.com	         //
//***********************************************//

//INCLUDED LIBRARIES
#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

//SERIAL PIN ASSIGNMENT, BAUDRATE, MESSAGE LENGTH
#define PIN_TX    2
#define PIN_RX    3
#define BAUDRATE  9600

#define MESSAGE_LENGTH 20

char gprsBuffer[64];
int i = 0;
char *s = NULL;
int inComing = 0;

GPRS GSMTEST(PIN_TX,PIN_RX,BAUDRATE);//RX, TX, BAUDRATE

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
   if(GSMTEST.readable()) {
       inComing = 1;
   }else{ delay(100);}
   
   if(inComing){
      sim900_read_buffer(gprsBuffer,32,DEFAULT_TIMEOUT);
      //Serial.print(gprsBuffer);
      
      if(NULL != strstr(gprsBuffer,"RING")) {
          GSMTEST.answer();
      }else if(NULL != (s = strstr(gprsBuffer,"+CMTI: \"SM\""))) { //SMS: $$+CMTI: "SM",24$$
          char message[MESSAGE_LENGTH];
          int messageIndex = atoi(s+12);
          GSMTEST.readSMS(messageIndex, message,MESSAGE_LENGTH);
          Serial.print("RECV MESSAGE: ");
          Serial.println(message);
     }
     sim900_clean_buffer(gprsBuffer,32);  
     inComing = 0;
   }
}
