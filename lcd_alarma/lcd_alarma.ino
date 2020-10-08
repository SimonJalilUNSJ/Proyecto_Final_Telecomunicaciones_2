#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);

void setup() {
 lcd.begin(16,02);

}

void loop() {
 lcd.setCursor(0,0);
 lcd.print("Ingrese clave:");
 lcd.setCursor(0,1);
 lcd. cursor();
 delay(500);
 lcd.noCursor();
 delay(500);
}
