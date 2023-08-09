#pragma once

#include "sampler.h"
#include "geometry.h"
#include "Transform.h"

class Camera
{
public:
	Camera();
	Camera(int width, int height, float fovy, vec3 eye, vec3 center, vec3 up);
	void generateRay(Sample& sample, Ray* ray);
	vec3 eye, up, center, w, u, v;

private:
	int width, height;
	float fovy, fovx;
};

