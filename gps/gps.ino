#include <SoftwareSerial.h> //incluimos las librerias SoftwareSerial y TinyGPS
#include <TinyGPS.h>

TinyGPS gps; // Declaramos el objeto GPS
SoftwareSerial serialgps(6, 7); // Declaramos el pin 4(Tx del GPS) y el 3 (Rx del GPS)

void setup() {

  Serial.begin(115200);
  serialgps.begin(9600);
  
  Serial.print("DATOS RECIBIDOS DEL GPS ");
  
  Serial.println();

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
           sprintf(sz, "%02d:%02d:%02d" , hour, minute, second);
           Serial.print(sz);
           Serial.println();
           Serial.println();
           sprintf(sz, "%02d/%02d/%02d ", month, day, year);
           Serial.print(sz);
           Serial.println();
           Serial.print("****************************************************************************************** ");
           Serial.println();

        }
    
}
