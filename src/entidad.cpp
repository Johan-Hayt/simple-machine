#include <Arduino.h>
#include <entidad.h>



Entidad::Entidad(uint8_t digital_pin,uint8_t analog_pin, uint32_t tiempo){

    this->digital_pin = digital_pin;
    this->analog_pin  =  analog_pin;
    this->tiempo      = tiempo;
    this->state = 0;
    this->timeMillis = 0;
};

void Entidad::begin(){

    pinMode(this->digital_pin, OUTPUT);
    this->timeMillis = map(analogRead(this->analog_pin),0,1023,0,this->tiempo);
    this->setState(0);
    digitalWrite(this->digital_pin,this->state);

};

void Entidad::readpot(){

    this->timeMillis = map(analogRead(this->analog_pin),0,1023,0,this->tiempo);

};

boolean Entidad::getState(){
    return this->state;
};

void Entidad::setState(boolean state){
    this->state = state;
    digitalWrite(digital_pin,state);
};

void Entidad::toggleState(){
    this->state = !this->getState();
    digitalWrite(this->digital_pin,this->state);
};

void Entidad::changebyTime(boolean state,ExternalCallbackPointer onTimeoutCallbackPointer){
    
    if(!this->once){
        this->setState(state);
        handle_time.start(this->timeMillis,onTimeoutCallbackPointer);
        this->once  = 1;
    }
    else{
        handle_time.loop();
    }
}



