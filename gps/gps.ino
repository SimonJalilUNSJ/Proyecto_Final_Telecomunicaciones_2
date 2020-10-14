#include <SoftwareSerial.h> //incluimos las librerias SoftwareSerial y TinyGPS
#include <TinyGPS.h>

TinyGPS gps; // Declaramos el objeto GPS
SoftwareSerial serialgps(3, 4); // Declaramos el pin 4(Tx del GPS) y el 3 (Rx del GPS)

void setup() {

Serial.begin(115200);
serialgps.begin(9600);

Serial.print("DATOS PARA LA GEOLOCALIZACION DE OBJETOS ");
Serial.println();
Serial.println();

}

void loop() {

while (serialgps.available())
{
int c = serialgps.read(); // para leer los datos
if (gps.encode(c)){ // Pregunto si ha entrado una nueva sentencia valida

        float latitud, longitud;
        gps.f_get_position(&latitud, &longitud);
        Serial.print ("\nLa latitud es= ");
        Serial.print (latitud,5);
        Serial.print (",");
        Serial.print (" y la longitud es= ");
        Serial.print (longitud,5);
        Serial.println();

        
        
        Serial.print ("\nLa latitud en coordenadas google map es= ");

}
}

}
