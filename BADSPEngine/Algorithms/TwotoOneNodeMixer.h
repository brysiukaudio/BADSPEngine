#pragma once
/*
AutoMixer 4 to 2 channel mixer


Created 02/06/2015 by Chad Bartlett


*/
#pragma once


#include "..\Engine\DSPComponent.h"
class TwotoOneNodeMixer : public DSPComponent
{

private:
	virtual void processSubComponent();
public:
	TwotoOneNodeMixer(float sampleRate, int frameSize, int numOfInputChannelsPerNode, int numOfOutputChannels);
	~TwotoOneNodeMixer();

	virtual void init();
	virtual void process();
	virtual void reset();

	virtual void setBuffers(float** inBuffer, float** outBuffer);
	virtual void setInputBuffer(float ** inBuffer);
	void setInputBuffer(float ** inNode1, float** inNode2);
	virtual void setOutputBuffer(float ** outBuffer);
	void setNodeGain(float Gain1, float Gain2);
	void setGlobalGain(float globalGain);

	float** m_pfInBuffer2 = nullptr;

	float fGain1 = 0.5;
	float fGain2 = 0.5;
	float fGlobalGain = 1;




};