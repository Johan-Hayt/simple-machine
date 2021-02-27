

#include <Arduino.h>

class TimeoutCallback {

public:
    typedef void (*ExternalCallbackPointer)();
    TimeoutCallback();
    void start(unsigned long durationMillis, ExternalCallbackPointer onTimeoutCallbackPointer);
   // void restart();
    void stop();
    void loop();
    void reset();
protected:

private:
    ExternalCallbackPointer onTimeoutCallbackPointer;
    unsigned long duration;
    unsigned long lastMillis;
    boolean running = false;
};

