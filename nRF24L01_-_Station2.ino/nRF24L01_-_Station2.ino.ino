#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>  
#include <RF24.h>
#include <RF24Network.h>
#define I2C_ADDR 0x27 // Define I2C Address for controller
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#define BACKLIGHT 3

double reading_spvol = 0;
double reading_batvol = 0;
double reading_spcur = 0;
double initial_spvol = 0;
double initial_batvol = 0;
double initial_spcur = 0;
int samples = 0;
int charge = 5;
double SPVol;
double BatVol;
double SPCur;
int relay_solar = 2;
int relay_battery = 3;
int relay_load = 4;
unsigned long lastMillis = 0;
unsigned long lastMillis1 = 0;
unsigned long lastMillis2 = 0;
const long interval = 1000;
const long interval1 = 1000;
const long interval2 = 50;

unsigned long lastMicros_ON = 0;
const long intervalMicros_ON = 500;

unsigned long lastMicros_OFF = 0;
const long intervalMicros_OFF = 150;

boolean toggle = false;

const uint16_t station_2= 0121;
const uint16_t controller = 02;
//const uint16_t station_2= 01;
//const uint16_t controller = 00;



LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

RF24 radio (7, 8);                           // CE to 7 and CSN to 8
RF24Network network(radio);


struct payload_2 {
  double spv2;
  double btv2;
  double spc2;
  double timer;
};
payload_2 data2;


struct payload_4 {
  int Rs2;
  int Rb2;
  int Rl2;
};
payload_4 control2;


void setup() 
{
//  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(/*channel*/ 90, /*node address*/ station_2);
  pinMode(relay_solar, OUTPUT);
  pinMode(relay_battery, OUTPUT);
  pinMode(relay_load, OUTPUT);
  pinMode(charge, OUTPUT);
  lcd.begin (20,4);
  lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(HIGH);
  digitalWrite(charge,HIGH);
}


void Timer(){
  data2.timer = random(0, 99);
}


void Charge_ON(){
  if (toggle){
    digitalWrite(charge, HIGH);
    if (micros() - lastMicros_ON >= intervalMicros_ON){
      lastMicros_ON = micros();
      toggle = false;
    }
  }
  if (!toggle){
    digitalWrite(charge, LOW);
    if (micros() - lastMicros_OFF >= intervalMicros_OFF){
      lastMicros_OFF = micros();
      toggle = true;
    }
  }
}


void Charge_OFF(){
  digitalWrite(charge, LOW);
}


void RelayControl(){
  if (control2.Rs2 == 1){
    digitalWrite( relay_solar, HIGH );
  }
  if (control2.Rs2 == 2){
    digitalWrite( relay_solar, LOW );
  }
  if (control2.Rb2 == 1){
    digitalWrite( relay_battery, HIGH );
  }
  if (control2.Rb2 == 2){
    digitalWrite( relay_battery, LOW );
  }
  if (control2.Rl2 == 1){
    digitalWrite( relay_load, HIGH );
  }
  if (control2.Rl2 == 2){
    digitalWrite( relay_load, LOW );
  }
}


void RFreceive()
{
  while (network.available()){
    RF24NetworkHeader header;
    network.peek(header);
    if(header.type == 'T'){
      network.read(header,&control2,sizeof(control2));
    }
  }
}


void RFsend()
{
  readInput();
  
  if (millis() - lastMillis >= interval) {
    lastMillis = millis();
    Timer();
    RF24NetworkHeader header(controller, 'T');
    boolean sent = network.write(header,&data2,sizeof(data2));
//    if (sent){
//      Serial.println("ok");
//    }
//    else{
//      Serial.println("failed");
//    }
  }
}


void LcdReading()
{
  if (millis() - lastMillis1 >= interval1) {
    lastMillis1 = millis();
    lcd.clear();
    lcd.home();
    lcd.setCursor(2,0);
    lcd.print("***Station 2***");
    lcd.setCursor(0,1);
    lcd.print("SP Volts: ");
    lcd.setCursor(13,1);
    lcd.print(data2.spv2);
    lcd.setCursor(0,2);
    lcd.print("SP Amps: ");
    lcd.setCursor(13,2);
    lcd.print(data2.spc2);
    lcd.setCursor(0,3);
    lcd.print("Bat.Volts: ");
    lcd.setCursor(13,3);
    lcd.print(data2.btv2);
  }
}


void ChargeCont()
{
  if (SPVol > BatVol){
    if (BatVol <= 28.0){
      Charge_ON();
    }
    if (BatVol > 28.0){
      Charge_OFF();
    }
  }
  if (BatVol >= SPVol){
      Charge_OFF();
  }
}



void readInput() {
  //change this to time interval alterations
  //optimize the sensor reading by averaging voltage and soldering capacitor on filter pins
  if (millis() - lastMillis2 >= interval2){
    lastMillis2 = millis();
    
    reading_spvol = ((analogRead(A0)/1023.0)*80.00);
    reading_batvol = ((analogRead(A1)/1023.0)*80.00);
    reading_spcur = (((511 - analogRead(A2))/1023.0)*50.0);
    
    initial_spvol += reading_spvol;
    initial_batvol += reading_batvol;
    initial_spcur += reading_spcur;
    samples++;

    if (samples >=20){
      data2.spv2 = (initial_spvol/20);
      data2.btv2 = (initial_batvol/20);
      if ((initial_spcur/20) < 0){
        data2.spc2 = 0;
      }
      if ((initial_spcur/20) >= 0){
        data2.spc2 = (initial_spcur/20);
      }
      
      
      SPVol = data2.spv2;
      BatVol = data2.btv2;
      SPCur = data2.spc2;
      
      samples = 0;
      initial_spvol = 0;
      initial_batvol = 0;
      initial_spcur = 0;
    }
  }
}


//void readInput1() {
//  data2.spv2 = random(10, 39);
//  data2.btv2 = random(20, 28);
//  data2.spc2 = random(1, 10);
//  
//  SPVol = data2.spv2;
//  BatVol = data2.btv2;
//  SPCur = data2.spc2;
//}


void loop()  
{
  network.update();
  RFreceive();
  RFsend();
  LcdReading();
  RelayControl();
  ChargeCont();
}
