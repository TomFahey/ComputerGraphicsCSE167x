#pragma once

#include "sampler.h"
#include "material.h"
#include <FreeImage.h>
#include <string>
#include <iostream>

class Film
{
public:
	Film(int width, int height, std::string fname);
	void commit(Sample& sample, Color col);
	void saveScreenshot();
	int width, height;
private:
	std::string fname;
	BYTE* pixels;

};

