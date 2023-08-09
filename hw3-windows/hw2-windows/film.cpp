#include "film.h"

Film::Film(int width, int height, std::string fname) : width(width), height(height), fname(fname) {
	pixels = new BYTE[3 * width * height];
}

void Film::commit(Sample& sample, Color col) {
	int pixelNumber = 3 * sample.x + 3 * sample.y * width ;
	pixels[pixelNumber] = std::min(int(255.f * col.r), 255);
	pixels[pixelNumber + 1] = std::min(int(255.f * col.g), 255);
	pixels[pixelNumber + 2] = std::min(int(255.f * col.b), 255);
}

void Film::saveScreenshot() {
	FreeImage_Initialise();
	FIBITMAP* img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
	std::cout << "Saving screenshot: " << fname.c_str() << std::endl;
	FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
	FreeImage_DeInitialise();
}
