#pragma once
#include <list>
#include "EngineDefinitions.h"
#include "Component.h"

class Engine {
private:
	float * inBuffer[NUM_OF_CHANNELS];
	float * outBuffer[NUM_OF_CHANNELS];
	float *	internalBuffer1[NUM_OF_CHANNELS];
	float * internalBuffer2[NUM_OF_CHANNELS];
	int sampleRate;
	int frameSize;
	std::list<Component> componentList;
	

public:
	Engine(int sampleRate, int frameSize);
	~Engine();


	void addComponent(Component component);

	int getSampleRate();
	int getFrameSize();
	float ** getInputBuffer();
	float ** getOutputBuffer();

	void init();
	void process();
	void reset();
};