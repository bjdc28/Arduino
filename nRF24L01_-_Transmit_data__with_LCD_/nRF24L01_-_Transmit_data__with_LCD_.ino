#include <LiquidCrystal.h>
#include <nRF24L01.h>
#include <SPI.h>  
#include <RF24.h>
int pwm = 7;
double a;
double b;
int relay_solar = 46;
int relay_battery = 47;
byte address[][6] = {"00001", "00002"};

LiquidCrystal lcd (12,11,5,4,3,2);

RF24 radio (9, 53);                           // CE to 7 and CSN to 8


struct package
{
  double reading1;
  double reading2;
};
package data;

struct Control
{
  int cont;
};
Control control;


void setup() 
{
  pinMode(relay_solar, OUTPUT);
  pinMode(relay_battery, OUTPUT);
  pinMode(pwm, OUTPUT); 
  digitalWrite(relay_solar, HIGH);
  digitalWrite(relay_battery, HIGH);
  lcd.begin (16,2);
//  Serial.begin(9600);
  delay(1000);                               //for stabilization of RF Module
//  Serial.print("Setup Initialized");
  radio.begin();                             //start RF
  radio.setChannel(115);                     //Channel range = 0-124, Recommended Channel = 100 - 124 (for not interfering w/ WiFi)
  radio.setPALevel(RF24_PA_HIGH);             //Set Power level, can be of these (RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX)
  radio.openReadingPipe(1, address[0]);      //Change to address[1] for the other device
  radio.openWritingPipe(address[1]);         //Change to address[0] for the other device
}


void WriteData()                             //for writing DATA
{
  radio.stopListening();                     //must stop listening before writing
  radio.write(&data, sizeof(data));          //sends DATA
//  Serial.println(data.reading);            //prints the content
}

void ReadData()
{
  radio.startListening();
  while (radio.available())
  {
      radio.read(&control, sizeof(control));
      relay();
  }
}

void readInput() {
  a = ((analogRead(A0)/1023.0)*38.69852);
  data.reading1 = a;
  b = ((analogRead(A1)/1023.0)*37.69635);
  data.reading2 = b;
  delay(46);
}

void readInput1() {
  data.reading1 = ((analogRead(A0)/1023.0)*38.69852);
  data.reading1 = a;
  b = random(20, 29);
  data.reading2 = b;
//  delay(47);
}

void relay(){
  switch (control.cont){
    case 1:
      digitalWrite(relay_solar, LOW);
      break;
      
    case 2:
      digitalWrite(relay_solar, HIGH);
      break;
      
    case 3:
      digitalWrite(relay_battery, LOW);
      break;

    case 4:
      digitalWrite(relay_battery, HIGH);
      break;
  }
}

void loop()  
{
  ReadData();
  readInput();
  WriteData();

  lcd.setCursor(0,0);
  lcd.print("S.Panel: ");
  lcd.setCursor(9,0);
  lcd.print(a);
  lcd.setCursor(0,1);
  lcd.print("Battery: ");
  lcd.setCursor(9,1);
  lcd.print(b);
  if (a > b){
    if (b <= 28.0){
      analogWrite(pwm, 110);
    }
    if (b > 28.0){
      analogWrite(pwm, 0);
    }
  }
  if (b >= a){
    analogWrite(pwm, 0);
  }
//  Serial.print(a);
//  Serial.print(",");
//  Serial.println(b);
  delay(1);
}

