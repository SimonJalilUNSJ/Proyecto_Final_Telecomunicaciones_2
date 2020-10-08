#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);

void setup() {
 lcd.begin(16,02);

}

void loop() {
 lcd.setCursor(2,0);
 lcd.print("Prueba scroll");
 lcd.scrollDisplayLeft();
 delay(500);
}
