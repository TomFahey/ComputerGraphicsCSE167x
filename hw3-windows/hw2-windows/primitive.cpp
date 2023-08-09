#include "primitive.h"

Primitive::Primitive() : worldBound(Bounds(vec3(maxNum), vec3(minNum))) {}

Primitive::~Primitive() {}

//bool Primitive::Intersect(Ray& ray, Interaction* in) { return false; }
//bool Primitive::IntersectP(Ray& ray) { return false; }
//void Primitive::getBRDF(LocalGeo& local, BRDF* brdf) {}

GeometricPrimitive::GeometricPrimitive(const std::shared_ptr<Shape> &shape,
	const std::shared_ptr<Material> &mat)
	: Primitive(), shape(shape), material(mat) {
	worldBound = shape->WorldBound();
};

bool GeometricPrimitive::Intersect(Ray& ray, SurfaceInteraction* in) {
	float tHit;
	bool doesHit = shape->Intersect(ray, &tHit, in);
	if (!doesHit) return false;
	ray.tMax = tHit;
	in->primitive = this;
	return true;
}

bool GeometricPrimitive::IntersectP(Ray& ray) {
	if (ray.tMax < maxNum) {
		float tHit;
		bool doesHit = shape->Intersect(ray, &tHit, nullptr);
		bool inRange = tHit <= ray.tMax;
		return (doesHit && inRange);
	}
	else {
		bool doesHit = shape->IntersectP(ray);
		return doesHit;
	}
}

Bounds GeometricPrimitive::WorldBound() {
	return shape->WorldBound();
}

Material *GeometricPrimitive::GetMaterial() {
	return material.get();
}

AggregatePrimitive::AggregatePrimitive() : Primitive()
{
}


bool AggregatePrimitive::Intersect(Ray& ray, SurfaceInteraction* in) {
	if (!worldBound.Intersect(ray)) return false;
	bool hitSomething = false;
	for (int i = 0; i < primitives.size(); i++) {
		float* tHit;
		bool doesHit = primitives[i]->IntersectP(ray);
		if (doesHit) {
			bool hitThis = primitives[i]->Intersect(ray, in);
			hitSomething = hitSomething || hitThis;
		}
	}
	if (hitSomething) return true;
	return false;
}
	
bool AggregatePrimitive::IntersectP(Ray& ray) {
	if (!worldBound.Intersect(ray)) return false;
	for (int i = 0; i < primitives.size(); i++) {
		bool doesHit = primitives[i]->IntersectP(ray);
		if (doesHit) return true;
	}
	return false;
}

Bounds AggregatePrimitive::WorldBound() {
	return worldBound;
}

Material* AggregatePrimitive::GetMaterial() {
	return nullptr;
}
