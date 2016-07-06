#include "RMS.h"
#include "..\Engine\DSPComponent.h"

RMS::RMS(float sampleRate, int frameSize, int numOfInputChannels, int numOfOutputChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfInputChannels;
	this->inumOfOutputChannels = numOfOutputChannels;
}

RMS::~RMS() {

}

void process() {
}

void RMS::init() {

}

void RMS::reset() {

}

void RMS::process() {
	
}
void RMS::setBuffers(float **inBuffer, float** outBuffer) {

}

void RMS::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;


}
void RMS::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;

}

void RMS::processSubComponent() {

}
