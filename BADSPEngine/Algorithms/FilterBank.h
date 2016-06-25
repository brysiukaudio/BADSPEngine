/*
Mandryk Audio Filter Bank
Passes the input buffer through a filter bank and outputs multiple buffers for each band

Created 15/06/2016 by Kaegan Mandryk
Copyright MandrykAudio


*/

#pragma once


#include "..\Engine\DSPComponent.h"
class FilterBank : public DSPComponent
{

private:
	virtual void processSubComponent();
public:
	FilterBank(float sampleRate, int frameSize, int numOfInputChannels, int numOfOutputChannels);
	~FilterBank();


	virtual void init();
	virtual void process();
	virtual void reset();

	virtual void setBuffers(float ** inBuffer, float ** outBuffer);
	virtual void setInputBuffer(float ** inBuffer);
	virtual void setOutputBuffer(float ** outBuffer);
	void setGain(float gain);
	float fgain;
};