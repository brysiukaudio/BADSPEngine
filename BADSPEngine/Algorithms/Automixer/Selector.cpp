#include "Selector.h"



Selector::Selector(float sampleRate, int frameSize, int numOfChannels)
{
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfChannels;
	this->inumOfOutputChannels = numOfChannels;
	this->m_bIsLiveAudio = false;
	this->m_bIsPlaying = false;
}


Selector::~Selector()
{
}

void Selector::setBuffers(float** inBuffer, float** outBuffer) {
	this->setInputBuffer(inBuffer);
	this->setOutputBuffer(outBuffer);
}
void Selector::setBuffers(float** inBufferOne, float** inBufferTwo, float** outBuffer) {
	this->m_pinBuffer = inBufferOne;
	this->m_pInBufferTwo = inBufferTwo;
	this->m_poutBuffer = outBuffer;
}
void Selector::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;
}
void Selector::setInputBuffer(float ** inBufferOne, float** inBufferTwo) {
	this->m_pinBuffer = inBufferOne;
	this->m_pInBufferTwo = inBufferTwo;
}
void Selector::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;
}

void Selector::init() {

}

void Selector::reset() {

}

void Selector::process() {

	if (this->m_bIsPlaying && !(this->m_bIsLiveAudio)) {
		for (int i = 0; i < this->inumOfInputChannels; i++) {
			for (int j = 0; j < iframeSize; j++) {
				this->m_poutBuffer[i][j] = this->m_pInBufferTwo[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < this->inumOfInputChannels; i++) {
			for (int j = 0; j < iframeSize; j++) {
				this->m_poutBuffer[i][j] = this->m_pinBuffer[i][j];
			}
		}
	}
}

void Selector::setIsPlaying(bool isPlaying) {
	this->m_bIsPlaying = isPlaying;
}

void Selector::processSubComponent() {

}