#pragma once

#include <memory>
#include "shape.h"
#include "material.h"

class Primitive {
public:
	Primitive();
	virtual ~Primitive();
	virtual bool Intersect(Ray& ray, SurfaceInteraction* in) = 0;
	virtual bool IntersectP(Ray& ray) = 0;
	virtual Bounds WorldBound() = 0;
	virtual Material *GetMaterial() = 0;
protected:
	Bounds worldBound;
};

class GeometricPrimitive : public Primitive {
public:
	GeometricPrimitive(const std::shared_ptr<Shape> &shape, const std::shared_ptr<Material> &mat);
	bool Intersect(Ray& ray, SurfaceInteraction* in);
	bool IntersectP(Ray& ray);
	Bounds WorldBound();
	Material *GetMaterial();

private:	
	std::shared_ptr<Shape> shape;
	std::shared_ptr<Material> material;
};

class AggregatePrimitive : public Primitive {
public:
	AggregatePrimitive();
	template<typename T>
	void addPrimitive(T* primitive) {
		std::shared_ptr<T> element = std::make_shared<T>(*primitive);
		primitives.push_back(element);
		worldBound = worldBound && element->WorldBound();
	};
	bool Intersect(Ray& ray, SurfaceInteraction* in);
	bool IntersectP(Ray& ray);
	Bounds WorldBound();
	Material *GetMaterial();
private:
	std::vector<std::shared_ptr<Primitive>> primitives;
};