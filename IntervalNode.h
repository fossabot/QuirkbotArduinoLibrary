#ifndef IntervalNode_h_
#define IntervalNode_h_

#include "Bot.h"
#include "Node.h"
#include "Updatable.h"
#include "Input.h"
#include "Output.h"

class Node;
class Updatable;

class IntervalNode : public Node, public Updatable{
	public:
	IntervalNode(){
		registerInput(interval);
		interval = 1;
	};

	void update(){
		if((int)(Bot::millis) % (int)interval == 0) onInterval();
	};

	virtual void onInterval(){};

	Input<float> interval;

	/*protected:
	void onInternalInputChange(BaseInput &input);
	void onIntervalChange();
	*/
};

#endif