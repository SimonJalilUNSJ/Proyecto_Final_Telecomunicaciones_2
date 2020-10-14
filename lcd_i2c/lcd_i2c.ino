#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCD.h>


LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); //Dir,E,RW,RS,D4,D5,D6,D7

void setup() {
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16,2);
  lcd.clear();

}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Hola, han pasado");
  lcd.setCursor(0,1);
  lcd.print(millis() / 1000);
  lcd.print(" seg.");  

}
