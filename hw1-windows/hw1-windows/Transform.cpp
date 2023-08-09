// Transform.cpp: implementation of the Transform class.

#include "Transform.h"
#include <iostream>
#include <string>
#include <sstream>
#include "glm/gtx/string_cast.hpp"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
	float radians = glm::radians(degrees);
	glm::mat3 aDotA = mat3(axis.x * axis, axis.y * axis, axis.z * axis);
	glm::mat3 aStar = mat3(vec3(0, axis.z, -axis.y), vec3(-axis.z, 0, axis.x), vec3(axis.y, -axis.x, 0));
	glm::mat3 R = mat3(1) * glm::cos(radians) + aDotA * (1 - glm::cos(radians)) + aStar * glm::sin(radians);
	//R[0] = glm::normalize(R[0]);
	//R[1] = glm::normalize(R[1]);
	//R[2] = glm::normalize(R[2]);
	return R;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	mat3 R = rotate(degrees, up);
	vec3 result = R * eye;
	eye = result;
	float length = glm::length(result);
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 rotAxis = glm::normalize(glm::cross(up, eye));
	mat3 R = rotate(-degrees, rotAxis);
	vec3 result = R * eye;
	eye = result;
	up = glm::normalize(glm::cross(eye, rotAxis));
	float length = glm::length(result);
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, eye));
	vec3 v = glm::normalize(glm::cross(w, u));
	mat4 result, rotate, translate;
	rotate[0] = vec4(u, 0);
	rotate[1] = vec4(v, 0);
	rotate[2] = vec4(w, 0);
	rotate[3] = vec4(0, 0, 0, 1);
	rotate = glm::transpose(rotate);
	translate[0] = vec4(1, 0, 0, -eye.x);
	translate[1] = vec4(0, 1, 0, -eye.y);
	translate[2] = vec4(0, 0, 1, -eye.z);
	translate[3] = vec4(0, 0, 0, 1);
	translate = glm::transpose(translate);
	result = rotate * translate;
	return result;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}