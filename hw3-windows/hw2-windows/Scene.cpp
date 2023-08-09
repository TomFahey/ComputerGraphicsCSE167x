#include "Scene.h"

Scene::Scene() : sceneFilm(Film(640, 480, "scene")), sceneSampler(640, 480, 1),
				sceneCamera(Camera(640, 480, 45, vec3(0, 0, -4), vec3(0, 0, 0), vec3(0, 1, 0))),
				ambientLight(0.2), shininess(20) {}


Scene::Scene(int w, int h, float fovy) : sceneFilm(Film(w, h, "scene")), sceneSampler(w, h, 1),
				sceneCamera(Camera(w, h, fovy, vec3(0, 0, -4), vec3(0, 0, 0), vec3(0, 1, 0))),
				ambientLight(0.2), shininess(20) {}
				

Scene::Scene(Camera inputCamera, Film inputFilm) : 
				sceneFilm(inputFilm), sceneSampler(inputFilm.width, inputFilm.height, 1),
				sceneCamera(inputCamera), ambientLight(0.2), shininess(20) {}

Scene::Scene(Camera inputCamera, 
	Film inputFilm, AggregatePrimitive scenePrimitive) : 
		sceneFilm(inputFilm), sceneSampler(inputFilm.width, inputFilm.height, 1), sceneCamera(inputCamera), 
		scenePrimitive(scenePrimitive), ambientLight(0.2), shininess(20) {}
			 
Scene::Scene(Camera inputCamera, Film inputFilm, AggregatePrimitive scenePrimitive, 
				float ambientLight, float shininess) :
		sceneFilm(inputFilm), sceneSampler(inputFilm.width, inputFilm.height, 1), 
		sceneCamera(inputCamera), scenePrimitive(scenePrimitive), 
		ambientLight(ambientLight), shininess(shininess) {}
		
			 
Scene::Scene(Camera inputCamera, Film inputFilm, AggregatePrimitive scenePrimitive,
	std::vector<Light> sceneLights, float ambientLight, float shininess) :
	sceneFilm(inputFilm), sceneSampler(inputFilm.width, inputFilm.height, 1),
	sceneCamera(inputCamera), scenePrimitive(scenePrimitive), sceneLights(sceneLights),
	ambientLight(ambientLight), shininess(shininess) {}
		
			 

void Scene::render() {
	Sample sample;
	std::shared_ptr<AggregatePrimitive> pscenePrimitive = std::make_shared<AggregatePrimitive>(scenePrimitive);
	std::shared_ptr<std::vector<Light>> psceneLights = std::make_shared<std::vector<Light>>(sceneLights);
	Raytracer raytracer = Raytracer(3, pscenePrimitive, psceneLights, ambientLight, shininess);
	int noperations = sceneFilm.width * sceneFilm.height;
	int npercent = noperations / 100;
	int counter = 1;
	while (sceneSampler.getSample(&sample)) {
		if (sample.x == 165 && sample.y==148) { //
			std::cout << "Sample is met" << std::endl;
		}
		if (!((sample.x + sample.y*sceneFilm.width)%npercent)) {
			printf("Progress: %d%\n", counter);
			counter = counter >= 100 ? counter : ++counter;
		}
		Ray ray = Ray(sceneCamera.eye, vec3(0));
		sceneCamera.generateRay(sample, &ray);
		Color col = Color(0);
		raytracer.Trace(ray, 0, &col);
		sceneFilm.commit(sample, col);
	}
	sceneFilm.saveScreenshot();
}
