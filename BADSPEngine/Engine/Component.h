#pragma once
#include "EngineDefinitions.h"
class Component {
private:
	float * inBuffer[NUM_OF_CHANNELS];
	float * outBuffer[NUM_OF_CHANNELS];
	void processSubComponent();
public:
	Component();
	~Component();

	void init();
	void process();
	void reset();
};