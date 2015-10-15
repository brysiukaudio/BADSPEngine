#pragma once
#include "EngineDefinitions.h"
class Component {
private:
	float * m_pinBuffer[NUM_OF_CHANNELS];
	float * m_poutBuffer[NUM_OF_CHANNELS];
	void processSubComponent();
public:
	Component();
	~Component();

	void init();
	void process();
	void reset();

	void setBuffers(float ** inBuffer, float ** outBuffer);
	void setInputBuffer(float ** inBuffer);
	void setOutputBuffer(float ** outBuffer);
};