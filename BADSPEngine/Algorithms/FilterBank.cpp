/*
Mandryk Audio Filter Bank
Passes the input buffer through a filter bank and outputs multiple buffers for each band

Created 15/06/2016 by Kaegan Mandryk
Copyright MandrykAudio


*/


#include "FilterBank.h"
#include "..\Engine\DSPComponent.h"
#include <numeric>

FilterBank::FilterBank(float sampleRate, int frameSize, int numOfInputChannels, int numOfOutputChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfInputChannels;
	this->inumOfOutputChannels = numOfOutputChannels;
}

FilterBank::~FilterBank() {

}

void FilterBank::init() {

}

void FilterBank::reset() {

}

void FilterBank::process() {
	const int numOfBands = 5;
	float filter_results[numOfBands][sizeof(m_poutBuffer) / sizeof(m_poutBuffer[0][0])];
	for (int i = 0; i < inumOfChannels; i++) { // for each channel
		for (int j = 0; j < numOfBands; ++j)
		{
			applyFilter(this->m_pinBuffer[i], filter_results[i], filterCoefficients[j]);
		}
	}
}

/*
 Applies a 1-D filter to the input buffer.
*/
void FilterBank::applyFilter(float * inBuffer, float * outBuffer, float * H) {
	if (H[0] != NULL)
	{
		int L = sizeof(H) / sizeof(H[0]);
		int N = sizeof(inBuffer) / sizeof(inBuffer[0]);
		float* in_lead = inBuffer;
		float* in_lag = in_lead;

		int outIdx = 0;

		while (1)
		{
			if (in_lead == nullptr || in_lag == nullptr || H == nullptr)
			{
				// something went wrong
				int x = 0;
			}

			outBuffer[outIdx++] = std::inner_product(in_lag, in_lead, H, 0.0);

			// increment the lead pointer unless at the end of the input Buffer
			if (in_lead != &inBuffer[sizeof(inBuffer)])
			{
				in_lead++;
			}

			// only increment the lag pointer once the lead pointer has a gap the size of the filter length
			// or if the lead pointer is at the end of the input sequence
			if (in_lead - in_lag >= L || in_lead == &inBuffer[sizeof(inBuffer)])
			{
				in_lag++;
			}

			// once the lead and lag pointers are the same again, the process is finished. Finish last computation
			if (in_lead == in_lag) 
			{
				outBuffer[outIdx++] = std::inner_product(in_lag, in_lead, H, 0.0);
				break;
			}
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
