#include "RMS.h"
#include "..\Engine\DSPComponent.h"

RMS::RMS(float sampleRate, int frameSize, int numOfInputChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfInputChannels;
	prevRMS = new float[numOfInputChannels]();
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
	/* Xrms(n) = (1 - TAV)*Xrms(n-1) + x(n)^2 */
	int i, iBuffer;
	for (iBuffer = 0; iBuffer < inumOfInputChannels; iBuffer++) {
		for (i = 0; i < iframeSize; i++) {
			if (i == 0) {
				this->m_poutBuffer[iBuffer][i] = (1 - TAV)*prevRMS[iBuffer] + TAV*(this->m_pinBuffer[iBuffer][i] * this->m_pinBuffer[iBuffer][i]);
			} /*End if*/
			else {
				this->m_poutBuffer[iBuffer][i] = (1 - TAV)*prevRMS[iBuffer] + TAV*(this->m_pinBuffer[iBuffer][i] * this->m_pinBuffer[iBuffer][i]);
			} /*End else*/
			prevRMS[iBuffer] = this->m_poutBuffer[iBuffer][iframeSize - 1];
		} /*End for*/
	} /*End for*/
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
