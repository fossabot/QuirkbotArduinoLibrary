#ifndef Oscillator_h_
#define Oscillator_h_

#include <Arduino.h>

#include "Bot.h"
#include "IntervalNode.h"
#include "Input.h"
#include "Output.h"
#include "ContainsInputs.h"
#include "ContainsOutputs.h"
#include "Streams.h"
#include "OscillatorTables.h"

enum OscillatorType{
	OSC_SINE = 0,
	OSC_SQUARE,
	OSC_TRIANGLE,
	OSC_PULSE,
	OSC_RAMP_UP,
	OSC_RAMP_DOWN
};


class Oscillator :
public IntervalNode,
public OutputStream<float>,
public Contains6Inputs<float,float,float,float,float,float>,
public Contains1Output<float>
{
	public:

	Oscillator():
	OutputStream<float>
		(value),
	Contains6Inputs<float,float,float,float,float,float>
		(begin, end, duration, offset, type, interval),
	Contains1Output<float>
		(value){
		registerInput(begin);
		registerInput(end);
		registerInput(duration);
		registerInput(offset);
		registerInput(type);

		begin = 0.0;
		end = 1.0;
		type = OSC_SINE;
		duration = 1.0;
		interval = 33;
		offset = 0.0;

		table = OSC_SINE_TABLE;
	};

	void onInterval();

	Input<float> begin;
	Input<float> end;

	Input<float> duration;
	Input<float> offset;
	Input<float> type;
	
	Output<float> value;

	protected:

	const int16_t * table;
	
	void onInternalInputChange(BaseInput &input);
};

void Oscillator::onInternalInputChange(BaseInput &input){
	if(&input == &type){
		switch ((int)type){
			case OSC_SQUARE:
				table = OSC_SQUARE_TABLE;
				break;
			case OSC_PULSE:
				table = OSC_PULSE_TABLE;
				break;
			case OSC_TRIANGLE:
				table = OSC_TRIANGLE_TABLE;
				break;
			case OSC_RAMP_UP:
				table = OSC_RAMP_UP_TABLE;
				break;
			case OSC_RAMP_DOWN:
				table = OSC_RAMP_DOWN_TABLE;
				break;
			case OSC_SINE:
			default:
				table = OSC_SINE_TABLE;
				break;
		}
	}
};


void Oscillator::onInterval(){
	float seconds = fmod(Bot::seconds + offset * duration, duration);
	float position = seconds / duration;
	int index = position * 256.0;
	float base = (float)(pgm_read_word_near(table + index)) * 0.001;
	value = mapFloat(base, 0, 1.0, begin, end);
}

#endif