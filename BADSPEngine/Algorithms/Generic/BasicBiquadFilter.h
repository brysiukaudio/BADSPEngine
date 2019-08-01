#pragma once

#include "Engine\DSPComponent.h"

class BasicBiquadFilter : public DSPComponent
{
public:

	enum
	{
		LOWPASS,
		HIGHPASS,
	} FilterTypes;

	enum
	{
		Enable,
		CutoffFrequency,
		FilterType,
	} Parameters;

	BasicBiquadFilter(float sampleRate, int frameSize, int numOfChannels);
	~BasicBiquadFilter();


	virtual void init();
	virtual void process();
	virtual void reset();

	virtual void setBuffers(float** inBuffer, float** outBuffer);
	virtual void setInputBuffer(float ** inBuffer);
	virtual void setOutputBuffer(float ** outBuffer);
	virtual void processSubComponent();

	void setParameter(int paramID, float value);

private:
	int cutOffFrequency;
	int type;
	float inverseSampleRate;
	bool enabled;
	float b[3];
	float a[2]; 
	float** states;

};

