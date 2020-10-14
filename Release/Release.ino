#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <LiquidCrystal_I2C.h>
#include <LCD.h>
#include <Wire.h>

LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7); //Dir,E,RW,RS,D4,D5,D6,D7
TinyGPS gps; // Declaramos el objeto GPS
SoftwareSerial serialgps(6, 7); // Declaramos el pin 4(Tx del GPS) y el 3 (Rx del GPS)

#define dt 2
#define clk 4 

int anterior = 1;
volatile int posicion = 1;

void setup(){
  pinMode(dt,INPUT);
  pinMode(clk,INPUT);
  Serial.begin(115200);
  serialgps.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(dt),encoder,LOW);
  
  //Serial.println("Listo:");

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
  bool newData = false;
    
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (serialgps.available())
    {
      char c = serialgps.read();// para leer los datos
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Pregunto si ha entrado una nueva sentencia valida
        newData = true;
    }
  }
  if (newData)
  {
    float latitud, longitud;
    unsigned long age;
    int year;
    byte month, day, hour, minute, second, hundredths;

            gps.f_get_position(&latitud, &longitud, & age);
             gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
            //LATITUD
            Serial.print ("\nLAT= ");
            Serial.print(latitud == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : latitud, 6);
            Serial.println ();
             
            //LONGITUD
            Serial.println();
            Serial.print ("LONG= ");
            Serial.print(longitud == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : longitud, 6);
            Serial.println();
            
            //CANT SATELITES
            Serial.println();
             Serial.print("SAT=");
             Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
             Serial.println();


            // LINK GPS (GOOGLE MAPS)
            Serial.println();
            Serial.print("www.google.com/maps/place/");
            Serial.print (latitud,5);
            Serial.print(",");
            Serial.print (longitud,5);
            Serial.println();

            //FECHA Y HORA
            Serial.println();
           char sz[32];
           char hra[32];
           sprintf(hra, "%02d:%02d:%02d" , hour, minute, second);
           Serial.print(sz);
           Serial.println();
           Serial.println();
           sprintf(sz, "%02d/%02d/%02d ", month, day, year);
           Serial.print(sz);
           Serial.println();
           Serial.print("****************************************************************************************** ");
           Serial.println();
          
  switch (posicion) {
    case 0:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Lat: ");
      lcd.setCursor(5,0);
      lcd.print(latitud,5);
      lcd.setCursor(0,1);
      lcd.print("Long: ");
      lcd.setCursor(5,1);
      lcd.print(longitud,5);
      Serial.println("Latitud y longitud");
      delay(500);
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Dia: ");
      lcd.setCursor(0,1);
      lcd.print(sz);
      Serial.println("Dia");
      delay(500);
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cant satelites:");
      lcd.setCursor(0,1);
      lcd.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
      Serial.println("Cantidad Satelites");
      delay(500);
      break;
    default:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Hora: ");
      lcd.setCursor(0,1);
      lcd.print(hra);
      Serial.println("Hora");
      delay(500);
      break;
    }
  
  if (posicion != anterior)
    anterior = posicion;
      
  }
  
}

void encoder(){
  static unsigned long ultimaInterrupcion = 0;
  unsigned long tiempoInterrupcion = millis();
   
  if (tiempoInterrupcion - ultimaInterrupcion > 20){
    if (digitalRead(clk) == HIGH)
      posicion++;
    else 
      posicion--;

    posicion = min(3, max(0,posicion));  
    ultimaInterrupcion = tiempoInterrupcion;
  }
}
