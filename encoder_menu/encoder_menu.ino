#include <LiquidCrystal.h>
LiquidCrystal lcd;

//Variables para el menu de encoder.
int counter = 0;
int page = 1;
int Ready = 1;
int submenu = 0;
int last_counter = 0;
bool clk_state;
bool last_state;
bool dt_state;
int pushed = 0;

//Pin para el boton de encoder.
#define push 10;

//Vectors for musical note and arrow
//uint8_t note[8]  = {0x02, 0x03, 0x02, 0x0e, 0x1e, 0x0c, 0x00, 0x00};
//uint8_t arrow[8] = {0x0, 0x04 ,0x06, 0x1f, 0x06, 0x04, 0x00, 0x00};

void setup() {
  pinMode(push,INPUT);

  lcd.init();
  lcd.backlight();
  //lcd.createChar(0,note);
  //lcd.createChar(1,arrow);
  lcd.home();
  
  PCICR |= (1 << PCIE0);    //Habilita el scan de registro PCMSK0 
  PCMSK0 |= (1 << PCINT0);  //Habilita pin D8 trigger como interrupcion de cambio de estado.
  PCMSK0 |= (1 << PCINT1);  //Habilita pin D9 trigger como interrupcion de cambio de estado.
  DDRB &= B11111100;        //8,9 como intradas para el encoder clock y pins de datos.

  last_state = (PINB & B00000001); //Estado del pin 8.
   
  //Muestra un texto inicial.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Teleco 2");
  lcd.write(0);
  lcd.setCursor(0,1);
  lcd.print("ProyectoGPSyGSM")
  delay(3000);

  //Mostrar la primer pagina del menu.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(1); 
  lcd.print
}

void loop() {
  

}



//Vector de interrupcion

ISR(PCINT0_vect){
  
  clk_State =   (PINB & B00000001);// Estado de pin 8, estado de clock. 
  dt_State  =   (PINB & B00000010); 
  if (clk_State != Last_State){ 
     //Si el estado de la data es diferente al del clock, entonces quiere decir que esra rotando en sentido horario.    
     if (dt_State != clk_State) { 
       counter ++;
     }
     else {
       counter --;
     } 
   } 
   Last_State = clk_State; // Updates the previous state of the data with the current state
  
}
