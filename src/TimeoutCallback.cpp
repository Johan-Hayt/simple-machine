#include "TimeoutCallback.h"

TimeoutCallback::TimeoutCallback() {
	this->onTimeoutCallbackPointer = NULL;
    this->duration = 0;
}

void TimeoutCallback::start(unsigned long durationMillis, ExternalCallbackPointer onTimeoutCallbackPointer) {

	this->onTimeoutCallbackPointer = onTimeoutCallbackPointer;
    this->duration = durationMillis;
    this->lastMillis = millis();
	this->running = true;
}

/*void TimeoutCallback::restart() {
	this->start();
}*/

void TimeoutCallback::stop() {
    this->running = false;
}

// Call this in Arduino loop() function
void TimeoutCallback::loop() {
	if (this->running) {
		unsigned long currentMillis = millis();
		if ((currentMillis - this->lastMillis) >= this->duration) {
			this->stop();
			this->onTimeoutCallbackPointer();
		}
	}
}

void TimeoutCallback::reset() {
	this->lastMillis = millis();
}
