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
	float ** processedRemainBuffer;
	float ** unprocessedRemainBuffer;
	double sampleRate;
	int frameSize;
	int fixedframeSize = 0;
	int processedRemain = 0;
	int unprocessedRemain = 0;
	bool useFixedFrame = false;
	int numChannels;
	std::list<DSPComponent*> componentList;
	

public:
	Engine(double sampleRate, int frameSize, int numOfChannels, int fixedFrameSize = 0);
	~Engine();


	void addComponent(DSPComponent * component);

	int getSampleRate();
	int getFrameSize();

	float ** getInputBuffer();
	float ** getOutputBuffer();

	bool usingFixedFrame() { return useFixedFrame; };

	void processAudio(float ** liveIn, float ** liveOut);

	void init();
	void process();
	void reset();
};