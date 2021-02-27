#include "Entidad.h"

enum State{
  Inicio,
  auto_llenado,
  auto_sellado,
  Llenado,
  Sellado,
  Espera
};

typedef enum State state_t;

state_t currentState = Inicio;
state_t nextState = currentState;

const uint8_t  muletilla = 7;
const uint8_t  pedal = 6;



uint8_t flg_llenado = 0,flg_mordaza = 0, flg_resistencia= 0;
void cb_llenado();
void cb_Mordaza();
void cb_Resistencia();

Entidad v(8,0),m(9,1),r(10,2);



void cb_llenado(){
  Serial.println("cb_Llenado OK!");
  v.setState(0);
  flg_llenado = 1;
  
}

void cb_r(){
  Serial.println("cb_r OK!");
  r.setState(0);
  flg_resistencia = 1;

}

void cb_m(){
  Serial.println("cb_m OK!");
  m.setState(0);
  flg_mordaza = 1;

}

void fct_Inicio(){

  v.readpot();
  r.readpot();
  m.readpot();
  Serial.println("Inicio");

  if(!(digitalRead(muletilla))){
    Serial.println("Inicio->Automatico");
    nextState = auto_llenado;
  }else
  {
    Serial.println("Inicio->Espera");
    nextState = Espera;
  }
  

}

void fct_Llenado(){

    v.changebyTime(1,cb_llenado);
    if(flg_llenado){
      flg_llenado = 0;
      v.setFlag(0);
      Serial.println("llenado->Sellado");
      nextState = Sellado;
    }

}

void fct_Sellado(){

  
  r.changebyTime(1,cb_r);
  m.changebyTime(1,cb_m);

  if(flg_mordaza&&flg_resistencia){
    flg_mordaza = 0;
    flg_resistencia = 0;
    r.setFlag(0);
    m.setFlag(0);
    Serial.println("Sellado->Inicio");
    nextState = Inicio;
  }

}

void fct_Espera(){
  

  Serial.println("Espera");
  while(digitalRead(pedal)){
    v.readpot();
    r.readpot();
    m.readpot();
    delay(100);
  }
  Serial.println("Espera->Llenado");
  nextState = Llenado;

}

void fct_autollenado(){

  v.changebyTime(1,cb_llenado);
  if(flg_llenado){
    flg_llenado = 0;
    v.setFlag(0);
    Serial.println("llenado->Sellado");
    nextState = auto_sellado;
    delay(1000); /*TIEMPO DE ESPERA ENTRE LLENADO Y SELLADO AUTOMATICO*/
  }
  


}

void fct_autosellado(){


  r.changebyTime(1,cb_r);
  m.changebyTime(1,cb_m);

  if(flg_mordaza&&flg_resistencia){
    flg_mordaza = 0;
    flg_resistencia = 0;
    r.setFlag(0);
    m.setFlag(0);
    Serial.println("Sellado->Inicio");
    nextState = Inicio;
  }


}




void setup() {
  Serial.begin(9600);
  pinMode(muletilla, INPUT);
  pinMode(pedal, INPUT);
  v.begin();
  r.begin();
  m.begin();

}

void loop() {



  currentState = nextState;
  switch (currentState)
  {
  case Inicio:
    fct_Inicio();
    break;

  case auto_llenado: 
    fct_autollenado();
    break;
  
  case auto_sellado: 
    fct_autosellado();
    break;

  
  case Espera:
    fct_Espera();
    break;

  case Llenado:
    fct_Llenado();
    break;

  case Sellado:
    fct_Sellado();
    break;   

  default:
    break;
  }
 

  
  
  
}