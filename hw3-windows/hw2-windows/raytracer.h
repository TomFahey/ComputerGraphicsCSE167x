#pragma once

#include "light.h"
#include "interaction.h"
#include "primitive.h"


class Raytracer
{
public:
	Raytracer(int maxDepth, std::shared_ptr<AggregatePrimitive> scenePrimitive, 
				std::shared_ptr<std::vector<Light>> sceneLights, 
				float ambientLight, float shininess);
	void Trace(Ray& ray, int depth, Color* color);
	Color Shading(const LocalGeo& local, const BRDF& brdf, const Ray& ray, 
				const Ray& lray, const Color& lcolor, float shininess);
private:
	const std::shared_ptr<AggregatePrimitive> primitive;
	const std::shared_ptr<std::vector<Light>> lights;
	int maxDepth;
	float ambientLight;
	float shininess;
};

