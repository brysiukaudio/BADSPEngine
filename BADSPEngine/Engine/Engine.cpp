/*
Brysiuk Audio DSP Engine
Loads and initializes components, organizes call chain and internal buffer sharing

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio

*/

#include "Engine.h"

Engine::Engine(int sampleRate, int frameSize)
{
	this->sampleRate = sampleRate;
	this->frameSize = frameSize;
	this->internalBuffer[0][0] = new float[frameSize];
	this->internalBuffer[0][1] = new float[frameSize];
	this->internalBuffer[1][0] = new float[frameSize];
	this->internalBuffer[1][1] = new float[frameSize];
}

Engine::~Engine() {
	this->inBuffer[0] = nullptr;
	this->outBuffer[0] = nullptr;
	this->inBuffer[1] = nullptr;
	this->outBuffer[1] = nullptr;
	delete[] this->internalBuffer[0][0];
	delete[] this->internalBuffer[0][1];
	delete[] this->internalBuffer[1][0];
	delete[] this->internalBuffer[1][1];
}