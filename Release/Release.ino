#include <LiquidCrystal_I2C.h>
#include <LCD.h>
#include <Wire.h>

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); //Dir,E,RW,RS,D4,D5,D6,D7

#define dt 2
#define clk 4 

int anterior = 1;
volatile int posicion = 1;

void setup(){
  pinMode(dt,INPUT);
  pinMode(clk,INPUT);
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(dt),encoder,LOW);
  
  Serial.println("Listo:");

  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16,2);
  lcd.clear();
  

  lcd.setCursor(0,0);
  lcd.print("ProyTeleco2");
  lcd.setCursor(0,1);
  lcd.print("GSM y GPS");
  delay(3000);
  lcd.clear();
}


void loop() {

  switch (posicion) {
    case 0:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Lat: ");
      lcd.setCursor(0,1);
      lcd.print("Long: ");
      Serial.println("Latitud y longitud");
      delay(750);
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Dia: ");
      Serial.println("Dia");
      delay(750);
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cant satelites:");
      Serial.println("Cantidad Satelites");
      delay(750);
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Altura: ");
      Serial.println("Altura");
      delay(750);
      break;
    default:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Hora: ");
      Serial.println("Hora");
      delay(750);
      break;
}
  
  if (posicion != anterior)
    anterior = posicion;
  
}

void encoder(){
  static unsigned long ultimaInterrupcion = 0;
  unsigned long tiempoInterrupcion = millis();
   
  if (tiempoInterrupcion - ultimaInterrupcion > 20){
    if (digitalRead(clk) == HIGH)
      posicion++;
    else 
      posicion--;

    posicion = min(4, max(0,posicion));  
    ultimaInterrupcion = tiempoInterrupcion;
  }
}
