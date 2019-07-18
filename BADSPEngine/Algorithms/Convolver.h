#pragma once
/*
Convolver block

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio

*/
#include "..\Engine\DSPComponent.h";
#include "..\Engine\CircularBuffer16ByteAligned.h";
#include "..\Third Party\pffft\pffft.h"
#include <algorithm>

class Convolver : public DSPComponent {
private:
	CircularBuffer16ByteAligned<float>* m_pfImpulseFFTBuffer;
	CircularBuffer16ByteAligned<float>* m_pCBInputFFTBuffer;
	CircularBuffer16ByteAligned<float>* inputConcatination;
	PFFFT_Setup* FFT = nullptr;


	float* FFTOutBuffer;
	float* iFFTInBuffer;
	float* FFTWorkBuffer;
	float* impulseFFTBuffer;

	float* FFTInputBuffer;
	float* iFFTOutput;
	int impulseSections;
	int N;

public:
	Convolver(float sampleRate, int frameSize, int numOfChannels);
	~Convolver();
	virtual void init();
	virtual void process();
	virtual void reset();

	virtual void setBuffers(float ** inBuffer, float ** outBuffer);
	virtual void setInputBuffer(float ** inBuffer);
	virtual void setOutputBuffer(float ** outBuffer);
	virtual void processSubComponent();
	void setImpulseFFTBuffer(CircularBuffer16ByteAligned<float>* impulseBuffer, int numOfSections);
};

