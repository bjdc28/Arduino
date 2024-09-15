//***********************************************//
//	        GSM/GPRS TCP CONNECTION		 //
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

//INCLUDE LIBRARIES
#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

//SERIAL PIN ASSIGNMENT, BAUDRATE
#define PIN_TX    7
#define PIN_RX    8
//MAKE SURE THAT THE BAUDRATE OF SIM800/900 IS 9600!
//YOU CAN USE THE AT COMMAND (AT+IPR=9600) TO SET IT THROUGH SERIALDEBUG
#define BAUDRATE  9600

char http_cmd[] = "GET /media/uploads/mbed_official/hello.txt HTTP/1.0\r\n\r\n";
char buffer[512];
GPRS GSMTEST(PIN_TX, PIN_RX, BAUDRATE);
void setup(){
  Serial.begin(9600);
  // USE DHCP
  while(!GSMTEST.init()) {
      delay(1000);
      Serial.print("INIT ERROR\r\n");
  }
  delay(3000);    
  // ATTEMPT DHCP
  while(!GSMTEST.join(F("CMNET"))) {
      Serial.println("GSM JOIN NETWORK ERROR");
      delay(2000);
  }

  // SUCCESSFUL DHCP
  Serial.print("IP ADDRESS IS ");
  Serial.println(GSMTEST.getIPAddress());

  if(!GSMTEST.connect(TCP,"mbed.org", 80)) {
      Serial.println("CONNECT ERROR");
  }else{
      Serial.println("CONNECT mbed.org SUCCESS");
  }

  Serial.println("WAITING TO FETCH...");
  GSMTEST.send(http_cmd, sizeof(http_cmd)-1);
  while (true) {
      int ret = GSMTEST.recv(buffer, sizeof(buffer)-1);
      if (ret <= 0){
          Serial.println("FETCH OVER...");
          break; 
      }
      buffer[ret] = '\0';
      Serial.print("RECV: ");
      Serial.print(ret);
      Serial.print(" BYTES: ");
      Serial.println(buffer);
  }
  GSMTEST.close();
  GSMTEST.disconnect();
}

void loop(){

}
