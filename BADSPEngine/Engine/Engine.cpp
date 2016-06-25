/*
Brysiuk Audio DSP Engine
Loads and initializes components, organizes call chain and internal buffer sharing

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio

*/

#include "Engine.h"

Engine::Engine(double sampleRate, int frameSize, int numOfInputChannels, int numOfOutputChannels)
{
	this->sampleRate = sampleRate;
	this->frameSize = frameSize;
	this->numOfInputChannels = numOfInputChannels;
	this->numOfOutputChannels = numOfOutputChannels;
	this->inBuffer = new float*[numOfInputChannels]();
	this->outBuffer = new float*[numOfOutputChannels]();
	
	for (int i = 0; i < this->numOfInputChannels; i++) {
		this->inBuffer[i] = new float[frameSize]();
	}
	for (int i = 0; i < this->numOfOutputChannels; i++) {
		this->outBuffer[i] = new float[frameSize]();
	}

}

Engine::~Engine() {
	for (int i = 0; i < this->numOfInputChannels; i++) {
		delete[] this->inBuffer[i];
		this->inBuffer[i] = nullptr;
	}
	for (int i = 0; i < this->numOfOutputChannels; i++) {
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
	
	for (int i = 0; i < this->numOfInputChannels; i++) {
		memcpy(this->inBuffer[i], liveIn[i], this->frameSize*sizeof(float));
	}
	for (int i = 0; i < this->numOfOutputChannels; i++) {
		memcpy(liveOut[i], this->outBuffer[i], this->frameSize*sizeof(float));
	}
	
	this->process();
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