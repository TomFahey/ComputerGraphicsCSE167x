#pragma once

#include "geometry.h"

class Light {
public:
	Light(vec3 color);
	virtual void generateLightRay(LocalGeo& local, Ray* lray, vec3* lColor) = 0;
		
	vec3 color;
};

class pointLight : public Light {
public:
	pointLight(vec3 position, vec3 color);
	void generateLightRay(LocalGeo& local, Ray *lray, vec3 *lColor);

	vec3 position;
};

class directionalLight : public Light {
public:
	directionalLight(vec3 direction, vec3 color);
	void generateLightRay(LocalGeo& local, Ray* lray, vec3* lColor);

	vec3 direction;
};
