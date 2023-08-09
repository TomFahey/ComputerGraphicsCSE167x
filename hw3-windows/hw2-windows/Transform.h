// Transform header file to define the interface. 
// The class is all static for simplicity
// You need to implement left, up and lookAt
// Rotate is a helper function

// Include the helper glm library, including matrix transform extensions

#pragma once

#include <valarray>
#include <algorithm>
#include <stack>
#include <vector>
#include "geometry.h"

class Transform {
public:
	Transform();
	Transform(const float mat[4][4]);
	Transform(const mat4 &mat);
	Transform(const mat4 &mat, const mat4 &matInv);
	static bool isIdentity(mat4 M);
	bool isIdentity();
	static mat4 Invert(const mat4 mat);
	static mat3 InvertMat3(const mat3 mat);
	static Transform Translate(const vec3 &T);
	static Transform Scale(const vec3 &T);
	static Transform Rotate(const float degrees, const vec3 &axis);
	static Transform LookAt(const vec3 &pos, const vec3 &look, const vec3 &up);
	Bounds operator()(const Bounds& b) const;
	Bounds operator()(Bounds b);
	Ray operator()(const Ray& ray);
	vec3 Transform::operator()(const vec3& v);
	
	const mat4 m, mInv;
};
