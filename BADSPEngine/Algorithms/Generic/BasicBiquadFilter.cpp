#include "BasicBiquadFilter.h"
#include "FilterDesign.h"


BasicBiquadFilter::BasicBiquadFilter(float sampleRate, int frameSize, int numOfChannels)
{
		
	assert(numOfChannels < 3 && numOfChannels > 0);

	inumOfInputChannels = numOfChannels;
	inumOfOutputChannels = numOfChannels;
	fsampleRate = sampleRate;
	inverseSampleRate = 1 / sampleRate;
	iframeSize = frameSize;
	b[0] = 1;
	b[1] = 0;
	b[2] = 0;
	a[0] = 0;
	a[1] = 0;
	states = new float*[numOfChannels]();
	for (int i = 0; i < numOfChannels; i++)
	{
		states[i] = new float[2]();
	}
	cutOffFrequency = 20000;
	type = LOWPASS;
	enabled = false;
}


BasicBiquadFilter::~BasicBiquadFilter()
{
}


void BasicBiquadFilter::init()
{

}
void BasicBiquadFilter::process()
{
	float X = 0;
	float Y = 0;
	for (int i = 0; i < iframeSize; i++)
	{
		X = m_pinBuffer[0][i];
		Y = states[0][1] + b[0] * X;
		states[0][1] = states[0][2] - a[0] * Y + b[1] * X;
		states[0][2] = -1 * a[1] * Y + b[2] * X;

		m_poutBuffer[0][i] = Y;

		if (inumOfInputChannels > 1)
		{
			X = m_pinBuffer[1][i];
			Y = states[1][1] + b[0] * X;
			states[1][1] = states[1][2] - a[0] * Y + b[1] * X;
			states[1][2] = -1 * a[1] * Y + b[2] * X;
			m_poutBuffer[1][i] = Y;
		}
	}
}
void BasicBiquadFilter::reset()
{

}

void BasicBiquadFilter::setBuffers(float** inBuffer, float** outBuffer)
{
	assert(inBuffer != nullptr && inBuffer[0] != nullptr);
	assert(outBuffer != nullptr && outBuffer[0] != nullptr);

	assert(!(inumOfInputChannels > 1 && inBuffer[1] == nullptr));
	assert(!(inumOfOutputChannels > 1 && outBuffer[1] == nullptr));

	m_pinBuffer = inBuffer;
	m_poutBuffer = outBuffer;

}
void BasicBiquadFilter::setInputBuffer(float ** inBuffer)
{
	assert(inBuffer != nullptr && inBuffer[0] != nullptr);
	assert(!(inumOfInputChannels > 1 && inBuffer[1] == nullptr));
	m_pinBuffer = inBuffer;
}
void BasicBiquadFilter::setOutputBuffer(float ** outBuffer)
{
	assert(outBuffer != nullptr && outBuffer[0] != nullptr);
	assert(!(inumOfOutputChannels > 1 && outBuffer[1] == nullptr));
	m_poutBuffer = outBuffer;
}
void BasicBiquadFilter::processSubComponent()
{

}

void BasicBiquadFilter::setParameter(int paramID, float value)
{
	switch (paramID)
	{
	case Enable:
		enabled = (bool)value;
		break;
	case CutoffFrequency:
		cutOffFrequency = value;
		if (value > fsampleRate * 0.5) cutOffFrequency = fsampleRate* 0.5;
		FilterDesign::designLPHPBQFilter(b, a, cutOffFrequency * inverseSampleRate, type == HIGHPASS);
		break;
	case FilterType:
		type = (int)value;
		if (value > HIGHPASS || value < LOWPASS) type = LOWPASS;
		FilterDesign::designLPHPBQFilter(b, a, cutOffFrequency * inverseSampleRate, type == HIGHPASS);
		break;
	default:
		break;
	}
}
