int dt = 2;
int clk =  4;
int anterior = 50;

volatile int posicion = 50;

void setup() {
  pinMode(dt,INPUT);
  pinMode(clk,INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(dt), encoder, LOW);
  Serial.println("Listo");  

}

void loop() {
  if (posicion != anterior){
    Serial.println(posicion);
    anterior = posicion;
  }
}

void encoder(){
  static unsigned long ultimaInterrupcion = 0;
  unsigned long tiempoInterrupcion = millis();

  if (tiempoInterrupcion - ultimaInterrupcion > 5){
    if (digitalRead(clk) == HIGH)
      posicion++;
    else 
      posicion--;

    posicion = min(100, max(0,posicion));  
    ultimaInterrupcion = tiempoInterrupcion;
  }
}
