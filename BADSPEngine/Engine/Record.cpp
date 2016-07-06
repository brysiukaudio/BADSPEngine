#include "Record.h"
#include "..\Engine\DSPComponent.h"

Record::Record(float sampleRate, int frameSize, int numOfChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->inumOfInputChannels = numOfChannels;
	this->inumOfOutputChannels = numOfChannels;
	this->inputname = "guitar.wav";
	this->insound = new SoundFileRead(inputname);
	this->header = *insound;
}

Record::~Record() {

}

void Record::init() {

}

void Record::reset() {

}

void Record::process() {
	const char* filename = "test.wav";
	
	if (0 /* If the User has selected record */ ) {
		SoundHeader header;
		header.setHighMono();
		header.setChannels(this->inumOfInputChannels);
		header.setSrate(int(fsampleRate));
		SoundFileWrite outsound(filename, header);

		int i, channel;
		for (i = 0; i<this->iframeSize; i++) {
			for (channel = 0; channel < this->inumOfInputChannels; channel++) {

				outsound.writeSampleDouble(this->m_pinBuffer[channel][i]);

			} /*End for*/

		} /*End for*/

		outsound.close();

	} /*End if*/

	if (1 /*If the User has selected play back*/) {
		int i, channel;
		for (i = 0; i < this->iframeSize; i++) {
			for (channel = 0; channel < 2/*this->inumOfInputChannels*/; channel++) {
				
				m_poutBuffer[channel][i] = this->insound->getCurrentSampleDouble(channel);

			} /*End for*/

			insound->incrementSample();

		} /*End for*/

	} /*End if*/
}


void Record::setBuffers(float ** inBuffer, float ** outBuffer)
{
}

void Record::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;


}
void Record::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;

}

void Record::setGain(float gain)
{
}

void Record::processSubComponent() {

}