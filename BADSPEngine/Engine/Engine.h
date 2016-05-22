/*
Brysiuk Audio DSP Engine
Loads and initializes components, organizes call chain and internal buffer sharing

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio


*/
#pragma once
#include <list>
#include "EngineDefinitions.h"
#include "DSPComponent.h"

class Engine {
private:
	float ** inBuffer;
	float ** outBuffer;
	float ** internalBuffer[2];
	double sampleRate;
	int frameSize;
	int numOfChannels;
	std::list<DSPComponent*> componentList;
	

public:
	Engine(double sampleRate, int frameSize, int numOfChannels);
	~Engine();


	void addComponent(DSPComponent * component);

	int getSampleRate();
	int getFrameSize();

	float ** getInputBuffer();
	float ** getOutputBuffer();

	void processAudio(float ** liveIn, float ** liveOut);

	void init();
	void process();
	void reset();
};