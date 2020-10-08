#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);

void setup() {
 lcd.begin(16,02);

}

void loop() {
 lcd.setCursor(0,0);
 lcd.print("Hola, han pasado");
 lcd.setCursor(0,1);
 lcd.print(millis() / 1000);
 lcd.print(" seg");
 

}
