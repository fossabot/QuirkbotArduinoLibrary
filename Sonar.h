#ifndef Sonar_h_
#define Sonar_h_

#include "Sensor.h"

class Sonar :
public Sensor
{
	public:
	
	Sonar(){
		registerInput(pin);

		normalizingFactor = 5000.0;
	};

	void onInterval();

	Input<int> pin;

	
	protected:
	void onInternalInputChange(BaseInput &internalInput);
};

void Sonar::onInternalInputChange(BaseInput &internalInput){
	if(&internalInput == &interval){
		if(interval.get() < 0.05) interval = 0.05;
	}
};
void Sonar::onInterval(){
	if(pin.get() == -1) return;


	pinMode(pin.get(), OUTPUT);

	digitalWrite(pin.get(), LOW);
	delayMicroseconds(2);
	digitalWrite(pin.get(), HIGH);
	delayMicroseconds(5);
	digitalWrite(pin.get(), LOW);

	pinMode(pin.get(), INPUT);

	float reading = pulseIn(pin.get(), HIGH, 5000);

	if(reading == 0) reading = 5000;

	processReading(reading);
};


#endif
