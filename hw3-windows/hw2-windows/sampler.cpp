#include "sampler.h"

Sampler::Sampler(int width, int height) : width(width), height(height), samplesPerPixel(1) {
	currentSample = 0;
	nSamples = width * height;
}
Sampler::Sampler(int width, int height, int samplesPerPixel) : width(width), height(height), samplesPerPixel(samplesPerPixel) {
	currentSample = 0;
	nSamples = width * height * samplesPerPixel;
}

bool Sampler::getSample(Sample* sample) {
	sample->x = currentSample % width;
	sample->y = currentSample / width;
	currentSample++;
	if (currentSample == nSamples) {
		return false;
	}
	else
		return true;
}
