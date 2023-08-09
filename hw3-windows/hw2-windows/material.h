#pragma once

#include "variables.h"
#include "geometry.h"

class Color {
public:
	Color(float r, float g, float b) : r(r), g(g), b(b) {}
	Color(vec3 rgb) : r(rgb.x), g(rgb.y), b(rgb.z) {}
	Color(float gs) : r(gs), g(gs), b(gs) {}

	Color operator+(Color rhs) {
		return Color(r + rhs.r, g + rhs.g, b + rhs.g);
	}
	
	Color operator-(Color rhs) {
		return Color(r - rhs.r, g - rhs.g, b - rhs.g);
	}

	Color& operator+=(Color& rhs) {
		this->r += rhs.r;
		this->g += rhs.g;
		this->b += rhs.b;
		return *this;
	}
	
	Color& operator+=(const Color& rhs) {
		this->r += rhs.r;
		this->g += rhs.g;
		this->b += rhs.b;
		return *this;
	}
	
	Color& operator-=(Color& rhs) {
		this->r -= rhs.r;
		this->g -= rhs.g;
		this->b -= rhs.b;
		return *this;
	}

	Color operator*(Color rhs) {
		return Color(r * rhs.r, g * rhs.g, b * rhs.b);
	}

	Color operator/(Color rhs) {
		return Color(r / rhs.r, g / rhs.g, b / rhs.b);
	}


	Color operator*(float rhs) {
		return Color(r * rhs, g * rhs, b * rhs);
	}

	Color operator/(float rhs) {
		return Color(r / rhs, g / rhs, b / rhs);
	}

	Color operator*(float rhs) const {
		return Color(r * rhs, g * rhs, b * rhs);
	}

	Color operator/(float rhs) const {
		return Color(r / rhs, g / rhs, b / rhs);
	}

	float r, g, b;
};

struct BRDF {
	Color diffuse;
	Color specular;
	Color ambient;
	Color reflective;
};

class Material {
public:
	Material(BRDF* brdf);
	BRDF materialBRDF;
};
