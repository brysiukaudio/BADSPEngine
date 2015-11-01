/*
Brysiuk Audio DSP Engine
Loads and initializes components, organizes call chain and internal buffer sharing

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio


*/
#pragma once
#include <list>
#include "EngineDefinitions.h"
#include "Component.h"

class Engine {
private:
	float * inBuffer[NUM_OF_CHANNELS];
	float * outBuffer[NUM_OF_CHANNELS];
	float *	internalBuffer[2][NUM_OF_CHANNELS];
	int sampleRate;
	int frameSize;
	std::list<Component*> componentList;
	

public:
	Engine(int sampleRate, int frameSize);
	~Engine();


	void addComponent(Component * component);

	int getSampleRate();
	int getFrameSize();

	float ** getInputBuffer();
	float ** getOutputBuffer();

	void processAudio(float ** liveIn, float ** liveOut);

	void init();
	void process();
	void reset();
};