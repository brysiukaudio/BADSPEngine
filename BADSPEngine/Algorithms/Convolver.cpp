#include "Convolver.h"


Convolver::Convolver(float sampleRate, int frameSize, int numOfChannels) {
	this->fsampleRate = sampleRate;
	this->iframeSize = frameSize;
	this->N = frameSize * 2;
	this->inumOfInputChannels = numOfChannels;
	this->inumOfOutputChannels = numOfChannels;
	this->m_pCBInputFFTBuffer = new CircularBuffer16ByteAligned<float>(N);
	this->inputConcatination = new CircularBuffer16ByteAligned<float>(N);
	this->FFTOutBuffer = (float*)pffft_aligned_malloc(sizeof(float)*N);

	//this->FFTOutBuffer = fftw_alloc_complex(frameSize + 1);// (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*(2*frameSize));
	this->FFTWorkBuffer = (float*)pffft_aligned_malloc(sizeof(float)*N);
	this->impulseFFTBuffer = (float*)pffft_aligned_malloc(sizeof(float)*N);
	//this->FFTMultiplyBuffer = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*(frameSize + 1));

	this->iFFTInBuffer = (float*)pffft_aligned_malloc(sizeof(float)*N);
	//this->iFFTInBuffer = new fftw_complex[(frameSize + 1)];
	this->FFTInputBuffer = (float*)pffft_aligned_malloc(sizeof(float)*N);
	this->iFFTOutput = (float*)pffft_aligned_malloc(sizeof(float)*N);

	this->FFT = pffft_new_setup(N, PFFFT_REAL);
	
}
Convolver::~Convolver() {
	delete m_pCBInputFFTBuffer;
	m_pCBInputFFTBuffer = nullptr;
	delete inputConcatination;
	inputConcatination = nullptr;
	//delete[] FFTOutBuffer;
	pffft_aligned_free(FFTOutBuffer);
	FFTOutBuffer = nullptr;
	pffft_aligned_free(FFTWorkBuffer);
	//fftw_free(FFTMultiplyBuffer);
	FFTWorkBuffer = nullptr;
	//delete[] iFFTInBuffer;
	pffft_aligned_free(iFFTInBuffer);
	iFFTInBuffer = nullptr;
	pffft_aligned_free(FFTInputBuffer);
	FFTInputBuffer = nullptr;
	pffft_aligned_free(iFFTOutput);
	iFFTOutput = nullptr;
	m_pfImpulseFFTBuffer = nullptr;
	pffft_destroy_setup(this->FFT);
}
void Convolver::init() {

}
void Convolver::process() {
	inputConcatination->addFrames(m_pinBuffer[0], iframeSize);
	inputConcatination->getFramesWithDelay(FFTInputBuffer, iframeSize*2, iframeSize * 2);
	pffft_transform(this->FFT, this->FFTInputBuffer, this->FFTOutBuffer, this->FFTWorkBuffer, PFFFT_FORWARD);

	if (m_pCBInputFFTBuffer != nullptr && m_pfImpulseFFTBuffer != nullptr) {
		this->m_pCBInputFFTBuffer->addFrames(FFTOutBuffer, N);
		memset(iFFTInBuffer, 0, sizeof(float)*N);
		
		for (int i = 0; i < impulseSections; i++) {
			this->m_pCBInputFFTBuffer->getFramesWithDelay(FFTOutBuffer, (N)*(i + 1), (N));
			this->m_pfImpulseFFTBuffer->getFramesWithDelay(this->impulseFFTBuffer, (N)*(impulseSections - i), (N));
			pffft_zconvolve_accumulate(this->FFT, impulseFFTBuffer, FFTOutBuffer, iFFTInBuffer, 1.0);
		}

		pffft_transform(this->FFT, iFFTInBuffer, iFFTOutput, this->FFTWorkBuffer, PFFFT_BACKWARD);
		for (int i = 0; i < (iframeSize) * 2; i++) {
			iFFTOutput[i] = iFFTOutput[i] / (N);
		}
		//memcpy(&(iFFTOutput[iframeSize]), m_poutBuffer[0], sizeof(float)*iframeSize);
		std::copy(iFFTOutput + iframeSize, iFFTOutput + iframeSize * 2, m_poutBuffer[0]);
	}


}
void Convolver::reset() {

}

void Convolver::processSubComponent(){

}

void Convolver::setBuffers(float ** inBuffer, float ** outBuffer) {
	this->setInputBuffer(inBuffer);
	this->setOutputBuffer(outBuffer);
}
void Convolver::setInputBuffer(float ** inBuffer) {
	this->m_pinBuffer = inBuffer;
}
void Convolver::setOutputBuffer(float ** outBuffer) {
	this->m_poutBuffer = outBuffer;
}

void Convolver::setImpulseFFTBuffer(CircularBuffer16ByteAligned<float>* impulseBuffer, int numOfSections){
	if (impulseBuffer != nullptr) {
		m_pfImpulseFFTBuffer = impulseBuffer;
		impulseSections = numOfSections;
		m_pCBInputFFTBuffer = new CircularBuffer16ByteAligned<float>((iframeSize*2) * numOfSections);
	}
	else {
		m_pfImpulseFFTBuffer = nullptr;
		delete m_pCBInputFFTBuffer;
		m_pCBInputFFTBuffer = nullptr;
	}
	
}