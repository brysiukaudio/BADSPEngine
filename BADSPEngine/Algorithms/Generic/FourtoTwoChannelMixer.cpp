#include "FourtoTwoChannelMixer.h"
#include "..\Engine\DSPComponent.h"
#include <cmath>

FourtoTwoChannelMixer::FourtoTwoChannelMixer(float sampleRate, int frameSize, int numOfInputChannels, int numOfOutputChannels){
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfInputChannels;
	this->inumOfOutputChannels = numOfOutputChannels;
}

FourtoTwoChannelMixer::~FourtoTwoChannelMixer() {

}


void FourtoTwoChannelMixer::init() {

}

void FourtoTwoChannelMixer::reset() {

}

void FourtoTwoChannelMixer::process() {
	for (int i = 0; i < iframeSize; i++) {
		this->m_poutBuffer[0][i] = ((*fGain1)*vocalBoost*this->m_pinBuffer[0][i]) + ((*fGain2)*guitarBoost*this->m_pinBuffer[1][i]) + ((*fGain3)*bassBoost*this->m_pinBuffer[2][i]) + ((*fGain4)*drumsBoost*this->m_pinBuffer[3][i]);
		this->m_poutBuffer[1][i] = ((*fGain1)*vocalBoost*this->m_pinBuffer[0][i]) + ((*fGain2)*guitarBoost*this->m_pinBuffer[1][i]) + ((*fGain3)*bassBoost*this->m_pinBuffer[2][i]) + ((*fGain4)*drumsBoost*this->m_pinBuffer[3][i]);
			}
		}

void FourtoTwoChannelMixer::setBuffers(float** inBuffer, float** outBuffer) {
	this->setInputBuffer(inBuffer);
	this->setOutputBuffer(outBuffer);
}

void FourtoTwoChannelMixer::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;
	

}
void FourtoTwoChannelMixer::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;

}

void FourtoTwoChannelMixer::setGain(float* Gain1, float* Gain2, float* Gain3, float* Gain4) {
	this->fGain1 = Gain1;
	this->fGain2 = Gain2;
	this->fGain3 = Gain3;
	this->fGain4 = Gain4;
}

void FourtoTwoChannelMixer::setVocalAdjust(float vocalAdjust) {
	this->vocalBoost = powf(10, vocalAdjust / 20);
}
void FourtoTwoChannelMixer::setGuitarAdjust(float guitarAdjust) {
	this->guitarBoost = powf(10, guitarAdjust / 20);
}
void FourtoTwoChannelMixer::setBassAdjust(float bassAdjust) {
	this->bassBoost = powf(10, bassAdjust / 20);
}
void FourtoTwoChannelMixer::setDrumAdjust(float drumAdjust) {
	this->drumsBoost = powf(10, drumAdjust / 20);
}

void FourtoTwoChannelMixer::processSubComponent() {

}
