/*
Brysiuk Audio Passthrough
A simple objected that just passes audio from the input buffer to the output buffer

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio


*/

#pragma once


#include "Engine\DSPComponent.h"
class Passthrough : public DSPComponent
{

private:
	virtual void processSubComponent();
public:
	Passthrough(float sampleRate, int frameSize, int numOfInputChannels, int numOfOutputChannels);
	~Passthrough();


	virtual void init();
	virtual void process();
	virtual void reset();

	virtual void setBuffers(float ** inBuffer, float ** outBuffer);
	virtual void setInputBuffer(float ** inBuffer);
	virtual void setOutputBuffer(float ** outBuffer);
	void setGain(float gain);
	float fgain;
};