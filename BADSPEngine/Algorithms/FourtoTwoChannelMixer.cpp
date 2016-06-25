#include "FourtoTwoChannelMixer.h"
#include "..\Engine\DSPComponent.h"

FourtoTwoChannelMixer::FourtoTwoChannelMixer(float sampleRate, int frameSize, int numOfInputChannels, int numOfOutputChannels){
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfInputChannels;
	this->inumOfOutputChannels = numOfOutputChannels;
}

FourtoTwoChannelMixer::~FourtoTwoChannelMixer() {

}

void process(){
}

void FourtoTwoChannelMixer::init() {

}

void FourtoTwoChannelMixer::reset() {

}

void FourtoTwoChannelMixer::process() {
	for (int i = 0; i < iframeSize; i++) {
		this->m_poutBuffer[0][i] = (fGain1*this->m_pinBuffer[0][i]) + (fGain2*this->m_pinBuffer[1][i]) + (fGain3*this->m_pinBuffer[2][i]) + (fGain4*this->m_pinBuffer[3][i]);
		this->m_poutBuffer[1][i] = (fGain1*this->m_pinBuffer[0][i]) + (fGain2*this->m_pinBuffer[1][i]) + (fGain3*this->m_pinBuffer[2][i]) + (fGain4*this->m_pinBuffer[3][i]);
			}
		}


void FourtoTwoChannelMixer::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;
	

}
void FourtoTwoChannelMixer::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;

}

void FourtoTwoChannelMixer::setGain(float Gain1, float Gain2, float Gain3, float Gain4) {
	this->fGain1 = Gain1;
	this->fGain2 = Gain2;
	this->fGain3 = Gain3;
	this->fGain4 = Gain4;
}

void FourtoTwoChannelMixer::processSubComponent() {

}
