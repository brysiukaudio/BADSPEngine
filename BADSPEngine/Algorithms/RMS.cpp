#include "RMS.h"
#include "..\Engine\DSPComponent.h"

RMS::RMS(float sampleRate, int frameSize, int numOfInputChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfInputChannels;
	prevRMS = new float[numOfInputChannels]();
	numFrames = new int[numOfInputChannels]();
}

RMS::~RMS() {

}

void RMS::init() {

}

void RMS::reset() {

}

void RMS::process() {
	if (calibrate) {
		int i, iBuffer;
		float temp = 0;
		for (iBuffer = 0; iBuffer < inumOfInputChannels; iBuffer++) {
			for (i = 0; i < iframeSize; i++) {
				temp = temp + (this->m_pinBuffer[iBuffer][i] * this->m_pinBuffer[iBuffer][i]);
			} /*End for*/

			if (temp / iframeSize > THRESHOLD) {
				prevRMS[iBuffer] = prevRMS[iBuffer] + temp / iframeSize;
				numFrames[iBuffer] = numFrames[iBuffer] + 1;
			} /*End if*/
			temp = 0;
		} /*End for*/
	}
}

void RMS::getRMS(float* pfRMSValues_) {
	int i;
	for (i = 0; i < inumOfInputChannels; i++) {
		pfRMSValues_[i] = prevRMS[i] / (float)numFrames[i];
	}

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

void RMS::setCalibrate(bool calibrate) {
	this->calibrate = calibrate;
}
