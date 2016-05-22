/*
Brysiuk Audio DSP Engine
Loads and initializes components, organizes call chain and internal buffer sharing

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio

*/

#include "Engine.h"

Engine::Engine(double sampleRate, int frameSize, int numOfChannels)
{
	this->sampleRate = sampleRate;
	this->frameSize = frameSize;
	this->numOfChannels = numOfChannels;
	this->inBuffer = new float*[numOfChannels]();
	this->outBuffer = new float*[numOfChannels]();
	this->internalBuffer[0] = new float*[numOfChannels]();
	this->internalBuffer[1] = new float*[numOfChannels]();
	
	for (int i = 0; i < this->numOfChannels; i++) {
		this->inBuffer[i] = new float[frameSize]();
		this->outBuffer[i] = new float[frameSize]();
		this->internalBuffer[0][i] = new float[frameSize]();
		this->internalBuffer[1][i] = new float[frameSize]();
	}

}

Engine::~Engine() {
	for (int i = 0; i < this->numOfChannels; i++) {
		delete[] this->inBuffer[i];
		delete[] this->outBuffer[i];
		delete[] this->internalBuffer[0][i];
		delete[] this->internalBuffer[1][i];
		this->inBuffer[i] = nullptr;
		this->outBuffer[i] = nullptr;
		this->internalBuffer[0][i] = nullptr;
		this->internalBuffer[1][i] = nullptr;
	}

}

void Engine::addComponent(DSPComponent* component) {
	assert(component != nullptr);


	if (componentList.empty()) {
		component->setBuffers(this->inBuffer, this->outBuffer);
		componentList.push_back(component);
	}
	else {
		int bufferIt = (componentList.size() - 1) % 2;
		componentList.back()->setOutputBuffer(this->internalBuffer[bufferIt]);
		component->setBuffers(this->internalBuffer[bufferIt], this->outBuffer);
		componentList.push_back(component);
	}
	

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
	
	for (int i = 0; i < this->numOfChannels; i++) {
		memcpy(this->inBuffer[i], liveIn[i], this->frameSize*sizeof(float));
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