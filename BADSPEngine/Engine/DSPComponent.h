/*
Brysiuk Audio DSP component
Base class for all DSP components

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio


*/

#pragma once
#include "EngineDefinitions.h"
class DSPComponent {
protected:
	double ** m_pinBuffer;
	double ** m_poutBuffer;
	float fsampleRate;
	int	  iframeSize;
	int	  inumOfInputChannels;
	int	  inumOfOutputChannels;
	virtual void processSubComponent() = 0;
public:

	virtual ~DSPComponent() {};
	virtual void init() = 0;
	virtual void process() = 0;
	virtual void reset() = 0;

	virtual void setBuffers(float ** inBuffer, float ** outBuffer) = 0;
	virtual void setInputBuffer(float ** inBuffer) = 0;
	virtual void setOutputBuffer(float ** outBuffer) = 0;
};