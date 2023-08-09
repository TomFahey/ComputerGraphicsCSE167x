#include "raytracer.h"

Raytracer::Raytracer(int maxDepth, std::shared_ptr<AggregatePrimitive> scenePrimitive,
	std::shared_ptr<std::vector<Light>> sceneLights, float ambientLight, float shininess) :
	maxDepth(maxDepth), primitive(scenePrimitive), lights(sceneLights), 
	ambientLight(ambientLight), shininess(shininess) {};

void Raytracer::Trace(Ray& ray, int depth, Color* color) {
	if (depth >= maxDepth) {
		*color = Color(0);
		return;
	}
	SurfaceInteraction* in = new SurfaceInteraction();
	if (!this->primitive->Intersect(ray, in)) {
		*color = vec3(0);
		return;
	}
	Ray lray = Ray();
	vec3 lcolor = vec3(0);
	BRDF& rBRDF = in->primitive->GetMaterial()->materialBRDF;
	auto iterLight = lights.get();
	for (Light light : *iterLight) {
		light.generateLightRay(in->localGeo, &lray, &lcolor);
		bool shadowed = this->primitive->IntersectP(lray); // Can't use the same variable @in surely?
		//bool lray_blocked = shadowed && (lray.tMax > glm::distance(in->localGeo.point, light.position));
		if (!shadowed) {
			*color += this->Shading(in->localGeo, rBRDF, ray, lray, lcolor, shininess);
		}
	}
	vec3 reflectDir = ray.dir - 2 * glm::dot(ray.dir, in->localGeo.normal) * in->localGeo.normal;
	Ray rray = Ray(in->localGeo.point+0.001f*reflectDir, reflectDir);
	Color rcolor = Color(0);
	Trace(rray, ++depth, &rcolor);
	*color += rBRDF.reflective * rcolor;
	*color += rBRDF.ambient *ambientLight;
}


Color Raytracer::Shading(const LocalGeo& local, const BRDF& brdf, const Ray& ray, 
						const Ray& lray, const Color& lcolor, float shininess) {
	float d = lray.tMax;
	float c0 = 1;
	float c1 = 0.0;
	float c2 = 0.0;
	vec3 h = glm::normalize(lray.dir - ray.dir);
	Color L = lcolor / (c0 + c1 * d + c2 * d * d);
	return  L * (brdf.diffuse * std::max(glm::dot(lray.dir, local.normal), 0.f)
		+ brdf.specular * std::pow(std::max(glm::dot(h, local.normal), 0.f), shininess));
}
