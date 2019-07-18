#include "Impulse.h"


Impulse::Impulse(float sampleRate, int frameSize, int numOfInChannels, int numOfOutChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->N = frameSize * 2;
	this->inumOfInputChannels = numOfInChannels;
	this->inumOfOutputChannels = numOfOutChannels;


	this->FFTOutBuffer = (float*)pffft_aligned_malloc(sizeof(float)*(N));
	memset(FFTOutBuffer, 0, sizeof(float)*N);
	this->inputWithZeros = (float*)pffft_aligned_malloc(sizeof(float)*(N));
	memset(inputWithZeros, 0, sizeof(float)*N);
	this->FFTWorkBuffer = (float*)pffft_aligned_malloc(sizeof(float)*(N));
	memset(FFTWorkBuffer, 0, sizeof(float)*N);
	this->FFTSetup = pffft_new_setup(N, PFFFT_REAL);


	testImpulse = new CircularBuffer16ByteAligned<float>(2 * N);
	float* testBuffer = (float*)pffft_aligned_malloc(sizeof(float)*(N));

	for (int i = 0; i < N; i += 2) 
	{
		testBuffer[i] = 1;
		testBuffer[i + 1] = 0;
	}
	
	float* outTestBuffer = (float*)pffft_aligned_malloc(sizeof(float)*(N));
	pffft_zreorder(this->FFTSetup, testBuffer, outTestBuffer, PFFFT_BACKWARD);

	testImpulse->addFrames(outTestBuffer, N);

	pffft_aligned_free(testBuffer);
	pffft_aligned_free(outTestBuffer);
}
Impulse::~Impulse() {

	pffft_aligned_free(FFTOutBuffer);
	FFTOutBuffer = nullptr;
	pffft_aligned_free(inputWithZeros);
	inputWithZeros = nullptr;
	delete m_pfImpulseFFTBuffer;
	m_pfImpulseFFTBuffer = nullptr;
	if (testImpulse != nullptr) delete testImpulse;
	testImpulse = nullptr;
	pffft_destroy_setup(this->FFTSetup);
}
void Impulse::init() {

}
void Impulse::process() {
	for (int i = 0; i < inumOfInputChannels; i++) {
		for (int j = 0; j < iframeSize; j++) {
			m_poutBuffer[i][j] = gain*m_pinBuffer[i][j];
		}
	}
}
void Impulse::reset() {

}

void Impulse::setBuffers(float ** inBuffer, float ** outBuffer) {
	this->setInputBuffer(inBuffer);
	this->setOutputBuffer(outBuffer);
}
void Impulse::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;
}
void Impulse::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;
}


int Impulse::prepareForNewImpulse(int filelength, float fileSampleRate)
{
	gain = 0;
	if (m_pfImpulseFFTBuffer != nullptr) {
		delete m_pfImpulseFFTBuffer;
		m_pfImpulseFFTBuffer = nullptr;
	}
	m_pConvolverBlock->setImpulseFFTBuffer(nullptr, 0);
	int length = ceil((float)(filelength *(fsampleRate/fileSampleRate)));
	int numberOfSections = ceil((float)length / iframeSize);
	length = numberOfSections * N;
	m_pfImpulseFFTBuffer = new CircularBuffer16ByteAligned<float>(length);
	return numberOfSections;
}

void Impulse::addBlockFFT(float* inAudioBlock) {
	


		std::copy(inAudioBlock, inAudioBlock + (iframeSize-1), inputWithZeros);
		pffft_transform(FFTSetup, inputWithZeros, FFTOutBuffer, FFTWorkBuffer, PFFFT_FORWARD);
		m_pfImpulseFFTBuffer->addFrames(FFTOutBuffer, N);
		//count += 1;
	//}
	
	//transport.stop();
	//transport.setSource(0, 0, nullptr, fsampleRate);
}

void Impulse::finalizeImpulse(int numberOfSections)
{
	m_pConvolverBlock->setImpulseFFTBuffer(m_pfImpulseFFTBuffer, numberOfSections);
	gain = 1;
}

void Impulse::processSubComponent() {

}

void Impulse::setConvolerPtr(Convolver* convolverBlock) {
	m_pConvolverBlock = convolverBlock;
}

