#include <deque>
#include <iostream>
#include <stack>

#include "camera.h"
#include "film.h"
#include "raytracer.h"
#include "sampler.h"
#include "primitive.h"


#pragma once
class Scene {
public:
	Scene();
	Scene(int width, int height, float fovy);
	Scene(Camera inputCamera, Film inputFilm);
	Scene(Camera inputCamera, Film inputFilm,
		AggregatePrimitive scenePrimitive);
	Scene(Camera inputCamera, Film inputFilm,
		AggregatePrimitive scenePrimitive, float ambientLight, float shininess);
	Scene(Camera inputCamera, Film inputFilm, AggregatePrimitive scenePrimitive,
		std::vector<Light> sceneLights, float ambientLight, float shininess);

	void render();
private:
	Film sceneFilm;
	Sampler sceneSampler;
	Camera sceneCamera;
	AggregatePrimitive scenePrimitive;
	std::vector<Light> sceneLights;
	float ambientLight;
	float shininess;
	friend class Raytracer;

};

