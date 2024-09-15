#include <LiquidCrystal.h>
 float average = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
   
}

void LCD_1 (){
  lcd.print("Current :");
  lcd.print(average);
  lcd.print("A");
}

void loop() {


   average = ((.0264 * analogRead(A0)) -13.51);//for the 5A mode,  
// average = average + (.049 * analogRead(A0) -25);// for 20A mode
// average = average + (.742 * analogRead(A0) -37.8);// for 30A mode
   delay(1);
 Serial.print("Current :");
 Serial.print(average);
 Serial.println("A");
 LCD_1();
 delay(1000);
 lcd.clear();
}
