/*
Simple Temperature uses the lm35 in the basic centigrade temperature configuration
*/
float tempFirst;
float tempSecond;
float tempCel;
float tempFar;
float temporary;
int input = 2;
int timeDelay = 10;
int sec = 00;
int mn = 00;
int hr = 00;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  
  tempFirst = analogRead(input);
  delay(1000);
  tempSecond = analogRead(input);
  sec = sec + 1;
  
  if ( sec == 60 ){
    mn = mn + 1;
    sec = 0;
  }

  if ( mn == 60 ){
    hr = hr + 1;
    mn = 0;
  }

  if ( hr == 99 ){
    sec = 0;
    mn = 0;
    hr = 0;
  Serial.print("MAXIMUM TIME REACHED!");
  }
  
  //if ( tempFirst != tempSecond ){

  /*Serial.print("Time Passed (hh:mm:ss): ");
  Serial.print(hr);
  Serial.print(":");
  Serial.print(mn);
  Serial.print(":");
  Serial.print(sec);
  Serial.println(" ");
  Serial.println(" ");
  
  Serial.print("RAW DATA: ");
  Serial.print (tempSecond);
  Serial.println(" ");
  */
  //converts raw data into degrees celsius and prints it out
  // 5000mV/1024=.48828125
  tempCel = tempSecond * 0.48828125;
  Serial.print(millis());
  Serial.print("");
  Serial.print(tempCel);
  //Serial.println("*C ");
  
  //converts celsius into fahrenheit 
  /*temporary = tempCel *9 / 5;
  tempFar = temporary + 32;
  Serial.print("FAHRENHEIT: ");
  Serial.print(tempFar);
  Serial.println("*F");

  Serial.println(" ");
  Serial.println("====================================");
  Serial.println(" ");
  */
  //}
  
}
