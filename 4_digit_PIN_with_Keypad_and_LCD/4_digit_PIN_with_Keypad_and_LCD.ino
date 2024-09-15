#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27 //Input LCD Address here
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
#define BACKLIGHT 3

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

#include <Keypad.h>

const int ROW_NUM    = 4; // four rows
const int COLUMN_NUM = 4; // four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6};      // connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

int cursorColumn = 0;
int pin = 1234;
int pinTemp = 0;

void setup(){
//  lcd.init(); // initialize the lcd
  lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Enter PIN:");
}

void loop(){
  char key = keypad.getKey();

  if ((key - 48 >= 0) && (key - 48 <= 9)) {
    lcd.setCursor(cursorColumn, 1); // move cursor to   (cursorColumn, 0)
    lcd.print(key);                 // print key at (cursorColumn, 0)

    if (cursorColumn == 0){
      pinTemp = ((key - 48) * 1000);
    }
    if (cursorColumn == 1){
      pinTemp = pinTemp + ((key - 48) * 100);
    }
    if (cursorColumn == 2){
      pinTemp = pinTemp + ((key - 48) * 10);
    }
    if (cursorColumn == 3){
      pinTemp = pinTemp + (key - 48);
    }
    
    cursorColumn++;                 // move cursor to next position
    if (cursorColumn == 5) {        // if reaching limit, clear LCD
      lcd.clear();
      cursorColumn = 0;
      pinTemp = 0;
      lcd.setCursor(0, 0);
      lcd.print("Enter PIN:");
    }
  }
  if (key == 'A'){
    lcd.clear();
    cursorColumn = 0;
    lcd.setCursor(0, 0);
    lcd.print("Enter PIN:");
  }
  if (key == 'B'){
    lcd.clear();
    if (pinTemp == pin){
      lcd.setCursor(0, 0);
      lcd.print("PIN Correct!");
      delay(3000);
    }
    if (pinTemp != pin){
      lcd.setCursor(0, 0);
      lcd.print("PIN Incorrect!");
      delay(3000);
    }
    cursorColumn = 0;
    pinTemp = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter PIN:");
  }
}
