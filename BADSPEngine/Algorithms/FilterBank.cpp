/*
Mandryk Audio Filter Bank
Passes the input buffer through a filter bank and outputs multiple buffers for each band

Created 15/06/2016 by Kaegan Mandryk
Copyright MandrykAudio


*/


#include <algorithm>
#include "FilterBank.h"
#include "..\Engine\DSPComponent.h"


FilterBank::FilterBank(float sampleRate, int frameSize, int numOfInputChannels, int numOfOutputChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfInputChannels;
	this->inumOfOutputChannels = numOfOutputChannels;
}

FilterBank::~FilterBank() {

}

/*
	Constructs the filter coefficients based off of the preset cutoff frequencies and the given sampling rate.
	The given filter is based off of the continuous time domain 2nd order butterworth filter design, and thus 
	the cutoff frequencies must be 'pre-warped' to compensate for the non-linearity of the bilateral z-tranform. 
*/
void FilterBank::init() {
	float samplingPeriod = 1 / this->fsampleRate;
	float warpFreq;

	for (int i = 0; i < 3; ++i)
	{
		warpFreq = tan(cutoffFreq[i] * samplingPeriod / 2);
		float b =  pow(warpFreq,2);
		filterCoefficients[i][0][0] = b; //z^-2
		filterCoefficients[i][0][1] = 2 * b;
		filterCoefficients[i][0][2] = b;

		filterCoefficients[i][1][0] = 1 + sqrt(2 * b) + b; //z^-2
		filterCoefficients[i][1][1] = 2 * (b - 1);
		filterCoefficients[i][1][2] = 1 - sqrt(2 * b) + b;
	}
}

void FilterBank::reset() {

}


/*
	filters current input frame into multiple bands, and (TODO) calculates Mean Square values.
	MS values are summed
*/
void FilterBank::process() {
	const int numOfBands = 4;
	float filter_results[numOfBands][sizeof(m_poutBuffer) / sizeof(m_poutBuffer[0][0])];


	int L = sizeof(filterCoefficients[0][0]) / sizeof(filterCoefficients[0][0][0]);



	for (int i = 0; i < inumOfInputChannels; i++) 
	{ // for each channel
		int N = sizeof(this->m_pinBuffer[i]) / sizeof(this->m_pinBuffer[i][0]);
		float* temp_out = new float[N + 2];
		float* temp_in = new float[N + 2];

		for (int j = 0; j < numOfBands; ++j)
		{
			//applyFilter(this->m_pinBuffer[i], filter_results[i]);

			// The first two values are set to zero for input and output to acompany delays in the difference equation.
			// outIdx will then start at 2 to avoid negative indexing
			temp_in[0] = 0;
			temp_in[1] = 0;
			std::memcpy(&temp_in[2], this->m_pinBuffer[i], N * sizeof(float));

			temp_out[0] = 0;
			temp_out[1] = 0;

			for (int outIdx = 2; i < N; ++i) {
				temp_out[outIdx] = filterCoefficients[j][0][0] * temp_in[outIdx - 2] + filterCoefficients[j][0][1] * temp_in[outIdx - 1] + filterCoefficients[j][0][2] * temp_in[outIdx]
					- filterCoefficients[j][1][0] * temp_out[outIdx - 2] - filterCoefficients[j][1][1] * temp_out[outIdx - 1];
				temp_out[outIdx + 2] *= filterCoefficients[j][1][2];
			}
			// copy results to an output buffer
			std::memcpy(&filter_results[i], &temp_out[2], N * sizeof(float));

			// calculate mean square values and add to running sum
			//filter_MS[i] += 
		}
	}
}

/*
 Applies a 1-D filter to the input buffer.
*/
void FilterBank::applyFilter(float * inBuffer, float * outBuffer) {

	int L = sizeof(filterCoefficients[0][0]) / sizeof(filterCoefficients[0][0][0]);
	int N = sizeof(inBuffer) / sizeof(inBuffer[0]);
	float* in_lead = inBuffer;
	float* in_lag = in_lead;


	float* temp_out = new float[N + 2];
	float* temp_in = new float[N + 2];
	temp_out[0] = 0;
	temp_out[1] = 0;
	int outIdx = 0;

	while (1)
	{
		if (in_lead == nullptr || in_lag == nullptr)
		{
			// something went wrong
			int x = 0;
		}

		/*outBuffer[outIdx++] = std::inner_product(in_lag, in_lead, H, 0.0);*/

		temp_out[outIdx + 2] = filterCoefficients[0][0][0] * temp_in[outIdx] + filterCoefficients[0][0][1] * temp_in[outIdx] + filterCoefficients[0][0][2] * temp_in[outIdx]
			- filterCoefficients[0][1][0] * temp_in[outIdx] - filterCoefficients[0][1][1] * temp_in[outIdx];
		temp_out[outIdx + 2] *= filterCoefficients[0][1][2];

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
			/*outBuffer[outIdx++] = std::inner_product(in_lag, in_lead, H, 0.0);*/
			break;
		}
	}
	
	delete temp_out;
	delete temp_in;
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
