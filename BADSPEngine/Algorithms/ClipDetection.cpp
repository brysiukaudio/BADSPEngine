#include "ClipDetection.h"



ClipDetection::ClipDetection(float sampleRate, int frameSize, int numOfChannels)
{
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfChannels;
	this->inumOfOutputChannels = numOfChannels;
}


ClipDetection::~ClipDetection()
{
}

void ClipDetection::setBuffers(float** inBuffer, float** outBuffer) {
	this->setInputBuffer(inBuffer);
	this->setOutputBuffer(outBuffer);
}

void ClipDetection::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;
}

void ClipDetection::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;
}

void ClipDetection::init() {

}

void ClipDetection::reset() {

}

void ClipDetection::process() {
	
	for (int i = 0; i < inumOfInputChannels; i++) {
		for (int j = 0; j < iframeSize; j++) {
			if (m_pinBuffer[i][j] > 1) {
				if (m_pinBuffer[i][j] > this->max) {
					max = m_pinBuffer[i][j];
					gain = 0.95 / m_pinBuffer[i][j];
				}
			}
		}
	}
	for (int i = 0; i < inumOfInputChannels; i++) {
		for (int j = 0; j < iframeSize; j++) {
			m_poutBuffer[i][j] = gain*m_pinBuffer[i][j];
		}
	}
	
}
