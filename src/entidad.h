#include <TimeoutCallback.h>


class Entidad {

    public:
    typedef void (*ExternalCallbackPointer)();
    Entidad(uint8_t digital_pin,uint8_t analog_pin,uint32_t tiempo);
    void begin();
    void readpot();
    boolean getState();
    void setFlag(boolean b){ this->once = b;};
    void setState(boolean state);
    void toggleState();
    void changebyTime(boolean state,ExternalCallbackPointer onTimeoutCallbackPointer);
    
    private:
    TimeoutCallback handle_time;
    uint8_t digital_pin;
    uint8_t analog_pin;
    uint32_t tiempo;
    boolean state;
    boolean once = 0;
    unsigned long timeMillis;
};


