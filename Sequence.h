#ifndef Sequence_h_
#define Sequence_h_

#include "Bot.h"
#include "Node.h"
#include "HasInterval.h"
#include "HasInputCollection.h"
#include "HasTrigger.h"
#include "Input.h"
#include "Output.h"
#include "HasIn.h"
#include "HasOut.h"


class Sequence:
public Node,
public HasInterval,
public HasInputCollection<float>,
public HasTrigger,
public HasOut<float>
{
	public:
	
	Sequence():
	HasInterval
		(this),
	HasInputCollection<float>
		(this),
	HasTrigger
		(this),
	HasOut<float>
		(this){
		registerInput(duration);
		selected = NULL;

		interval = 0.033;
		duration = 1.0;
	};

	void onInterval();

	Input<float> duration;
	
	protected:

	void onInternalInputChange(BaseInput &internalInput);

	private:

	Input<float> * selected;
	bool running;
	float startTime;

};
void Sequence::onInterval(){
	if(!running) return;
	float position = (Bot::seconds - startTime) / duration.get();
	if(position > 1){
		position = 1;
		running = false;
	}
	int i = floor(position * items.size());
	if( i == items.size()) i = items.size() - 1;
	if(items[i] != selected){
		selected = items[i];
		out.set(selected->get());
	}
}

void Sequence::onInternalInputChange(BaseInput &internalInput){
	if(&internalInput == &trigger){
		if(!running && isTriggerActive()){
			startTime = Bot::seconds;
			running = true;
			onInterval(); // start immediatelly
		}
	}
};

#endif
