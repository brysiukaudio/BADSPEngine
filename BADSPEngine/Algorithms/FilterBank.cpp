/*
Mandryk Audio Filter Bank
Passes the input buffer through a filter bank and outputs multiple buffers for each band

Created 15/06/2016 by Kaegan Mandryk
Copyright MandrykAudio


*/


#include <algorithm>
#include "FilterBank.h"
#include "..\Engine\DSPComponent.h"

#define PI 3.14159

FilterBank::FilterBank(float sampleRate, int frameSize, int numOfInputChannels, int numOfOutputChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfInputChannels;
	this->inumOfOutputChannels = numOfOutputChannels;


	/*
	Constructs the filter coefficients based off of the preset cutoff frequencies and the given sampling rate.
	The given filter is based off of the continuous time domain 2nd order butterworth filter design, and thus
	the cutoff frequencies must be 'pre-warped' to compensate for the non-linearity of the bilateral z-tranform.
	*/

	float samplingPeriod = 1 / this->fsampleRate;
	float warpFreq;

	for (int i = 0; i < 3; ++i)
	{
		warpFreq = tan(2*PI*cutoffFreq[i] * samplingPeriod / 2);
		float b = pow(warpFreq, 2);
		filterCoefficients[i][0][0] = b; //z^-2
		filterCoefficients[i][0][1] = 2 * b;
		filterCoefficients[i][0][2] = b;

		filterCoefficients[i][1][0] = 1 + sqrt(2 * b) + b; //z^-2
		filterCoefficients[i][1][1] = 2 * (b - 1);
		filterCoefficients[i][1][2] = 1 - sqrt(2 * b) + b;


	}

	// initialize the filterResults 3-D array ( [inumOfInputChannels][numOfBands][iframeSize] )

	filterResults = new float**[inumOfInputChannels];
	for (int i = 0; i < inumOfInputChannels; ++i)
	{
		filterResults[i] = new float*[numOfBands];
		for (int j = 0; j < numOfBands; ++j)
		{
			filterResults[i][j] = new float[iframeSize];
			filterResults[i][j][2] = 12;
		}
		// init first inputs
		firstInput[i] = 0;
		secondInput[i] = 0;
	}
	for(int i = 0; i < inumOfInputChannels*numOfFilters; ++i)
	{
		// init first outputs
		firstOutput[i] = 0;
		secondOutput[i] = 0;
	}
}

FilterBank::~FilterBank() {

	for (int i = 0; i < inumOfInputChannels; ++i)
	{
		filterResults[i] = new float*[numOfBands];
		for (int j = 0; j < numOfBands; ++j)
		{
			delete[] filterResults[i][j];
		}
		delete[] filterResults[i];
	}
	delete[] filterResults;
}


void FilterBank::init() {


}

void FilterBank::reset() {

}


/*
	filters current input frame into multiple bands, and (TODO) calculates Mean Square values.
	MS values are summed
*/


/*


NOTE: Currently testing with impulse responses on each channel. first two values of the output appear correct, values after deviate
from the impulse response as described in matlab implementation.

still a problem with writing to to filterResults buffer array.



*/
void FilterBank::process() {
	if (calibrationMode)
	{
		int N = this->iframeSize;
		float* temp_out = new float[N];
		float* temp_in = new float[N];

		for (int i = 0; i < inumOfInputChannels; i++)
		{ // for each channel


			std::memcpy(&temp_in[0], this->m_pinBuffer[i], N * sizeof(float));

			for (int j = 0; j < numOfFilters; ++j)
			{



				// firstInput refers to x[n-2], secondInput to x[n-1], same for outputs

				// compute y[0]
				temp_out[0] = filterCoefficients[j][0][0] * firstInput[i] + filterCoefficients[j][0][1] * secondInput[i] + filterCoefficients[j][0][2] * temp_in[0]
					- filterCoefficients[j][1][2] * firstOutput[3 * i + j] - filterCoefficients[j][1][1] * firstOutput[3 * i + j];
				temp_out[0] /= filterCoefficients[j][1][0];


				//compute y[1]
				temp_out[1] = filterCoefficients[j][0][0] * secondInput[i] + filterCoefficients[j][0][1] * temp_in[0] + filterCoefficients[j][0][2] * temp_in[1]
					- filterCoefficients[j][1][2] * firstOutput[3 * i + j] - filterCoefficients[j][1][1] * temp_out[0];
				temp_out[1] /= filterCoefficients[j][1][0];

				for (int outIdx = 2; outIdx < N; ++outIdx) {
					temp_out[outIdx] = filterCoefficients[j][0][0] * temp_in[outIdx - 2] + filterCoefficients[j][0][1] * temp_in[outIdx - 1] + filterCoefficients[j][0][2] * temp_in[outIdx]
						- filterCoefficients[j][1][2] * temp_out[outIdx - 2] - filterCoefficients[j][1][1] * temp_out[outIdx - 1];
					temp_out[outIdx] /= filterCoefficients[j][1][0];
				}
				// copy results to an output buffer

				memcpy(&filterResults[i][j][0], &temp_out[0], N * sizeof(float));
				
				// last two values of the output and input sequences are copied to class variables, to be carried over to the next frame
				firstOutput[3 * i + j] = temp_out[N - 2];
				secondOutput[3 * i + j] = temp_out[N - 1];

			}
			float* addy = &filterResults[i][0][0];
			addy = &filterResults[i][1][0];
			addy = &filterResults[i][2][0];

			// last two values of the output and input sequences are copied to class variables, to be carried over to the next frame
			firstInput[i] = temp_in[N - 2];
			secondInput[i] = temp_in[N - 1];

		}

		/*

		use a filter bank approach to create each of the bands

		*/

		float* lowBand = new float[N];
		float* midLowBand = new float[N];
		float* midHighBand = new float[N];
		float* highBand = new float[N];
		for (int i = 0; i < inumOfInputChannels; i++)
		{
			for (int Idx = 0; Idx < N; ++Idx) {
				lowBand[Idx] = filterResults[i][0][Idx];
				midLowBand[Idx] = filterResults[i][1][Idx] - filterResults[i][0][Idx];
				midHighBand[Idx] = filterResults[i][2][Idx] - filterResults[i][1][Idx];
				highBand[Idx] = temp_in[Idx] - filterResults[i][2][Idx];
			}

			memcpy(&this->m_poutBuffer[4 * i][0], &lowBand[0], N * sizeof(float));
			memcpy(&this->m_poutBuffer[4 * i + 1][0], &midLowBand[0], N * sizeof(float));
			memcpy(&this->m_poutBuffer[4 * i + 2][0], &midHighBand[0], N * sizeof(float));
			memcpy(&this->m_poutBuffer[4 * i + 3][0], &highBand[0], N * sizeof(float));
		}

		delete[] lowBand;
		delete[] midLowBand;
		delete[] midHighBand;
		delete[] highBand;

		delete[] temp_in;
		delete[] temp_out;
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
void FilterBank::setCalibrationMode(bool mode) {
	this->calibrationMode = mode;
}

void FilterBank::processSubComponent() {

}
