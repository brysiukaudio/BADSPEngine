#include "TwotoOneNodeMixer.h"
#include "..\Engine\DSPComponent.h"
#include <cmath>

TwotoOneNodeMixer::TwotoOneNodeMixer(float sampleRate, int frameSize, int numOfInputChannelsPerNode, int numOfOutputChannels){
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfInputChannelsPerNode;
	this->inumOfOutputChannels = numOfOutputChannels;
}

TwotoOneNodeMixer::~TwotoOneNodeMixer() {

}


void TwotoOneNodeMixer::init() {

}

void TwotoOneNodeMixer::reset() {

}

void TwotoOneNodeMixer::process() {
	for (int i = 0; i < inumOfInputChannels; i++) {
		for (int j = 0; j < iframeSize; j++) {
			this->m_poutBuffer[i][j] = fGlobalGain*((fGain1*m_pinBuffer[i][j]) + (fGain2*m_pfInBuffer2[i][j]));
		}
	}
}


void TwotoOneNodeMixer::setBuffers(float** inBuffer, float** outBuffer) {
	this->setInputBuffer(inBuffer);
	this->setOutputBuffer(outBuffer);
}

void TwotoOneNodeMixer::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;
}

void TwotoOneNodeMixer::setInputBuffer(float ** inNode1, float** inNode2) {
	this->m_pinBuffer = inNode1;
	this->m_pfInBuffer2 = inNode2;

}
void TwotoOneNodeMixer::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;

}

void TwotoOneNodeMixer::setNodeGain(float Gain1, float Gain2) {
	this->fGain1 = Gain1;
	this->fGain2 = Gain2;
}

void TwotoOneNodeMixer::setGlobalGain(float globalGain) {
	this->fGlobalGain = globalGain;
}

void TwotoOneNodeMixer::processSubComponent() {

}
