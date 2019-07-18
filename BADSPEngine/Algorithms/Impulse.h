/*
This block read the impulse wave file and create the impulse FFT in blocks for use by the Convolver
It comes before the Convolver in the signal chain so that it can mute incoming audio when the impulse file
is changed

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio

*/
#pragma once

//#include "../JuceLibraryCode/JuceHeader.h"
#include "..\Engine\DSPComponent.h"
#include "..\Third Party\pffft\pffft.h"
#include "..\Engine\CircularBuffer16ByteAligned.h"
#include "Convolver.h"

class Impulse : public DSPComponent {
private:
	bool newFile;
	/*ScopedPointer<File> file;*/
	float gain = 1;


	CircularBuffer16ByteAligned<float>* m_pfImpulseFFTBuffer = nullptr;
	float* inputWithZeros = nullptr;
	PFFFT_Setup* FFTSetup = nullptr;
	

	float* FFTOutBuffer = nullptr;
	float* FFTWorkBuffer = nullptr;
	int N = 0;
	CircularBuffer16ByteAligned<float>* testImpulse = nullptr;

	Convolver* m_pConvolverBlock = nullptr;

public:
	Impulse(float sampleRate, int frameSize, int numOfInChannels, int numOfOutChannels);
	~Impulse();
	virtual void init();
	virtual void process();
	virtual void reset();

	virtual void setBuffers(float ** inBuffer, float ** outBuffer);
	virtual void setInputBuffer(float ** inBuffer);
	virtual void setOutputBuffer(float ** outBuffer);
	virtual void processSubComponent();

	void addBlockFFT(float* inAudioBlock);
	void setConvolerPtr(Convolver* convolverBlock);

	/*
	Prepares the Component to take in a new impulse.
	In: The length of the file in samples, and the sample Rate of the File
	Out: Returns the number of Blocks need to represent the impulse
	*/
	int prepareForNewImpulse(int filelength, float fileSampleRate);
	void finalizeImpulse(int numberOfSections);
};
