#pragma once

#include "variables.h"

struct Sample {
	int x;
	int y;
};

class Sampler {
public:
	Sampler(int width, int height);
	Sampler(int width, int height, int samplesPerPixel);
	bool getSample(Sample* sample);

private:
	int width, height, samplesPerPixel, currentSample, nSamples;
	std::vector<std::vector<Sample>> sampleArray;
};
