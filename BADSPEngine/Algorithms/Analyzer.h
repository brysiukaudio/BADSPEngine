/*
Brysiuk Audio Analyzer
This Block is the parent block to the filterbank and the rms blocks does the logic for assigning gains

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio


*/

#pragma once


#include "..\Engine\DSPComponent.h"
#include "..\Algorithms\FilterBank.h"
#include "..\Algorithms\RMS.h"
class Analyzer : public DSPComponent
{

private:
	enum rmsValueTypes
	{
		fullRange,
		lowFreq,
		lowMidFreq,
		highMidFreq,
		highFreq,

		numofTypes,
	};
	virtual void processSubComponent();
	FilterBank* filterBlock = nullptr;
	RMS* rmsBlock = nullptr;
	bool m_bRecordComplete = false;
	
	//All the RMS values for each track the order being F
	float m_pfVocalRMSValues[numofTypes];
	float m_pfGuitarRMSValues[numofTypes];
	float m_pfBassRMSValues[numofTypes];
	float m_pfDrumsRMSValues[numofTypes];

	//Modifier Values as Obtained from the Research
	const float m_fBassModifier = 0.5;
	const float m_fGuitarModifier = 0.5;
	const float m_fDrumsModifier = 0.5;

	float* m_pfVocalGain;
	float* m_pfBassGain;
	float* m_pfGuitarGain;
	float* m_pfDrumGain;

	float* m_InternalBuffers[16];
public:
	Analyzer(float sampleRate, int frameSize, int numOfChannels);
	~Analyzer();


	virtual void init();
	virtual void process();
	virtual void reset();

	virtual void setBuffers(float ** inBuffer, float ** outBuffer);
	virtual void setInputBuffer(float ** inBuffer);
	virtual void setOutputBuffer(float ** outBuffer);
	void setRecordComplete(bool recordComplete);
	void setGainOutputs(float* vocals, float* guitar, float* bass, float* drums);
};