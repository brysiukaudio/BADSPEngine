#include "Record.h"
#include "..\Engine\DSPComponent.h"

Record::Record(float sampleRate, int frameSize, int numOfChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfChannels;
	this->inumOfOutputChannels = numOfChannels;
}

Record::~Record() {

}

void Record::init() {

}

void Record::reset() {

}

void Record::process() {
	const char* filename = "C:\test.wav";
	
	if (1 /* If the User has selected record */ ) {
		SoundHeader header;
		header.setHighMono();
		header.setChannels(this->inumOfInputChannels);
		header.setSrate(int(fsampleRate));
		SoundFileWrite outsound(filename, header);

		int i, channel;
		for (i = 0; i<iframeSize; i++) {
			for (channel = 0; channel < this->inumOfInputChannels; channel++) {
				outsound.writeSampleDouble(this->m_pinBuffer[channel][i]);
			}
		}

		outsound.close();
	}

	if (1 /*If the User has selected play back*/) {

		SoundHeader header;
		//header.SoundHeader(filename);
		SoundFileRead* input = new SoundFileRead(filename,0, iframeSize);
	}

}


void Record::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;


}
void Record::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;

}

void Record::processSubComponent() {

}