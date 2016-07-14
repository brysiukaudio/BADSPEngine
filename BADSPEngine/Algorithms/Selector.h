#pragma once

#include "..\Engine\DSPComponent.h"
class Selector : public DSPComponent
{
public:
	Selector(float sampleRate, int frameSize, int numOfChannels);
	~Selector();


	virtual void init();
	virtual void process();
	virtual void reset();

	virtual void setBuffers(float** inBuffer, float** outBuffer);
	virtual void setBuffers(float** inBufferOne, float** inBufferTwo, float** outBuffer);
	virtual void setInputBuffer(float ** inBuffer);
	virtual void setInputBuffer(float ** inBufferOne, float** inBufferTwo);
	virtual void setOutputBuffer(float ** outBuffer);
	void setIsPlaying(bool isPlaying);

private:
	float** m_pInBufferTwo;

	bool	m_bIsPlaying;
	bool	m_bIsLiveAudio;

};

