#pragma once
class FilterDesign
{
public:
	designLPHPBQFilter(float* b, float* a, float gain, float normalizedCutOff, float slope, bool highpass);

private:
	FilterDesign();
	~FilterDesign();
};

