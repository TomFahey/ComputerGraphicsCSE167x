#include "camera.h"

Camera::Camera() : width(640), height(480), fovy(65), eye(vec3(0, 4, -4)), center(vec3(0)), up(vec3(0, 1, 0)) {
	w = glm::normalize(eye - center);
	u = glm::normalize(glm::cross(up, w));
	v = glm::cross(w, u);
	fovx = (180.f / pi) * 2 * glm::atan(glm::tan(glm::radians(fovy / 2)) * (width / height));
}
Camera::Camera(int width, int height, float fovy, vec3 eye, vec3 center, vec3 up) : 
	width(width), height(height), fovy(fovy), eye(eye), center(center), up(up) {
	w = glm::normalize(eye - center);
	u = glm::normalize(glm::cross(up, w));
	v = glm::cross(w, u);
	fovx = (180.f / pi) * 2 * glm::atan(glm::tan(glm::radians(fovy / 2)) * (float(width) / float(height)));
};
void Camera::generateRay(Sample& sample, Ray* ray) {
	vec3 displacement;
	float alpha, beta;
	alpha = glm::tan(fovx / 2) * (sample.x - (width / 2)) / (width / 2);
	beta = glm::tan(fovy / 2) * ((height / 2)- sample.y) / (height / 2);
	displacement = ((alpha * u) + (beta * v)) - w;
	ray->dir = glm::normalize(displacement);
}
