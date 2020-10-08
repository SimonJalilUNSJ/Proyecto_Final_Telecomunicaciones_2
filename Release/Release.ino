#include <LiquidCrystal.h>

//LiquidCrystal lcd(7,6,5,4,3,2);
LiquidCrystal lcd(10,9,8,7,6,5);

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

  lcd.begin(16,02);

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
      lcd.setCursor(0,0);
      lcd.print("Lat: ");
      lcd.setCursor(0,1);
      lcd.print("Long: ");
      //lcd.clear();
      Serial.println("Latitud y longitud");
      break;
    case 1:
      lcd.setCursor(0,0);
      lcd.print("Dia: ");
      //lcd.clear();
      Serial.println("Dia");
      break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("Cant satelites:");
      //lcd.clear();
      Serial.println("Cantidad Satelites");
      break;
    case 3:
      lcd.setCursor(0,0);
      lcd.print("Altura: ");
      //lcd.clear();
      Serial.println("Altura");
      break;
    default:
      lcd.setCursor(0,0);
      lcd.print("Hora: ");
      //lcd.clear();
      Serial.println("Hora");
      break;
}
  
  if (posicion != anterior)
    anterior = posicion;
  
}

void encoder(){
  static unsigned long ultimaInterrupcion = 0;
  unsigned long tiempoInterrupcion = millis();
  
  lcd.clear();
 
  if (tiempoInterrupcion - ultimaInterrupcion > 20){
    if (digitalRead(clk) == HIGH)
      posicion++;
    else 
      posicion--;

    posicion = min(4, max(0,posicion));  
    ultimaInterrupcion = tiempoInterrupcion;
  }
}
