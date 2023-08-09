#pragma once

#include <assert.h>
#include "variables.h"
#include <algorithm>


class Ray {
public:
	Ray();
	Ray(const vec3 o, const vec3 d);
	vec3 operator()(float t) const;
	
	glm::vec3 point, dir;
	float tMin, tMax;
};



class Bounds {
public:
	Bounds();
	Bounds(vec3 p);
	Bounds(vec3 p0, vec3 p1);
	Bounds(vec4 p);
	Bounds(vec4 p0, vec4 p1);
	vec3 operator[](int index) const;
	Bounds operator&&(Bounds rBound);
	Bounds operator+(vec3 v);
	vec3 Vertex(int index) const;
	vec3 Diagonal() const;
	float Volume() const;
	bool Intersect(const Ray& ray, float* t0Hit = nullptr, float* t1Hit = nullptr) const;

	vec3 pMin, pMax;
};

class LocalGeo {
public:
	LocalGeo(vec3 p, vec3 n) : point(p), normal(n) {}
	vec3 point;
	vec3 normal;
};
