/*
Brysiuk Audio Analyzer
This Block is the parent block to the filterbank and the rms blocks does the logic for assigning gains

Created 10/10/2015 by Ben Brysiuk
Copyright BrysiukAudio


*/

#include <cstdlib>
#include <cstdio>
#include "Analyzer.h"
#include "..\Engine\DSPComponent.h"

Analyzer::Analyzer(float sampleRate, int frameSize, int numOfChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfChannels;
	this->inumOfOutputChannels = numOfChannels;
	this->filterBlock = new FilterBank(sampleRate, frameSize, numOfChannels, numOfChannels);
	this->rmsBlock = new RMS(sampleRate, frameSize, numOfChannels*5);
	for (int i = 0; i < numOfChannels * 4; i++) {
		m_InternalBuffers[i] = new float[frameSize];
	}

}

Analyzer::~Analyzer() {
	delete this->rmsBlock;
	this->rmsBlock = nullptr;
	delete this->filterBlock;
	this->filterBlock = nullptr;
	for (int i = 0; i < inumOfInputChannels * 4; i++) {
		delete [] m_InternalBuffers[i];
	}
	delete [] m_InternalBuffers;
}

void Analyzer::init() {

}

void Analyzer::reset() {

}

void Analyzer::process() {
	float bassvVocals = 0;
	float guitarvVocals = 0;
	float drumsvVocals = 0;
	processSubComponent();
	if (m_bRecordComplete) {
		//Get RMS Values
		rmsBlock->getRMS(this->m_pfRMSValues);

		//Calculate relative values
		bassvVocals = m_pfRMSValues[bFullRange] / m_pfRMSValues[vFullRange];
		guitarvVocals = m_pfRMSValues[gFullRange] / m_pfRMSValues[vFullRange];
		drumsvVocals = m_pfRMSValues[dFullRange] / m_pfRMSValues[vFullRange];
		
		//Set Gain based on relative values and the modifier

		*m_pfBassGain = m_fBassModifier / bassvVocals;
		*m_pfDrumGain = m_fDrumsModifier / drumsvVocals;
		*m_pfGuitarGain = m_fGuitarModifier / guitarvVocals;

		//Get Filter Values

		//Calulate Relative Values

		//Modify Gain based on relative values and modifiers

		m_bRecordComplete = false;
	}
}


void Analyzer::setBuffers(float ** inBuffer, float ** outBuffer) {
	this->m_pinBuffer = inBuffer;
	this->m_poutBuffer = outBuffer;
	this->rmsBlock->setBuffers(inBuffer, outBuffer);
	this->filterBlock->setBuffers(inBuffer, outBuffer);
	
}
void Analyzer::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;
	this->filterBlock->setInputBuffer(inBuffer);
	for (int i = 0; i < inumOfInputChannels*5; i++) {
		if (i < 4) {
			this->m_CombinedBuffers[i] = this->m_pinBuffer[i];
		}
		else {
			this->m_CombinedBuffers[i] = m_InternalBuffers[i - 4];
		}
		
	}
	this->rmsBlock->setInputBuffer(this->m_CombinedBuffers);
}

void Analyzer::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;
	this->setOutputBuffer();
	
}
void Analyzer::setOutputBuffer() {
	this->filterBlock->setOutputBuffer(m_InternalBuffers);
}

void Analyzer::processSubComponent() {
	this->rmsBlock->process();
	this->filterBlock->process();
}

void Analyzer::setRecordComplete(bool recordComplete) {
	this->m_bRecordComplete = recordComplete;
}
void Analyzer::setGainOutputs(float* vocals, float* guitar, float* bass, float* drums) {
	this->m_pfVocalGain = vocals;
	this->m_pfBassGain = bass;
	this->m_pfGuitarGain = guitar;
	this->m_pfDrumGain = drums;
}