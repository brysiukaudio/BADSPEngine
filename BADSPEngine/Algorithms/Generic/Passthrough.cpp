/*
Brysiuk Audio Passthrough
A simple objected that just passes audio from the input buffer to the output buffer

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio


*/


#include "Passthrough.h"
#include "..\Engine\DSPComponent.h"

Passthrough::Passthrough(float sampleRate, int frameSize, int numOfInputChannels, int numOfOutputChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfInputChannels;
	this->inumOfOutputChannels = numOfOutputChannels;
}

Passthrough::~Passthrough() {

}

void Passthrough::init() {

}

void Passthrough::reset() {

}

void Passthrough::process() {
	for (int i = 0; i < inumOfOutputChannels; i++) {
		for (int j = 0; j < iframeSize; j++) {
			this->m_poutBuffer[i][j] = fgain*this->m_pinBuffer[i][j];
		}
	}
}


void Passthrough::setBuffers(float ** inBuffer, float ** outBuffer) {
	this->m_pinBuffer = inBuffer;
	this->m_poutBuffer = outBuffer;
}
void Passthrough::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;
}
void Passthrough::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;
}
void Passthrough::setGain(float gain) {
	this->fgain = gain;
}

void Passthrough::processSubComponent() {

}
