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
}


void loop() {

  switch (posicion) {
    case 0:
      Serial.println("Latitud y longitud");  
      break;
    case 1:
      Serial.println("Dia");
      break;
    case 2:
      Serial.println("Cantidad de satelites");
      break;
    case 3:
      Serial.println("Altura");
      break;
    default:
      Serial.println("Dia y hora");
      break;
}
  
  if (posicion != anterior)
    anterior = posicion;
  
}

void encoder(){
  static unsigned long ultimaInterrupcion = 0;
  unsigned long tiempoInterrupcion = millis();

  if (tiempoInterrupcion - ultimaInterrupcion > 5){
    if (digitalRead(clk) == HIGH)
      posicion++;
    else 
      posicion--;

    posicion = min(4, max(0,posicion));  
    ultimaInterrupcion = tiempoInterrupcion;
  }
}
