#pragma once
/*
AutoMixer 4 to 2 channel mixer


Created 02/06/2015 by Chad Bartlett


*/
#pragma once


#include "..\Engine\DSPComponent.h"
class FourtoTwoChannelMixer : public DSPComponent
{

private:
	virtual void processSubComponent();
public:
	FourtoTwoChannelMixer(float sampleRate, int frameSize, int numOfInputChannels, int numOfOutputChannels);
	~FourtoTwoChannelMixer();

	virtual void init();
	virtual void process();
	virtual void reset();

	virtual void setBuffers(float** inBuffer, float** outBuffer);
	virtual void setInputBuffer(float ** inBuffer);
	virtual void setOutputBuffer(float ** outBuffer);
	void setGain(float* Gain1, float* Gain2, float* Gain3, float* Gain4);

	void setVocalAdjust(float vocalAdjust);
	void setGuitarAdjust(float guitarAdjust);
	void setBassAdjust(float bassAdjust);
	void setDrumAdjust(float drumAdjust);


	float* fGain1;
	float* fGain2;
	float* fGain3;
	float* fGain4;

	float vocalBoost = 1;
	float guitarBoost = 1;
	float bassBoost = 1;
	float drumsBoost = 1;

};