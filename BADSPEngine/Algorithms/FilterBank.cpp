/*
Mandryk Audio Filter Bank
Passes the input buffer through a filter bank and outputs multiple buffers for each band

Created 15/06/2016 by Kaegan Mandryk
Copyright MandrykAudio


*/


#include "FilterBank.h"
#include "..\Engine\DSPComponent.h"

FilterBank::FilterBank(float sampleRate, int frameSize, int numOfChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfChannels = numOfChannels;
}

FilterBank::~FilterBank() {

}

void FilterBank::init() {

}

void FilterBank::reset() {

}

void FilterBank::process() {
	for (int i = 0; i < inumOfChannels; i++) {
		for (int j = 0; j < iframeSize; j++) {
			this->m_poutBuffer[i][j] = fgain*this->m_pinBuffer[i][j];
		}
	}
}


void FilterBank::setBuffers(float ** inBuffer, float ** outBuffer) {
	this->m_pinBuffer = inBuffer;
	this->m_poutBuffer = outBuffer;
}
void FilterBank::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;
}
void FilterBank::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;
}
void FilterBank::setGain(float gain) {
	this->fgain = gain;
}

void FilterBank::processSubComponent() {

}
