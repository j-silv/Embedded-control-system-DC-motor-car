#include <LiquidCrystal.h>

byte rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
char message;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
 lcd.begin(16, 2); 
 Serial.begin(9600);
}

void loop() {
  if((Serial.available() > 0)){
    lcd.clear();
    
    while((Serial.available() > 0)){
      message=Serial.read();
      delay(1);
      lcd.print(message);
    }      
  }
}
