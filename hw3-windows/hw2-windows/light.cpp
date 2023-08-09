#include "light.h"

Light::Light(vec3 color) : color(color) {};

pointLight::pointLight(vec3 position, vec3 color) : Light(color), position(position) {};

void pointLight::generateLightRay(LocalGeo& local, Ray* lRay, vec3* lColor) {
	vec3 ldir = glm::normalize(this->position - local.point);
	lRay->point = local.point + 0.001f * ldir;
	lRay->dir = ldir;
	lRay->tMax = glm::length(this->position - local.point);
	*lColor = this->color;
}

directionalLight::directionalLight(vec3 direction, vec3 color) : Light(color), direction(glm::normalize(direction)) {};

void directionalLight::generateLightRay(LocalGeo& local, Ray* lRay, vec3* lColor) {
	lRay->point = local.point - 0.001f * direction;
	lRay->dir = -direction;
	lRay->tMax = maxNum;
	*lColor = this->color;
}
