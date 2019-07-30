#pragma once

#include "Engine\DSPComponent.h"
class ClipDetection : public DSPComponent
{
public:
	ClipDetection(float sampleRate, int frameSize, int numOfChannels);
	~ClipDetection();


	virtual void init();
	virtual void process();
	virtual void reset();

	virtual void setBuffers(float** inBuffer, float** outBuffer);
	virtual void setInputBuffer(float ** inBuffer);
	virtual void setOutputBuffer(float ** outBuffer);
	virtual void processSubComponent();

private:

	float gain = 1.0;
	float max = 0;

};