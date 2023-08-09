#pragma once

#include "variables.h"
#include "geometry.h"

class Primitive;
class GeometricPrimitive;

class Interaction {
public:
	Interaction() : localGeo(LocalGeo(vec3(0), vec3(0))), pError(vec3(0)) {}
	Interaction(vec3 point, vec3 normal, vec3 pError) : localGeo(LocalGeo(point, normal)), pError(pError) {}
	LocalGeo localGeo;
	vec3 pError;
};

class SurfaceInteraction : public Interaction {
public:
	SurfaceInteraction() : Interaction() {}
	SurfaceInteraction(vec3 point, vec3 normal, vec3 pointError);
	Primitive *primitive = nullptr;
};
