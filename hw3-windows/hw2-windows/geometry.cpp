#include "geometry.h"

Ray::Ray() : point(vec3(0)), dir(vec3(0)), tMin(0), tMax(maxNum) {};

Ray::Ray(const vec3 o, const vec3 d) : point(o), dir(glm::normalize(d)), tMin(0), tMax(maxNum) {};

vec3 Ray::operator()(float t) const {
	return point + t * dir;
}

Bounds::Bounds() {
	pMin = vec3(minNum);
	pMax = vec3(maxNum);
}

Bounds::Bounds(vec3 p) : pMin(p), pMax(p) {}

Bounds::Bounds(vec3 p0, vec3 p1) : pMin(p0), pMax(p1) {}

Bounds::Bounds(vec4 p) : pMin(p), pMax(p) {}

Bounds::Bounds(vec4 p0, vec4 p1) : pMin(vec3(p0)), pMax(vec3(p1)) {}

vec3 Bounds::operator[](int index) const {
	assert(index == 0 || index == 1);
	return (index == 0) ? pMin : pMax;
}

Bounds Bounds::operator&&(Bounds rBound) {
	pMin = glm::min(pMin, rBound.pMin);
	pMax = glm::max(pMax, rBound.pMax);
	return Bounds(pMin, pMax);
}

Bounds Bounds::operator+(vec3 v) {
	return Bounds(pMin+v, pMax+v);
}

vec3 Bounds::Vertex(int index) const {
	return vec3((*this)[index & 1].x,
		(*this)[(index & 2) ? 1 : 0].y,
		(*this)[(index & 4) ? 1 : 0].z);
}

vec3 Bounds::Diagonal() const {
	return pMax - pMin;
}

float Bounds::Volume() const {
	vec3 diag = (*this).Diagonal();
	return diag.x * diag.y, diag.z;
}

bool Bounds::Intersect(const Ray& ray, float* t0Hit, float* t1Hit) const {
	float t0 = ray.tMin, t1 = ray.tMax;
	float invRayDir, tNear, tFar;
	for (int i = 0; i < 3; i++) {
		invRayDir = 1 / ray.dir[i];
		tNear = (pMin[i] - ray.point[i]) * invRayDir;
		tFar = (pMax[i] - ray.point[i]) * invRayDir;
		if (tNear > tFar) std::swap(tNear, tFar);
		t0 = tNear > t0 ? tNear : t0;
		t1 = tFar < t1 ? tFar : t1;
		if (t0 > t1) return false;
	}
	if (t0Hit) *t0Hit = t0;
	if (t1Hit) *t1Hit = t1;
	return true;
}


