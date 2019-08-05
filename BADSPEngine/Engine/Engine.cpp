/*
Brysiuk Audio DSP Engine
Loads and initializes components, organizes call chain and internal buffer sharing

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio

*/

#include "Engine.h"

Engine::Engine(double sampleRate, int frameSize, int numOfChannels, int fixedFrameSize)
{
	this->sampleRate = sampleRate;
	this->frameSize = frameSize;
	if (fixedFrameSize != 0)
	{
		this->fixedframeSize = fixedFrameSize;
		unprocessedRemain = 0;
		processedRemain = fixedFrameSize;
		useFixedFrame = true;
	}
	this->numChannels = numOfChannels;
	this->inBuffer = new float*[numChannels]();
	this->outBuffer = new float*[numChannels]();
	if (useFixedFrame)
	{
		this->processedRemainBuffer = new float*[numChannels]();
		this->unprocessedRemainBuffer = new float*[numChannels]();
		for (int i = 0; i < this->numChannels; i++)
		{
			this->processedRemainBuffer[i] = new float[fixedFrameSize];
			this->unprocessedRemainBuffer[i] = new float[fixedFrameSize];
		}
	}
	

	
	for (int i = 0; i < this->numChannels; i++) {
		this->inBuffer[i] = useFixedFrame ? new float[fixedframeSize]() : new float[frameSize]();
		this->outBuffer[i] = useFixedFrame ? new float[fixedframeSize]() : new float[frameSize]();
	}

}

Engine::~Engine() {
	for (int i = 0; i < this->numChannels; i++) {
		delete[] this->inBuffer[i];
		this->inBuffer[i] = nullptr;
		delete[] this->outBuffer[i];
		this->outBuffer[i] = nullptr;
	}
	delete[] this->inBuffer;
	delete[] this->outBuffer;
	this->inBuffer = nullptr;
	this->outBuffer = nullptr;

}

void Engine::addComponent(DSPComponent* component) {
	assert(component != nullptr);


		componentList.push_back(component);

}

int Engine::getSampleRate() {
	return this->sampleRate;
}

int Engine::getFrameSize() {
	return this->frameSize;
}

float ** Engine::getInputBuffer() {
	return this->inBuffer;
}

float ** Engine::getOutputBuffer() {
	return this->outBuffer;
}

void Engine::processAudio(float ** liveIn, float ** liveOut) {
	assert(liveIn != nullptr);
	assert(liveOut != nullptr);
	

	if (useFixedFrame)
	{
		int inRemain = this->frameSize;
		int outCollected = 0;
		int start = 0;
		int outRemain = 0;
		bool pulledFromLiveIn = false;

		for (int i = 0; i < this->numChannels; i++) {
			memcpy(this->inBuffer[i], this->unprocessedRemainBuffer[i], unprocessedRemain * sizeof(float));
			if (unprocessedRemain < fixedframeSize)
			{
				memcpy(this->inBuffer[i] + unprocessedRemain, liveIn[i], (fixedframeSize - unprocessedRemain) * sizeof(float));
				pulledFromLiveIn = true;
			}
		}

		if (pulledFromLiveIn) inRemain -= (fixedframeSize - unprocessedRemain);

		this->process();

		for (int i = 0; i < this->numChannels; i++) {
			memcpy(liveOut[i], this->processedRemainBuffer[i], processedRemain * sizeof(float));
			outCollected = processedRemain;
		}

		

		while (outCollected <= (frameSize - fixedframeSize) && inRemain >= fixedframeSize)
		{
			start = frameSize - inRemain;
			for (int i = 0; i < this->numChannels; i++) {
				memcpy(this->inBuffer[i], liveIn[i] + start, this->fixedframeSize * sizeof(float));
			}

			for (int i = 0; i < this->numChannels; i++) {
				memcpy(liveOut[i] + outCollected, this->outBuffer[i], this->fixedframeSize * sizeof(float));
			}

			this->process();
			inRemain -= fixedframeSize;
			outCollected += fixedframeSize;
		}

		assert(frameSize - outCollected <= fixedframeSize);
		assert(inRemain <= fixedframeSize);

		start = frameSize - inRemain;
		for (int i = 0; i < this->numChannels; i++) {
			memcpy(this->unprocessedRemainBuffer[i], liveIn[i] + start, inRemain * sizeof(float));
		}
		unprocessedRemain = inRemain;

		outRemain = frameSize - outCollected;
		for (int i = 0; i < this->numChannels; i++) {
			memcpy(liveOut[i] + outCollected, this->outBuffer[i], outRemain * sizeof(float));
			memcpy(processedRemainBuffer[i], this->outBuffer[i] + outRemain, (fixedframeSize - outRemain) * sizeof(float));
			processedRemain = (fixedframeSize - outRemain);
		}

	}
	else
	{
		for (int i = 0; i < this->numChannels; i++) {
			memcpy(this->inBuffer[i], liveIn[i], this->frameSize * sizeof(float));
		}
		this->process();

		for (int i = 0; i < this->numChannels; i++) {
			memcpy(liveOut[i], this->outBuffer[i], this->frameSize * sizeof(float));
		}
	}

}

void Engine::init() {
	for (std::list<DSPComponent*>::iterator currentComponent = componentList.begin(); currentComponent != componentList.end(); ++currentComponent) {
		(*currentComponent)->init();
	}
}

void Engine::process() {
	for (std::list<DSPComponent*>::iterator currentComponent = componentList.begin(); currentComponent != componentList.end(); ++currentComponent) {
		(*currentComponent)->process();
	}
}

void Engine::reset() {
	for (std::list<DSPComponent*>::iterator currentComponent = componentList.begin(); currentComponent != componentList.end(); ++currentComponent) {
		(*currentComponent)->reset();
	}
}