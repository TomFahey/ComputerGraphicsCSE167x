#pragma once

#include "Transform.h"
#include "geometry.h"
#include "interaction.h"

class Shape {
public:

	Shape();
	Shape(Transform O2W, Transform W2O, bool invertSurface);
	Shape(Transform O2W);
	virtual ~Shape();
	virtual Bounds ObjectBound() = 0;
	virtual Bounds WorldBound();
	virtual bool Intersect(const Ray& ray, float* tHit, SurfaceInteraction* interaction) = 0;
	virtual bool IntersectP(const Ray& ray) = 0;
	
	Transform Obj2Wrld, Wrld2Obj;
	bool invertSurface;
};

class Sphere : public Shape {
public:

	Sphere();
	Sphere(float radius, Transform Obj2Wrld);
	Sphere(float radius, Transform Obj2Wrld, Transform Wrld2Obj);
	Bounds ObjectBound();
	Bounds WorldBound();
	virtual bool Intersect(const Ray& ray, float* tHit, SurfaceInteraction *surface);
	virtual bool IntersectP(const Ray& ray);
	vec3 getNormal(vec3 point);

	const float radius;

};

class Ellipsoid : public Sphere {
public:

	Ellipsoid();
	Ellipsoid(float radius, Transform Obj2Wrld);
	Ellipsoid(float radius, Transform Obj2Wrld, Transform Wrld2Obj);
	bool Intersect(const Ray& ray, float* tHit, SurfaceInteraction *surface);
	bool IntersectP(const Ray& ray);
	vec3 getNormal(vec3 point);
};

class Triangle : public Shape {
public:
	Triangle();
	Triangle(vec3 v1, vec3 v2, vec3 v3, Transform Obj2Wrld);
	Triangle(vec3 v1, vec3 v2, vec3 v3, Transform Obj2Wrld, Transform Wrld2Obj);
	Bounds ObjectBound();
	Bounds WorldBound();
	bool Intersect(const Ray& ray, float* tHit, SurfaceInteraction *surface);
	bool IntersectP(const Ray& ray);
	vec3 getNormal();
private:
	const vec3 v1, v2, v3;

};

