#pragma once
class FilterDesign
{
public:
	static void designLPHPBQFilter(float* b, float* a, float normalizedCutOff, bool highpass);
	//static void designParametric(float* b, float* a, float gain, float normalizedCentre, Q,);

private:
	FilterDesign();
	~FilterDesign();
};

